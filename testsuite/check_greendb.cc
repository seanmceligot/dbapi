
#include "greendb/greenenv.hh"
#include "greendb/greendb.hh"
#include "greendb/debug.hh"
#include <malloc.h>
//#include <exception>
#include <string.h>
#include <ostream>
//#include <iomanip>
#include "greendb/strdatum.hh"
#include <assert.h>

static GreenEnv ge(".");
static GreenDb *db;

static void
init ()
{
  ge.open ();

  db = new GreenDb (&ge,"test.db", "data");
  db->open (0,0,0);
}
static void
deinit ()
{
  db->close ();
  ge.close ();
}
static void
check_get4 ()
{
  StrDatum key ("a");
  StrDatum get;
  db->fetch (key, get);
  debug << "got: " << get.value() << std::endl;
  assert(strcmp ( get.value(), "one") == 0);
}
static void
check_get3 ()
{
  StrDatum key ("a");
  StrDatum get;
  db->fetch (key, get);
  debug << "got: " << get.value() << std::endl;
  assert(strcmp ( get.value(), "one") == 0);
}
static void
check_get2 ()
{
  StrDatum key ("a");
  StrDatum get;
  db->fetch (key, get);
  debug << "got: " << get.value() << std::endl;
  assert(strcmp ( get.value(), "one") == 0);
}
static void
check_get ()
{
  StrDatum key ("a");
  StrDatum get;
  db->fetch (key, get);
  debug << "got: " << get.value() << std::endl;
  assert(strcmp ( get.value(), "one") == 0);
}
static void
check_put ()
{
  StrDatum key ("a");
  StrDatum val ("one");
  db->put (key, val);
}

int
main (int argc, char **argv)
{
  try {
    //debug << std::setiosflags (std::ios::stdio);
    //debug << std::setiosflags (std::ios::stdio);
    init ();
    check_put ();
    check_get ();
    check_get2 ();
    check_get3 ();
    check_get4 ();
  } catch (const char* s) {
    error << "DbException caught: " << s << std::endl;
    deinit ();
    abort ();
  } catch (DbException & ex) {
    error << "DbException caught: " << ex.what () << std::endl;
    deinit ();
    abort ();
  } catch (...) {
    error << "Exception caught: " << std::endl;
    deinit ();
    abort ();
  }
  deinit ();
  return 0;
}
