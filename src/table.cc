#include "greendb/table.hh"
#include "greendb/row.hh"
#include "greendb/strdatum.hh"
#include "greendb/debug.hh"
#include "greendb/schema.hh"
#include <string>

Table::Table (const char* name, GreenEnv & ge): _name(name), _ge (ge) {
		_schema = new Schema(this);
		_schema->load();
} 

Table::~Table () {
  close ();
}
CursorRow* Table::last(const char* colname) {
	Datum* pkkey = new Datum();
	Datum pkval;
	Cursor* cur = cursor(colname);
	if (cur->last(*pkkey,pkval) == 0) {
		CursorRow* row = new CursorRow(this, _schema->size(), cur, colname, pkkey); 
		return row;
	}
	return NULL;
}
CursorRow* Table::first(const char* colname) {
	Datum* pkkey = new Datum();
	Datum pkval;
	Cursor* cur = cursor(colname);
	if (cur->next(*pkkey,pkval) == 0) {
		CursorRow* row = new CursorRow(this, _schema->size(), cur, colname, pkkey); 
		return row;
	}
	return NULL;
}
CursorRow* Table::next(CursorRow* row, const char* colname) {
	Datum* pkkey = row->get_column(0);
	debug<<"next after: "<<*pkkey<<std::endl;
	Datum pkval;
	Cursor* cur = row->get_cursor();
	if (cur->next(*pkkey,pkval) == 0) {
		debug<<"next is: "<<*pkkey<<std::endl;
		CursorRow* row = new CursorRow(this, _schema->size(), cur, colname, pkkey); 
		return row;
	}
	return NULL;
}

Row*
Table::fetch(const char *iname, Datum& ikey) {
  GreenDb *db = get_database (iname);
  Datum* pk = new Datum ();
  if (db->fetch (ikey, *pk) == DB_NOTFOUND) {
    debug << ikey << " not found" << std::endl;
		free(pk);
    return NULL;
  }
	Row* row = new Row(this, _schema->size());
	row->set(0,*pk);
  return row;
}
void
Table::close () {
  for (StringDbMap::iterator it = _dbhash.begin (); it != _dbhash.end (); it++) {
    const char *colname = it->first;
    GreenDb *db = it->second;
    debug << "close db:" << colname << " --> " << db << std::endl;
    db->close ();
    free (db);
  }
  _dbhash.clear ();
}
const char* Table::get_col_name(int colno) const {
	return _schema->get_name(colno);
}
bool Table::exists() {
  GreenDb* tables = get_database("tables");
	StrDatum key(_name.c_str());
  Datum val;
  return (tables->fetch(key, val) == 0);

}
void
Table::save (Row * row) {
  Datum& pk = row->getpk ();
  for (size_t i = 0; i < row->size(); i++) {
    const char *colname = _schema->get_name(i);
    Datum *datum = row->get_existing_column(i);
		if (datum) {
	    GreenDb *db = get_database (colname);
			char* str = row->to_string(colname);
			debug<< "put " << colname << ":"<<pk<<"=" <<str << std::endl;
			free(str);
	    db->put (pk, *datum);
		}
  }
  GreenDb* tables = get_database("tables");
	StrDatum table_name_key(_name.c_str());
  StrDatum table_location("");
  if (tables->fetch(table_name_key, table_location) != 0) {
    StrDatum tables_db("tables_db");
    tables->put(table_name_key, tables_db);
  }

}
Cursor* Table::cursor(const char*name) {
  GreenDb *db = get_database (name);
	return db->cursor();
}

void Table::index (const char* iname, Datum& pk, Datum& index) {
  GreenDb *db = get_database (iname);
  debug << "save " << iname << ":" << pk << ":" << index << std::endl;
  db->put (index, pk);
}

Schema* Table::get_schema () {
  return _schema;
}

Row *
Table::new_row() {
  return new Row (this, _schema->size());
}

GreenDb *
Table::get_database (const char *colname, bool create)
{
  GreenDb *db;
	StringDbMap::iterator it = _dbhash.find(colname);
	if (it == _dbhash.end()) {
    debug << "table " << _name << std::endl;
		std::string tablecolname (_name);
    tablecolname.append ("_");
    tablecolname.append (colname);
    debug << "open " << tablecolname.c_str() << std::endl;
    db = new GreenDb (&_ge, "tables.db", tablecolname.c_str ());
    db->open_btree (create);
    _dbhash[colname] = db;
  } else {
		db = it->second;
	}
  return db;
}

const char* Table::get_name() const {
	return _name.c_str();
}
