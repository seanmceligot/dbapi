#ifndef SCHEMA_HH
#define SCHEMA_HH

//#include <vector>
//#include <map>
//#include <string>
#include <typeinfo>
#include "greendb/debug.hh"
#include "greendb/table.hh"

using namespace std;

class GreenDbIterator {
		virtual bool hasmore()=0;
		virtual Datum* next();
		virtual Datum* current();
		virtual ~GreenDbIterator();

};
class Schema {
	int _size;
	Table* _table;
  Schema (Table* table);
	friend class Table;
	friend class Row;
public:
	void add_column(const char* colname, DataType type, bool index);
	void add_columns(const char *cols[], DataType types[], unsigned int length);
	//void add_index(const char* colname, int type, bool index);
	DataType get_type(int n) const;
	const char* get_type_name(int n) const;
	DataType get_type(const char* colname) const;
	const char* get_type_name(const char* colname) const;
	Datum* create_datum(const char* colname) const;
	Datum* create_datum(int coln) const;
	Datum* create_datum_for_type(int type) const;
	int get_col_no(const char* colname) const;
	const char* get_name(int n) const;
	const char** get_names() const;
	bool indexed(int colno) const;
	size_t size() const;
protected:
	const std::type_info* get_typeid(int colno);
	const std::type_info* get_typeid(const char* colname);
	void load();
private:
	const std::type_info* get_typeid_from_type(int coltype);
};


#endif
