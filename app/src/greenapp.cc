#include "greenapp.hh"
#include "callbacks.hh"
#include "browse.hh"

struct LoadTable: public Callback {
    void operator()(Frame* frame, const char* args) {
      frame->get_model()->load_table(args);
      if (!frame->get_model()->get_table()->exists()) {
        return;
      }
std::cout<<__FILE__<<":"<<__LINE__<<std::endl;
      Browser* browser = new Browser(frame->get_model());
std::cout<<__FILE__<<":"<<__LINE__<<std::endl;
      frame->push_view(browser);
			std::cout<<"leaving load-table operator() "<<args<<std::endl;
    }
};

void GreenApp::show() {
  gtk_widget_show (greenWin);
  gtk_widget_grab_focus(cmd_entry);
}
void GreenApp::main() {
  gtk_main ();
}
void GreenApp::create()
{
  greenWin = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_object_set_data (GTK_OBJECT (greenWin), "greenWin", greenWin);
  gtk_window_set_title (GTK_WINDOW (greenWin), _("Green App"));
  gtk_window_set_policy (GTK_WINDOW (greenWin), TRUE, TRUE, FALSE);

  vbox = gtk_vbox_new (FALSE, 0);
  gtk_widget_ref (vbox);
  gtk_object_set_data_full (GTK_OBJECT (greenWin), "vbox", vbox,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (vbox);
  gtk_container_add (GTK_CONTAINER (greenWin), vbox);
  create_menus();
  GtkWidget* frame = gtk_frame_new (NULL);
  gtk_widget_ref (frame);
  assert(frame);
  gtk_object_set_data_full (GTK_OBJECT (greenWin), "frame", frame,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (frame);
  gtk_box_pack_start (GTK_BOX (vbox), frame, TRUE, TRUE, 0);
  _frame = new Frame(frame);
  cmd_entry = gtk_entry_new ();
  gtk_widget_ref (cmd_entry);
  gtk_object_set_data_full (GTK_OBJECT (greenWin), "cmd_entry", cmd_entry,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (cmd_entry);
  gtk_box_pack_start (GTK_BOX (vbox), cmd_entry, FALSE, FALSE, 0);

  status_bar = gtk_statusbar_new ();
  gtk_widget_ref (status_bar);
  gtk_object_set_data_full (GTK_OBJECT (greenWin), "status_bar", status_bar,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (status_bar);
  gtk_box_pack_start (GTK_BOX (vbox), status_bar, FALSE, FALSE, 0);

  Callbacks::get_instance()->add_action("load-table", new LoadTable());
  gtk_signal_connect (GTK_OBJECT (quit), "activate",
                      GTK_SIGNAL_FUNC (on_quit_activate),
                      this);
  gtk_signal_connect (GTK_OBJECT (cmd_entry), "insert_text",
                      GTK_SIGNAL_FUNC (on_cmd_entry_insert_text), _frame);
  gtk_signal_connect (GTK_OBJECT (cmd_entry), "activate",
                      GTK_SIGNAL_FUNC (on_cmd_entry_activate_text),
                      _frame);
  gtk_signal_connect (GTK_OBJECT (cmd_entry), "key_release",
                      GTK_SIGNAL_FUNC (on_cmd_entry_key_release),
                      _frame);
}
void GreenApp::create_menus() {
  menubar1 = gtk_menu_bar_new ();
  gtk_widget_ref (menubar1);
  gtk_object_set_data_full (GTK_OBJECT (greenWin), "menubar1", menubar1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (menubar1);
  gtk_box_pack_start (GTK_BOX (vbox), menubar1, FALSE, FALSE, 0);

  file = gtk_menu_item_new_with_label (_("File"));
  gtk_widget_ref (file);
  gtk_object_set_data_full (GTK_OBJECT (greenWin), "file", file,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (file);
  gtk_container_add (GTK_CONTAINER (menubar1), file);

  file_menu = gtk_menu_new ();
  gtk_widget_ref (file_menu);
  gtk_object_set_data_full (GTK_OBJECT (greenWin), "file_menu", file_menu,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (file), file_menu);
  file_menu_accels = gtk_menu_ensure_uline_accel_group (GTK_MENU (file_menu));

  quit = gtk_menu_item_new_with_label (_("Quit"));
  gtk_widget_ref (quit);
  gtk_object_set_data_full (GTK_OBJECT (greenWin), "quit", quit,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (quit);
  gtk_container_add (GTK_CONTAINER (file_menu), quit);

}
