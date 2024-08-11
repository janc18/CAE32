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
events *p_copy = NULL;
struct libevdev *dev = NULL;
int fd;
event_buffer getDeviceBuffer() { return device_buffer; }

void push(events **headRef, int val, const char *event_name) {
  events *newNode = (events *)malloc(sizeof(events));
  newNode->val = val;
  strncpy(newNode->event_name, event_name, 30 - 1);
  newNode->event_name[sizeof(newNode->event_name) - 1] = '\0';
  newNode->siguiente = NULL;
  if (*headRef == NULL) {
    *headRef = newNode;
  } else {
    events *current = *headRef;
    while (current->siguiente != NULL) {
      current = current->siguiente;
    }
    current->siguiente = newNode;
  }
}

void free_memory_events(events *head) {
  events *current;

  while (head != NULL) {
    current = head;
    head = current->siguiente;
    free(current);
  }
}
int updateValue(events *head, const char *event_name, int value) {

  events *current = head;
  while (current != NULL) {
    if (strcmp(current->event_name, event_name) == 0) {
      printf("updating value :%d\n", value);
      current->val = value;
      return 1;
    }
    current = current->siguiente;
  }
  push(&head, value, event_name);
  return 0;
}

void terminal_print(events *head) {
  events *current = head;
  printf("\e[1;1H\e[2J");
  while (current != NULL) {
    printf("Event:%s\tValue:%d\n", current->event_name, current->val);
    current = current->siguiente;
  }
}

void handle_signal(int sig) {
  stopThreads();
  libevdev_free(dev);
  close(fd);
  printf("\n");
  free_memory_events(p_copy);
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
void stopThreads() {
  pthread_mutex_lock(&device_buffer.mutex);
  device_buffer.stop = 1;
  pthread_cond_broadcast(&device_buffer.cond);
  pthread_mutex_unlock(&device_buffer.mutex);
}
void *processEvents(void *arg) {
  events *head = (events *)arg;
  p_copy = (events *)arg;
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
    updateValue(head, libevdev_event_code_get_name(ev.type, ev.code), ev.value);
    terminal_print(head);
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

  int fd = 1;
  int rc = 0;
  int iteration = 0;
  struct libevdev *dev = NULL;

  while (fd > 0) {
    char *event_path_generated = generatePath(event_path, iteration);
    fd = open(event_path_generated, O_RDONLY | O_NONBLOCK);
    rc = libevdev_new_from_fd(fd, &dev);
    if (rc < 0) {
      close(fd);
      libevdev_free(dev);
      free(event_path_generated);
      return NULL;
    }
    if (strcmp(name_to_compare, libevdev_get_name(dev)) == 0) {
      close(fd);
      libevdev_free(dev);
      return event_path_generated;
    }
    free(event_path_generated);
    close(fd);
    libevdev_free(dev);
    iteration++;
  }
  return NULL;
}
