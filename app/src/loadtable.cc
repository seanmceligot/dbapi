#include "loadtable.hh"

LoadTable::handle(Model* model, StrQueue* args) {
  model->load_tables(args->front());
}
