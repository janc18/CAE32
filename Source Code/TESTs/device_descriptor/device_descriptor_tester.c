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
#include <stdlib.h>

int main(int argc, char *argv[]) {
  devices_handle *devices;
  devices=get_all_information_from_device_c_32(argv[1]);
  free_all_memory(devices);
  return EXIT_SUCCESS;
}
// Check how to read joystick devices
