#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "sleepywrap/sleepywrap.h"
#include "libcutils/mybool.h"
#include "libcutils/debug.h"
#include "libcutils/xmalloc.h"

static int g_verbose_error = TRUE;
static int g_verbose_debug = TRUE;
static int g_verbose_fail = TRUE;
static int g_fail = FALSE;

#undef DB_LOGGING
#define DEFAULT_OPEN_FLAGS DB_CREATE|DB_INIT_MPOOL
//#define dberror(dberr) error(db_strerror(dberr) )
//#define dbcheck_return(dberr) if (dberr) { dberror (dberr); }
#define db_return_if_err(dberr) if (dberr) { return dberr; }

#define debug_dbt(msg, dbt) debugf("dbt %s size:%d ulen:%d flags:%d", msg, dbt.size, dbt.ulen, dbt.flags)
#define debug_dbt_str(msg, dbt) debugf("dbt %s (%s) size:%d ulen:%d flags:%d", msg, (char*)dbt.data, dbt.size, dbt.ulen, dbt.flags)

void
sleepywrap_setdebug (BOOL tf)
{
  g_verbose_debug = tf;
}

char *
sleepywrap_strerr (int dberr)
{
  return db_strerror (dberr);
}

void
sleepywrap_env_seterrfile (SleepyWrapEnv * se, FILE * file)
{
  se->env->set_errfile (se->env, file);
}

int
sleepywrap_env_open (const char *home, SleepyWrapEnv * se,
                     void *(*db_malloc) (size_t size),
                     void *(*db_realloc) (void *ptr, size_t size),
                     void (*db_free) (void *))
{
  int dberr;
  DB_ENV *env;
  int major;
  int minor;
  int patch;
  uint32_t flags;

  db_version (&major, &minor, &patch);
  debugf ("db version: %d %d %d", major, minor, patch);
  dberr = db_env_create (&env, 0);
  db_return_if_err (dberr);
  se->env = env;
  //dberr =env->set_cachesize (env, 0, 4 * 1024, 0644);
  //dbcheck_return(dberr);

  env->set_data_dir (env, home);
  db_return_if_err (dberr);

  env->set_lg_dir (env, home);
  db_return_if_err (dberr);

  sleepywrap_set_alloc (se, db_malloc, db_realloc, db_free);
  // DB_CREATE | DB_INIT_MPOOL | DB_PRIVATE | DB_INIT_TXN | DB_INIT_LOG | DB_RECOVER
  flags = DEFAULT_OPEN_FLAGS;
	if (home == NULL) {
		flags |= DB_USE_ENVIRON;
	}
  dberr = env->open (env, home, flags, 0);
  db_return_if_err (dberr);
  env->set_errfile (env, stderr);

  env->set_errpfx (env, "dberr:");

  se->home = strdup (home);
  return 0;
}

int
sleepywrap_env_close (SleepyWrapEnv * se)
{
  int dberr;
  DB_ENV *env = se->env;

  if (se != NULL) {
    if (env != NULL) {
#ifdef DB_LOGGING
      debug ("log flush");
      dberr = env->log_flush (env, 0);
      db_return_if_err (dberr);
#endif
      debug ("env close");
      dberr = env->close (env, 0);
      db_return_if_err (dberr);
      xfree (env);
      debugf ("env freed %p", env);
      env = NULL;
    }
  }
  if (se->home != NULL) {
    free (se->home);
    se->home = NULL;
  }
  return 0;
}

int
sleepywrap_startup ()
{
  debug ("startup");
  return 0;

}

int
sleepywrap_shutdown ()
{
  debug ("shutdown.");
  return 0;
}

SleepyWrap *
sleepywrap_new(char *filename, SleepyWrapEnv * senv)
{
  SleepyWrap *sw = xmalloc (sizeof (SleepyWrap));
  debugf ("sleepywrap_new_env %p", sw);
  sw->filename = xstrdup (filename);
  sw->senv = senv;
  assert (sw->filename != NULL, "filename is NULL");
  sw->db = NULL;
  sw->txn = NULL;
  return sw;
}
/*
SleepyWrap *
sleepywrap_new (char *filename)
{
  SleepyWrap *sw = xmalloc (sizeof (SleepyWrap));
  debugf ("sleepywrap_new %p", sw);
  sw->filename = xstrdup (filename);
  assert (sw->filename != NULL, "filename is NULL");
  sw->db = NULL;
  sw->txn = NULL;
  return sw;
}
*/
void
sleepywrap_free (SleepyWrap * sw)
{
  debugf ("sleepywrap_free %p", sw);
  if (sw->filename != NULL) {
    xfree (sw->filename);
    sw->filename = NULL;
  }
  if (sw != NULL) {
    xfree (sw);
  }
}
static DB_ENV *
sleepywrap_getdbenv (SleepyWrap * sw)
{
  if ((sw == NULL) || (sw->senv == NULL)) {
    return NULL;
  }
  return sw->senv->env;
}

int
sleepywrap_transaction_start (SleepyWrap * sw)
{
  int dberr =
    sleepywrap_getdbenv (sw)->txn_begin (sleepywrap_getdbenv (sw), NULL,
                                         &sw->txn, 0);
  return dberr;
}

int
sleepywrap_transaction_commit (SleepyWrap * sw)
{
  int dberr = 0;
  if (sw->txn != NULL) {
    dberr = sw->txn->commit (sw->txn, DB_TXN_SYNC);
    sw->txn = NULL;
  }
  return dberr;
}

int
sleepywrap_transaction_abort (SleepyWrap * sw)
{
  int dberr = 0;
  if (sw->txn != NULL) {
    dberr = sw->txn->abort (sw->txn);
    sw->txn = NULL;
  }
  return dberr;
}

int
sleepywrap_create (SleepyWrap * sw)
{
  int dberr;
  DB_ENV *env = sleepywrap_getdbenv (sw);
  dberr = db_create (&sw->db, env, 0);
  assert_notnull (env);
  assert_notnull (sw);
  assert_notnull (sw->db);
  db_return_if_err (dberr);
  sw->db->set_errfile (sw->db, stderr);
  sw->db->set_errpfx (sw->db, "error: ");
  //dberr = sw->db->set_pagesize (sw->db, 1024);

  return dberr;
}

int
sleepywrap_set_alloc (SleepyWrapEnv * se, void *(*db_malloc) (size_t size),
                      void *(*db_realloc) (void *ptr, size_t size),
                      void (*db_free) (void *))
{
  int dberr;

  //dberr =sw->db->set_realloc(sw->db, db_realloc);
  //db_return_if_err (dberr);
  dberr = se->env->set_alloc (se->env, db_malloc, db_realloc, db_free);
  return dberr;
}

int	sleepywrap_set_dup_compare(SleepyWrap *sw, int (*dup_compare_fn)(DB *, const DBT *, const DBT *)) {
	sw->db->set_flags(sw->db, DB_DUP|DB_DUPSORT);
	return sw->db->set_dup_compare(sw->db, dup_compare_fn);
}
int
sleepywrap_open (SleepyWrap * sw, DBTYPE type)
{
  int dberr;
  uint32_t flags;

  assert_notnull (sw->db);
  assert_notnull (sw->filename);

  flags = DEFAULT_OPEN_FLAGS;
  dberr = sw->db->open (sw->db, sw->filename, NULL, type, DB_CREATE, 0664);
  db_return_if_err (dberr);
  debugf ("%s opened", sw->filename);
  return 0;
}
/*
int sleepywrap_open_secondary(DB* secondary, DB* primary, DbCreateSecondaryFromPrimaryFunc callback, char* filename) {
 int dberr;
 dberr = secondary->set_flags(secondary, DB_DUP | DB_DUPSORT);
 dberr = secondary->open (secondary, filename, NULL, DB_BTREE, DB_CREATE, 0664);
 if (dberr != 0) {
  secondary->err(secondary, dberr, "%s:%d", __FILE__, __LINE__);
  return -1;
 }
 dberr = secondary->associate(primary, secondary, callback, 0);
 if (dberr != 0) {
  secondary->err(secondary, dberr, "%s:%d", __FILE__, __LINE__);
  return -1;
 }
 return SUCCESS;
}
*/
int
sleepywrap_remove (SleepyWrap * sw)
{
  int failed;
  failed = remove (sw->filename);
  debugf ("%s removed %d", sw->filename, failed);
  return failed;
}

int
sleepywrap_close (SleepyWrap * sw)
{
  if (sw->db != NULL) {
    if (sw->txn != NULL) {
      sleepywrap_transaction_commit (sw);
    }
    sw->db->sync (sw->db, 0);
    debug ("closing...");
    sw->db->sync (sw->db, 0);
    sw->db->close (sw->db, 0);
    sw->db = NULL;
    debug ("closed");
  }
  return 0;
}

int
sleepywrap_putrec (SleepyWrap * sw, const void *keybuf,
                   const uint32_t keylen,
                   const void *databuf, const uint32_t datalen)
{
  int dberr;
  DBT key, data;

  memset (&key, 0, sizeof (DBT));
  memset (&data, 0, sizeof (DBT));
  key.data = (void *) keybuf;
  key.size = keylen;
  data.data = (void *) databuf;
  data.size = datalen;
	
  debug_dbt_str ("put key", key);
  debug_dbt_str ("put data", data);
  dberr = sw->db->put (sw->db, sw->txn, &key, &data, 0);
  dberr = sw->db->sync (sw->db, 0);
  return dberr;
}
int
sleepywrap_getrec_realloc (SleepyWrap * sw, const void *keybuf,
                           const uint32_t keylen,
                           void **databuf, uint32_t * datalen,
                           uint32_t * allocated)
{
  DBT key, data;
  int dberr;

  memset (&key, 0, sizeof (DBT));
  memset (&data, 0, sizeof (DBT));
  key.data = (void *) keybuf;
  key.size = keylen;
  data.data = *databuf;
  data.ulen = *allocated;
  data.flags = DB_DBT_REALLOC;
  debugf ("realloc ulen %d\n", data.ulen);
  dberr = sw->db->get (sw->db, sw->txn, &key, &data, 0);
  db_return_if_err (dberr);
  *databuf = data.data;
  if (data.size > *allocated) {
    *allocated = data.size;
  }
  *datalen = data.size;
  return 0;
}

int
sleepywrap_getrec_varlen (SleepyWrap * sw, const void *keybuf,
                          const uint32_t keylen,
                          void **databuf, uint32_t * datalen,
                          uint32_t * allocated)
{
  int dberr;
  if (*allocated == 0) {
    dberr = sleepywrap_getrec_alloc (sw, keybuf, keylen, databuf, allocated);
    *datalen = *allocated;
    return dberr;
  } else {
    return sleepywrap_getrec_realloc (sw, keybuf, keylen, databuf, datalen,
                                      allocated);
  }
}
int
sleepywrap_getrec_alloc (SleepyWrap * sw, const void *keybuf,
                         const uint32_t keylen,
                         void **databuf, uint32_t * datalen)
{
  DBT key, data;
  int dberr;

  memset (&key, 0, sizeof (DBT));
  memset (&data, 0, sizeof (DBT));
  key.data = (void *) keybuf;
  key.size = keylen;
  data.ulen = 0;
  data.flags = DB_DBT_MALLOC;
  debugf ("alloc ulen %d\n", data.ulen);
  dberr = sw->db->get (sw->db, sw->txn, &key, &data, 0);
  db_return_if_err (dberr);
  *databuf = data.data;
  *datalen = data.size;
  return 0;
}

int
sleepywrap_getrec_size (SleepyWrap * sw, const void *keybuf,
                        const uint32_t keylen, uint32_t * size)
{
  DBT key, data;
  int dberr;

  memset (&key, 0, sizeof (DBT));
  key.data = (void *) keybuf;
  key.size = keylen;

  memset (&data, 0, sizeof (DBT));
  data.ulen = 0;
  data.flags = DB_DBT_USERMEM;

  dberr = sw->db->get (sw->db, sw->txn, &key, &data, 0);
  if ((dberr == ENOMEM) || (dberr == 0)) {
    *size = data.size;
    return 0;
  }
  return dberr;
}

BOOL
sleepywrap_haskey (SleepyWrap * sw, const void *keybuf, const uint32_t keylen)
{
  int dberr;
  uint32_t size;

  dberr = sleepywrap_getrec_size (sw, keybuf, keylen, &size);
  if (dberr == 0) {
    return TRUE;
  }
  return FALSE;
}

/*
 * keylen and datalen are not read, just written
 * if *keybuf is NULL and *kalloc is 0, keybuf will be allocated
 * if *databuf is NULL and *dalloc is 0, databuf will be allocated
 * if *keybuf will be reallocated if the record size is > kalloc
 * if *databuf will be reallocated if the record size is > dalloc
 */
int
sleepywrap_getrec (SleepyWrap * sw, const void *keybuf,
                   const uint32_t keylen, void *databuf, uint32_t datalen)
{
  DBT key, data;
  int dberr;

  memset (&key, 0, sizeof (DBT));
  memset (&data, 0, sizeof (DBT));
  key.data = (void *) keybuf;
  key.size = keylen;
  data.data = databuf;
  data.size = datalen;
  data.ulen = datalen;
  data.flags = DB_DBT_USERMEM;
  dberr = sw->db->get (sw->db, sw->txn, &key, &data, 0);
  return dberr;
}

/*
 * keylen and datalen are not read, just written
 * if *keybuf is NULL and *kalloc is 0, keybuf will be allocated
 * if *databuf is NULL and *dalloc is 0, databuf will be allocated
 * if *keybuf will be reallocated if the record size is > kalloc
 * if *databuf will be reallocated if the record size is > dalloc
 */
int
sleepywrap_cursor_new (SleepyWrap * sw, SleepyWrapCursor * sc)
{
  int dberr;
  DBC *cursor;

  dberr = sw->db->cursor (sw->db, 0, &cursor, 0);
  db_return_if_err (dberr);
  sc->cursor = cursor;
  sc->sw = sw;
  memset (&sc->key, 0, sizeof (DBT));
  memset (&sc->data, 0, sizeof (DBT));
  return dberr;
}

/*
void dbt_init_alloc(DBT* dbt) {
  dbt->ulen = 0;
  dbt->flags = DB_DBT_USERMEM;
}
int dbt_needs_realloc(DBT dbt, int dberr) {
		if (dbt->flags == DB_DBT_REALLOC) {
				// realloc was called so set ulen accordingly
				dbt->ulen = dbt->size;
				// don't realloc a second time
  			dbt->flags = DB_DBT_USERMEM;
				return FALSE;
		}
    if (dberr == ENOMEM) {
      if (dbt->size > dbt->ulen) {
        // set key size
        dbt->ulen = *kalloc;
        if (dbt->size > *kalloc) {
          dbt->flags = DB_DBT_REALLOC;
        }
			}
}
*/
/*
 * keylen and datalen are not read, just written
 * if *keybuf is NULL and *kalloc is 0, keybuf will be allocated
 * if *databuf is NULL and *dalloc is 0, databuf will be allocated
 * if *keybuf will be reallocated if the record size is > kalloc
 * if *databuf will be reallocated if the record size is > dalloc
 */
int
sleepywrap_cursor_get_flag (SleepyWrapCursor * sc,
                            void **keybuf, uint32_t * keylen,
                            uint32_t * kalloc,
                            void **databuf, uint32_t * datalen,
                            uint32_t * dalloc, uint32_t flags)
{
  int dberr;
  debugf ("cursor get key %p val %p", *keybuf, *databuf);

  sc->key.data = *keybuf;
  sc->data.data = *databuf;

  sc->key.flags = DB_DBT_USERMEM;
  sc->data.flags = DB_DBT_USERMEM;
  sc->key.ulen = *kalloc;
  sc->data.ulen = *dalloc;
	
	//bzero(*databuf, *dalloc);
	sc->data.size = 0;
	sc->key.size = 0;

  do {
    // get key or data size
    debug_dbt_str ("before get size key", sc->key);
    debug_dbt_str ("before get size data", sc->data);
    dberr = sc->cursor->c_get (sc->cursor, &sc->key, &sc->data, flags);
    debug_dbt_str ("after get size key", sc->key);
    debug_dbt_str ("after get size data", sc->data);

    if (dberr == ENOMEM) {
      if (sc->key.flags == DB_DBT_REALLOC) {
        // don't realloc a second time
        sc->key.ulen = sc->key.size;
        sc->key.flags = DB_DBT_USERMEM;
      } else if (sc->key.size > sc->key.ulen) {
        debugf ("reallocating key %d", sc->key.size);
        // set key size
        if (sc->key.size > *kalloc) {
          sc->key.flags = DB_DBT_REALLOC;
        }
      }
      if (sc->data.flags == DB_DBT_REALLOC) {
        // don't realloc a second time
        sc->data.ulen = sc->data.size;
        sc->data.flags = DB_DBT_USERMEM;
      } else if (sc->data.size > sc->data.ulen) {
        debugf ("reallocating data %d", sc->data.size);
        // set data size
        if (sc->data.size > *dalloc) {
          sc->data.flags = DB_DBT_REALLOC;
        }
      }
		}
  } while (dberr == ENOMEM);

  db_return_if_err (dberr);

  // return key
  *keybuf = sc->key.data;
  if (sc->key.size > *kalloc) {
    *kalloc = sc->key.size;
  }
  *keylen = sc->key.size;

  // return data
  *databuf = sc->data.data;
  if (sc->data.size > *dalloc) {
    *dalloc = sc->data.size;
  }
  *datalen = sc->data.size;
  return 0;
}

int
sleepywrap_cursor_first (SleepyWrapCursor * sc,
                         void **keybuf,
                         uint32_t * keylen,
                         uint32_t * kalloc,
                         void **databuf,
                         uint32_t * datalen, uint32_t * dalloc)
{
  return sleepywrap_cursor_get_flag (sc,
                                     keybuf, keylen, kalloc,
                                     databuf, datalen, dalloc, DB_FIRST);
}

/*
 * keylen and datalen are not read, just written
 * if *keybuf is NULL and *kalloc is 0, keybuf will be allocated
 * if *databuf is NULL and *dalloc is 0, databuf will be allocated
 * if *keybuf will be reallocated if the record size is > kalloc
 * if *databuf will be reallocated if the record size is > dalloc
 */
int
sleepywrap_cursor_find(SleepyWrapCursor * sc,
                            void **keybuf, uint32_t * keylen,
                            uint32_t * kalloc,
                            void **databuf, uint32_t * datalen,
                            uint32_t * dalloc) {
  int dberr;
  debugf ("cursor get key %p val %p", *keybuf, *databuf);

  sc->key.data = *keybuf;
  sc->data.data = *databuf;

  sc->key.flags = DB_DBT_USERMEM;
  //sc->data.ulen = 0;
  sc->data.flags = DB_DBT_USERMEM;
  sc->key.ulen = *kalloc;
  sc->data.ulen = *dalloc;
  sc->key.size = *keylen;
  sc->data.size = *datalen;
  do {
    // get key or data size
    debug_dbt ("before find key", sc->key);
    debug_dbt ("before find data", sc->data);
    dberr = sc->cursor->c_get (sc->cursor, &sc->key, &sc->data, DB_SET);
    debug_dbt_str ("after find key", sc->key);
    debug_dbt_str ("after find data", sc->data);
    if (dberr == ENOMEM) {
      if (sc->key.flags == DB_DBT_REALLOC) {
        // don't realloc a second time
        sc->key.ulen = sc->key.size;
        sc->key.flags = DB_DBT_USERMEM;
      } else if (sc->key.size > sc->key.ulen) {
        debugf ("reallocating key %d", sc->key.size);
        // set key size
        if (sc->key.size > *kalloc) {
          sc->key.flags = DB_DBT_REALLOC;
        }
      }
      if (sc->data.flags == DB_DBT_REALLOC) {
        // don't realloc a second time
        sc->data.ulen = sc->data.size;
        sc->data.flags = DB_DBT_USERMEM;
      } else if (sc->data.size > sc->data.ulen) {
        debugf ("reallocating data %d", sc->data.size);
        // set data size
        if (sc->data.size > *dalloc) {
          sc->data.flags = DB_DBT_REALLOC;
        }
      }
		}
  } while (dberr == ENOMEM);
 
  if (dberr == ENOMEM) {
					dberr = 0;
	}
  db_return_if_err (dberr);

  // return key
  *keybuf = sc->key.data;
  if (sc->key.size > *kalloc) {
    *kalloc = sc->key.size;
  }
  *keylen = sc->key.size;

  // return data
  *databuf = sc->data.data;
  if (sc->data.size > *dalloc) {
    *dalloc = sc->data.size;
  }
  *datalen = sc->data.size;
  return 0;
}

int
sleepywrap_cursor_next (SleepyWrapCursor * sc,
                        void **keybuf,
                        uint32_t * keylen,
                        uint32_t * kalloc,
                        void **databuf, uint32_t * datalen, uint32_t * dalloc)
{

  return sleepywrap_cursor_get_flag (sc,
                                     keybuf, keylen, kalloc,
                                     databuf, datalen, dalloc, DB_NEXT);
}

int
sleepywrap_cursor_next_samekey (SleepyWrapCursor * sc,
                        void **keybuf,
                        uint32_t * keylen,
                        uint32_t * kalloc,
                        void **databuf, uint32_t * datalen, uint32_t * dalloc)
{

  return sleepywrap_cursor_get_flag (sc,
                                     keybuf, keylen, kalloc,
                                     databuf, datalen, dalloc, DB_NEXT_DUP);
}

int
sleepywrap_cursor_current(SleepyWrapCursor * sc,
                        void **keybuf,
                        uint32_t * keylen,
                        uint32_t * kalloc,
                        void **databuf, uint32_t * datalen, uint32_t * dalloc)
{
  int dberr;
  debugf ("cursor get key %p val %p", *keybuf, *databuf);

  //sc->key.data = *keybuf;
  //sc->data.data = *databuf;

  //sc->key.flags = DB_DBT_USERMEM;
  //sc->data.ulen = 0;
  //sc->data.flags = DB_DBT_USERMEM;
  //sc->key.ulen = *kalloc;
  //sc->data.ulen = *dalloc;
  do {
    // get key or data size
    debug_dbt ("before get size key", sc->key);
    debug_dbt ("before get size data", sc->data);
    dberr = sc->cursor->c_get (sc->cursor, &sc->key, &sc->data, DB_CURRENT);
    debug_dbt_str ("after get size key", sc->key);
    debug_dbt_str ("after get size data", sc->data);

    if (dberr == ENOMEM) {
      if (sc->key.flags == DB_DBT_REALLOC) {
        // don't realloc a second time
        sc->key.ulen = sc->key.size;
        sc->key.flags = DB_DBT_USERMEM;
      } else if (sc->key.size > sc->key.ulen) {
        debugf ("reallocating key %d", sc->key.size);
        // set key size
        if (sc->key.size > *kalloc) {
          sc->key.flags = DB_DBT_REALLOC;
        }
      }
      if (sc->data.flags == DB_DBT_REALLOC) {
        // don't realloc a second time
        sc->data.ulen = sc->data.size;
        sc->data.flags = DB_DBT_USERMEM;
      } else if (sc->data.size > sc->data.ulen) {
        debugf ("reallocating data %d", sc->data.size);
        // set data size
        if (sc->data.size > *dalloc) {
          sc->data.flags = DB_DBT_REALLOC;
        }
      }
		}
  } while (dberr == ENOMEM);

  db_return_if_err (dberr);

  // return key
  *keybuf = sc->key.data;
  if (sc->key.size > *kalloc) {
    *kalloc = sc->key.size;
  }
  *keylen = sc->key.size;

  // return data
  *databuf = sc->data.data;
  if (sc->data.size > *dalloc) {
    *dalloc = sc->data.size;
  }
  *datalen = sc->data.size;
  return 0;

}


/* set keybuf to NULL or it will be used
  */
int
sleepywrap_cursor_next_equals (SleepyWrapCursor * sc,
                               void *keybuf,
                               const int keylen,
                               void *databuf,
                               const int datalen,
                               const SleepyWrapCompareFunc
                               compare, const BOOL forward)
{
  DBT key, data;
  int dberr;
  const int dbnext = forward ? DB_NEXT : DB_PREV;

  memset (&key, 0, sizeof (DBT));
  memset (&data, 0, sizeof (DBT));
  key.data = keybuf;
  key.size = keylen;
  data.data = databuf;
  data.size = datalen;
  dberr = sc->cursor->c_get (sc->cursor, &key, &data, dbnext);
  db_return_if_err (dberr);
  if (memcmp (key.data, keybuf, key.size) != 0) {
    debugf ("key (%s) != (%s)", (char *) key.data, (char *) keybuf);
    return DB_NOTFOUND;
  }
  /*if (compare) {
     if (forward) {
     if (compare (keybuf, endkey) > 0) {
     return FALSE;
     }
     } else {
     if (compare (keybuf, endkey) < 0) {
     return FALSE;
     }
     }
     } */
  return 0;
}

void
sleepywrap_cursor_close (SleepyWrapCursor * sc)
{
  sc->cursor->c_close (sc->cursor);
  xfree (sc);
}

void
sleepywrap_getrecs_start (SleepyWrap * sw,
                          const void *startkey,
                          const int keylen,
                          const int datalen, const int count, BOOL forward)
{
  /*  if (startkey != NULL) {
     dberr = sc->c_get (sc, &key, &data, DB_SET);
     } */
  ;
}
