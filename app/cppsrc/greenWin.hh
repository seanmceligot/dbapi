// generated 2003/5/16 19:57:35 EDT by sean@blue.localhost.(none)
// using glademm V1.1.0c
//
// newer (non customized) versions of this file go to greenWin.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _GREENWIN_HH
#  include "greenWin_glade.hh"
#  define _GREENWIN_HH
class greenWin : public greenWin_glade
{  
        
        friend class greenWin_glade;
        void on_quit_activate();
        gint on_cmd_entry_key_release_event(GdkEventKey *ev);
};
#endif
