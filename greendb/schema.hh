#ifndef SCHEMA_HH
#define SCHEMA_HH

//#include <vector>
//#include <map>
//#include <string>
#include "greendb/debug.hh"
#include "greendb/table.hh"

class Schema {
	int _size;
	Table* _table;
  Schema (Table* table);
	friend class Table;
	friend class Row;
public:
	void add_column(const char* colname, int type, bool index);
	void add_columns(const char *cols[], int types[], unsigned int length);
	//void add_index(const char* colname, int type, bool index);
	int get_type(int n) const;
	int get_type(const char* colname) const;
	int get_col_no(const char* colname) const;
	const char* get_name(int n) const;
	size_t size() const;
  friend std::ostream & operator << (std::ostream & os, const Schema & schema);
protected:
	const std::type_info* get_typeid(int colno);
	const std::type_info* get_typeid(const char* colname);
	void load();
private:
	const std::type_info* get_typeid_from_type(int coltype);
};

std::ostream & operator << (std::ostream & os, const Schema & schema);

#endif
