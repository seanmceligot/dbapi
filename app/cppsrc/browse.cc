#include "browse.hh"
#include "greendb/greenenv.hh"
#include "greendb/debug.hh"
#include "greendb/table.hh"
#include "greendb/schema.hh"
#include "greendb/typemap.hh"
#include "greendb/row.hh"
#include <vector>
#include <string>

size_t get_schema_size(const char* table_name) {
	static GreenEnv ge(".");
	ge.open ();
	Table table (table_name, ge);
	Schema* schema = table.get_schema();
	std::cout <<table.get_name()<<std::endl;
	size_t size = schema->size();
	table.close();
	ge.close();
	return size;
}
void create_grid( Gtk::CList *grid, const char* table_name) {
	static GreenEnv ge(".");
	ge.open ();
	Table table (table_name, ge);
	Schema* schema = table.get_schema();
	std::cout <<table.get_name()<<std::endl;
	for (size_t i = 0; i < schema->size() ;i++) {
		int type = schema->get_type(i);
		const char* name = schema->get_name(i);
		std::cout<<i<<") "<<type<<"\t"<<name<<std::endl;
		grid->set_column_title(i, name);	
	}
	table.close();
	ge.close();
}
Gtk::CList* createGrid() {
	 size_t grid_size = get_schema_size("testtable");
   Gtk::CList *grid = manage(new class Gtk::CList(grid_size));
   grid->set_flags(GTK_CAN_FOCUS);
   /*grid->set_column_title(0, "label1");
   grid->set_column_justification(0, GTK_JUSTIFY_CENTER);
   grid->set_column_width(0, 80);
   grid->set_column_title(1, "label2");
   grid->set_column_justification(1, GTK_JUSTIFY_CENTER);
   grid->set_column_width(1, 80);
   grid->set_column_title(2, "label3");
   grid->set_column_justification(2, GTK_JUSTIFY_CENTER);
   grid->set_column_width(2, 80);
	 */
	 create_grid(grid, "testtable");
	 browse(grid, "testtable");
   grid->set_selection_mode(GTK_SELECTION_SINGLE);
   grid->column_titles_show();
   //scrolledwindow1->add(*grid);
   //grid->show();
}
void browse( Gtk::CList *grid, const char* table_name) {
	static GreenEnv ge(".");
	ge.open ();
	Table table (table_name, ge);
	Schema* schema = table.get_schema();
	std::cout <<table.get_name()<<std::endl;
	const char* pk = schema->get_name(0);
	Datum key;
	Datum val;
	CursorRow * row = table.first(pk);
	
	while(row) {
		std::vector<Gtk::string> data;
		for (size_t i = 0; i < row->size(); i++) {
			Datum* val = row->get_column(i);
			assert(val);
			//std::cout<<i<<") "<<*val<<std::endl;
			std::cout<<i<<") "<<row->to_string(i)<<std::endl;
			data.push_back(row->to_string(i));
		}
		grid->rows().push_back(data);
  	grid->set_column_justification(2, GTK_JUSTIFY_LEFT);
    //grid->set_column_width(2, 80);
		row->close();
		row = table.next(row, pk);
	}
	table.close();
	ge.close();
}
