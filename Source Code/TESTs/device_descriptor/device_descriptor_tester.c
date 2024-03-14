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

#include "read_file_descriptor.h"
#include "struct_manipulation.h"
#include <fcntl.h>
#include <linux/hidraw.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "read_event.h"

int main(int argc, char *argv[]) {

  // Check if it has sudo permission to read the report descriptor
  devices_handle *devices;
  devices = get_all_information_from_device_c_32(argv[1]);
  char *buttons = get_feature_value_from_device_c32_file(1, devices, "Buttons");
  char *object_name_1 = get_object_name(2, devices);
  print_data(buttons);

  char *event_path=get_event_path(object_name_1);
  printf("The path is:%s\nReading events\n",event_path);
  read_events(event_path);
  free_all_memory(devices);
  return EXIT_SUCCESS;
}
