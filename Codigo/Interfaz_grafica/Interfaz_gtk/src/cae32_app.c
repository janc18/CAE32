#include "cae32_app.h"
#include "device.h"
#include "objectsGtk.h"
G_DEFINE_TYPE_WITH_CODE(CAE32App, cae32_app, GTK_TYPE_APPLICATION, G_ADD_PRIVATE(CAE32App));

static void cae32_app_init(CAE32App *app) {
  app->priv = cae32_app_get_instance_private(app);
  app->priv->most_recent_id = 1;
}

static void cae32_app_activate(GApplication *app) {
  Device *device = g_malloc(sizeof(Device));
  CAE32_APP(app)->priv->UI = buildObjects(GTK_APPLICATION(app));
  ObjectsUI *UI = cae32_app_get_gui(CAE32_APP(app));
  g_set_prgname("CAE32");
  UI->pixbuf = gdk_pixbuf_new_from_file("../src_images/Volante2.png", NULL);
  UI->rotation = 0.0;
  signalsConnection(UI, CAE32_APP(app));
  CAE32_APP(app)->priv->device = device;
  gtk_main();
}

static void cae32_app_startup(GApplication *app) { G_APPLICATION_CLASS(cae32_app_parent_class)->startup(app); }

GtkApplication *cae32_app_new(void) {
  return g_object_new(CAT_TYPE_CAE32_APP, "application_id", "net.cat.cae32", "flags", G_APPLICATION_FLAGS_NONE, NULL);
}
ObjectsUI *cae32_app_get_gui(CAE32App *app) { return app->priv->UI; }
static void cae32_app_class_init(CAE32AppClass *class) {
  G_APPLICATION_CLASS(class)->startup = cae32_app_startup;
  G_APPLICATION_CLASS(class)->activate = cae32_app_activate;
}
