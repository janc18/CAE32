#include "read_event.h"

#include <errno.h>
#include <fcntl.h>
#include <libevdev-1.0/libevdev/libevdev.h>
#include <poll.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "read_file_descriptor.h"

char *event_path = "/dev/input/event";

bool hasSudoPermissions() {
  if (getuid()) {
    fprintf(stderr, "Doesn't have sudo permissions to read the events, Want to continue? Y/n\n");
    return false;
  } else {
    return true;
  }
}

bool continueWithoutSudoPermissions() {
  char response[9];
  fgets(response, 3, stdin);
  switch (response[0]) {
  case '\n':
    return true;
    break;
  case 'y':
    return true;
    break;
  case 'Y':
    return true;
    break;
  default:
    return false;
  }
}
void readEvents(char *path_event) {
    if (path_event == NULL) {
        return;
    }

    struct libevdev *dev = NULL;
    struct pollfd device;
    memset(&device, 0, sizeof(device));
    device.events = POLLIN;

    int fd;
    int rc = 1;
    fd = open(path_event, O_RDONLY | O_NONBLOCK);
    if (fd < 0) {
        fprintf(stderr,"ERROR: Opening the device\n");
        exit(1);
    }

    rc = libevdev_new_from_fd(fd, &dev);
    if (rc < 0) {
        fprintf(stderr,"ERROR: At starting libevdev\n");
        close(fd);
        exit(1);
    }

    device.fd = fd;
    do {
        struct input_event ev;
        int poll_result = poll(&device, 1, -1);
        if (poll_result < 0) {
            fprintf(stderr,"ERROR: At Poll\n");
            break;
        }

        if (device.revents & POLLIN) {
            rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL, &ev);
            if (rc == 0) {
                printf("Event: %s %s %d\n", libevdev_event_type_get_name(ev.type), libevdev_event_code_get_name(ev.type, ev.code), ev.value);
            } else if (rc < 0 && rc != -EAGAIN) {
                fprintf(stderr,"ERROR: Reading event\n");
                break;
            }
        } else if (device.revents & (POLLERR | POLLHUP)) {
            fprintf(stderr,"Device Disconnected\n");
            break;
        }
    } while (rc == 1 || rc == 0 || rc == -EAGAIN);

    libevdev_free(dev);
    close(fd);
}

char *getEventPath(char *name_to_compare) {
  printf("Searching the %s device\n", name_to_compare);
  if (name_to_compare == NULL)
    return NULL;

  int fd; // Valgrind:Conditional jump or move depends on uninitialised value(s)
  int rc = 0;
  int iteration = 0;
  struct libevdev *dev = NULL;

  while (fd > 0) {
    char *event_path_generated = generatePath(event_path, iteration);
    fd = open(event_path_generated, O_RDONLY | O_NONBLOCK);
    rc = libevdev_new_from_fd(fd, &dev);
    if (rc < 0) {
      close(fd);
      return NULL;
    }
    if (strcmp(name_to_compare, libevdev_get_name(dev)) == 0) {
      close(fd);
      return event_path_generated;
    }
    close(fd);
    free(event_path_generated);
    iteration++;
  }
  return NULL;
}
