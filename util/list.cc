#include "greendb/greenenv.hh"
#include "greendb/debug.hh"
#include "greendb/table.hh"
#include "greendb/schema.hh"
#include "greendb/typemap.hh"
#include "greendb/row.hh"
#include <malloc.h>
#include <assert.h>

void print_row(Row* row) {
		for (size_t i = 0; i < row->size(); i++) {
			Datum* val = row->get_column(i);
			assert(val);
			//std::cout<<i<<") "<<val->to_string() <<std::endl;
			std::cout<<row->to_string(i);
			if (i+1 < row->size()) {
				std::cout<<", ";
			}
		}
		std::cout<<std::endl;
}

int
main (int argc, char **argv) {
	static GreenEnv ge(".");
	char* table_name = argv[1];
	ge.open ();
	Table table (table_name, ge);
	Schema* schema = table.get_schema();
	//g_message(table.get_name());
	std::cout <<table.get_name()<<std::endl;
	const char* pk = schema->get_name(0);
	CursorRow * row = table.first(pk);
	fprintf(stderr, " listing by pk %s\n", pk);
	while(row) {
		print_row(row);
		//row->close();
		row = table.next(row, pk);

	}
	table.close();
	ge.close();
	return 0;
}
