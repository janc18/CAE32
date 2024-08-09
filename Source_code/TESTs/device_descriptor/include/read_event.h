#ifndef READ_EVENT_H
#define READ_EVENT_H
#include <libevdev-1.0/libevdev/libevdev.h>
#include <pthread.h>
#include <stdbool.h>
#define EVENT_BUFFER_SIZE 10

typedef struct event_buffer {
  struct input_event events[EVENT_BUFFER_SIZE];
  int head;
  int tail;
  int count;
  pthread_mutex_t mutex;
  pthread_cond_t cond;
  int stop;
} event_buffer;

typedef struct events {
  int val;
  char event_name[30];
  struct events *siguiente;
} events;

void terminal_print(events *cabeza);
void free_memory_events(events *cabeza);
int updateValue(events *cabeza, const char *event_name, int value);
void push(events **cabezaRef, int val, const char *event_name);
char *getEventPath(char *name_to_compare);
void *readEvents(void *path_event_void);
void *processEvents(void *arg);
void stopThreads();
void initializeEventBuffer(struct event_buffer *buffer);
void handle_signal(int sig);
event_buffer getDeviceBuffer();
#endif // !READ_EVENT_h
