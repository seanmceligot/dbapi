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

#define KLEN 2
#define VLEN 2
#define SLEN 2
typedef struct _Record Record;
struct _Record {
		char data[VLEN];
		char sort[SLEN];
};

int sortby_rec(DB* db, const DBT* first, const DBT* second) {
	Record* rec1 = (Record*)first->data;
	Record* rec2 = (Record*)second->data;
	char* sort1 = rec1->sort;
	char* sort2 = rec2->sort;
	int ret = strcmp(rec1->sort, rec2->sort);
	debugf("sort %s %s returning %d", sort1, sort2, ret);
	return ret;
}

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
	sw = sleepywrap_new("sort.db", &env);
  if (sleepywrap_create(sw)) {
    fail ("open failed");
  }
	sleepywrap_set_dup_compare(sw, sortby_rec);
  if (sleepywrap_open (sw, DB_BTREE)) {
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
void test_cursor() {
	int dberr;
  char *key;
  Record* rec = malloc(sizeof(Record));
	uint32_t kalloc = 2;
	uint32_t valloc = sizeof(Record);
	uint32_t klen = 2;
	uint32_t vlen = sizeof(Record);

	key = strdup("b");
	
	SleepyWrapCursor* sc = malloc(sizeof (SleepyWrapCursor));
	dberr = sleepywrap_cursor_new(sw, sc); 
	debugf("cursor %p", sc);
	assert(dberr ==0, sleepywrap_strerr(dberr));

	dberr = sleepywrap_cursor_find(sc, (void**)&key, &klen, &kalloc, (void**)&rec, &vlen, &valloc);
	assert(dberr ==0, sleepywrap_strerr(dberr));
	//dberr = sleepywrap_cursor_current(sc, (void**)&key, &klen, &kalloc, (void**)&rec, &vlen, &valloc);
	
	while (dberr == 0) {
		debugf("cursor got %s %s (sort)%s", key, rec->data, rec->sort);
		dberr = sleepywrap_cursor_next_samekey(sc, (void**)&key, &klen, &kalloc, (void**)&rec, &vlen, &valloc );
	}
	assert(dberr == DB_NOTFOUND, sleepywrap_strerr(dberr));
	sleepywrap_cursor_close(sc);
	if (key) {
					free(key);
	}
	if (rec) {
					free(rec);
	}
	return;
}
void put(char* key, char* val, char* sort) {
	Record rec;
	bzero(&rec, sizeof(rec));
	strncpy(rec.data, val, VLEN);
	strncpy(rec.sort, sort, SLEN);
	debugf("putrec %s:%s:%s", key, val, sort);
  if (sleepywrap_putrec(sw, key, KLEN, &rec, sizeof(Record))) {
    fail ("putrec failed");
  }

}
void
test_put ()
{
	put("z", "z", "z");
	put("b", "a", "b");
	put("b", "b", "c");
	put("b", "c", "a");
	put("a", "a", "a");
}
int
main (int argc, char **argv)
{
  xmalloc_init();
	test_init();
	test_put();
	test_cursor();
	test_shutdown();
	return g_fail?1:0;
}

