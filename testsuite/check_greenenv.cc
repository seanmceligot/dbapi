
#include "greendb/greenenv.hh"
#include "greendb/debug.hh"
#include <malloc.h>
#include <db_cxx.h>

const void
check_greenenv ()
{
  GreenEnv ge(".");
  ge.open ();
  ge.close ();
}

int
main (int argc, char **argv)
{
  try {
    check_greenenv ();
  }
  catch (DbException & ex) {
    error << ex.what ();
    abort ();
  }
  return 0;
}
