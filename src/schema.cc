#include "greendb/debug.hh"
#include "greendb/schema.hh"
#include "greendb/strdatum.hh"
#include "greendb/typemap.hh"
//#include <iostream>
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
	const char* Schema::get_type_name(int n) const {
		DataType type = get_type(n);
		TypeMap tm;
		return tm.get_type_name(type);
	}
	DataType Schema::get_type(int n) const {
		assert(n >= 0);
		DataTypeDatum type;
		IntDatum coln(n);
		GreenDb* db =_table->get_database("$schema_types");
		assert(db != NULL);
		if (db->fetch(coln,type) ==0) {
			return type.value();
		}
		return TYPE_UNDEFINED;
	}
	DataType Schema::get_type(const char* colname) const {
		int colno = get_col_no(colname);
		return get_type(colno);
	}
	const char* Schema::get_type_name(const char* colname) const {
		DataType type = get_type(colname);
		TypeMap tm;
		return tm.get_type_name(type);
	}
	Datum* Schema::create_datum_for_type(int type) const {
			switch(type) {
							case TYPE_STRING:
											return new Datum(TYPE_STRING);
							case TYPE_INT:
											return new Datum(TYPE_INT);
							default:
										return NULL;
			}
	}
	Datum* Schema::create_datum(const char* colname) const {
			return create_datum_for_type(get_type(colname));
	};
	Datum* Schema::create_datum(int coln) const {
			return create_datum_for_type(get_type(coln));
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
/**
 * caller must free
 */
	char** Schema::get_names() const {
		StrDatum name;
		IntDatum pk;
		char** names = new char*[_size+1];

		GreenDb* db = _table->get_database("$schema_ix_name");
		Cursor* cur = db->cursor();
		for (int i = 0;i < _size;i++) {
			cur->next(pk,name);
			char* n = name.to_string();
			names[i] = n;
		}
		names[_size] = NULL;
		return names;
	}
	const char* Schema::get_name(int colno) const {
		StrDatum name;
		IntDatum pk(colno);
		_table->get_database("$schema_ix_name")->fetch(pk,name);
		return name.value();
	}
	bool Schema::indexed(int colno) const {
		IntDatum mkindex;
		IntDatum pk(colno);
		_table->get_database("$schema_ix_mkindex")->fetch(pk,mkindex);
		return mkindex.value()==0?false:true;
	}
	void Schema::add_column(const char* colname, DataType type, bool index) {
		int idx = _size;
		_size++;
		IntDatum mkindex(index?1:0);
		IntDatum pk(idx);
		StrDatum dat_name(colname);
		_table->get_database("$schema_ix_name")->put(pk,dat_name);
		IntDatum dat_type(type);
		_table->get_database("$schema_types")->put(pk,dat_type);
		_table->get_database("$schema_name_ix")->put(dat_name,pk);
		_table->get_database("$schema_ix_mkindex")->put(pk,mkindex);
	
		StrDatum size_key("size");
		IntDatum dat_sz(_size);
		_table->get_database("$schema_meta")->put(size_key,dat_sz);
	}
	void Schema::load() {
		if (_size == -1) {
			StrDatum size_key("size");
			IntDatum dat_sz;
			if (_table->get_database("$schema_meta", false)->fetch(size_key,dat_sz) == 0) {
				_size = dat_sz.value();
			} else {
				_size = 0;
			}
		}
	}
	size_t Schema::size() const {
		return _size;
	}
	void Schema::add_columns(const char *cols[], DataType types[], unsigned int length) {
		for (int i = 0;i < length;i++) {
			const char* colname  = cols[i];
			DataType type = types[i];
			add_column(colname, type,false);
			i++;
  	}
	}
	/*
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
		case TYPE_STRING:
			return &(typeid(char*));
		case TYPE_INT:
			return &(typeid(int));
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

*/