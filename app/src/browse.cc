#include "browse.hh"
#include "greendb/greenenv.hh"
#include "greendb/debug.hh"
#include "greendb/table.hh"
#include "greendb/schema.hh"
#include "greendb/typemap.hh"
#include "greendb/row.hh"
#include "greendb/schema.hh"
#include "greenapp.hh"
#include "callbacks.hh"
#include "edit.hh"

struct AddRow: public Callback {
  void operator()(Frame* frame, const char* args) {
    Model* model = frame->get_model();
    StrQueue* words = split_words(args);
    if (words->empty()) {
      EditView* ev = new EditView(model);
		  std::cout<<"add-row <graphical>"<<std::endl;
      frame->push_view(ev);
      return;
    }
		std::cout<<"add-row "<<args<<std::endl;
    Table* table = model->get_table();
    if (!table) {
      return;
    }
  	Row* row = table->new_row();
    size_t count = row->size();
	  std::cout <<"row size: "<<count<<std::endl;

  	for (unsigned int colno = 0; colno < count;colno++) {
      assert(!words->empty());
  		char* val= words->front();
      words->pop();
  		const char* colname = table->get_col_name(colno);
  		assert(colname != NULL);
  		row->from_string(colname, val);
	  	std::cout <<"added "<<colname<<":"<<row->to_string(colno)<<std::endl;
  	}
  	table->save(row);
  }
};

Browser::Browser(Model* model): View("Browser", model) {
  create_grid(model->get_table()->get_schema()->size());
  create_grid_titles(model->get_table()->get_schema());
}
void Browser::open(Frame* frame) {
	std::cout <<"Browser::open()"<<std::endl;
  Table* table = get_model()->get_table();
  Schema* schema = table->get_schema();
  create_grid(schema->size());
  create_grid_titles(schema);
	const char* pk = schema->get_name(0);
  populate_grid(table, pk, table->first(pk));
  Callbacks::get_instance()->add_action("add-row", new AddRow() );
}
void Browser::close() {
  //Callbacks::get_instance()->remove_action("add-row");
}
void Browser::populate_grid(Table* table, const char* key_name, CursorRow* row) {
  assert(table);
	std::cout <<"populate_grid: "<<table->get_name()<<" by "<<key_name<<std::endl;
	Datum key;
	Datum val;
  if (row == NULL) {
	  row = table->first(key_name);
  }
  int rowno = 0;	
	while(row) {
    gchar* data[row->size()+1];
		for (size_t i = 0; i < row->size(); i++) {
			Datum* val = row->get_column(i);
			assert(val);
			data[i] = row->to_string(i);
		}
    data[row->size()] = NULL;
		gtk_clist_append(GTK_CLIST(_grid), data);
		row->close();
		row = table->next(row, key_name);
    rowno++;
	}
}

void Browser::create_grid_titles(Schema* schema) {
	for (size_t i = 0; i < schema->size() ;i++) {
		int type = schema->get_type(i);
		const char* name = schema->get_name(i);
		std::cout<<i<<") "<<type<<"\t"<<name<<std::endl;
		gtk_clist_set_column_title(GTK_CLIST(_grid), i, name);	
	}
}

void  Browser::create_grid(size_t column_count) {
   _grid = gtk_clist_new(column_count);
   //if (grid_size < 1) {
   //  return NULL;
   //}
   //gtk_clist_set_flags(GTK_CAN_FOCUS);
   /*grid->set_column_title(0, "label1");
   grid->set_column_justification(0, GTK_JUSTIFY_CENTER);
	 */
   gtk_clist_set_selection_mode(GTK_CLIST(_grid), GTK_SELECTION_SINGLE);
   gtk_clist_column_titles_show(GTK_CLIST(_grid));
   //scrolledwindow1->add(*grid);
   //grid->show();
}
GtkWidget* Browser::get_widget() {
  return _grid;
}
