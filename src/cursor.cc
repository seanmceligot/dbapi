#include "greendb/cursor.hh"
#include "greendb/debug.hh"
#include <errno.h>

#if !defined(DB_BUFFER_SMALL)
#define DB_BUFFER_SMALL ENOMEM
#endif

Cursor::Cursor (Dbc* dbc):_dbc (dbc) { };
Cursor::~Cursor  () { 
	close();
}

int
Cursor::last (Datum & key, Datum & val)
{
  return _next (key, val, DB_LAST);
}

int
Cursor::first (Datum & key, Datum & val)
{
  return _next (key, val, DB_FIRST);
}

int
Cursor::find (Datum & key, Datum & val)
{
  return _next (key, val, DB_SET);
}

int
Cursor::next (Datum & key, Datum & val)
{
  return _next (key, val, DB_NEXT);
}
int
Cursor::next_dup (Datum & key, Datum & val)
{
  return _next (key, val, DB_NEXT_DUP);
}
void Cursor::close () {
	if (_dbc) {
  	_dbc->close ();
		_dbc = NULL;
	};
};

int
Cursor::_next (Datum & key, Datum & val, u_int32_t flags)
{
  if (flags != DB_NEXT) {
					key.set_db_flags (DB_DBT_USERMEM);
					if (val.get_data () == NULL) {
						val.set_db_flags (DB_DBT_MALLOC);
					} else {
						val.set_db_flags (DB_DBT_USERMEM);
					}
	}
  int dberr;
retry:
  // we loop 3 times if key and value both need allocating; more if data changes between loops
  try {
    dberr = _dbc->get (&key, &val, flags);
  } catch (DbMemoryException & ex) {
    	//g_message( "DbMemoryException" );
			key.atleast_size();
      val.atleast_size();
      goto retry;
  } catch (DbException & ex) {
    if (ex.get_errno () == DB_BUFFER_SMALL) {
    	//g_message( "DB_BUFFER_SMALL reallocating: " );
			key.atleast_size();
      val.atleast_size();
      goto retry;
    } else {
     g_message( "Unhandled DbException : %s " , ex.what () );
      throw;
    }
  }
	//g_message("%d dbc->get %s ",dberr, key.str(),val.str());
	if (dberr && (dberr != DB_NOTFOUND)) {
		g_message( "unknown error %d" , dberr );
	}
  return dberr;
}
