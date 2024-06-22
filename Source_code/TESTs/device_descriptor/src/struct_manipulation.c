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

/**
 * @brief Get all the information from input file
 *
 * Create a device handle with all the data gived by the input file
 *
 *  @param char* File path to *.c32
 *  @return devices_handle* pointer On success, or NULL if an error occurs
 */
devices_handle *getAllInformationFromDeviceC32(char *file_path) {
  // Saving file into a string
  devices_handle *p_devices = malloc(sizeof(devices_handle));
  p_devices->string_file = fileToString(file_path);
  if (p_devices->string_file == NULL) {
    printf("ERROR: At open file\n");
    free(p_devices);
    return NULL;
  }

  //  Getting raw tokens
  p_devices->number_of_lines = findNumberOfLines(p_devices->string_file);
  p_devices->array_of_strings = getArrayOfStrings(p_devices->string_file);
  p_devices->values_tokens = getArrayOfTokensFromAnStringArray(p_devices->array_of_strings, p_devices->number_of_lines);

  // Alocating memory for all the objects indexes
  p_devices->number_of_correct_objects = findNumberOfObjects(p_devices->values_tokens);
  // object_index **all_objects_indexes==p_devices->indexes
  p_devices->indexes = NULL;
  p_devices->indexes = getAllObjects(p_devices->values_tokens);

  // Parameter Objects verification
  int result_object = verifyParametersOfAllObjects(p_devices->values_tokens, p_devices->indexes, p_devices->number_of_correct_objects);

  if (result_object == 0)
    printAllTheObjects(p_devices->indexes, p_devices->values_tokens, p_devices->number_of_correct_objects);

  return p_devices;
}

/**
 * @Free all the memory
 *
 *  Deallocate memory from the devices_handle struct
 *
 *  @param *devices_handle
 */
void freeAllMemory(devices_handle *p_devices) {
  if (p_devices != NULL) {
    freeGetAllObject(p_devices->indexes, p_devices->number_of_correct_objects);
    freeArrayOfLines(p_devices->array_of_strings, p_devices->number_of_lines);
    freeLineTokenizeStruct(p_devices->values_tokens);
    free(p_devices->string_file);
    free(p_devices);
  }
}

/**
 * @Check if a feature is valid
 *
 *  Compare a feature name to Keywords array(found at parser.h)
 *
 *  @param *char feature name
 *
 *  @return bool True if the word is found or false otherway
 */
bool featureNameIsValid(char *feature) {

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

/**
 * @Get the value from a feature in a given object
 *
 *  @param int Object number
 *  @param *devices_handle
 *  @char *feature
 *
 *  @return char* Value from the feature or NULL if an error occur
 */
char *getFeatureValueFromDeviceC32(int object_number, devices_handle *devices, char *feature) {
  if (feature == NULL) {
    fprintf(stderr, "ERROR: Feature parameter is NULL\n");
    return NULL;
  }
  if (object_number > devices->number_of_correct_objects) {
    fprintf(stderr, "ERROR: Invalid object number\n");
    return NULL;
  }

  if (!featureNameIsValid(feature)) {
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

/**
 * @Get the object name
 *
 *  @param int object_number
 *  @param *devices_handle
 *
 *  @return *char name of the object or NULL if doesn't exist
 */
char *getObjectName(int object_number, devices_handle *devices) {
  if (object_number < devices->number_of_correct_objects)
    return devices->values_tokens->all_tokens[devices->indexes[object_number]->start]->value;
  fprintf(stderr, "Doesn't exist at object with that index:%d\n", object_number);
  return NULL;
}

/**
 * @Print string securely
 *
 *  Check if doesn't is NULL
 *
 *  @param char* string to print
 */
void printData(char *data2print) {
  if (data2print != NULL) {
    printf("%s\n", data2print);
  } else {
    fprintf(stderr, "ERROR: Getting feature description\n");
  }
}
