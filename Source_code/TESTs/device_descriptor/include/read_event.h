#ifndef READ_EVENT_H
#define READ_EVENT_H
#include <libevdev-1.0/libevdev/libevdev.h>
#include <pthread.h>
#include <stdbool.h>
#define EVENT_BUFFER_SIZE 19
#define MAX_NUMBER_OF_VALUES 200
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
  int values[MAX_NUMBER_OF_VALUES];
  struct events *siguiente;
  int id;
} events;

void terminal_print(events *cabeza);
void free_memory_events(events *cabeza);
int updateValue(events *cabeza, const char *event_name, int value);
void push(events **cabezaRef, int val, const char *event_name);
char *getEventPath(char *name_to_compare);
void *readEvents(void *path_event_void);
void *processEvents(void *arg);
void stopThreads(void);
void initializeEventBuffer(struct event_buffer *buffer);
void handle_signal(int sig);
event_buffer getDeviceBuffer(void);
#endif // !READ_EVENT_h
