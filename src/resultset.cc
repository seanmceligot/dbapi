#include "greendb/table.hh"
#include "greendb/row.hh"
#include "greendb/strdatum.hh"
#include "greendb/debug.hh"
#include "greendb/schema.hh"
#include "greendb/resultset.hh"
#include <string>

ResultSet::ResultSet (Table * table, CursorRow* row, Datum* fk, Datum* pk,size_t column_count): _table(table), _row(row),_fk(fk),_pk(pk),_column_count(column_count) {
} 

ResultSet::~ResultSet () {
	close();
}
void ResultSet::close() {
	if (_row) {
  	_row->close ();
		_row = NULL;
	}
}
CursorRow* ResultSet::row() {
	return _row;
}
bool ResultSet::has_row() {
	return _row != NULL;
}
bool ResultSet::next() {
	Cursor * cursor = _row->get_cursor();
	int dberr = cursor->next_dup(*_fk, *_pk);
	_row = NULL;
	if (dberr == 0 ) {
		_row = new CursorRow(_table, _column_count, cursor, _pk); 
		return true;
	} else {
		rError("next_dup %d", dberr);
		return false;
	}
}
