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
	TypeMap typemap;
	if (table.exists()) {
		fprintf(stderr, "table already created\n");
	} else {
		for (int i = 2; i < argc;i++) {
			char* type = argv[i];
			DataType datatype = typemap.get_type_id(type);
			char* name = argv[++i];
			fprintf(stderr, "adding %d %s %s\n", datatype, type, name);
			assert(datatype > TYPE_UNDEFINED);
			assert(datatype < TYPE_END);
			schema->add_column(name, datatype, 1);
		}
	}
	table.close();
	ge.close();
	return 0;
}
