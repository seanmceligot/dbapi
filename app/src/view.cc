#include "view.hh"
#include "frame.hh"

View::View(const char* title, Model* model):_title(title), _model(model) {
}
Model* View::get_model() {
  return _model;
}
const char* View::get_title() {
  return _title;
}

