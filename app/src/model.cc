#include "model.hh"

Model ::Model () : _table(NULL) {
  _env = new GreenEnv(".");
  _env->open();
}
Model::~Model () {
  if (_table != NULL) {
    _table->close();
  }
  _env->close();
}
void Model::load_table(const char* table_name) {
  if (_table != NULL) {
    _table->close();
  }
  _table = new Table(table_name, *_env);
  //close_browser();
}
Table* Model::get_table() {
  return _table;
}

/*
void Model::show_browser() {
  if (_browser == NULL) {
    _browser = new Browser(_table->get_schema());
  }
  _browser->populate_grid(_table);
  _app->set_frame_widget(_grid);
}
void Model::close_browser() {
  if (_browser != NULL) {
    delete _browser;
    _browser = NULL;
  }
}
*/
