#ifndef __TYPEMAP_HH
#define __TYPEMAP_HH
#include <cwctype>
//#include <cstring>
//#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include "greendb/datum.hh"

template <class T>
void to_string_t(void* ptr,std::string& str) {
  std::stringstream stream;
	stream << *(T*)ptr;
  str = stream.str ();
}

template <class T>
void from_string_t(const char* s, void* ptr) {
	T* ip = (T*)ptr;
  std::stringstream stream;
	stream <<s;
	stream >>*ip;
}
template <class T>
size_t from_string_size_t(const char* s) {
	return sizeof(T);
}

typedef void(*XFromString)(const char*,void*); 
typedef size_t(*XFromStringSize)(const char*); 
typedef void(*XToString)(void* ptr, std::string& str);

class StringConvert {
	XFromString _from;
	XToString _to;
	XFromStringSize _from_size;
public:
	StringConvert(XFromString from, XToString to, XFromStringSize from_size): _from(from),_to(to),_from_size(from_size) {};
	void from_string(const char*s,void* ptr) {
		_from(s,ptr);
	}
	void to_string(void* ptr,std::string& str) {
		_to(ptr,str);
	}
	size_t from_string_size(const char*s) {
		return _from_size(s);
	}
};

class TypeMap {
private:
	TypeMap();
	static TypeMap* _singleton;
	typedef std::map < const std::type_info*, StringConvert*> StrConvertMap;
	StrConvertMap _convert_map;
public:
	static TypeMap* get_type_map();
	void add_string_convert(const std::type_info* ti, StringConvert* sc);
	char* to_string(const std::type_info* ti, Datum* datum);
	void from_string(const std::type_info*, Datum* datum, const char* str);
	size_t from_string_size(const std::type_info* ti, const char* str);
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
		BOOL,
		END
	};
};


#endif
