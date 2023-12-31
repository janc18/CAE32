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

#include "parser.h"
#include "token_manipulation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  char *contents_file = file_to_string(argv[1]);
  if (contents_file == NULL) {
    printf("ERROR");
    return EXIT_FAILURE;
  }
  int number_of_lines= find_number_of_lines(contents_file);

  line_token **all_tokens;
  all_tokens = get_file_tokens(contents_file);
  object_index first_object;
  first_object=get_object(all_tokens,number_of_lines);
  printf("Printing object contents\n");
  get_contents_of_object(all_tokens,first_object);
  free_memory_tokens(all_tokens,number_of_lines);
  free(contents_file);
  return EXIT_SUCCESS;
}
// Check how to read joystick devices
