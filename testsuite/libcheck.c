#ifdef HAVE_CONFIG_H 
#include "config.h"
#endif

#include "sleepywrap/sleepywrap.h"

#define KLEN 25
#define VLEN 256
#define DBFILE "test.db"
DB *dbp;
extern int sleepywrap_debug;

void
setup ()
{
  sleepywrap_debug = TRUE;
  sleepywrap_startup ();
  if (sleepywrap_create (&dbp) == FAILURE) {
    fail ("create failed");
  }
  if (sleepywrap_open (dbp, DBFILE) == FAILURE) {
    fail ("open failed");
  }
}
void
teardown ()
{
  sleepywrap_close (dbp);
  //sleepywrap_remove(dbp, DBFILE);
  sleepywrap_shutdown ();
}

void test_get()
{
  char key[KLEN + 1];
  char val[VLEN + 1];
  memset (key, 0, KLEN);
  memset (val, 0, VLEN);
  strcpy (key, "b");
  sleepywrap_getrec (dbp, key, KLEN, val, VLEN);
  fail_unless (strcmp (val, "two") == 0, val);
}


void test_put()
{
  char key[KLEN + 1];
  char val[VLEN + 1];
  memset (key, 0, KLEN);
  memset (val, 0, VLEN);
  strncpy (key, "a", KLEN);
  strncpy (val, "one", VLEN);
  if (sleepywrap_putrec (dbp, key, KLEN, val, VLEN) == FAILURE) {
    fail ("putrec failed");
  }
  strncpy (key, "b", KLEN);
  strncpy (val, "two", VLEN);
  if (sleepywrap_putrec (dbp, key, KLEN, val, VLEN) == FAILURE) {
    fail ("putrec failed");
  }
}
int
main (void)
{
  setup();
	testput();
	testget();
	teardown();
}
