#ifndef __CAE32_APP_H__
#define __CAE32_APP_H__

#include "device.h"
#include "glibconfig.h"
#include <gtk/gtk.h>

#define CAT_TYPE_CAE32_APP (cae32_app_get_type())
#define CAE32_APP(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), CAT_TYPE_CAE32_APP, CAE32App))

#define G_POINTER_TO_CAE32_APP(p) ((CAE32App *)(p))
typedef struct _ObjectsUI ObjectsUI;

struct _ObjectsUI {
  GtkWidget *ventana;
  GtkWidget *visual_status;
  GtkWidget *text_status;
  GtkWidget *boton;
  GtkWidget *etiqueta;
  GtkWidget *barra_acelerador;
  GtkWidget *barra_freno;
  GtkWidget *barra_clutch;
  GtkWidget *output;
  GtkWidget *swa; // sterring wheel animation
  gint8  rotation;
  GtkWidget *reconectar;
  GtkWidget *search_updates; // button
  GtkWidget *tv_updatelog;
  GdkPixbuf *pixbuf;
};

typedef struct _CAE32AppPrivate CAE32AppPrivate;
typedef struct _CAE32App CAE32App;
typedef struct _CAE32AppClass CAE32AppClass;

struct _CAE32AppPrivate {
  ObjectsUI *UI;
  Device *device;
  guint most_recent_id;
};

struct _CAE32App {
  GtkApplication parent;
  CAE32AppPrivate *priv;
};

struct _CAE32AppClass {
  GtkApplicationClass parent_class;
};

ObjectsUI *cae32_app_get_gui(CAE32App *app);
GtkApplication *cae32_app_new(void);

GType cae32_app_get_type(void);
#endif
