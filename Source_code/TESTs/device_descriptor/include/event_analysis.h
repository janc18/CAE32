#ifndef EVENT_ANALYSIS_H
#define EVENT_ANALYSIS_H

#include "read_event.h"
int getNumberOfEvents(events *head);

typedef struct eventCharacteristics{
  int eventValue[10];
  char eventName[30];
}eventCharacteristics;

#endif // !EVENT_ANALYSIS_H
