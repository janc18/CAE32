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
#include "setup.h"
#include "struct_manipulation.h"
#include <fcntl.h>
#include <linux/hidraw.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if(argc!=2){
    printf("Doesn't give input file (devices.cae32)");
    return EXIT_FAILURE;
  }
  signal(SIGINT, handle_signal);

  if (!itHasSudoPermissions(argv[1])) {
    return EXIT_FAILURE;
  }
  // Get device's information using the file *.cae32
  devices_handle *devices = NULL;
  devices = getAllInformationFromDeviceC32(argv[1]);
  // Checking if the device's information was correct
  if (devices == NULL) {
    printf("Error at getting devices\n");
    return EXIT_FAILURE;
  }

  // Searching from the device's name given and getting the event_path
  // event_path example: /dev/input/event15
  if (!isDevicefind(devices, 2)){
    if (devices != NULL) {
      printf("The device doesn't found\n");
      freeAllMemory(devices);
      return EXIT_FAILURE;
    }
  }
  if (devices->eventPath == NULL) {
    printf("An error happend getting the path");
    return EXIT_FAILURE;
  }
  printf("The path is:%s\nReading events in 3 seconds ...\n", devices->eventPath);
  sleep(3);
  // Creation of threads to read and print the output data from de device
  pthread_t reader_thread = 0, processor_thread=0;
  if (!threadCreation(reader_thread, processor_thread, devices->eventPath)) {
    fprintf(stderr, "ERROR: Creating threads\n");
    freeAllMemory(devices);
    return EXIT_FAILURE;
  }
  if (devices != NULL) {
    freeAllMemory(devices);
  }
  return EXIT_SUCCESS;
}
