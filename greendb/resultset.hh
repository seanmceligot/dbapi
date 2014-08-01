
#ifndef RESULTSET_HH
#define RESULTSET_HH

#include "greendb/datum.hh"
#include "greendb/cursor.hh"

class ResultSet {
	Table *_table;
	CursorRow* _row;
	Datum *_fk;
	Datum *_pk;
	size_t _column_count;
public:
  ResultSet (Table * table, CursorRow* row, Datum* fk, Datum* pk, size_t column_count);
	~ResultSet ();
    void close ();
	CursorRow* row();
	bool next();
	bool has_row();
};

#endif
