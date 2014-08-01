#include "greendb/typemap.hh"
#include "greendb/memory.hh"
#include "greendb/datum.hh"
#include <assert.h>
#include <cstring>

TypeMap::TypeMap() {
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
