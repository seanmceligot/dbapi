// generated 2003/5/15 22:38:38 EDT by sean@blue.localhost.(none)
// using glademm V1.1.0c
//
// newer (non customized) versions of this file go to greenapp.cc_new

// This file is for your program, I won't touch it again!

#include <gtk--/main.h>

#include "greenWin.hh"

int main(int argc, char **argv)
{  
   
   Gtk::Main m(&argc, &argv);
manage(new class greenWin());
   m.run();
   return 0;
}
