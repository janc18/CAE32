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

#include "struct_manipulation.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  devices_handle *devices;
  devices = get_all_information_from_device_c_32(argv[1]);
  char *buttons = get_feature_value_from_device_c32_file(1, devices, "Buttons");
  if (buttons != NULL)
    printf("Quantity of buttons %s\n", buttons);
  free_all_memory(devices);
  return EXIT_SUCCESS;
}
