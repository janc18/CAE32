#ifndef SETUP_H
#define SETUP_H
#include "struct_manipulation.h"
#include <pthread.h>
#include <stdbool.h>
bool hasSudoPermissions();
bool continueWithoutSudoPermissions();
bool itHasSudoPermissions(char *device_information_path);
bool isDevicefind(devices_handle *devices, int device_number, char *event_path);
bool threadCreation(pthread_t reader_thread, pthread_t processor_thread, char *event_path);
#endif // !SETUP_H
