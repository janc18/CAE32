#ifndef READ_EVENT_H
#define READ_EVENT_H
#include <stdbool.h>
char *getEventPath(char *name_to_compare);
void readEvents(char *path_event);
bool hasSudoPermissions();
bool continueWithoutSudoPermissions();
#endif // !READ_EVENT_h
