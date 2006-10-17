#include "greendb/greenenv.hh"
#include "greendb/debug.hh"
#include "greendb/table.hh"
#include "greendb/schema.hh"
#include "greendb/typemap.hh"
#include <malloc.h>
#include <assert.h>

int
main (int argc, char **argv) {
	RLogInit( argc, argv );
  StdioNode stdLog(2,1|4 );
	stdLog.subscribeTo( GetGlobalChannel("") );
	static GreenEnv ge(".");
	char* table_name = argv[1];
	ge.open ();
	Table table (table_name, ge);
	Schema* schema = table.get_schema();
	TypeMap* typemap = TypeMap::get_type_map();
	if (table.exists()) {
		rDebug("table already created");
	} else {
		for (int i = 2; i < argc;i++) {
			char* type = argv[i];
			DataType datatype = typemap->get_type_id(type);
			char* name = argv[++i];
			rDebug("adding %d %s %s", datatype, type, name);
			assert(datatype > TYPE_UNDEFINED);
			assert(datatype < TYPE_END);
			schema->add_column(name, datatype, 1);
		}
	}
	table.close();
	ge.close();
	return 0;
}
