%module greendb

%{
#include <db_cxx.h>
#include "greendb/greendb.hh"
#include "greendb/datum.hh"
#include "greendb/strdatum.hh"
#include "greendb/greenenv.hh"
#include "greendb/row.hh"
#include "greendb/table.hh"
#include "greendb/cursor.hh"
#include "greendb/typemap.hh"
#include "greendb/schema.hh"
%}

%newobject Row::to_string();
%newobject Table::fetch ();
%newobject Table::cursor();

class GreenDb {
public:
  GreenDb (GreenEnv * env, const char *dbfile, const char *name);
  ~GreenDb ();
  void open (int type, int flags, int mode);
	void open_unknown();
	void open_queue();
	void open_recno();
	void open_hash();
	void open_btree();
  const char *dbfile () const;
  const char *name () const;
  void put (Datum & key, Datum & val);
  int fetch (Datum & key, Datum & val);
  Cursor *cursor ();
  void close ();
};

class GreenEnv {
public:
  GreenEnv (const char *home);
  ~GreenEnv ();
  void open ();
  void close ();
  const char *home ();
};

class Datum {
};

class StrDatum: public Datum {
  public:
  	StrDatum (char*ptr);
    const char * type_name () const;
		~StrDatum ();
	  const char * repr () const;
	  const char* value();
		char* set_value(char* newvalue);
};
class IntDatum: public Datum {
  public:
  	IntDatum (int ptr);
    const char * type_name () const;
		~IntDatum ();
	  const char * repr () const;
	  const int value();
		int set_value(int newvalue);
};
class Cursor {
  Cursor ();
public:
  ~Cursor ();
  int first (Datum & key, Datum & val);
  int last (Datum & key, Datum & val);
  int find (Datum & key, Datum & val);
  int next (Datum & key, Datum & val);
  void close ();
};
class Row {
public:
  Row (Table * table, size_t size);
	~Row ();
  void close ();
  Datum& getpk ();
  %name(set_n) void set (int index, Datum & newDatum);
  bool set (const char *colname, Datum & newDatum);
	%name(from_string_n) void from_string(int index, const char* s);
	void from_string(const char* colname, const char* s);
	%name(to_string_n) char* to_string(int index);
	char* to_string(const char* colname);
	%name(get_column_n) Datum * get_column (int idx);
  Datum *get_column (const char *colname);
	int get_col_no(const char* colname);
  Datum * get_existing_column (int index);
	int size();
};
class Table {
public:
  Table (const char* name, GreenEnv & ge);
	Schema *get_schema ();
  void close ();
  ~Table ();
	const char* get_name() const;
  void save (Row * row);
  void index (const char *iname, Datum & pk, Datum & index);
  Row *fetch (const char *iname, Datum & ikey);
  Row *new_row();
	Cursor* cursor(const char* name);
  CursorRow* first(const char* colname);
  CursorRow* last(const char* colname);
  CursorRow* next (CursorRow* row, const char* colname);
	const char* get_col_name(int colno) const;
};
class Schema {
private:
	Schema();
public:
	void add_column(const char* colname, int type, bool index);
	%name(get_type_n) int get_type(int n) const;
	int get_type(const char* colname) const;
	int get_col_no(const char* colname) const;
	const char* get_name(int n) const;
	size_t size() const;
};

class TypeMap {
private:
	TypeMap();
public:
	static TypeMap* get_type_map();
	enum { 
		UNDEFINED,
		USER,
		STRING,
		WSTRING,
		INT,
		SHORT,
		LONG,
		DOUBLE,
		UINT,
		USHORT,
		ULONG,
		CHAR,
		WCHAR,
		BOOL
	};

};

class CursorRow : public Row {
public:
	CursorRow(Table* table, size_t size, Cursor* cursor, const char* index, Datum* pk);
	Cursor* get_cursor();
};
