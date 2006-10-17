#ifndef _SMART_HH
#define _SMART_HH
#include "greendb/memory.hh"

class SmartString {
	char* _str;
public:
	SmartString(char* str):_str(str) {
	}
	~SmartString() {
			rDebug("~SmartString");
			greendb_free(_str);
	}
	operator const char*() {
		return _str;
	}
};
#endif
