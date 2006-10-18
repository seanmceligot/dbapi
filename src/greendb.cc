#include "greendb/greendb.hh"
#include "greendb/debug.hh"
#include <errno.h>
#include <ctype.h>
#include <iostream>

#if !defined(DB_BUFFER_SMALL)
#define DB_BUFFER_SMALL ENOMEM
#endif
//#include <exception>

/*
GreenDb::GreenDb (DbEnv * env, const char *dbfile):Db (env, 0), _dbfile (dbfile),
    _name (NULL), _txn (NULL) {
  };
	*/
GreenDb::GreenDb (GreenEnv * env, const char *dbfile, const char *name):Db ((DbEnv*)env, 0),
    _name (name), _dbfile (dbfile), _txn (NULL) {
		//rDebug("new GreenDb: %s %s",_name.c_str(),_dbfile.c_str());
  };
GreenDb::~GreenDb () {
  };
  const char *GreenDb::dbfile () const {
    return _dbfile.c_str();
  };
  const char *GreenDb::name () const {
    return _name.c_str();
  };
  void GreenDb::close () {
    Db::close (0);
  };

void
GreenDb::open_unknown(bool create) {
  int open_flags = 0;
  if (create) {
    open_flags=DB_CREATE;
  }
	open(DB_UNKNOWN,0,open_flags,0644);
}
void
GreenDb::open_queue(bool create) {
  int open_flags = 0;
  if (create) {
    open_flags=DB_CREATE;
  }
	open(DB_QUEUE,0, open_flags,0644);
}
void
GreenDb::open_recno(bool create) {
  int open_flags = 0;
  if (create) {
    open_flags=DB_CREATE;
  }
	open(DB_RECNO,0, open_flags,0644);
}
void
GreenDb::open_hash(bool create) {
  int open_flags = 0;
  if (create) {
    open_flags=DB_CREATE;
  }
	open(DB_HASH,0, open_flags,0644);
}
void
GreenDb::open_btree (bool create, bool allow_dups) {
  u_int32_t open_flags = 0;
  if (create) {
    open_flags=DB_CREATE;
  }
	u_int32_t flags = 0;
  if (allow_dups) {
    flags=DB_DUP;
  }
	open(DB_BTREE,flags,open_flags,0644);
}
void
GreenDb::open (int type,u_int32_t flags, u_int32_t open_flags, int mode)
{
  u_int32_t l_open_flags = open_flags;
  DBTYPE ltype = (DBTYPE)type;
	if (type == 0) {
			ltype =DB_BTREE;
	}
	if (ltype == DB_BTREE) {
		Db::set_flags(flags);
	}
	if (open_flags == 0) {
			l_open_flags = DB_CREATE;
	}
	if (mode == 0) {
			mode = 0644;
	}
	int dberr = -1;
  //rDebug( "opening %s %s" , _dbfile.c_str() , _name.c_str() );
	try {	
    DbTxn* txn = NULL;
#if DB_VERSION_MAJOR > 3
  	dberr = Db::open (txn, _dbfile.c_str(), _name.c_str(), ltype, l_open_flags, mode);
#else
  	dberr = Db::open (_dbfile.c_str(), _name.c_str(), ltype, l_open_flags, mode);
#endif
  } catch (DbException & ex) {
    rDebug( "Unhandled DbException : %s " , ex.what () );
		throw;
	}
	if (dberr) {
		rDebug("Db::open dberr: %d", dberr);
	}
}

void
  GreenDb::put (Datum & key, Datum & val)
{
  key.set_db_flags (0);
  val.set_db_flags (0);
  int dberr = Db::put (_txn, &key, &val, 0);
  if (dberr) {
		rError("dberr: %s", strerror(dberr));
	}
  Db::sync (0);
}

Cursor *
GreenDb::cursor ()
{
  Dbc *dbc;
  Db::cursor (_txn, &dbc, 0);
  Cursor *cur = new Cursor (dbc);
  return cur;
}

int
  GreenDb::fetch (Datum & key, Datum & val )
{
  key.set_db_flags (DB_DBT_USERMEM);

  if (val.get_data () == NULL) {
    val.set_db_flags (DB_DBT_MALLOC);
  } else {
    val.set_db_flags (DB_DBT_USERMEM);
  }

  int dberr;
retry:
  // we loop 3 times if key and value both need allocating
  try {
    dberr = Db::get (_txn, &key, &val, 0);
  } catch (DbMemoryException & ex) {
    	//rDebug( "DbMemoryException: " );
			key.atleast_size();
      val.atleast_size();
      goto retry;
  } catch (DbException & ex) {
    if (ex.get_errno () == DB_BUFFER_SMALL) {
    	//rDebug( "DB_BUFFER_SMALL reallocating: " );
			key.atleast_size();
      val.atleast_size();
      goto retry;
    } else {
    	rDebug( "Unhandled DbException : %s " , ex.what () );
      throw;
    }
  }
	//rDebug("%d Db->get %s %s ",dberr, key.str(),val.str());
	if (dberr && (dberr != DB_NOTFOUND)) {
	  Db::err(dberr, "dberr: ");
  }
  return dberr;
}

std::ostream & operator << (std::ostream & os, const GreenDb & db)
{
  os << db.dbfile ();
  if (db.name ()) {
    os << ":" << db.name ();
  }
  return os;
}

std::ostream & operator << (std::ostream & os, const GreenDb * db)
{
  os << db->dbfile ();
  if (db->name ()) {
    os << ":" << db->name ();
  }
  return os;
}

/*bool sleepywrap_getrec(GreenDb* db, StaticDatum* key, StaticDatum* value) throw(GreenException) {
  int dberr;
  DBT* key = key->getdbt();
  DBT* value = value->getdbt();

  value->flags = DB_DBT_USERMEM;
  key->flags = DB_DBT_USERMEM;
  dberr = sw->db->get (sw->db, sw->txn, &key, &data, 0);
}*/
