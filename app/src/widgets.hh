#ifndef _WIDGETS_HH
#define _WIDGETS_HH

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

#include "callbacks.hh"
#include "support.hh"
#include "util.hh"
#include <map>

class NameValueBox {
  GtkWidget* _box;
  GtkWidget* _label;
  GtkWidget* _entry;
public:
  NameValueBox(const char* label);
  GtkWidget* get_box() { return _box;}
  GtkWidget* get_label(){ return _label;}
  GtkWidget* get_entry(){ return _entry;}
  void show();
  void pack();
};
//typedef std::map < const char *, NameValueBox* ,ltstr > NameValueBoxMap;
typedef std::map < const char *, GtkWidget* ,ltstr > WidgetMap;
//typedef std::map < const char *, GtkEntry* ,ltstr > EntryMap;

#endif
