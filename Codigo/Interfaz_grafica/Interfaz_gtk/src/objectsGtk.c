
/*
 * Copyright (C) 2023 OpenHF
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version. This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include "objectsGtk.h"
#include "cae32_app.h"
#include <cairo.h>
#include <gtk/gtk.h>
/**
 * @brief Start gui
 *
 * Load glade files
 */
void start_gui(void) {
  GError *error = NULL;
  GtkBuilder *constructor = gtk_builder_new();
  gtk_init(NULL, NULL);

  if (gtk_builder_add_from_file(constructor, "../gladeFiles/UI1.glade", &error) == 0) {
    g_printerr("Error no se encontro el archivo :%s \n", error->message);
    g_clear_error(&error);
  }

  g_set_prgname("CAE32");
  g_object_unref(G_OBJECT(constructor));
  gtk_main();
}
/**
 * @brief Draw steering wheel
 * @param GtkWidget widget to draw
 * @param cairo_t
 * @gpointer pointer with CAE32App
 */
static gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer data) {

  CAE32App *app = G_POINTER_TO_CAE32_APP(data);
  ObjectsUI *UI = cae32_app_get_gui(app);
  cairo_save(cr);
  cairo_translate(cr, gtk_widget_get_allocated_width(widget) / 2.0, gtk_widget_get_allocated_height(widget) / 2.0);

  cairo_rotate(cr, UI->rotation);
  gdk_cairo_set_source_pixbuf(cr, UI->pixbuf, -gdk_pixbuf_get_width(UI->pixbuf) / 2.0, -gdk_pixbuf_get_height(UI->pixbuf) / 2.0);
  cairo_paint(cr);
  cairo_restore(cr);

  return TRUE;
}
/**
 * @brief Build all GUI objects
 * @param GtkApplication pointer with
 */
ObjectsUI *buildObjects(GtkApplication *app) {
  GtkBuilder *constructor = gtk_builder_new();
  gtk_builder_add_from_file(constructor, "../gladeFiles/UI1.glade", NULL);
  ObjectsUI *obj = g_malloc(sizeof(ObjectsUI));

#ifdef DEBUG
  g_printerr("UI %p \n", obj);
#endif

  obj->boton = GTK_WIDGET(gtk_builder_get_object(constructor, "boton_test"));
  obj->ventana = GTK_WIDGET(gtk_builder_get_object(constructor, "ventana"));
  obj->barra_acelerador = GTK_WIDGET(gtk_builder_get_object(constructor, "valor_acelerador"));
  obj->barra_freno = GTK_WIDGET(gtk_builder_get_object(constructor, "valor_freno"));
  obj->barra_clutch = GTK_WIDGET(gtk_builder_get_object(constructor, "valor_clutch"));
  obj->output = GTK_WIDGET(gtk_builder_get_object(constructor, "salida"));
  obj->reconectar = GTK_WIDGET(gtk_builder_get_object(constructor, "reconnect"));
  obj->visual_status = GTK_WIDGET(gtk_builder_get_object(constructor, "visual_status"));
  obj->text_status = GTK_WIDGET(gtk_builder_get_object(constructor, "text_status"));
  obj->swa = GTK_WIDGET(gtk_builder_get_object(constructor, "swa"));
  obj->search_updates = GTK_WIDGET(gtk_builder_get_object(constructor, "actualizar"));
  obj->tv_updatelog = GTK_WIDGET(gtk_builder_get_object(constructor, "tv_updatelog"));
  return obj;
  g_object_unref(G_OBJECT(constructor));
}
/**
 * @brief Deallocated memory
 *
 * Deallocated GUI elements and device data
 *
 * @param gpoiter that contains Device,ObjectsUI and app
 */
void freeElements(gpointer data) {
  CAE32App *app = G_POINTER_TO_CAE32_APP(data);
  ObjectsUI *UI = cae32_app_get_gui(app);
  Device *cae = CAE32_APP(app)->priv->device;

#ifdef DEBUG
  g_printerr("%p UI\n", UI);
  g_printerr("%p device\n", cae);
#endif

  g_free(cae);
  g_free(UI);
  gtk_main_quit();
}
/**
 * @brief Connected signals
 *
 * Connect ObjectsUI with callbacks
 * @param ObjectsUI struct with all the GtkWidget elements
 * @param CAE32App
 */
void signalsConnection(ObjectsUI *obj, CAE32App *app) {
  g_signal_connect_swapped(obj->reconectar, "clicked", G_CALLBACK(searchDevice), app);
  g_signal_connect_swapped(obj->ventana, "destroy", G_CALLBACK(freeElements), app);
  g_signal_connect(G_OBJECT(obj->swa), "draw", G_CALLBACK(on_draw), app);
}
