#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "userid.hh"
#include "buffer.hh"
#include "libcutils/ioutil.h"
#include "libcutils/debug.h"
#include <stdbool.h>

static int g_verbose_debug = true;
static int g_verbose_error = true;
static int g_verbose_fail = true;
static int g_fail = 0;

const char *
check_write (UserIdDb * rm, char *userid)
{
  const char *key = rm->put (userid);
  debugf ("key: %s", key);
  return key;
}

void
check_read (UserIdDb * rm, const char *key, char *compare)
{
  char *val;

  val = rm->get (key);
  debugf ("got: %s", val);
  assert (strcmp (val, compare) == 0, "bad return value");
}

void
check_list (UserIdDb * rm)
{
  Buffer key (128);
  Buffer val (128);
  DbCursor *cursor = rm->cursor ();
  while (cursor->next (&key, &val)) {
    debugf ("cursor got %s %s", key.ptr (), val.ptr ());
  }
}
int
main (int argc, char **argv)
{
  size_t len = 0;
  UserIdDb rm;
  DbEnv env;
  Buffer buf (128);
  const char *key;

  try {
    env.open (".");
    rm.open (&env);
    key = check_write (&rm, "sean");
    key = check_write (&rm, "betty");
    check_read (&rm, "1", "sean");
    check_read (&rm, "2", "betty");
    check_list (&rm);
    rm.close ();
    env.close ();
  }
  catch (DbException & ex) {
    ex.print (ERRFILE);
    rm.close ();
    env.close ();
    abort ();
  }
  return 0;
}
