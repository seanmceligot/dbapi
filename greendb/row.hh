#ifndef ROW_HH
#define ROW_HH

#include "greendb/datum.hh"
#include "greendb/greendb.hh"
#include "greendb/table.hh"
#include "greendb/memory.hh"

class Row {
	const size_t _size;
	Datum** _colDatum;
  Table *_table;
public:
  Row (Table * table, size_t size);
	virtual ~Row ();
	size_t size();
  void close ();
  Datum& getpk ();
  void set (int index, Datum & newDatum);
  bool set (const char *colname, Datum & newDatum);
	void from_string(int index, const char* s);
	void from_string(const char* colname, const char* s);
	char* to_string(int index);
	char* to_string(const char* colname);
	Datum * get_column (int idx);
  Datum *get_column (const char *colname);
	int get_col_no(const char* colname);
  Datum * get_existing_column (int index);
};
class CursorRow : public Row {
	Cursor* _cursor;
public:
	CursorRow(Table* table, size_t size, Cursor* cursor, Datum* pk);
	Cursor* get_cursor();
};

#endif
