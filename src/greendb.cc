#include "greendb/greendb.hh"
#include "greendb/debug.hh"
#include <errno.h>
#include <ctype.h>
#include <iostream>
//#include <exception>

/*
GreenDb::GreenDb (DbEnv * env, const char *dbfile):Db (env, 0), _dbfile (dbfile),
    _name (NULL), _txn (NULL) {
  };
	*/
GreenDb::GreenDb (GreenEnv * env, const char *dbfile, const char *name):Db ((DbEnv*)env, 0),
    _name (name), _dbfile (dbfile), _txn (NULL) {
		debug<<"new GreenDb: "<<_name<<":"<<_dbfile<<std::endl;
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
  int flags = 0;
  if (create) {
    flags=DB_CREATE;
  }
	open(DB_UNKNOWN,flags,0644);
}
void
GreenDb::open_queue(bool create) {
  int flags = 0;
  if (create) {
    flags=DB_CREATE;
  }
	open(DB_QUEUE,flags,0644);
}
void
GreenDb::open_recno(bool create) {
  int flags = 0;
  if (create) {
    flags=DB_CREATE;
  }
	open(DB_RECNO,flags,0644);
}
void
GreenDb::open_hash(bool create) {
  int flags = 0;
  if (create) {
    flags=DB_CREATE;
  }
	open(DB_HASH,flags,0644);
}
void
GreenDb::open_btree (bool create) {
  int flags = 0;
  if (create) {
    flags=DB_CREATE;
  }
	open(DB_BTREE,flags,0644);
}
void
GreenDb::open (int type, u_int32_t flags, int mode)
{
  u_int32_t lflags = flags;
  DBTYPE ltype = (DBTYPE)type;
	if (type == 0) {
			ltype =DB_BTREE;
	}
	if (flags == 0) {
			lflags = DB_CREATE;
	}
	if (mode == 0) {
			mode = 0644;
	}
  debug << "opening " << _dbfile << ":" << _name << std::endl;
	try {	
    DbTxn* txn = NULL;
#if DB_VERSION_MAJOR > 3
  	Db::open (txn, _dbfile.c_str(), _name.c_str(), ltype, lflags, mode);
#else
  	Db::open (_dbfile.c_str(), _name.c_str(), ltype, lflags, mode);
#endif
  } catch (DbException & ex) {
    error << "DbException caught: " << ex.what () << std::endl;
		throw;
	}
}

void
  GreenDb::put (Datum & key, Datum & val)
{
  key.set_db_flags (0);
  val.set_db_flags (0);
  int dberr = Db::put (_txn, &key, &val, 0);
  if (dberr) {
		debug <<"dberr: ";
		err(dberr, NULL);
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
		debug<<_name<<" get key: "<<key<<std::endl;
    dberr = Db::get (_txn, &key, &val, 0);
  } catch (DbException & ex) {
    if (ex.get_errno () == ENOMEM) {
    	debug << "ENOMEM reallocating: " << std::endl;
			key.atleast_size();
      val.atleast_size();
      goto retry;
    } else {
    	error << "Exception caught: " << ex.what () << std::endl;
      throw;
    }
  }
  if (dberr) {
		debug <<"dberr: ";
		err(dberr, NULL);
    return dberr;
  }
  return 0;
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
