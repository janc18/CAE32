/**
 * @file device_descriptor_tester.c
 * @brief Device descriptor tester
 *
 * @brief Checks if the desiered features are included at the device descriptor
 *
 * - To check if the device descriptor works correctly, it will tested after it's
 *   parser from the kernel
 *
 * - it require an input file to automate a little bit the test process
 */

#include "read_event.h"
#include "read_file_descriptor.h"
#include "struct_manipulation.h"
#include <fcntl.h>
#include <linux/hidraw.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  // Check if it has sudo permission to read the report descriptor
  if (argv[1] == NULL) { // Checking if a path was given
    fprintf(stderr, "ERROR: Doesn't give any input path\n");
    return EXIT_FAILURE;
  }

  devices_handle *devices;
  devices = getAllInformationFromDeviceC32(argv[1]);

  if (devices == NULL) {
    return EXIT_FAILURE;
  }

  char *buttons = getFeatureValueFromDeviceC32(1, devices, "Buttons");
  char *object_name_1 = getObjectName(2, devices);
  printData(buttons);

  char *event_path = getEventPath(object_name_1);
  printf("The path is:%s\nReading events\n", event_path);
  readEvents(event_path);
  freeAllMemory(devices);
  return EXIT_SUCCESS;
}
