#include "greendb/debug.hh"
#include "greendb/schema.hh"
#include "greendb/strdatum.hh"
#include "greendb/typemap.hh"
#include <iostream>
#include <assert.h>
/*
 * schema
 * 	columns
 *	 	name
 *	 	type
 *	 meta
 *	 	size
 * 		version
 *
 * 	mapping
 * 		schema1
 * 		schema2
 * 		name1=name2
 * 		name1=name2
 * 		name1=name2
 * 		....
 * 		convert1
 * 		convert2
 * 		convert3
 * 		...
 */
	Schema::Schema (Table* table):_size(-1),_table(table) {
	}
	int Schema::get_type(int n) const {
		assert(n >= 0);
		IntDatum type;
		IntDatum coln(n);
		debug<<"get_type:"<<n<<std::endl;
		GreenDb* db =_table->get_database("$schema_types");
		assert(db != NULL);
		if (db->fetch(coln,type) ==0) {
			return type.value();
		}
		return TypeMap::UNDEFINED;
	}
	int Schema::get_type(const char* colname) const {
		int colno = get_col_no(colname);
		return get_type(colno);
	}
	int Schema::get_col_no(const char* colname) const {
		IntDatum pk;
		StrDatum named(colname);
		GreenDb* db = _table->get_database("$schema_name_ix");
		assert(db != NULL);
		if (db->fetch(named,pk) == 0) {
			return pk.value();
		}
		return -1;
	}
	const char* Schema::get_name(int colno) const {
		StrDatum name;
		IntDatum pk(colno);
		_table->get_database("$schema_ix_name")->fetch(pk,name);
		return name.value();
	}
	void Schema::add_column(const char* colname, int type, bool index) {
		int idx = _size;
		_size++;
		IntDatum pk(idx);
		StrDatum dat_name(colname);
		_table->get_database("$schema_ix_name")->put(pk,dat_name);
		IntDatum dat_type(type);
		_table->get_database("$schema_types")->put(pk,dat_type);
		_table->get_database("$schema_name_ix")->put(dat_name,pk);
	
		StrDatum size_key("size");
		IntDatum dat_sz(_size);
		_table->get_database("$schema_meta")->put(size_key,dat_sz);
	}
	void Schema::load() {
		if (_size == -1) {
			StrDatum size_key("size");
			IntDatum dat_sz;
			if (_table->get_database("$schema_meta")->fetch(size_key,dat_sz) == 0) {
				_size = dat_sz.value();
			} else {
				_size = 0;
			}
		}
	}
	size_t Schema::size() const {
		return _size;
	}
	void Schema::add_columns(const char *cols[], int types[], unsigned int length) {
		for (int i = 0;i < length;i++) {
			const char* colname  = cols[i];
    	int type = types[i];
			add_column(colname, type,false);
			i++;
  	}
	}
const std::type_info* Schema::get_typeid(int colno) {
	int coltype = get_type(colno);
	return get_typeid_from_type(coltype);
}
const std::type_info* Schema::get_typeid(const char* colname) {
	int coltype = get_type(colname);
	return get_typeid_from_type(coltype);
}
const std::type_info* Schema::get_typeid_from_type(int coltype) {
	switch(coltype) {
		case TypeMap::STRING:
			return &(typeid(char*));
		case TypeMap::WSTRING:
			return &(typeid(wchar_t*));
		case TypeMap::INT:
			return &(typeid(int));
		case TypeMap::SHORT:
			return &(typeid(short));
		case TypeMap::LONG:
			return &(typeid(long));
		case TypeMap::DOUBLE:
			return &(typeid(double));
		case TypeMap::UINT:
			return &(typeid(unsigned int));
		case TypeMap::USHORT:
			return &(typeid(unsigned short));
		case TypeMap::ULONG:
			return &(typeid(unsigned long));
		case TypeMap::CHAR:
			return &(typeid(char));
		case TypeMap::WCHAR:
			return &(typeid(wchar_t));
		case TypeMap::BOOL:
			return &(typeid(bool));
		default:
			return NULL;
	}
}

std::ostream & operator << (std::ostream & os, const Schema & schema)
{
	for (size_t i = 0; i < schema.size(); i++) {
			os<<':'<<schema.get_name(i);
	}
  return os;
}

