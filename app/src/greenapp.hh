#ifndef _GREENAPP_HH
#define _GREENAPP_HH

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
#include "frame.hh"

class GreenApp {
  GtkWidget *greenWin;
  GtkWidget *vbox;
  GtkWidget *menubar1;
  GtkWidget *file;
  GtkWidget *file_menu;
  GtkAccelGroup *file_menu_accels;
  GtkWidget *quit;
  GtkWidget *cmd_entry;
  GtkWidget *status_bar;
  Frame* _frame;
public:
  void create();
  void show();
  void main();
  GtkWidget *get_status_bar() { return status_bar;};
  void set_frame_widget(GtkWidget* widget);
private:
  void create_menus();
};

#endif
