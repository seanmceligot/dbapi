#ifndef __SIMPLE_HH
#define __SIMPLE_HH

#include "greendb/greenenv.hh"
#include "greendb/debug.hh"
#include "greendb/table.hh"
#include "greendb/schema.hh"
#include "greendb/typemap.hh"
#include "greendb/row.hh"
#include <malloc.h>

class SimpleInterface {
  GreenEnv _env;
  Table* _table;
  Row* _row;
public:
  SimpleInterface(const char* home);
  void open_table(const char* table_name);
  Table* get_table();
  Row* get_row();
}

#endif
