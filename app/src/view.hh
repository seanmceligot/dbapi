#ifndef __VIEW_HH
#define __VIEW_HH

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
#include "appmem.hh"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "model.hh"

class Frame;
// TODO: create a Frame class with push and pop and store in view
class View {
  const char* _title;
  Model* _model;
public:
  View(const char* title, Model* model);
  Model* get_model(); 
  const char* get_title();
  virtual GtkWidget* get_widget() = 0;
  virtual void open(Frame* frame) = 0;
  virtual void close() = 0;
};

#endif
