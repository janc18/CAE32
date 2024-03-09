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
#include <linux/hidraw.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  devices_handle *devices;
  devices = get_all_information_from_device_c_32(argv[1]);
  char *buttons = get_feature_value_from_device_c32_file(1, devices, "Buttons");
  char *object_name_1 = get_object_name(2, devices);
  if (object_name_1 != NULL) {
    printf("%s\n", object_name_1);
    char *hid_path = search_device(object_name_1);
    if (hid_path != NULL) {
      struct hidraw_report_descriptor *rpt_des;
      rpt_des = get_report_descriptor(hid_path);
      free(hid_path);
      printf("%xxh\n",rpt_des->value[0]);
    }
  }
  free_all_memory(devices);
  return EXIT_SUCCESS;
}
