#include "greendb/greenenv.hh"
#include "greendb/debug.hh"
#include "greendb/table.hh"
#include "greendb/schema.hh"
#include "greendb/typemap.hh"
#include <malloc.h>
#include <assert.h>

int
main (int argc, char **argv) {
	static GreenEnv ge(".");
	char* table_name = argv[1];
	ge.open ();
	Table table (table_name, ge);
	Schema* schema = table.get_schema();
	if (table.exists()) {
		std::cerr<<"table already created"<<std::endl;
	} else {
		for (int i = 2; i < argc;i++) {
			int type = atoi(argv[i]);
			char* name = argv[++i];
			std::cout <<"adding "<<type<<":"<<name<<std::endl;
			assert(type > TypeMap::UNDEFINED);
			assert(type < TypeMap::END);
			schema->add_column(name, type, 0);
		}
	}
	table.close();
	ge.close();
	return 0;
}
