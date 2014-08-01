#include "greendb/greenenv.hh"
#include "greendb/debug.hh"
#include "greendb/table.hh"
#include "greendb/schema.hh"
#include "greendb/typemap.hh"
#include "greendb/row.hh"
#include <malloc.h>
#include <assert.h>

void show( Table& table) {
	int colno = 0;
	const char* colname = table.get_col_name(colno);
	assert(colname != NULL);
	CursorRow* row = table.first(colname);
	  for (size_t i = 0; i < row->size(); i++) {
	      //Datum* val = row->get_column(i);
	      //assert(val);
	      std::cout<<row->to_string(i);
	      if (i+1 < row->size()) {
	        std::cout<<", ";
	      }
	    }
	    std::cout<<std::endl;
}

int main(int argc, char **argv) {
	static GreenEnv ge(".");
	char* table_name = argv[1];
	ge.open();
	Table table(table_name, ge);
	Row* row = table.new_row();
	for (int i = 2; i < argc; i++) {
		char* val = argv[i];
		int colno = i - 2;
		const char* colname = table.get_col_name(colno);
		assert(colname != NULL);
		fprintf(stderr, "adding %s %s\n", colname, val);
		row->from_string(colname, val);
		fprintf(stderr, "to_string %s %s\n", colname, row->to_string(colname));
	}
	table.save(row);
	//show(table);

	table.close();
	ge.close();
	return 0;
}
