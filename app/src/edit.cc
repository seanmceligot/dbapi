#include "edit.hh"
#include "greenapp.hh"

EditView::EditView(Model* model): View("edit", model) {
  _columns = new NameValueBox*[model->get_table()->get_schema()->size()];
}
NameValueBox* EditView::get_column(int i) {
  return _columns[i];
}
static void on_add_button(GtkButton* button, gpointer p_frame) {
  Frame* frame = (Frame*)p_frame;
  EditView* edit_view = (EditView*)frame->current_view();
  Table* table = edit_view->get_model()->get_table();
  if (!table) {
    return;
  }
  Schema* schema = table->get_schema();
  Row* row = table->new_row();
  for (size_t i = 0; i < schema->size(); i++) {
    NameValueBox* nv = edit_view->get_column(i);
    const char* name = schema->get_name(i);
    const char* value = gtk_entry_get_text(GTK_ENTRY(nv->get_entry()));
    if ( (i == 0) && (strlen(value) == 0) ) {
      // this is a hack because add_row is called before button is pressed
      delete row;
      return;
    }
    std::cout <<name<<" = "<<value<<std::endl;
  	row->from_string(name, value);
  }
  table->save(row);
  frame->pop_view(edit_view);
}

void EditView::open(Frame* frame) {
  Table* table = get_model()->get_table();
  if (!table) {
    return;
  }
  GtkWidget* box = gtk_vbox_new (FALSE, 0);
  gtk_widget_ref (box);
  
  Schema* schema = table->get_schema();
  for (size_t i = 0; i < schema->size() ;i++) {
    const char* name = schema->get_name(i);
    NameValueBox* nv = new NameValueBox(name);
    nv->pack();
    nv->show();
    gtk_box_pack_start (GTK_BOX (box), nv->get_box(), FALSE, FALSE, 1);
    _columns[i] = nv;
  }
  GtkWidget* button = gtk_button_new_with_label ("Add");
  gtk_widget_show (button);
  gtk_signal_connect (GTK_OBJECT (button), "enter", GTK_SIGNAL_FUNC (on_add_button), frame);
  gtk_box_pack_start (GTK_BOX (box), button, FALSE, FALSE, 1);
  //gtk_widget_show (box);
  _widget = box;
}
void EditView::close() {
}
GtkWidget* EditView::get_widget() {
  return _widget;
}
