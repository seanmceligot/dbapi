#include "frame.hh"
#include "greendb/debug.hh"

Frame::Frame(GtkWidget* frame): _frame(frame) {};

void
Frame::pop_view (View * view)
{
  gtk_container_add (GTK_CONTAINER (_frame), view->get_widget ());
  debug << "pop view " << _views.top()->get_title()<<std::endl;
  _views.pop ();                //remove(view) would be better
  if (!_views.empty ()) {
    View *view = _views.top ();
    GtkWidget *widget = view->get_widget ();
    gtk_container_add (GTK_CONTAINER (_frame), widget);
    gtk_widget_show (widget);
    gtk_widget_show (_frame);
  }
}
void
Frame::push_view (View * view)
{
  assert (view);
  {
    GList* children = gtk_container_children(GTK_CONTAINER (_frame));
    GtkWidget* widget = (GtkWidget*)g_list_nth_data(children, 0);
    if (widget) {
        gtk_container_remove(GTK_CONTAINER (_frame), widget);
    }
  }
  debug << "push view " << view->get_title()<<std::endl;
  _views.push (view);
  view->open (this);
  GtkWidget *widget = view->get_widget ();
  gtk_container_add (GTK_CONTAINER (_frame), widget);
  gtk_widget_show (widget);
  gtk_widget_show (_frame);
}
Model* Frame::get_model() {
  if (_model == NULL) {
      _model = new Model();
  }
  return _model;
}
View *
Frame::current_view ()
{
  debug << "view size " << _views.size()<<std::endl;
  if (!_views.empty ()) {
    View *view = _views.top ();
    debug << "current view " << view->get_title()<<std::endl;
    return view;
  }
  return NULL;
}
