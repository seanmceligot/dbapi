#ifndef _FRAME_HH
#define _FRAME_HH

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
#include "appmem.hh"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "support.hh"
#include "model.hh"
#include "view.hh"
#include <stack>

class Frame {
  typedef std::stack<View*> ViewStack;
  ViewStack _views;
  GtkWidget *_frame;
  Model* _model;
public:
  Frame(GtkWidget* frame);
  GtkWidget* get_frame_widget();
  void push_view(View* view);
  void pop_view(View* view);
  View* current_view();
  Model* get_model();

};

#endif
