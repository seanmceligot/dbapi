#ifndef __EDIT_HH
#define __EDIT_HH

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
#include "appmem.hh"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include "view.hh"
#include "widgets.hh"
#include "greendb/schema.hh"
#include "greendb/table.hh"
#include "greendb/row.hh"

class EditView : public View {
  GtkWidget* _widget;
  NameValueBox** _columns;
public:
  EditView(Model* model);
  GtkWidget* get_widget();
  void open(Frame* frame);
  void close();
  NameValueBox* get_column(int i);
};

#endif
