#ifndef __CALLBACKS_HH
#define __CALLBACKS_HH

#include "appmem.hh"
#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "greenapp.hh"
#include "util.hh"

void
on_quit_activate (GtkMenuItem * menuitem, gpointer user_data);

void
on_cmd_entry_insert_text (GtkEditable * editable,
   gchar * new_text,
   gint new_text_length,
   gint * position, gpointer user_data);

void
on_cmd_entry_activate_text (GtkEditable * editable, gpointer user_data);

gboolean on_cmd_entry_key_release(GtkWidget* widget, GdkEventKey* event, gpointer user_data);

struct Callback {
  virtual void operator() (Frame* frame, const char* args) = 0;
};

//typedef std::hash_map <const char *, Callback* > CallbackMapT;
class Callbacks {
	typedef std::map < const char *, Callback*,ltstr > CallbackMap;
  //typedef std::hash_map <const char *, Callback* > CallbackMap;
  CallbackMap _actions;
  static Callbacks* _instance;
public:
  Callbacks();
  Callback* lookup(const char* text);
  void add_action(const char* name, Callback* action);
  static Callbacks* get_instance();
};

#endif
