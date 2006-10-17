#include "greendb/greenenv.hh"
#include "greendb/debug.hh"
#include "greendb/table.hh"
#include "greendb/schema.hh"
#include "greendb/typemap.hh"
#include "greendb/row.hh"
#include <malloc.h>

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
	std::cout <<table.get_name()<<std::endl;
	for (size_t i = 0; i < schema->size() ;i++) {
		const char* type = schema->get_type_name(i);
		const char* name = schema->get_name(i);
		std::cout<<i<<") "<<type<<"\t"<<name<<std::endl;
	}
	table.close();
	ge.close();
	return 0;
}
