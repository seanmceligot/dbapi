#include "greendb/row.hh"
#include "greendb/schema.hh"
#include "greendb/typemap.hh"
#include "greendb/debug.hh"
#include "greendb/datum.hh"
#include "greendb/strdatum.hh"
#include <assert.h>

Row::Row (Table * table, size_t size):_size (size), _table (table)  {
	g_message("new Row(%s,size=%d)", table->get_name(), size);
	_colDatum = new Datum*[size];
  //Schema* schema = table->get_schema();
	for (size_t i = 0; i < size;i++) {
		_colDatum[i] = NULL;
	}
}
Row::~Row () {
	close();
}
Datum& Row::getpk () {
 Datum* d= _colDatum[0];
 return *d;
}

size_t Row::size() {
	return _size;
}

void
Row::close ()
{
	g_message("Row.close");
	/*for (size_t i = 0; i < _size;i++) {
		free(_colDatum[i]);
	}
  delete[] _colDatum;*/
}

void
Row::set (int idx, Datum & newDatum)
{
  Datum *datum = _colDatum[idx];
  /*if (datum) {
    free (datum);
  }*/
  _colDatum[idx] = &newDatum;
}
int Row::get_col_no(const char* colname) {
		Schema* schema = _table->get_schema();
		assert (schema != NULL);
	return schema->get_col_no(colname);
}
bool Row::set_int (const char *colname, int value) {
	int idx = get_col_no(colname);
	Schema* schema = _table->get_schema();
	Datum* datum = schema->create_datum(idx);
	datum->set_int(value);
	set(idx, *datum);
}
bool Row::set_string (const char *colname, const char* value) {
	int idx = get_col_no(colname);
	Schema* schema = _table->get_schema();
	Datum* datum = schema->create_datum(idx);
	datum->set_string(value);
	set(idx, *datum);
}
bool
Row::set (const char *colname, Datum & newDatum)
{
	int idx = get_col_no(colname);
	if (idx >=0) {
			set(idx, newDatum);
		  return true;
	}
	return false;
}
Datum *
Row::get_column (int idx) {
	const char* colname = _table->get_schema()->get_name(idx);
	return get_column(colname);
}

Datum *
Row::get_column (const char *colname)
{
	int idx = get_col_no(colname);
	g_message("get_column[%s %d]", colname, idx);
	if (idx < 0) {
			return NULL;
	}
  Datum *val = get_existing_column(idx);
	if (val == NULL) {
		val = _table->get_schema()->create_datum(idx);
	}
  GreenDb *db = _table->get_database (colname);
	Datum* pk = _colDatum[0];
	g_message("pk %s", pk->to_string());
	if (pk != NULL) {
   	db->fetch (*pk, *val);
	}
	g_message("fetched colum %s", val->repr());
  return val;
}

Datum *
Row::get_existing_column (int idx) {
	Datum* col=_colDatum[idx];
	return col;
}
void Row::from_string(const char* colname, const char* s) {
	int idx = get_col_no(colname);
	from_string(idx,s);
}
void Row::from_string(int idx, const char* s) {
	Schema* schema = _table->get_schema();
	//const std::type_info* ti = schema->get_typeid(idx);
	Datum* datum = get_existing_column(idx);
	if (!datum) {
		datum = schema->create_datum(idx);
		set(idx, *datum);
	}
	datum->from_string(s);
	//datum->atleast(TypeMap::get_type_map()->from_string_size(ti, s));
	//TypeMap::get_type_map()->from_string(datum, s);
}
/**
 * caller must free
 * see Datum.to_string
 */
char* Row::to_string(int idx) {
	Datum* datum = get_column(idx);
	if (datum == NULL) {
    return NULL;
  }
	return datum->to_string();
}
/**
 * caller must free
 * see Datum.to_string
 */
char* Row::to_string(const char* colname) {
	Datum* datum = get_column(colname);
	if (datum == NULL) {
    return NULL;
  }
	return datum->to_string();
}
int Row::get_int (const char *colname) {
	Datum* datum = get_column(colname);
	if (datum == NULL) {
    return 0;
  }
	return datum->get_int();
}

const char* Row::get_string (const char *colname) {
	Datum* datum = get_column(colname);
	if (datum == NULL) {
    return NULL;
  }
	return datum->get_string();
}

CursorRow::CursorRow(Table* table, size_t size, Cursor* cursor, Datum* pk) :
	Row(table, size), _cursor(cursor) {
	g_message("CursorRow table %p, size %d, cursor %p, ok %s", table, size, cursor, pk->repr());
	set(0, *pk);
}

Cursor* CursorRow::get_cursor() {
	return _cursor;
}

