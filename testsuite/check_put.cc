#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rawmsg.hh"
#include "buffer.hh"
#include "libcutils/ioutil.h"
#include "libcutils/debug.h"
#include <stdbool.h>

static int g_verbose_debug = true;
static int g_verbose_error = true;
static int g_verbose_fail = true;
static int g_fail = 0;

const char *
check_write (RawMsgDb * rm)
{
  const char *key = rm->put (msg);
  debugf ("key: %s", key);
  return key;
}

void
check_read (RawMsgDb * rm, const char *key)
{
  char *val;

  val = rm->get (key);
  debugf ("got: %s", val);
  assert (strcmp (val, msg) == 0, "bad return value");
}

void
check_list (RawMsgDb * rm)
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
  RawMsgDb rm;
  DbEnv env;
  Buffer buf (128);
  const char *key;

  try {
    env.open (".");
    rm.open (&env);
    key = check_write (&rm);
    check_read (&rm, "1");
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
