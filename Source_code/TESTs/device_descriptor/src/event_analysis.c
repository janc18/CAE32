#include "event_analysis.h"
#include "read_event.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
void generateDataSet(events *head, eventCharacteristics *event) {
  // Allocating memory
  eventCharacteristics *peventcharacteristics = calloc(sizeof(eventCharacteristics), 1);
}
*/
int getNumberOfEvents(events *head) {
  int numberOfEvents = 0;
  events *current = head;

  if (head == NULL) {
    printf("(arg)Head is null\n");
    return -1;
  }

  while (current != NULL) {
    numberOfEvents++;
    current = current->siguiente;
  }
  return numberOfEvents;
}
int search_by_prefix(events *head, const char *prefix) {
  events *current = head;
  int numberOfElements = 0;
  while (current != NULL) {
    if (strncmp(current->event_name, prefix, 3) == 0) {
      numberOfElements++;
    }
    current = current->siguiente;
  }
  return numberOfElements;
}
