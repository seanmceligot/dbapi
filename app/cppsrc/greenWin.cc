// generated 2003/5/16 19:31:57 EDT by sean@blue.localhost.(none)
// using glademm V1.1.0c
//
// newer (non customized) versions of this file go to greenWin.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "greenWin.hh"
#include <iostream>

void greenWin::on_quit_activate()
{  
}

gint greenWin::on_cmd_entry_key_release_event(GdkEventKey *ev)
{ 
	std::cout << "key press: "<< ev->string << std::endl;
	if (ev->keyval == '\t') {
		std::cout << "<tab>"<<std::endl;
		gtk_signal_emit_stop_by_name(ev->window, "insert_text");
		return 0;
	}
	return 0;
}
