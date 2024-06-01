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


devices_handle *getAllInformationFromDeviceC32(char *file_path) ;
void freeAllMemory(devices_handle *p_devices);
char *getFeatureValueFromDeviceC32(int object_number, devices_handle *devices, char *feature);
char *getObjectName(int object_number,devices_handle *devices);
void printData(char *data2print);
#endif
