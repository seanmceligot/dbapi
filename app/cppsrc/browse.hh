#ifndef __BROWSE_HH
#define __BROWSE_HH

#include "config.h"
#include "greenWin.hh"
#include <gtk--/clist.h>

size_t get_schema_size(const char* table_name);
void create_grid( Gtk::CList *grid, const char* table_name);
void browse( Gtk::CList *grid, const char* table_name);

#endif
