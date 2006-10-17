
#include "greendb/greenenv.hh"
#include "greendb/debug.hh"
#include "greendb/table.hh"
#include "greendb/schema.hh"
#include "greendb/typemap.hh"
#include "greendb/row.hh"
#include "greendb/datum.hh"
#include "greendb/strdatum.hh"
#include "greendb/resultset.hh"
#include <malloc.h>
#include <assert.h>
#include "mcheck.h"
void print_row(Row* row) {
		for (size_t i = 0; i < row->size(); i++) {
			Datum* val = row->get_column(i);
			assert(val);
			//std::cout<<i<<") "<<*val<<std::endl;
			std::cout<<row->to_string(i);
			if (i+1 < row->size()) {
				std::cout<<", ";
			}
		}
		std::cout<<std::endl;
}
void print_person(Row* row) {
	IntDatum* id = (IntDatum*)row->get_column("id");
	rDebug("id: %d", id->value());
	StrDatum* name = (StrDatum*)row->get_column("name");
	rDebug("name: %s", name->value());
	IntDatum* age = (IntDatum*)row->get_column("age");
	rDebug("age: %d", age->value());
}
int
main (int argc, char **argv) {
	mtrace();
	RLogInit( argc, argv );
  StdioNode stdLog(2,1|4 );
	stdLog.subscribeTo( GetGlobalChannel("") );

	rDebug("test");
	static GreenEnv ge(".");
	rDebug("greenenv: %s", ge.home());
	char* table_name = argv[1];
	ge.open ();
	Table table (table_name, ge);
	{ 
		rDebug("fetch by primary key 2");
		IntDatum key(2);
		Row * row = table.fetch("id",key);
		print_row(row);
		print_person(row);
		row->close();
	}
	{ // fetch by name
		rDebug("fetch by foreign key name Bob");
		StrDatum key("Bob");
		Row * row = table.fetch("name",key);
		print_row(row);
		print_person(row);
		row->close();
	}
	{ 
		rDebug("fetch by foreign key age 18");
		IntDatum key(18);	
		{
		Row * row = table.fetch("age",key);
		print_row(row);
		print_person(row);
		row->close();
		}
	} 
	{ 
		rDebug("fetch all by foreign key");
		IntDatum key(18);	
		//IntDatum pk(0);
		ResultSet* rs = table.find_all("age", &key);
		while(rs->has_row()) {
			CursorRow* row = rs->row();
			print_row(row);
			rs->next();
		}
	}
	table.close();
	ge.close();
	return 0;
}
