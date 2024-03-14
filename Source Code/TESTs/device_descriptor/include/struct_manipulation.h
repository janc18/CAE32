#ifndef STRUCT_MANIPULATION_H
#define STRUCT_MANIPULATION_H
#include "parser.h"
#include "token_manipulation.h"

typedef struct devices_handle {
  object_index **indexes;
  line_token *token;
  char* string_file;
  char** array_of_strings;
  lines_tokenize *values_tokens;
  int number_of_correct_objects;
  int number_of_lines;
} devices_handle;


devices_handle *get_all_information_from_device_c_32(char *file_path) ;
void free_all_memory(devices_handle *p_devices);
char *get_feature_value_from_device_c32_file(int object_number, devices_handle *devices, char *feature);
char *get_object_name(int object_number,devices_handle *devices);
void print_data(char *data2print);
#endif
