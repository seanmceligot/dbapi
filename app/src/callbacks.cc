#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.hh"
#include "support.hh"
#include "greendb/debug.hh"
#include <iostream>
#include <cctype>
#include "complete.hh"
#include "browse.hh"

Callbacks* Callbacks::_instance = NULL;

Callbacks::Callbacks()  {
}

Callbacks* Callbacks::get_instance() {
  if (_instance == NULL) {
    _instance = new Callbacks();
  }
  return _instance;
}

void Callbacks::add_action(const char* name, Callback* action) {
  _actions[name] = action;
}

Callback* Callbacks::lookup(const char* name) {
  return _actions[name];
}



void
on_quit_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  gtk_exit(0);
}

gboolean
on_cmd_entry_key_release(GtkWidget* widget, GdkEventKey* event, gpointer user_data)
{
	//gtk_signal_emit_stop_by_name(GTK_OBJECT(widget), "insert_text");
  //return FALSE;
  return TRUE;
}

void
on_cmd_entry_insert_text (GtkEditable * editable, gchar * new_text,
                          gint new_text_length, gint * position,
                          gpointer user_data)
{
  std::cout << "insert: ";
  for (int i = 0; i < new_text_length; i++) {
    gchar ch = new_text[i];
    if (ch == '\t') {
      std::cout << "<TAB>";
      std::cout << Completions::get_instance ()->
        complete (gtk_entry_get_text (GTK_ENTRY (editable))) << std::endl;
      gtk_signal_emit_stop_by_name (GTK_OBJECT (editable), "insert_text");
    } else if (ch == '\n') {
      std::cout << "<NEWLINE>";
      std::cout << Completions::get_instance ()->
        complete (gtk_entry_get_text (GTK_ENTRY (editable)));
    } else {
      if (isalnum (ch)) {
        std::cout << ch;
      } else {
        std::cout << '<' << (int) ch << '>';
      }
    }
  }
  std::cout << std::endl;
}
void on_cmd_entry_activate_text (GtkEditable *editable, gpointer user_data)
{
  Frame* frame = (Frame*)user_data;
  char* text = gtk_entry_get_text(GTK_ENTRY(editable));
  std::cout<<"activate: "<< text<<std::endl;
  const char* cmd = Completions::get_instance()->complete(text);
  std::cout<<"complete returned: "<<cmd<<std::endl;
  if (cmd) {
	  const char* args = next_word(text);
	  std::cout<<"args: "<<args<<std::endl;
    Callback* callback = Callbacks::get_instance()->lookup(cmd);
		std::cout<<"callback: "<<(void*)callback<<std::endl;
    if (callback) {
      (*callback)(frame, args);
    }
  }
}

