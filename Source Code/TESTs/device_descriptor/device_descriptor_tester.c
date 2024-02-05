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
    printf("ERROR: At open file\n");
    return EXIT_FAILURE;
  }
  // Variable declaration
  int number_of_lines = 0;
  lines_tokenize *array_of_objects;
  char **array_of_strings;
  object_index *first_object= NULL;

  // Getting raw tokens
  number_of_lines = find_number_of_lines(contents_file);
  array_of_strings = get_array_of_strings(contents_file);
  array_of_objects = get_array_of_tokens_from_an_string_array(array_of_strings, number_of_lines);

  first_object= find_object(array_of_objects,0);


  if (first_object != NULL) {
    free(first_object);
  }

  free_array_of_lines(array_of_strings, number_of_lines);
  free_line_tokenize_struct(array_of_objects);
  free(contents_file);
  return EXIT_SUCCESS;
}
// Check how to read joystick devices
