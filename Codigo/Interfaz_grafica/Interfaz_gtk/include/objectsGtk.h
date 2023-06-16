#include "cae32_app.h"
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <gtk/gtk.h>

void start_gui(void);
ObjectsUI *buildObjects(GtkApplication *app);
void signalsConnection(ObjectsUI *obj, CAE32App *app);
//  #pragma once
