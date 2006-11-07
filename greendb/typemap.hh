#ifndef __TYPEMAP_HH
#define __TYPEMAP_HH

class Datum;

typedef enum DataType { 
TYPE_UNDEFINED,
TYPE_USER,
TYPE_STRING,
TYPE_INT,
TYPE_END
} DataType;

class TypeMap {
public:
	TypeMap();
	// convert typename to type id. 
	// ex: string -> STRING
	DataType get_type_id(const char* type);
	const char* get_type_name(int type);
};


#endif
