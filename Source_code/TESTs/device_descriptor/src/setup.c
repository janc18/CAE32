#include "setup.h"
#include "read_event.h"
#include "struct_manipulation.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
/**
 * @brief Check if was executed with sudo permissions
 *
 *  @return bool True if has sudo permission or false if wasn't
 */
bool hasSudoPermissions() {
  if (getuid()) {
    fprintf(stderr, "Doesn't have sudo permissions to read the events, Want to continue? Y/n\n");
    return false;
  } else {
    return true;
  }
}
/**
 * @brief Read the input(one character) of the user
 *
 * Check if the user wants to keep executing the program without sudo permission,
 * this function verify if the input was(y,Y,\n)
 * @return bool True if the user wants to continue without sudo permission and false if wasn't
 */
bool continueWithoutSudoPermissions() {
  char response[9];
  fgets(response, 3, stdin);
  switch (response[0]) {
  case '\n':
    return true;
    break;
  case 'y':
    return true;
    break;
  case 'Y':
    return true;
    break;
  default:
    return false;
  }
}
/**
 * @brief Check if the program was executed as sudo user
 *
 * If the program wasn't executed as sudo or the given path for the device is invalid
 * the program would close
 *
 * @param char* device information path *.c32
 *
 * @return int -1 Doesn't want to continue or the path is invalid
 *              0 The program was executed as sudo and the given path is correct
 */
bool itHasSudoPermissions(char *device_information_path) {
  bool sudoPermission = false;
  // Check if it has sudo permission to read the report descriptor
  sudoPermission = hasSudoPermissions();
  if (!sudoPermission) {
    if (continueWithoutSudoPermissions() == false) {
      fprintf(stderr, "Isn't posible to read events without sudo permission, execute with sudo access\n");
      return false; // Quit program
    }
  }
  // Checking if a path was given
  if (device_information_path == NULL) {
    fprintf(stderr, "ERROR: Doesn't give any input path\n");
    return false;
  }
  return true;
}

/**
 * @brief Search for an specific device index
 *
 * It search for a given device number object at the input file
 *
 * @param devices_handle* device handle
 * @param int device number (Object device found in the input file)
 * @param char **
 * @return int -1 Doesn't want to continue or the path is invalid
 *              0 The program was executed as sudo and the given path is correct
 */
bool isDevicefind(devices_handle *devices, int device_number) {
  // demo code to extract information from the device(device *.cae32)
  // char *buttons = getFeatureValueFromDeviceC32(1, devices, "Buttons");
  char *object_name = getObjectName(device_number, devices);
  if (object_name!= NULL){
    return false;
  }
  // Getting information of the real device using the name extracted from the file
  char *pEventPathHeap = getEventPath(object_name); // Valgrind: Conditional jump or move depends on uninitialised value(s)
  if (pEventPathHeap == NULL) {
    fprintf(stderr, "ERROR: Doesn't found any device with that name:%s\n", object_name);
    // freeAllMemory(devices);
    return false;
  }
  devices->eventPath =pEventPathHeap;
  return true;
}

bool threadCreation(pthread_t reader_thread, pthread_t processor_thread, char *event_path) {

  events *cabeza = (events *)calloc(sizeof(events), 1);
  if (pthread_create(&reader_thread, NULL, readEvents, (void *)event_path) != 0) {
    fprintf(stderr, "Error creating reader thread\n");
    return false;
  }

  if (pthread_create(&processor_thread, NULL, processEvents, (void *)cabeza) != 0) {
    fprintf(stderr, "Error creating processor thread\n");
    return false;
  }
  pthread_join(reader_thread, NULL);
  pthread_join(processor_thread, NULL);
  return true;
}
