/**
 * @file struct_manipulation.c
 *
 * @brief Abstract all the functions from the functions token manipulation
 *
 * - To avoid direct access to all the components of the tokens structs, the functions developed here,
 *   have the objective to do very easily like just ask for the specific feature from an object regardless
 *   it's position of the feature in the array
 */

#include "struct_manipulation.h"
#include "parser.h"
#include "token_manipulation.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

devices_handle *get_all_information_from_device_c_32(char *file_path) {
  // Saving file into a string
  devices_handle *p_devices = malloc(sizeof(devices_handle));
  p_devices->string_file = file_to_string(file_path);
  if (p_devices->string_file == NULL) {
    printf("ERROR: At open file\n");
    free(p_devices);
    return NULL;
  }

  //  Getting raw tokens
  p_devices->number_of_lines = find_number_of_lines(p_devices->string_file);
  p_devices->array_of_strings = get_array_of_strings(p_devices->string_file);
  p_devices->values_tokens = get_array_of_tokens_from_an_string_array(p_devices->array_of_strings, p_devices->number_of_lines);

  // Alocating memory for all the objects indexes
  p_devices->number_of_correct_objects = find_number_of_objects(p_devices->values_tokens);
  // object_index **all_objects_indexes==p_devices->indexes
  p_devices->indexes = NULL;
  p_devices->indexes = get_all_objects(p_devices->values_tokens);

  // Parameter Objects verification
  int result_object = verify_parameters_of_all_objects(p_devices->values_tokens, p_devices->indexes, p_devices->number_of_correct_objects);

  if (result_object == 0)
    print_all_the_objects(p_devices->indexes, p_devices->values_tokens, p_devices->number_of_correct_objects);

  return p_devices;
}

void free_all_memory(devices_handle *p_devices) {
  if (p_devices != NULL) {
    free_get_all_object(p_devices->indexes, p_devices->number_of_correct_objects);
    free_array_of_lines(p_devices->array_of_strings, p_devices->number_of_lines);
    free_line_tokenize_struct(p_devices->values_tokens);
    free(p_devices->string_file);
    free(p_devices);
  }
}

bool feature_name_is_valid(char *feature) {

  int number_of_keywords = sizeof(Keywords) / sizeof(Keywords[0]);
  bool word_found = false;
  for (int i = 0; i < number_of_keywords; i++) {
    if (strcmp(Keywords[i], feature) == 0) { // Parameter found
      word_found = true;
      return true;
    }
  }
  if (!word_found) {
    fprintf(stderr, "ERROR: Unknown parameter [%s]\n", feature);
    return false;
  }
  return false;
}

char *get_feature_value_from_device_c32_file(int object_number, devices_handle *devices, char *feature) {
  if (feature == NULL) {
    fprintf(stderr, "ERROR: Feature parameter is NULL\n");
    return NULL;
  }
  if (object_number > devices->number_of_correct_objects) {
    fprintf(stderr, "ERROR: Invalid object number\n");
    return NULL;
  }

  if (!feature_name_is_valid(feature)) {
    return NULL;
  }

  for (int j = devices->indexes[object_number]->start + 1; j < devices->indexes[object_number]->end; j++) {
    if (strcmp(feature, devices->values_tokens->all_tokens[j]->parameter) == 0) { // Parameter found
      return devices->values_tokens->all_tokens[j]->value;
    }
  }
  fprintf(stderr, "This object [%s] doesn't have that feature[%s]\n",
          devices->values_tokens->all_tokens[devices->indexes[object_number]->start]->value, feature);
  return NULL;
}

char *get_object_name(int object_number, devices_handle *devices) {
  if (object_number < devices->number_of_correct_objects)
    return devices->values_tokens->all_tokens[devices->indexes[object_number]->start]->value;
  fprintf(stderr, "Doesn't exist at object with that index:%d\n", object_number);
  return NULL;
}

void print_data(char *data2print) {
  if (data2print != NULL) {
    printf("%s\n", data2print);
  } else {
    fprintf(stderr, "ERROR: Getting feature description\n");
  }
}
