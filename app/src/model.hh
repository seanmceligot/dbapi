#ifndef __MODEL_HH
#define __MODEL_HH

#include "appmem.hh"
#include "greendb/greenenv.hh"
#include "greendb/table.hh"


class Model {
 GreenEnv* _env;
 Table* _table;
public:
 Model();
 ~Model();
 void load_table(const char* table_name);
 Table* get_table();
};

#endif
