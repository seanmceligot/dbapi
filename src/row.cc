#include "greendb/row.hh"
#include "greendb/schema.hh"
#include "greendb/typemap.hh"
#include "greendb/debug.hh"
#include <assert.h>

Row::Row (Table * table, size_t size):_size (size), _table (table)  {
	_colDatum = new Datum*[size];
	for (size_t i = 0; i < size;i++) {
		_colDatum[i] = NULL;
	}
}
Row::~Row () {
  debug << "~Row()" << std::endl;
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
  //delete[] _colDatum;
}

void
Row::set (int idx, Datum & newDatum)
{
  Datum *datum = _colDatum[idx];
  if (datum) {
    free (datum);
  }
  debug<<"set: "<<idx<<":"<<newDatum<<std::endl;
  _colDatum[idx] = &newDatum;
}
int Row::get_col_no(const char* colname) {
		Schema* schema = _table->get_schema();
		assert (schema != NULL);
	return schema->get_col_no(colname);
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
	if (idx < 0) {
      debug<<"get_col_no: "<<colname<<" not found"<<std::endl;
			return NULL;
	}
  Datum *val = get_existing_column (idx);
  if (!val) {
    GreenDb *db = _table->get_database (colname);
		Datum* pk = _colDatum[0];
		if (pk == NULL) {
      debug<<"get_database: "<<colname<<" not found"<<std::endl;
			return NULL;
		}
		val = new Datum();
    if (db->fetch (*pk, *val) == DB_NOTFOUND) {
      debug << *pk << " not found" << std::endl;
      return NULL;
    }
		debug<<"get_column: " <<pk<<":"<<val<<std::endl;
		_colDatum[idx] = val;
  }
  return val;
}

Datum *
Row::get_existing_column (int idx) {
	return _colDatum[idx];
}
void Row::from_string(const char* colname, const char* s) {
  debug << "from_string: "<<colname<<std::endl;
	int idx = get_col_no(colname);
	from_string(idx,s);
}
void Row::from_string(int idx, const char* s) {
  debug << "from_string: "<<idx<<std::endl;
	Schema* schema = _table->get_schema();
	const std::type_info* ti = schema->get_typeid(idx);
	Datum* datum = get_existing_column(idx);
	if (!datum) {
		datum = new Datum();
		set(idx, *datum);
	}
	datum->atleast(TypeMap::get_type_map()->from_string_size(ti, s));
	TypeMap::get_type_map()->from_string(ti, datum, s);
}
char* Row::to_string(int idx) {
  debug << "to_string: "<<idx<<std::endl;
	Schema* schema = _table->get_schema();
	const std::type_info* ti = schema->get_typeid(idx);
	debug << "typeinfo: "<<ti->name()<<std::endl;
	Datum* datum = get_column(idx);
	if (datum == NULL) {
    return "NULL";
  }
	return TypeMap::get_type_map()->to_string(ti,datum);
}
char* Row::to_string(const char* colname) {
  debug << "to_string: "<<colname<<std::endl;
	Schema* schema = _table->get_schema();
	const std::type_info* ti = schema->get_typeid(colname);
	debug << "typeinfo: "<<ti->name()<<std::endl;
	Datum* datum = get_column(colname);
	assert(datum != NULL);
std::cout<<__FILE__<<":"<<__LINE__<<std::endl;
	char* str = TypeMap::get_type_map()->to_string(ti,datum);
std::cout<<__FILE__<<":"<<__LINE__<<std::endl;
  return str;
}

CursorRow::CursorRow(Table* table, size_t size, Cursor* cursor, const char* index, Datum* pk) :
	Row(table, size), _cursor(cursor) {
	bool isset = set(index, *pk);
	assert (isset);
}

Cursor* CursorRow::get_cursor() {
	return _cursor;
}

