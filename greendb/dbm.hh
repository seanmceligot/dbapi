
#ifndef DBM_HH
#define DBM_HH

#include "greendb/datum.hh"
#include "greendb/greendb.hh"
#include "greendb/table.hh"
#include <hash_map>

class Dbm {
	GreenDb* _column_db;
public:
	GreenDb* getColumnDb();
}
#endif

