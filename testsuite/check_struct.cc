#include "greendb/greenenv.hh"
#include "greendb/greendb.hh"
#include "greendb/debug.hh"
#include "greendb/row.hh"
#include <malloc.h>
//#include <exception>
#include <string.h>
#include <ostream>
//#include <iomanip.h>

static GreenEnv ge(".");
Table* table;

const char* colnames[] = {"userid", NULL};
int coltypes[] = {Types::UNDEFINED, Types::NIL};

class UserTable {
	enum {USERID_LEN=64,FIRSTNAME_LEN=256,LASTNAME_LEN=256};
	char _userid[USERID_LEN];
	char _firstname[FIRSTNAME_LEN];
	char _lastname[LASTNAME_LEN];
};
class User {
	char _userid[64];
	char _firstname[256];
	char _lastname[256];
public:
	User(
									const char* userid,
									const char* firstname,
									const char* lastname) {
		strncpy(_userid, userid, 64);
		strncpy(_firstname, firstname, 256);
		strncpy(_lastname, lastname, 256 );
	}
	const char* lastname() {
			return _lastname;
	}
	const char* pk() {
			return _userid;
	}
	friend std::ostream& operator<<(std::ostream& os, User&);
};
std::ostream& operator<<(std::ostream& os, User* u) {
	if (u) {
		return os << *u;
	} else {
		return os << "NULL";
	}
}
std::ostream& operator<<(std::ostream& os, User& u) {
		os << u._userid;	
		os << ":";
		os << u._firstname;		
		os << ":";
		os << u._lastname;		
		os << std::endl;
		return os;
}

static void
init ()
{
  ge.open ();
	Schema* schema = new Schema("struct", colnames, coltypes);
	table = new Table(ge, schema);
}
static void
shutdown ()
{
	free(table->getschema());
	table->close();
	free(table);
  ge.close ();
}
static void
get_index()
{
	StaticDatum key("McEligot");
	Row* row = table->fetch("lastname", &key);
	Schema* schema = table->getschema();
	for (Schema::iterator it = schema->begin(); !it.end(); it++) {
			const char* colname = *it;
			Datum* datum = row->get_column(colname);
			User*user = (User*)datum->ptr();
			debug<< "index:got " << colname << ":" <<user<< std::endl;
	}
}
static void
check_get ()
{
	StaticDatum key("smceligot");
	Row* row = table->fetch(&key);
	Schema* schema = table->getschema();
	for (Schema::iterator it = schema->begin(); !it.end(); it++) {
			const char* colname = *it;
			Datum* datum = row->get_column(colname);
			User*user = (User*)datum->ptr();
			debug<< "got " << colname << ":" <<user<< std::endl;
	}
}
static void putuser(User* u) {
	StaticDatum pk(u->pk());
	Row row(table, &pk);
	//row.set("userid", new StaticDatum(u, sizeof(User)));
	StaticDatum udatum(u, sizeof(User));
	row.set(&udatum);
	StaticDatum ln(u->lastname());
	table->index("lastname", &pk, &ln );
	table->save(&row);	
}
static void
check_put ()
{
	User* u;
	u= new User("smceligot","Sean","McEligot");
	putuser(u);
	u= new User("zzz","Zoo","Lander");
	putuser(u);
	u= new User("aaa","Abe","Lincoln");
	putuser(u);
	free(u);
}
/*
 * users_userid: smceligot smceligot
 * users_firstname smceligot sean
 * users_userid: testuser
 * users_firstname firstname Test
 */
int
main (int argc, char **argv)
{
  try {
    //debug << setiosflags (ios::stdio) <<std::endl;
    init ();
    check_put ();
    check_get ();
    get_index();
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
