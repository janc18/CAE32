#include "cae32_app.h"
#include <gtk/gtk.h>
int main(int argc, char *argv[]) {
  GtkApplication *app;
  app = cae32_app_new();
  return g_application_run(G_APPLICATION(app), argc, argv);
}
