
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
void print_row(Row* row) {
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
void print_person(Row* row) {
  IntDatum* id = (IntDatum*)row->get_column("id");
  fprintf(stdout, "id: %d\n", id->value());
  StrDatum* name = (StrDatum*)row->get_column("name");
  fprintf(stdout, "name: %s\n", name->value());
  IntDatum* age = (IntDatum*)row->get_column("age");
  fprintf(stdout, "age: %d\n", age->value());
}
int
main (int argc, char **argv) {
  static GreenEnv ge(".");
  fprintf(stderr, "greenenv: %s\n", ge.home());
  // open people database
  char* table_name = "people";
  ge.open ();
  Table table (table_name, ge);
  // get schema
  Schema* schema = table.get_schema();

  // testing int datatype (not connected to any table)
  IntDatum* ii = new IntDatum(99);
  fprintf(stderr, "%s\n", ii->repr());
  fprintf(stderr, "%s\n", ii->str());
  Datum* dd = ii;
  fprintf(stderr, "%s\n", dd->repr());
  fprintf(stderr, "%s\n", dd->str());

  // create and fill database if it doesn't already exist
  if (!table.exists()) {
      // create type columns
      schema->add_column("id", TYPE_INT , 1);
      schema->add_column("name", TYPE_STRING , 1);
      schema->add_column("age", TYPE_INT , 1);

			char** colnames = schema->get_names();
			for(int i=0; colnames[i];i++) {
				fprintf(stderr, "colnames[%d]=%s\n", i, colnames[i]);
			}
      // create datums for columns -- these are reusable
      int n=1;
      {
         Row* row = table.new_row();
         row->set_int("id", n++ );
         row->set_string("name", "Luke");
         row->set_int("age", 23);
         table.save(row);
      }
      {
         // another way to create a row
         Row* row = table.new_row();
         row->set_int("id", n++ );
         row->set_string("name", "Mary");
         row->set_int("age", 18);
         table.save(row);
      }
      {
         // demonstrate datum reuse
         IntDatum id(n++);
         StrDatum name("Mathew");
         fprintf(stderr, "name %s\n", name.to_string());
         IntDatum age(18);
         {
                 // create a row
                 Row* row = table.new_row();
                 row->set("id", id );
                 row->set("name", name );
                 row->set("age", age);
                 table.save(row);
              }
              {
                 // set columns and add another row
                 Row* row = table.new_row();
                 id.set_int(n++);
                 row->set("id", id );
                 name.set_string("Thomas");
                 row->set("name", name );
                 age.set_int(23);
                 row->set("age", age);
                 table.save(row);
              }
      }

  }
  { 
    fprintf(stderr, "fetch by primary key 2\n");
    IntDatum key(2);
    Row * row = table.fetch("id",key);
		fflush(stdout);
    assert(row != NULL);
		assert(strcmp(row->get_string("name"), "Mary")==0);
    print_row(row);
    // 2, Thomas, 23
    print_person(row);
    row->close();
  }
  { // fetch by name
    fprintf(stderr, "fetch by foreign key name Luke\n");
    StrDatum key("Luke");
    Row * row = table.fetch("name",key);
    assert(row != NULL);
		assert(strcmp(row->get_string("name"), "Luke")==0);
    print_row(row);
    // 4, Luke, 23
    print_person(row);
    row->close();
  }
  { 
    fprintf(stderr, "fetch by foreign key age 18\n");
    IntDatum key(18);  
    {
    Row * row = table.fetch("age",key);
    print_row(row); 
    // 1, Mathew, 18
    print_person(row);
    row->close();
    }
  } 
  { 
    fprintf(stderr, "fetch all by foreign key\n");
    IntDatum key(18);  
    ResultSet* rs = table.find_all("age", &key);
    while(rs->has_row()) {
      CursorRow* row = rs->row();
      print_row(row);
       // 1, Mathew, 18
       // 3, Mary, 18
      rs->next();
    }
  }
  table.close();
  ge.close();
  return 0;
}
