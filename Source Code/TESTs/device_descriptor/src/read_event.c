#include "read_event.h"

#include <errno.h>
#include <fcntl.h>
#include <libevdev-1.0/libevdev/libevdev.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "read_file_descriptor.h"

char *event_path = "/dev/input/event";

void read_events(char *path_event) {
  
  if(path_event==NULL){
    return;
  }

  struct libevdev *dev = NULL;
  struct pollfd device;
  memset(&device, 0, sizeof(device));
  device.events = POLLIN;
  
  int fd;
  int rc = 1;
  fd = open(path_event, O_RDONLY | O_NONBLOCK);
  rc = libevdev_new_from_fd(fd, &dev);
  if (rc < 0) {
    exit(1);
  }

  device.fd = fd;
  do {
    struct input_event ev;
    poll(&device, 1, -1);
    if (device.revents & POLLIN) {
      rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL, &ev);
      if (rc == 0)
        printf("Event: %s %s %d\n", libevdev_event_type_get_name(ev.type), libevdev_event_code_get_name(ev.type, ev.code), ev.value);
    }
  } while (rc == 1 || rc == 0 || rc == -EAGAIN);
}

char *get_event_path(char *name_to_compare) {
  printf("Searching the %s device\n", name_to_compare);
  if (name_to_compare == NULL)
    return NULL;

  int fd; // Conditional jump or move depends on uninitialised value(s)
  int rc = 0;
  int iteration = 0;
  struct libevdev *dev = NULL;

  while (fd > 0) {
    char *event_path_generated = generate_path(event_path, iteration);
    fd = open(event_path_generated, O_RDONLY | O_NONBLOCK);
    rc = libevdev_new_from_fd(fd, &dev);
    if (rc < 0) {
      close(fd);
      return NULL;
    }
    if (strcmp(name_to_compare, libevdev_get_name(dev)) == 0) {
      return event_path_generated;
      close(fd);
      break;
    }
    close(fd);
    free(event_path_generated);
    iteration++;
  }
  return NULL;
}
