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
  int number_of_lines = find_number_of_lines(contents_file);
  lines_tokenize *all_tokens;
  all_tokens = get_file_tokens(contents_file);
  int start_index = 0;
  object_index **objects;
  objects = get_objects_index(all_tokens->all_tokens, number_of_lines);
  print_contents_of_n_object(all_tokens->all_tokens, *objects[2]);//printing third object contents
  free_memory_tokens(all_tokens->all_tokens, number_of_lines);
  free_memory_object(objects);
  free(contents_file);
  return EXIT_SUCCESS;
}
// Check how to read joystick devices
