#ifdef HAVE_CONFIG_H 
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sleepywrap/sleepywrap.h"
#include "libcutils/debug.h"
#include "libcutils/xmalloc.h"

static int g_verbose_debug=1;
static int g_fail = 0;
static int g_verbose_fail=1;

SleepyWrap* sw;
SleepyWrapEnv env; 

void * my_realloc (void *PTR, size_t NEWSIZE) {
	debugf("realloc %p %d", PTR, NEWSIZE);
	return realloc(PTR, NEWSIZE);
}

void
test_init()
{
	int dberr; sleepywrap_setdebug(TRUE);
	debug("starting up");
  sleepywrap_startup ();
	dberr = sleepywrap_env_open(".", &env, malloc, my_realloc, free);
	sw = sleepywrap_new("test.db", &env);
  if (sleepywrap_create(sw)) {
    fail ("open failed");
  }
  if (sleepywrap_open (sw, DB_HASH)) {
    fail ("open failed");
  }
	
	//debug("starting transaction");
	//sleepywrap_transaction_start (sw);
}

void
test_shutdown()
{
	debug("closing");
  sleepywrap_close (sw);
	debug("shutting down");
	sleepywrap_env_close(&env);
  sleepywrap_shutdown ();
  sleepywrap_free(sw);
}
#define KLEN 2
#define VLEN 5
void
test_get ()
{
  char key[KLEN];
  char* val;
	uint32_t vlen;
	int dberr;

  memset (key, 0, KLEN);
  strcpy (key, "b");
	debug("getrec");
  dberr = sleepywrap_getrec_size (sw, key, KLEN, &vlen);
	debugf("size [%"PRIi32"]", vlen );
	val = xmalloc(vlen);
  sleepywrap_getrec (sw, key, KLEN, val, vlen);
	debugf("got %s:%s", key, val );
  assert(strcmp (val, "two") == 0, val);
	free(val);
}
void
test_get_alloc ()
{
  char key[KLEN];
  char* val;
	uint32_t vlen = 0;
  memset (key, 0, KLEN);
  strcpy (key, "b");
	debug("getrec_alloc");
  sleepywrap_getrec_alloc (sw, key, KLEN, (void**)&val, &vlen);
	debugf("alloc got %s:%s[%"PRIi32"]", key, val, vlen );
  assert(strcmp (val, "two") == 0, val);
	free(val);
}
void
test_get_realloc ()
{
  char key[KLEN];
  char* val;
	uint32_t vlen = 0;
	uint32_t allocated = 1;

  memset (key, 0, KLEN);
  strcpy (key, "b");
	val = xmalloc(1);
	bzero(val, 1);

	// allocated is 1, need realloc
  sleepywrap_getrec_realloc (sw, key, KLEN, (void**)&val, &vlen, &allocated);
	debugf("realloc got %s:%s len:[%"PRIi32"] alloc:[%"PRIi32"]", key, val, vlen, allocated );
  assert(strcmp (val, "two") == 0, val);

	//allocated = 1024;
  assert(allocated > 3, "allocated not changed");
 	val = xrealloc(val, allocated); 

	sleepywrap_getrec_realloc (sw, key, KLEN, (void**)&val, &vlen, &allocated);
	debugf("realloc got %s:%s len:[%"PRIi32"] alloc:[%"PRIi32"]", key, val, vlen, allocated );
  assert(strcmp (val, "two") == 0, val);
	free(val);
}
void test_cursor() {
	int dberr;
  char *key = NULL;
  char *val = NULL;
	uint32_t kalloc = 0;
	uint32_t valloc = 0;
	uint32_t klen = 0;
	uint32_t vlen = 0;

	//key = malloc(kalloc);
	//val = malloc(valloc);
	SleepyWrapCursor* sc = malloc(sizeof (SleepyWrapCursor));
	dberr = sleepywrap_cursor_new(sw, sc); 
	debugf("cursor %p", sc);
	assert(dberr ==0, sleepywrap_strerr(dberr));

	dberr = sleepywrap_cursor_next(sc, (void**)&key, &klen, &kalloc, (void**)&val, &vlen, &valloc );
	assert(dberr ==0, sleepywrap_strerr(dberr));
	
	while (dberr == 0) {
		debugf("cursor got %s %d %s %d", key, klen, val, vlen);
		dberr = sleepywrap_cursor_next(sc, (void**)&key, &klen, &kalloc, (void**)&val, &vlen, &valloc );
	}
	assert(dberr == DB_NOTFOUND, sleepywrap_strerr(dberr));
	sleepywrap_cursor_close(sc);
	if (key) {
					free(key);
	}
	if (val) {
					free(val);
	}
	return;
}

void
test_put ()
{
  char key[KLEN];
  char val[VLEN];
  memset (key, 0, KLEN);
  memset (val, 0, VLEN);
  strncpy (key, "a", KLEN);
  strncpy (val, "one", VLEN);
	debugf("putrec %s:%s", key, val );
  if (sleepywrap_putrec (sw, key, KLEN, val, VLEN)) {
    fail ("putrec failed");
  }
  strncpy (key, "b", KLEN);
  strncpy (val, "two", VLEN);
	debugf("putrec %s:%s", key, val );
  if (sleepywrap_putrec (sw, key, KLEN, val, VLEN)) {
    fail ("putrec failed");
  }
}
int
main (int argc, char **argv)
{
  xmalloc_init();
	test_init();
	test_put();
	test_get();
	test_get_alloc();
	test_get_realloc();
	test_cursor();
	test_shutdown();
	return g_fail?1:0;
}

