#ifndef __GREENDB_HH
#define __GREENDB_HH

#include <db_cxx.h>
#include "greendb/datum.hh"
#include "greendb/cursor.hh"
#include "greendb/greenenv.hh"
#include <string>

//bool sleepywrap_getrec(GreenDb* db, DynamicDatum* key, DynamicDatum* value) throw(GreenException);
//bool sleepywrap_getrec(GreenDb* db, StaticDatum* key, StaticDatum* value) throw(GreenException);

class GreenDb:protected Db {
  const std::string _name;
  const std::string _dbfile;
  DbTxn *_txn;
public:
  //GreenDb (DbEnv * env, const char *dbfile);
  GreenDb (GreenEnv * env, const char *dbfile, const char *name);
  ~GreenDb ();
	void open_unknown(bool create=true);
	void open_queue(bool create=true);
	void open_recno(bool create=true);
	void open_hash(bool create=true);
	void open_btree(bool create=true);
  Cursor *cursor ();
  void open (int type, u_int32_t flags, int mode);
//  void open (DBTYPE type = DB_BTREE, u_int32_t flags = DB_CREATE, int mode = 0644);
  const char *dbfile () const;
  const char *name () const;
  void put (Datum & key, Datum & val);
  int fetch (Datum & key, Datum & val);
  void close ();
};

std::ostream & operator << (std::ostream & os, const GreenDb & db);
std::ostream & operator << (std::ostream & os, const GreenDb * db);

#endif
