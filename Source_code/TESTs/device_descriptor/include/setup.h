#ifndef SETUP_H
#define SETUP_H
#include <stdbool.h>
bool hasSudoPermissions();
bool continueWithoutSudoPermissions();
bool itHasSudoPermissions(char *device_information_path);
#endif // !SETUP_H
