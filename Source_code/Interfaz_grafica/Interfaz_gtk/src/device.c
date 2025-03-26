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

#include "device.h"
#include "cae32_app.h"
#include "glibconfig.h"
#include <fcntl.h>
#include <glib.h>
#include <gtk/gtk.h>
#include <linux/hidraw.h>
#include <linux/joystick.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
/**
 * @brief Name of the device to search
 */
const char nameCAE[] = "CAE32 CAE32";
/**
 * @brief Maximum number of times to search for the device
 */
int MAXDEVICES = 30;
/**
 * @brief HID path
 */
const char pathHID[] = "/dev/hidraw";
/**
 * @brief Joystick path
 */
const char pathJoystick[] = "/dev/input/js";

struct udev_source *source;

void updateAxisBar(ObjectsUI *UI, guint8 number, gdouble value);

/**
 * @brief Search for an HID and Joystick device.
 *
 * Search through HID and Joystick @ref MAXDEVICES times.
 *
 * Look on the next paths
 * - /dev/hidraw/
 * - /dev/input/
 *
 * And compare the name's file descriptor with @ref nameCAE
 *
 * @param *Device Struct with all the Device data
 * @param bool Device type to search, TRUE for HID and FALSE for Joystick
 * @return
 * - 1 Device found
 * - -1 No device found
 */
int searchHIDDevice(Device *cae, bool DeviceType) {
  memset(cae->path, 0, sizeof(cae->path));
  char buffer[256];
  char path[50];
  int fd, i;
  if (DeviceType) {
    g_printerr("Searching for HID Device\n");
    strcpy(path, pathHID);
  } else {
    g_printerr("Searching for Joystick Device\n");
    strcpy(path, pathJoystick);
  }
  for (i = 0; i <= MAXDEVICES; i++) {
    g_snprintf(buffer, sizeof(buffer), "%s%d", path, i);
    g_printerr("%s\n", buffer);
    fd = open(buffer, O_RDWR);
    if (fd > 0) {
      g_printerr("Found a device on %s\n", buffer);
      g_printerr("Comparing device name...\n");
      strcpy(cae->path, buffer);
      if (typeDevice(fd, buffer, cae, DeviceType) == 1) {
        break;
        return 1;
      }
    }
  }
  if (fd < 0) {
    g_printerr("No device found.\n");
    return -1;
  }

  close(fd);
  return 0;
}

static gboolean CaptureEvent(gpointer data) {

  CAE32App *app = G_POINTER_TO_CAE32_APP(data);
  ObjectsUI *UI = cae32_app_get_gui(app);
  Device *cae = CAE32_APP(app)->priv->device;
  struct js_event js;                           // create a struct to save all the events
  open(cae->path, O_RDWR | O_NONBLOCK);         // open the path to read on nonblocking mode
  ssize_t len = read(cae->fd, &js, sizeof(js)); // read the data from the device
  if (len < 0) {
    // detach device from the threadand update the visual state
    g_printerr("Error\n");
    cae->found = FALSE;
    g_source_destroy((GSource *)source);
    gtk_label_set_text(GTK_LABEL(UI->text_status), "Desconectado");
    gtk_image_set_from_file(GTK_IMAGE(UI->visual_status), "../src_images/red.png");
    return TRUE;
  }

  if (len == sizeof(js)) {
    gdouble mapped_value = 0;
    if (js.type & JS_EVENT_AXIS) {
      mapped_value = js.value / 255.0; // Already 0-255, map directly
      g_printerr("Event AXIS %f\n",mapped_value);
    } else {
      mapped_value = (js.value + 32767.0) / 65534.0; // Normalize -32767 to 32767
      g_printerr("Event SD %f\n",mapped_value);
    }
    updateAxisBar(UI, js.number, mapped_value * 255.0);
  } else if (js.type & JS_EVENT_BUTTON) {

    g_printerr("Button: %d, Value: %hd\n", js.number, js.value);
  }
return TRUE;
}

/**
 * @brief Compare name's device to @ref nameCAE
 * @param fd int value of file descriptor
 * @param name char value with the path's decice
 * @param Device* Struct with all the Device data
 * @param isHID bool search for HID or Joystick device
 * - TRUE HID
 * - FALSE Joystick
 * @return
 * - 1 Device's name equal to @ref nameCAE
 * - -1 Device's name not equal to @ref nameCAE
 */
int typeDevice(int fd, char name[256], Device *cae, bool isHID) {

  if (isHID == false) {
    ioctl(fd, JSIOCGNAME(60), name);  // get the joystick name
    if (strcmp(name, nameCAE) == 0) { // compare name
      g_printerr("Found joystick %s device \n", nameCAE);
      cae->fd = fd;
      ioctl(fd, JSIOCGAXES, &cae->axis);
      ioctl(fd, JSIOCGBUTTONS, &cae->buttons);
      ioctl(fd, JSIOCGVERSION, &cae->version);
      return 1;
    } else {
      g_printerr("Isn't %s device \n", nameCAE);
      return -1;
    }
  } else {
    ioctl(fd, HIDIOCGRAWNAME(256), name); // get the HID name
    g_printerr("name :%s\n", name);
    if (strcmp(name, nameCAE) == 0) { // compare name
      g_printerr("Found HID device\n");
      cae->fd = fd;
      return 1;
    } else {
      g_printerr("Isn't %s device \n", nameCAE);
      return -1;
    }
  }
}

/**
 *@brief Print on terminal Device's information
 *
 *Like:
 * - File Descriptor
 * - Device Version
 * - Number of Axis
 * - Number of Buttons
 * - Path on /dev/
 *
 *@param Device* Struct with all the Device data
 */

void showDevInfo(Device *cae) {

  g_printerr("\n-----------------\n");
  g_printerr("File Descriptor %d \n", cae->fd);
  g_printerr("Device Version %d \n", cae->version);
  g_printerr("Axis %u \n", cae->axis);
  g_printerr("Buttons %u \n", cae->buttons);
  g_printerr("Path %s \n", cae->path);
  g_printerr("-------------------\n");
}

/**
 *@brief Show the status connection in the GUI
 *@param *Device Struct with all the Device data
 *@param *ObjectsUI Struct with all the UI's components
 */
void showStatusConnection(Device *cae, ObjectsUI *UI) {
  if (cae->found) {
    if (cae->isHID) {

      gtk_label_set_text(GTK_LABEL(UI->text_status), "Conectado (HID)");
      gtk_image_set_from_file(GTK_IMAGE(UI->visual_status), "../src_images/green.png");
    } else {
      gtk_label_set_text(GTK_LABEL(UI->text_status), "Conectado (Joystick)");
      gtk_image_set_from_file(GTK_IMAGE(UI->visual_status), "../src_images/green.png");
    }
  } else {

    gtk_label_set_text(GTK_LABEL(UI->text_status), "Desconectado");
    gtk_image_set_from_file(GTK_IMAGE(UI->visual_status), "../src_images/red.png");
  }
}
struct udev_source {
  GSource base;
  gpointer tag;
};

static gboolean udev_source_prepare(G_GNUC_UNUSED GSource *source, gint *timeout) {
  *timeout = -1;
  return FALSE;
}

static gboolean udev_source_check(GSource *source) {
  struct udev_source *usrc = (struct udev_source *)source;
  return (g_source_query_unix_fd(source, usrc->tag) > 0);
}

static gboolean udev_source_dispatch(GSource *source, GSourceFunc callback, gpointer user_data) {
  struct udev_source *usrc = (struct udev_source *)source;
  GIOCondition revents = g_source_query_unix_fd(source, usrc->tag);

  if (revents & G_IO_IN | G_IO_HUP) {
    if (callback == NULL)
      return FALSE;
    return callback(user_data);
  }

  return TRUE;
}

GSourceFuncs udev_source_funcs = {
    .prepare = udev_source_prepare,
    .check = udev_source_check,
    .dispatch = udev_source_dispatch,
};
//

void configGSource(Device *cae, CAE32App *app) {

  source = (struct udev_source *)g_source_new(&udev_source_funcs, sizeof(*source));
  // struct udev_source *source;
  // source = (struct udev_source *)g_source_new(&udev_source_funcs, sizeof(*source));
  g_source_set_callback(&source->base, CaptureEvent, app, NULL); /* destroy_notify */
  source->tag = g_source_add_unix_fd(&source->base, cae->fd, G_IO_IN | G_IO_HUP);
  g_source_attach(&source->base, g_main_context_default());
  g_source_unref(&source->base);
}

/**
 *@brief Search for any type of device, it can be HID or Joystick
 *@param gpointer Reference to CAE32App
 *
 *@return
 * - 1 Joystick device found
 * - 2 HID device found
 * - 3 Device is already connected
 * - -1 No device found
 */
int searchDevice(gpointer data) {
  CAE32App *app = G_POINTER_TO_CAE32_APP(data);
  ObjectsUI *UI = cae32_app_get_gui(app);
  Device *cae = CAE32_APP(app)->priv->device;
  g_printerr("valor de encotrado?:%s\n", cae->found ? "true" : "false");
  if (cae->found == FALSE) {
    if (searchHIDDevice(cae, false) >= 0) { // Searching for a Joystick device
      g_printerr("Monitoring Joystick device\n");
      cae->found = TRUE;
      cae->isHID = FALSE;
      showStatusConnection(cae, UI);
      configGSource(cae, app);
      return 1;
    }
    if (searchHIDDevice(cae, true) >= 0) { // Searching for a HID device
      g_printerr("Monitoring HID device\n");
      cae->isHID = TRUE;
      cae->found = TRUE;
      showStatusConnection(cae, UI);
      return 2;
    }
    showStatusConnection(cae, UI);
    g_printerr("I can't find the Device\n");
    return -1;
  } else {
    g_printerr("The device is already connected\n");
    return 3;
  }
}
/**
 *@brief Update the steering wheel rotation
 *@param *ObjectsUI Struct with all the UI's components
 *@param guint16 Value of rotation
 *@todo Add implicity formula
 */
void updateSteeringWheel(ObjectsUI *UI, guint16 value) {
  guint16 valueCalculated=(value / 32767.0) * 8;
  UI->rotation = valueCalculated;
  g_printerr("value calcuted :%hu\n",valueCalculated);
  gtk_widget_queue_draw(UI->swa);
}
/**
 *@brief Update level bar ,corresponded to one axis
 *@param *ObjectsUI Struct with all the UI's components
 *@param guint8 Axis'number for example: number=1 correspond to the brake
 *@param gdouble Value of axis
 */
void updateAxisBar(ObjectsUI *UI, guint8 number, gdouble value) {
    gdouble normalized_value = value /32767;
  g_printerr("%f\n",normalized_value);
  switch (number) {
  case 0: {
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(UI->barra_freno), normalized_value);
    break;
  }
  case 3: {
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(UI->barra_clutch), normalized_value);
    break;
  }
  case 2: {
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(UI->barra_acelerador), normalized_value);
    break;
  }
  case 1: {
    updateSteeringWheel(UI, value);
    break;
  }
  }
}
