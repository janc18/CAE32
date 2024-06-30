#include "read_event.h"
#include "read_file_descriptor.h"
#include <bits/pthreadtypes.h>
#include <errno.h>
#include <fcntl.h>
#include <libevdev-1.0/libevdev/libevdev.h>
#include <poll.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/poll.h>
#include <time.h>
#include <unistd.h>
char *event_path = "/dev/input/event";

event_buffer device_buffer;

struct libevdev *dev = NULL;
int fd;
event_buffer getDeviceBuffer() { return device_buffer; }

void handle_signal(int sig) {
  stopThreads();
  libevdev_free(dev);
  close(fd);
  printf("\n");
}

void initializeEventBuffer(struct event_buffer *buffer) {
  buffer->head = 0;
  buffer->tail = 0;
  buffer->count = 0;
  buffer->stop = 0;
  pthread_mutex_init(&buffer->mutex, NULL);
  pthread_cond_init(&buffer->cond, NULL);
}

void cleanUpEventBuffer(struct event_buffer *buffer) {
  pthread_mutex_destroy(&buffer->mutex);
  pthread_cond_destroy(&buffer->cond);
}

const char EVENTS_AXIS_TABLE[3][10] = {"ABS_X", "ABS_Y", "ABS_Z"};
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
void stopThreads() {
  pthread_mutex_lock(&device_buffer.mutex);
  device_buffer.stop = 1;
  pthread_cond_broadcast(&device_buffer.cond);
  pthread_mutex_unlock(&device_buffer.mutex);
}
void *processEvents(void *arg) {
  while (1) {
    pthread_mutex_lock(&device_buffer.mutex);
    while (device_buffer.count == 0 && !device_buffer.stop) {
      pthread_cond_wait(&device_buffer.cond, &device_buffer.mutex);
    }

    if (device_buffer.stop && device_buffer.count == 0) {
      pthread_mutex_unlock(&device_buffer.mutex);
      break;
    }

    struct input_event ev = device_buffer.events[device_buffer.head];
    device_buffer.head = (device_buffer.head + 1) % EVENT_BUFFER_SIZE;
    device_buffer.count--;

    pthread_mutex_unlock(&device_buffer.mutex);

    printf("Event: %s %s %d\n", libevdev_event_type_get_name(ev.type), libevdev_event_code_get_name(ev.type, ev.code), ev.value);
  }
  return NULL;
}
void *readEvents(void *path_event_void) {
  char *path_event = path_event_void;

  printf("%s\n", path_event);
  if (path_event == NULL) {
    fprintf(stderr, "ERROR: invalid path\n");
  }

  // struct libevdev *dev = NULL;
  struct pollfd device;
  memset(&device, 0, sizeof(device));
  device.events = POLLIN;

  // int fd;
  int rc = 1;
  fd = open(path_event, O_RDONLY | O_NONBLOCK);
  if (fd < 0) {
    fprintf(stderr, "ERROR: Opening the device\n");
    exit(1);
  }

  rc = libevdev_new_from_fd(fd, &dev);
  if (rc < 0) {
    fprintf(stderr, "ERROR: At starting libevdev\n");
    close(fd);
    exit(1);
  }

  device.fd = fd;

  while (1) {
    pthread_mutex_lock(&device_buffer.mutex);
    if (device_buffer.stop) {
      pthread_mutex_unlock(&device_buffer.mutex);
      break;
    }
    pthread_mutex_unlock(&device_buffer.mutex);
    struct input_event ev;

    int poll_result = poll(&device, 1, 1000);
    if (poll_result < 0) {
      fprintf(stderr, "ERROR: At poll\n");
      break;
    }
    if (poll_result == 0) {
      continue;
    }
    if (device.revents & POLLIN) {
      rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL, &ev);
      if (rc == 0) {
        pthread_mutex_lock(&device_buffer.mutex);
        if (device_buffer.count < EVENT_BUFFER_SIZE) {
          device_buffer.events[device_buffer.tail] = ev;
          device_buffer.tail = (device_buffer.tail + 1) % EVENT_BUFFER_SIZE;
          device_buffer.count++;
          pthread_cond_signal(&device_buffer.cond);
        }
        pthread_mutex_unlock(&device_buffer.mutex);
      } else if (rc < 0 && rc != EAGAIN) {
        fprintf(stderr, "ERROR: Reading event\n");
        break;
      } else if (device.revents & (POLLERR | POLLHUP)) {
        fprintf(stderr, "Device Disconnected\n");
        break;
      }
    }
    // libevdev_free(dev);
    // close(fd);
  }
}

// struct libevdev *get_dev_reference() {
//
//   // return dev
// }

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
