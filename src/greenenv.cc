#include "greendb/greenenv.hh"
#include "greendb/debug.hh"
#include "greendb/memory.hh"
#include <stdlib.h>
//#include <stdint.h>
//#include <dirent.h>
//#include <sys/stat.h>
#include <string.h>
//#include "mcheck.h"

GreenEnv::GreenEnv (const char *home):DbEnv (0),_home(home)
{
  //g_message( "Env %s" , _home.c_str());
	// TODO: only run once
  //mtrace();
}

#define DEFAULT_OPEN_FLAGS DB_CREATE|DB_INIT_MPOOL
//GreenEnv::open (void *(*db_malloc) (size_t size), void *(*db_realloc) (void *ptr, size_t size), void (*db_free) (void *), char *home = "~/.db")
void
  GreenEnv::open ()
{
  int dberr;
  u_int32_t flags;
	const char* home = _home.size()?_home.c_str():NULL;


  {                             // print libdb version
    int
      major;
    int
      minor;
    int
      patch;
    //version (&major, &minor, &patch);
    //g_message( "db version: %d %d %d" , major, minor , patch );
  }
  if (home) {
		// create home
    //DIR * dir = opendir (home);
    //if (dir) {
    //  closedir (dir);
    //} else {
    //  mkdir (home, 0x600);
    //}
  	set_data_dir (home);

  	//set_lg_dir (home);
  }
  //dberr =env->set_cachesize (env, 0, 4 * 1024, 0644);
  //dbcheck_return(dberr);


  //set_alloc (db_malloc, db_realloc, db_free);
  // DB_CREATE | DB_INIT_MPOOL | DB_PRIVATE | DB_INIT_TXN | DB_INIT_LOG | DB_RECOVER
  flags = DEFAULT_OPEN_FLAGS;
  if (!home) {
    flags |= DB_USE_ENVIRON;
  }
	// this is 4.x specific
  // we'll do without for now
  // DbEnv::set_alloc(greendb_malloc,greendb_realloc,greendb_free);
  dberr = DbEnv::open (home, flags, 0);
  //set_errfile (stderr);

  //set_errpfx ("dberr:");

}

void
  GreenEnv::close ()
{
  DbEnv::close (0);
}
