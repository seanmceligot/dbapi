#ifndef TABLE_HH
#define TABLE_HH

#include "greendb/greendb.hh"
#include "greendb/greenenv.hh"
#include "greendb/datum.hh"
//#include "greendb/schema.hh"
#include <map>
#include <string>

class Row;
class CursorRow;
class Schema;

class Table {
  typedef std::map < const char *, GreenDb * >StringDbMap;
  StringDbMap _dbhash;
	std::string _name;
  GreenEnv & _ge;
  Schema *_schema;
public:
  Table (const char* name, GreenEnv & ge);
	Schema *get_schema ();
  void close ();
  ~Table ();
  void save (Row * row);
  void index (const char *iname, Datum & pk, Datum & index);
  Row *fetch (const char *iname, Datum & ikey);
  Row *new_row();
  GreenDb *get_database (const char *colname, bool create=true);
  CursorRow* first(const char* colname);
  CursorRow* last(const char* colname);
  CursorRow* next (CursorRow* row, const char* colname);
	Cursor* cursor(const char* name);
	const char* get_col_name(int colno) const;
	const char* get_name() const;
  bool exists();
};

#endif
