#include "greendb/table.hh"
#include "greendb/row.hh"
#include "greendb/strdatum.hh"
#include "greendb/debug.hh"
#include "greendb/schema.hh"
#include "greendb/resultset.hh"
#include <string>
#include <glib.h>

Table::Table (const char* name, GreenEnv & ge): _name(name), _ge (ge) {
		_schema = new Schema(this);
		_schema->load();
} 

Table::~Table () {
  close ();
}
CursorRow* Table::last(const char* colname) {
	Datum* pkkey = _schema->create_datum(0);
  Datum* pkval = _schema->create_datum(colname);
	Cursor* cur = cursor(colname);
  CursorRow* row = NULL;
	if (cur->last(*pkkey,*pkval) == 0) {
		row = new CursorRow(this, _schema->size(), cur, pkkey); 
	}
  free(pkval);
	return row;
}
ResultSet* Table::find_all(const char* index, Datum* fk) {
	Datum* pk = _schema->create_datum(0);
  GreenDb *db = get_index(index);
	Cursor* cur = db->cursor();
	//g_message("find %s", db->name());
	unsigned int column_count = _schema->size();
	if (cur->find(*fk, *pk) == 0 ) {
		CursorRow* row = new CursorRow(this, column_count, cur, pk); 
		return new ResultSet(this, row, fk, pk, column_count);
	}
	return new ResultSet(this, NULL, fk, pk, column_count);
}
CursorRow* Table::next(Cursor* cur, Datum& fk, Datum* pk) {
	int dberr = cur->next_dup(fk, *pk);
	if (dberr == 0 ) {
		CursorRow* row = new CursorRow(this, _schema->size(), cur, pk); 
		return row;
	} else {
		_ge.err(dberr);
	}
	return NULL;
}
CursorRow* Table::first(const char* colname) {
	Datum* pkkey = _schema->create_datum(0);
  Datum* pkval = _schema->create_datum(colname);
	Cursor* cur = cursor(colname);
	CursorRow* row = NULL;
	if (cur->next(*pkkey,*pkval) == 0) {
		//g_message("first pk=%s", pkkey->to_string());
		//g_message("next by %s got pk=%s", colname, pkkey->to_string());
		row = new CursorRow(this, _schema->size(), cur, pkkey); 
	}
  free(pkval);
	return row;
}
CursorRow* Table::next(CursorRow* row, const char* colname) {
	Datum* pkkey = row->get_column(0);
  Datum* pkval = _schema->create_datum(colname);
	Cursor* cur = row->get_cursor();
	//g_message("before first by %s pk=%s", colname, pkkey->to_string());
	if (cur->next(*pkkey,*pkval) == 0) {
		//g_message("first by %s got pk=%s", colname, pkkey->to_string());
		row = new CursorRow(this, _schema->size(), cur, pkkey); 
	} else {
		row = NULL;
	}
  free(pkval);
	return row;
}

Row*
Table::fetch(const char *colname, Datum& ikey) {
  GreenDb *db = get_index(colname);
	//g_message("fetch %s %s", db->name(), ikey.to_string());
  Datum* pk = _schema->create_datum(0);
  if (db->fetch (ikey, *pk) != 0) {
		free(pk);
    return NULL;
  }
	//g_message("found pk %s", pk->to_string());
	Row* row = new Row(this, _schema->size());
	row->set(0,*pk);
  return row;
}
void
Table::close () {
  for (StringDbMap::iterator it = _dbhash.begin (); it != _dbhash.end (); it++) {
    const char *colname = it->first;
    GreenDb *db = it->second;
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
  Datum val(TYPE_STRING);
  bool exists = (tables->fetch(key, val) == 0);
	return exists;
}
void
Table::save (Row * row) {
  Datum& pk = row->getpk ();
  for (size_t i = 0; i < row->size(); i++) {
    const char *colname = _schema->get_name(i);
    bool indexed = _schema->indexed(i);
		//g_message("save %s %s %d", _name.c_str(), colname, indexed);
    Datum *datum = row->get_existing_column(i);
		if (datum == NULL) {
					datum = _schema->create_datum(i);
		}
    GreenDb *db = get_database (colname);
		//char* str = row->to_string(colname);
		//free(str);
    // g_message("saving... %s %s %s", colname, pk.to_string(), datum->to_string());
    db->put (pk, *datum);
     if (indexed) {
       GreenDb* idb = get_index(colname, true);
       //g_message("indexing... %s %s %s", colname, datum->to_string(), pk.to_string());
       idb->put (*datum, pk);
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
Table::get_index(const char *colname, bool create)
{
  GreenDb *db;
	//g_message("get_index: %s %s _ix", _name.c_str(), colname);
		std::string tablecolname (_name);
    tablecolname.append ("_");
    tablecolname.append (colname);
    tablecolname.append ("_ix");
	StringDbMap::iterator it = _dbhash.find(tablecolname.c_str());
	if (it == _dbhash.end()) {
		//g_message("get_index: %s %d", tablecolname.c_str(), create);
    db = new GreenDb (&_ge, "tables.db", tablecolname.c_str ());
    db->open_btree (create, true);
		_dbhash[tablecolname.c_str()] = db;
  } else {
		//g_message("returning cached %s", tablecolname.c_str());
		db = it->second;
	}
  return db;
}

GreenDb *
Table::get_database (const char *colname, bool create)
{
  GreenDb *db;
	StringDbMap::iterator it = _dbhash.find(colname);
	if (it == _dbhash.end()) {
		std::string tablecolname (_name);
    tablecolname.append ("_");
    tablecolname.append (colname);
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
