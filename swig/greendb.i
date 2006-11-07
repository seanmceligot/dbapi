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

#ifdef SWIGPYTHON
#endif
#ifdef SWIGRUBY
#endif
#ifdef SWIGGUILE
#endif

%newobject Row::to_string();
%newobject Table::fetch ();
%newobject Table::cursor();

class GreenDb {
public:
  GreenDb (GreenEnv * env, const char *dbfile, const char *name);
  ~GreenDb ();
	void open_unknown();
	void open_queue();
	void open_recno();
	void open_hash();
	void open_btree();
  void open (int type, unsigned int flags,unsigned int open_flags, int mode);
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
  public:
  Datum (DataType type);
  const char * repr();
  Datum* set_int(int value);
  Datum* set_string(const char* value);
  int get_int();
  const char* get_string();
  void from_string(const char* value);
  char* to_string();
};

class StrDatum: public Datum {
  public:
  	StrDatum (char*ptr);
		~StrDatum ();
	  const char* value();
};
class IntDatum: public Datum {
  public:
  	IntDatum (int value);
	  int value();
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

%rename(to_string_n) to_string(int);
%rename(set_n) set(int, Datum*);
%rename(from_string_n) from_string(int, const char*);
%rename(get_column_n) get_column(int);

class Row {
public:
  Row (Table * table, size_t size);
	~Row ();
  void close ();
  Datum& getpk ();
  void set (int , Datum &);
  bool set (const char *colname, Datum & newDatum);
  bool set_int (const char *colname, int value);
  bool set_string (const char *colname, const char* value);
  int get_int (const char *colname);
  const char* get_string (const char *colname);
	void from_string(int index, const char* s);
	void from_string(const char* colname, const char* s);
	char* to_string(int);
	char* to_string(const char* colname);
	Datum* get_column (int idx);
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
  void save (Row * row);
  Row *fetch (const char *iname, Datum & ikey);
  Row *new_row();
  GreenDb *get_database (const char *colname);
	// get index for column name
  GreenDb *get_index(const char *colname);
  CursorRow* first(const char* colname);
  CursorRow* last(const char* colname);
  CursorRow* next (CursorRow* row, const char* colname);
	Cursor* cursor(const char* name);
  ResultSet* find_all(const char* index, Datum* fk);
	CursorRow* next(Cursor* cur, Datum& fk, Datum* pkholder);
	const char* get_col_name(int colno) const;
	const char* get_name() const;
  bool exists();
};

%rename(get_type_n) get_type(int);
class Schema {
private:
	Schema();
public:
	void add_column(const char* colname, DataType type, bool index);
	void add_columns(const char *cols[], DataType types[], unsigned int length);
  DataType get_type(int n);
	DataType get_type(const char* colname);
	int get_col_no(const char* colname);
	const char* get_name(int n);
	char** get_names() const;
	size_t size() const;
};

class TypeMap {
public:
	TypeMap();
	// convert typename to type id. 
	// ex: string -> STRING
	DataType get_type_id(const char* type);
	const char* get_type_name(int type);
};

typedef enum DataType { 
TYPE_UNDEFINED,
TYPE_USER,
TYPE_STRING,
TYPE_INT,
TYPE_END
} DataType;

class CursorRow : public Row {
public:
	CursorRow(Table* table, size_t size, Cursor* cursor, Datum* pk);
	Cursor* get_cursor();
};

