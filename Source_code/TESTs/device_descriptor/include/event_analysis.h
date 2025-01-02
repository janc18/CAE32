#ifndef EVENT_ANALYSIS_H
#define EVENT_ANALYSIS_H

#include "read_event.h"

typedef struct eventCharacteristics{
  int eventValue[10];
  char eventName[30];
}eventCharacteristics;
int getNumberOfEvents(events *head);
int search_by_prefix(events *head, const char *prefix);
#endif // !EVENT_ANALYSIS_H
