#include "widgets.hh"

NameValueBox::NameValueBox(const char* label) {
  _box = gtk_hbox_new(FALSE, 1);
  gtk_widget_ref (_box);
  _label = gtk_label_new(label);
  gtk_widget_ref (_label);
  _entry = gtk_entry_new ();
  gtk_widget_ref (_entry);
}
void NameValueBox::pack() {
  gtk_box_pack_start( GTK_BOX(_box), _label, FALSE, FALSE, 1);
  gtk_box_pack_end( GTK_BOX(_box), _entry, TRUE, TRUE, 1);
}
void NameValueBox::show() {
  gtk_widget_show (_label);
  gtk_widget_show (_entry);
  gtk_widget_show (_box);
}
