#include <gtk/gtk.h>

static void load_track(GtkWidget *widget, gpointer data) {
  GtkWidget *dialog;
  GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
  gint res;
  GtkWidget *parent_window = gtk_widget_get_toplevels(widget);

  dialog = gtk_file_chooser_dialog_new ("Open File",
      parent_window,
      action,
      _("_Cancel"),
      GTK_RESPONSE_CANCEL,
      _("_Open"),
      GTK_RESPONSE_ACCEPT,
      NULL);

  res = gtk_dialog_run (GTK_DIALOG (dialog));
  if (res == GTK_RESPONSE_ACCEPT)
  {
    char *filename;
    GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
    filename = gtk_file_chooser_get_filename (chooser);
    open_file (filename);
    g_free (filename);
  }

  gtk_widget_destroy (dialog);
}

static void activate (GtkApplication *app, gpointer user_data) {
  GtkWidget *window;
  GtkWidget *button;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Hello");
  gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

  button = gtk_button_new_with_label("Load Track");
  g_signal_connect(button, "clicked", G_CALLBACK(load_track), NULL);
  gtk_window_set_child(GTK_WINDOW (window), button);

  gtk_window_present(GTK_WINDOW(window));
}

int main (int argc, char **argv) {
  GtkApplication *app;
  int status;

  app = gtk_application_new("org.gtk.mp3", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
