#include "greendb/greenenv.hh"
#include "greendb/debug.hh"
#include "greendb/table.hh"
#include "greendb/schema.hh"
#include "greendb/typemap.hh"
#include "greendb/row.hh"
#include "greendb/xml.hh"
#include <malloc.h>
#include <iostream>

int
main (int argc, char **argv) {
	static GreenEnv ge(".");
	char* table_name = argv[1];
	ge.open ();
	Table table (table_name, ge);
	Schema* schema = table.get_schema();
	std::cout <<table.get_name()<<std::endl;
	const char* pk = schema->get_name(0);
	CursorRow * row = table.first(pk);
	while(row) {
		for (size_t i = 0; i < row->size(); i++) {
			to_xml(schema, row, std::cout);
		}
		row->close();
		row = table.next(row, pk);
	}
	table.close();
	ge.close();
	return 0;
}
