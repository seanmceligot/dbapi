#include "greendb/greenenv.hh"
#include "greendb/debug.hh"
#include "greendb/table.hh"
#include "greendb/schema.hh"
#include "greendb/typemap.hh"
#include "greendb/row.hh"
#include <malloc.h>
#include <assert.h>

int
main (int argc, char **argv) {
	static GreenEnv ge(".");
	char* table_name = argv[1];
	ge.open ();
	Table table (table_name, ge);
	Row* row = table.new_row();
	for (int i = 2; i < argc;i++) {
		char* val= argv[i];
    int colno = i-2;
		const char* colname = table.get_col_name(colno);
		assert(colname != NULL);
		std::cerr <<"adding "<<colname<<":"<<val<<std::endl;
		row->from_string(colname, val);
		std::cerr <<"added "<<colname<<":"<<row->to_string(colno)<<std::endl;
	}
	table.save(row);
	table.close();
	ge.close();
	return 0;
}
