
#include "greendb/greenenv.hh"
#include "greendb/greendb.hh"
#include "greendb/debug.hh"
#include "greendb/row.hh"
#include "greendb/schema.hh"
#include "greendb/strdatum.hh"
#include "greendb/cursor.hh"
#include "greendb/typemap.hh"
#include <malloc.h>
//#include <exception>
#include <string.h>
#include <ostream>
//#include <iomanip.h>
#include <assert.h>

static GreenEnv ge(".");
Table* table;
const char* colnames[] = {"userid","firstname", "lastname", NULL};
int coltypes[] = {TypeMap::STRING, TypeMap::STRING, TypeMap::STRING, 0};


static void
init ()
{
  ge.open ();
	table = new Table("users", ge);
	Schema* schema = table->get_schema();
	schema->add_columns(colnames, coltypes);
}
static void
shutdown ()
{
	table->close();
	delete table;
  ge.close ();
}
static void
check_cursor () {
	Cursor* cursor = table->cursor("userid");
	StrDatum key;
	StrDatum val;
	while(cursor->next(key,val) ==0) {
			std::cout << "cursor->next: key("<<key.value()<<')'<<std::endl;
			std::cout << "cursor->next: val("<<val.value()<<')'<<std::endl;
	}
	cursor->close();
}
static void
check_get ()
{
	StrDatum key("smceligot");
	Row* row = table->fetch("userid", key);
	assert(row != NULL);
	Schema* schema = table->get_schema();
	for (int i = 0; i < schema->size(); i++) {
			const char* colname = schema->get_name(i);
			debug<< "get " << colname << std::endl;
			Datum* datum = row->get_column(colname);
			char* str = row->to_string(colname);
			debug<< "got " << colname << ":(to_string)" << str << std::endl;
			free(str);
	}
}
static void
put_row (const char* userid, const char* firstname, const char* lastname) {
	StrDatum pk(userid);
	Row* row = table->new_row();
	row->set("userid", pk);
  StrDatum fname(firstname);
  StrDatum lname(lastname);
	row->set("firstname", fname);
	row->set("lastname", lname);
	table->save(row);
}
static void
check_put ()
{
	put_row("smceligot", "Sean", "McEligot");	
	put_row("zzz","Zoo","Lander");
	put_row("aaa","Abe","Lincoln");
}
int
main (int argc, char **argv)
{
  try {
    //debug << setiosflags (ios::stdio);
    //debug << setiosflags (ios::stdio);
    init ();
    check_put ();
    check_get ();
    check_cursor ();
  }
  catch (DbException & ex) {
    error << "DbException caught: " << ex.what () << std::endl;
    shutdown ();
    abort ();
  } catch (...) {
    error << "Exception caught: " << std::endl;
    shutdown ();
    abort ();
  }
  shutdown ();
  return 0;
}
