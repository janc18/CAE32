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

  // Getting raw tokens
  number_of_lines = find_number_of_lines(contents_file);
  array_of_strings = get_array_of_strings(contents_file);
  array_of_objects = get_array_of_tokens_from_an_string_array(array_of_strings, number_of_lines);

  // Alocating memory for all the objects indexes
  int number_of_correct_objects = find_number_of_objects(array_of_objects);
  object_index **all_objects_indexes = NULL;
  if (number_of_correct_objects != -1) {
    all_objects_indexes = calloc(sizeof(object_index), number_of_correct_objects);
    all_objects_indexes[0] = find_object(array_of_objects, 0);
    for (int i = 1; i < number_of_correct_objects; i++) {
      all_objects_indexes[i] = find_object(array_of_objects, all_objects_indexes[i - 1]->end);
    }
  } else {
    fprintf(stderr, "ERROR: Don't found any objects\n");
  }

  for (int i = 0; i < number_of_correct_objects; i++) {
    print_contents_of_n_object(array_of_objects, all_objects_indexes[i]);
  }
  for (int i = 0; i < number_of_correct_objects; i++) {
  free(all_objects_indexes[i]);
  }
  free(all_objects_indexes);
  // 
  free_array_of_lines(array_of_strings, number_of_lines);
  free_line_tokenize_struct(array_of_objects);
  free(contents_file);
  return EXIT_SUCCESS;
}
// Check how to read joystick devices
