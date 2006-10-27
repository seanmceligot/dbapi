
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
  fprintf(stdout, "id: %d", id->value());
  StrDatum* name = (StrDatum*)row->get_column("name");
  fprintf(stdout, "name: %s", name->value());
  IntDatum* age = (IntDatum*)row->get_column("age");
  fprintf(stdout, "age: %d", age->value());
}
int
main (int argc, char **argv) {
  rDebug("test");
  static GreenEnv ge(".");
  rDebug("greenenv: %s", ge.home());
  // open people database
  char* table_name = "people";
  ge.open ();
  Table table (table_name, ge);
  // get schema
  Schema* schema = table.get_schema();

  // testing int datatype (not connected to any table)
  IntDatum* ii = new IntDatum(99);
  rDebug(ii->repr());
  rDebug(ii->str());
  Datum* dd = ii;
  rDebug(dd->repr());
  rDebug(dd->str());

  // create and fill database if it doesn't already exist
  if (!table.exists()) {
      // create type columns
      schema->add_column("id", TYPE_INT , 1);
      schema->add_column("name", TYPE_STRING , 1);
      schema->add_column("age", TYPE_INT , 1);

      // create datums for columns -- these are reusable
      int n=1;
      IntDatum id(n++);
      StrDatum name("Mathew");
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
         row->set("id", id );
         id=n++;
         name = "Thomas";
         age=23;
         row->set("name", name );
         row->set("age", age);
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
         Row* row = table.new_row();
         row->set_int("id", n++ );
         row->set_string("name", "Luke");
         row->set_int("age", 23);
         table.save(row);
      }

  }
  {
    //  test 
    Row* row = table.new_row();
    Datum* ddd= row->get_column("id");
    rDebug("Datum->repr %s", ddd->repr());
    // id is an int column on the people table
    IntDatum* idd = dynamic_cast<IntDatum*>(ddd);
    *idd = 18;
    rDebug("IntDatum->repr %s", idd->repr());
    //6DatumTIi6Malloc11DatumTraitsIiEE(18)
    rDebug("IntDatum->str %s", idd->str());
    //18
    StrDatum* named = dynamic_cast<StrDatum*>(row->get_column("name"));
    named->set_value("James");
    rDebug("StrDatum->repr %s", named->repr());
    //13BasicStrDatumIcSt11char_traitsIcESaIcEE(Budda)
    rDebug("StrDatum->str %s", named->str());
    //Budda
  }
  { 
    rDebug("fetch by primary key 2");
    IntDatum key(2);
    Row * row = table.fetch("id",key);
    print_row(row);
    // 2, Thomas, 23
    print_person(row);
    row->close();
  }
  { // fetch by name
    rDebug("fetch by foreign key name Luke");
    StrDatum key("Luke");
    Row * row = table.fetch("name",key);
    assert(row != NULL);
    print_row(row);
    // 4, Luke, 23
    print_person(row);
    row->close();
  }
  { 
    rDebug("fetch by foreign key age 18");
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
    rDebug("fetch all by foreign key");
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
