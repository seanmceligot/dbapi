#ifndef __CURSOR_HH
#define __CURSOR_HH

#include <db_cxx.h>
#include "greendb/datum.hh"
#include "greendb/greendb.hh"

class Cursor {
  Dbc* _dbc;
  
	Cursor (Dbc* dbc);
  int _next (Datum & key, Datum & val, u_int32_t flags);

	friend class GreenDb;
public:
  ~Cursor ();
  int last (Datum & key, Datum & val);
  int first (Datum & key, Datum & val);
  int find (Datum & key, Datum & val);
  int next (Datum & key, Datum & val);
  int next_dup(Datum & key, Datum & val);
  void close ();
};

#endif
