#include "greendb/typemap.hh"
#include "greendb/memory.hh"
#include "greendb/smart.hh"
#include "greendb/datum.hh"
#include <assert.h>

TypeMap* TypeMap::_singleton = NULL;

TypeMap::TypeMap():_convert_map() {
}	

void charp_to_string(void* ptr,std::string& str) {
  //std::stringstream stream;
	//stream << (const char*)ptr;
  //str = stream.str ();
	str = (const char*)ptr;
}

void from_string_charp(const char* s, void* ptr) {
	char* ip = (char*)ptr;
	strcpy(ip, s);
  //std::stringstream stream;
	//stream <<s;
	//stream >>*ip;
}
size_t from_string_size_charp(const char* s) {
	return strlen(s)+1;
}

TypeMap* TypeMap::get_type_map() {
		if (_singleton == NULL) {
			_singleton = new TypeMap();
			_singleton->add_string_convert(&(typeid(int)), 
											new StringConvert( from_string_t<int>, to_string_t<int>, from_string_size_t<int>));
			_singleton->add_string_convert(&(typeid(float)), 
											new StringConvert(from_string_t<float>, to_string_t<float>, from_string_size_t<float>));
			_singleton->add_string_convert(&(typeid(bool)), 
											new StringConvert(from_string_t<bool>, to_string_t<bool>, from_string_size_t<bool>));
			_singleton->add_string_convert(&(typeid(char*)), 
											new StringConvert(from_string_charp, charp_to_string, from_string_size_charp));
		}
		return _singleton;
}

void TypeMap::add_string_convert(const std::type_info* ti, StringConvert* sc) {
	_convert_map[ti] = sc;
}
/*
 * return value must be freed by caller
 */
char* TypeMap::to_string(const std::type_info* ti, Datum* datum) {
	StringConvert* sc = _convert_map[ti];
	assert(sc!=NULL);
	std::string str;
	sc->to_string(datum->get_ptr(), str);
	size_t len = str.length();
	if (!len) {
		return NULL;
	}
	char* cstr = (char*)greendb_malloc(len);
	strncpy(cstr, str.data(), len);
	cstr[len] = 0;
	return cstr;
}

void TypeMap::from_string(const std::type_info* ti, Datum* datum, const char* str) {
	StringConvert* sc = _convert_map[ti];
	assert(sc);
	sc->from_string(str, datum->get_ptr());
	//rDebug("after fromstring: %s",datum->str());
}
size_t TypeMap::from_string_size(const std::type_info* ti, const char* str) {
	StringConvert* sc = _convert_map[ti];
	assert(sc);
	return sc->from_string_size(str);
}

DataType TypeMap::get_type_id(const char* type) {
	if (strcmp("user", type) == 0) {
		return TYPE_USER;
	}
	if (strcmp("string", type) == 0) {
		return TYPE_STRING;
	}
	if (strcmp("int", type) == 0) {
		return TYPE_INT;
	}
	return TYPE_UNDEFINED;
}
const char* TypeMap::get_type_name(int type) {
	switch(type) {
		case TYPE_USER:
			return "user";		
		case TYPE_STRING:
			return "string";		
		case TYPE_INT:
			return "int";		
		default:
			return NULL;
	}
}
