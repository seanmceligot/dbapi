#ifndef __BROWSE_HH
#define __BROWSE_HH

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
#include "greendb/schema.hh"
#include "greendb/table.hh"
#include "greendb/row.hh"
#include "view.hh"

class Browser: public View {
  GtkWidget* _grid;
public:
  Browser(Model* model);
  void populate_grid(Table * table, const char* key, CursorRow* row = NULL);
  GtkWidget* get_widget();
  void open(Frame* frame);
  void close();
private:
  void create_grid(size_t column_count);
  void create_grid_titles(Schema* schema);
};

#endif
