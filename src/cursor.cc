#include "greendb/cursor.hh"
#include "greendb/debug.hh"
#include <errno.h>

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
void Cursor::close () {
	if (_dbc) {
  	_dbc->close ();
		_dbc = NULL;
	};
};

int
Cursor::_next (Datum & key, Datum & val, u_int32_t flags)
{
  key.set_db_flags (DB_DBT_USERMEM);

  if (val.get_data () == NULL) {
    val.set_db_flags (DB_DBT_MALLOC);
  } else {
    val.set_db_flags (DB_DBT_USERMEM);
  }
	debug<<"cursor get "<<key<<std::endl;
  int dberr;
retry:
  // we loop 3 times if key and value both need allocating; more if data changes between loops
  try {
    dberr = _dbc->get (&key, &val, flags);
  } catch (DbException & ex) {
    if (ex.get_errno () == ENOMEM) {
    	debug << "ENOMEM reallocating: " << std::endl;
			key.atleast_size();
      val.atleast_size();
      goto retry;
    } else {
      throw;
    }
  }
  if (dberr) {
    debug << "returned: " << dberr <<std::endl;
    return dberr;
  }
  return 0;
}
