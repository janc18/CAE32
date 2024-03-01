/* Linux */
#include <linux/hidraw.h>
#include <linux/input.h>
#include <linux/types.h>

/*
 * Ugly hack to work around failing compilation on systems that don't
 * yet populate new version of hidraw.h to userspace.
 */
#ifndef HIDIOCSFEATURE
#warning Please have your distro update the userspace kernel headers
#define HIDIOCSFEATURE(len) _IOC(_IOC_WRITE | _IOC_READ, 'H', 0x06, len)
#define HIDIOCGFEATURE(len) _IOC(_IOC_WRITE | _IOC_READ, 'H', 0x07, len)
#endif

/* Unix */
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/* C */
#include <errno.h>
#include <libudev.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_hidraw_devices(int max_number_of_devices) {
  int fd;
  char buffer_name_device[80];
  for (int i = 0; i < max_number_of_devices; i++) {
    snprintf(buffer_name_device, 80, "/dev/hidraw%d", i);
    printf("open %s path\n", buffer_name_device);
    fd = open(buffer_name_device, O_RDWR | O_NONBLOCK);
    printf("%d\n", fd);
    if (fd > 0) {
      close(fd);
    } else {
      printf("Don't found a file descriptor at %s\n", buffer_name_device);
    }
  }
}
void enumerate_block_devices(struct udev *udev) {
  struct udev_enumerate *enumerate;
  struct udev_list_entry *devices, *dev_list_entry;

  // Crear el objeto de enumeración de dispositivos
  enumerate = udev_enumerate_new(udev);
  if (!enumerate) {
    printf("Error al crear el objeto de enumeración de dispositivos\n");
    return;
  }

  // Enumerar los dispositivos de bloque
  udev_enumerate_add_match_subsystem(enumerate, "hid");
  udev_enumerate_scan_devices(enumerate);
  devices = udev_enumerate_get_list_entry(enumerate);

  // Iterar sobre la lista de dispositivos
  udev_list_entry_foreach(dev_list_entry, devices) {
    const char *path;
    struct udev_device *dev;

    // Obtener la ruta del dispositivo
    path = udev_list_entry_get_name(dev_list_entry);
    dev = udev_device_new_from_syspath(udev, path);
    const char *model_name = udev_device_get_property_value(dev, "ID_MODEL");
    // Imprimir el nombre del modelo del dispositivo USB si está disponible
    if (model_name) {
      printf("Nombre del modelo del dispositivo USB: %s\n", model_name);
    } else {
      printf("No se encontró en este path %s \n",path);
    }

    // Liberar la memoria utilizada por el objeto de dispositivo
    udev_device_unref(dev);
  }

  // Liberar la memoria utilizada por el objeto de enumeración
  udev_enumerate_unref(enumerate);
}
//
// fd = open(device, O_RDWR | O_NONBLOCK);
// }
//
// const char *bus_str(int bus);
// int fd;
// int i, res, desc_size = 0;
// char buf[256];
// struct hidraw_report_descriptor rpt_desc;
// struct hidraw_devinfo info;
// char *device = "/dev/hidraw0";
