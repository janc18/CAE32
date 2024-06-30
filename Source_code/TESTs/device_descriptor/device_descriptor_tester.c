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
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  signal(SIGINT, handle_signal);
  bool sudoPermission = false;
  // Check if it has sudo permission to read the report descriptor
  sudoPermission = hasSudoPermissions();
  if (!sudoPermission) {
    if (continueWithoutSudoPermissions() == false) {
      return EXIT_FAILURE; // Quit program
    }
  }
  // Checking if a path was given
  if (argv[1] == NULL) {
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

  if (!sudoPermission) {
    fprintf(stderr, "Isn't posible to read events without sudo permission, execute with sudo access\n");
    freeAllMemory(devices);
    return EXIT_FAILURE;
  }

  char *event_path = getEventPath(object_name_1); // Valgrind: Conditional jump or move depends on uninitialised value(s)
  if (event_path == NULL) {
    fprintf(stderr, "ERROR: Doesn't found any device with that name:%s\n", object_name_1);
    freeAllMemory(devices);
    return EXIT_FAILURE;
  }
  /**/
  struct hidraw_report_descriptor *device1;
  device1 = getReportDescriptor(object_name_1);
  for (int i = 0; i < device1->size; i++) {
    existInArray(device1->value[i], usage_id_axis_values, 6);
  }

  /**/
  printf("The path is:%s\nReading events\n", event_path);
  if (event_path == NULL) {
    freeAllMemory(devices);
    return EXIT_FAILURE;
  }
  // readEvents(event_path);
  pthread_t reader_thread, processor_thread;
  event_buffer initializeDeviceBuffer = getDeviceBuffer();
  if (pthread_create(&reader_thread, NULL, readEvents, (void *)event_path) != 0) {
    fprintf(stderr, "Error creating reader thread\n");
    return 1;
  }

  if (pthread_create(&processor_thread, NULL, processEvents, NULL) != 0) {
    fprintf(stderr, "Error creating processor thread\n");
    return 1;
  }
  pthread_join(reader_thread, NULL);
  pthread_join(processor_thread, NULL);
  freeAllMemory(devices);
  return EXIT_SUCCESS;
}
