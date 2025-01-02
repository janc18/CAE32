#include "event_analysis.h"
#include "read_event.h"
#include <stdio.h>
#include <stdlib.h>
/*
void generateDataSet(events *head, eventCharacteristics *event) {
  // Allocating memory
  eventCharacteristics *peventcharacteristics = calloc(sizeof(eventCharacteristics), 1);
}
*/
int getNumberOfEvents(events *head) {
  int numberOfEvents = 0;
  events *current = head;
  
  if(head == NULL){
    printf("(arg)Head is null\n");
    return -1;
  }
  
  while (current != NULL) {
    numberOfEvents++;
    current = current->siguiente;
  }
  return numberOfEvents;
}
/*
int appendValue(events head){
//
}
*/
