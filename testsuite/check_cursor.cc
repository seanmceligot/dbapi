
#include "greendb/greenenv.hh"
#include "greendb/greendb.hh"
#include "greendb/cursor.hh"
#include "greendb/debug.hh"
#include "greendb/strdatum.hh"
#include <malloc.h>
//#include <exception>
#include <string.h>
#include <ostream>
#include <assert.h>

static GreenEnv ge(".");
static GreenDb *db;

void
my_free (void *ptr)
{
  debug << "free:" << ptr << std::endl;
  free (ptr);
}

void *
my_malloc (size_t size)
{
  debug << "malloc:" << size << std::endl;
  return malloc (size);
}

void *
my_realloc (void *ptr, size_t newsize)
{
  debug << "realloc:" << ptr << ':' << newsize << std::endl;
  return realloc (ptr, newsize);
}
static void
init ()
{
  ge.open ();

  db = new GreenDb (&ge,"test.db", "data");
  db->open (0,0,0);
}
static void
shutdown ()
{
  db->close ();
  ge.close ();
}

static void
check_next()
{
  debug << "next" << std::endl;
  Cursor *cur = db->cursor ();

  //StrDatum key ("two");
  StrDatum get;
  StrDatum key;

  cur->next(key, get);
	debug<<get.value()<<std::endl;
  cur->next(key, get);
	debug<<get.value()<<std::endl;
  cur->next(key, get);
	debug<<get.value()<<std::endl;
	cur->close();
}
static void
check_find()
{
  debug << "find" << std::endl;
  Cursor *cur = db->cursor ();

  StrDatum get;
	StrDatum key("two");

  cur->find (key, get);
	debug<<get.value()<<std::endl;
  assert (strcmp ((char *) get.value(), "dos") == 0);
	cur->close();
}
static void
check_put ()
{
  StrDatum key ("one");
  StrDatum val ("uno");
  db->put (key, val);
  key = "two";
  val = "dos";
  db->put (key, val);
  key = "three";
  val = "tres";
  db->put (key, val);
}

int
main (int argc, char **argv)
{
  try {
    //debug << setiosflags (ios::stdio);
    //debug << setiosflags (ios::stdio);
    init ();
    check_put ();
    check_next();
    check_find();
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
