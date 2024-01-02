/**
 * @file parser.c
 * @brief device.c32 File parser
 *
 * @brief Parser for automatic device descriptor test

 * - To quickly test new device descriptors and tested in a row,
 *   the input file "device.c32", has a technical description of how
 *   will be represent the new HID device(Pedals, Shifter, Steering Wheel)
 */

#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const char Keywords[][30] = {"Start",   "End", "Size_bits", "Logical_Minimum", "Logical_Maximum", "Physical_Minumum", "Physical_Maximum",
                             "Buttons", "Axis"};

/**
 * @brief Convert input file to an string
 *
 *  Read the file at the file path gived by the user and corverted
 *  to an string saved at the heap
 *
 *  @param file_path File path *.c32
 *  @return Pointer to the string created or NULL in the case of ERROR
 */
char *file_to_string(char *file_path) {
  FILE *fptr_devices;
  fptr_devices = fopen(file_path, "r");

  if (fptr_devices == NULL)
    return NULL;

  fseek(fptr_devices, 0, SEEK_END);
  int lenght = ftell(fptr_devices);
  fseek(fptr_devices, 0, SEEK_SET);

  char *string = malloc(sizeof(char) * (lenght + 1));

  char c;
  int i = 0;

  while ((c = fgetc(fptr_devices)) != EOF) {
    string[i] = c;
    i++;
  }
  string[i] = '\0';
  fclose(fptr_devices);
  return string;
}
/**
 * @brief Get the number of lines
 *
 *  Counts the number lines of an string_files until reach the end of strinf character '\0'
 *
 *  @param char* A string with the contents of file
 *
 *  @return int Number of lines or -1 if a the string file is null
 */
int find_number_of_lines(char *string_file) {
  if (string_file != NULL) {
    int number_of_lines = 0;
    int number_of_empty_lines = 0;
    int cursor = 0;
    while (string_file[cursor] != '\0') {
      cursor++;
      if (string_file[cursor] == '\n') {
        number_of_lines++;
      }
      if (string_file[cursor] == '\n' && string_file[cursor - 1] == '\n') {
        number_of_empty_lines++;
      }
    }
#ifdef DEBUG
    printf("Empty lines=%d\n", number_of_empty_lines);
#endif /* ifdef DEBUG */
    return number_of_lines;
  } else {
    return -1;
  }
}
/**
 * @brief Get a line token
 *
 *  Get a token in a string, this function separate that string with the
 *  ":" delimiter and return that values in a struct;
 *
 *  @param line char to try to separate
 *
 *  @return line_token A struct with the value an parameter
 */
line_token *get_line_tokens(char *line) {
  if (line == NULL) {
#ifdef DEBUG
    printf("ERROR: NULL input line\n");
#endif /* ifdef DEBUG */
    return NULL;
  }

  line_token *pline_token = malloc(sizeof(line_token));
  if (pline_token == NULL) {
#ifdef DEBUG
    printf("ERROR: Unable to allocate memory for line_token\n");
#endif /* ifdef DEBUG */
    return NULL;
  }

  char temp_line_buffer[50];
  strcpy(temp_line_buffer, line);

  char param[50] = {0};
  char value[50] = {0};
  int result = sscanf(line, "%49[^:]: %49[^\n]", param, value);
  if (result == 2) {
    pline_token->parameter = strdup(param);
    pline_token->value = strdup(value);
    return pline_token;
  } else {
#ifdef DEBUG
    printf("ERROR parsing line:%s\n", temp_line_buffer);
#endif /* ifdef DEBUG */
    if (strlen(temp_line_buffer) == 0) {
#ifdef DEBUG
      printf("Empty Line\n");
#endif /* ifdef DEBUG */
      pline_token->parameter = strdup("EL");
      pline_token->value = strdup("EL");
    } else {
      printf("Parameter=[%s],Value[%s]\n", param, value);
      pline_token->parameter = strdup("ERROR");
      pline_token->value = strdup("ERROR");
    }
    return pline_token;
  }
#ifdef DEBUG
  printf("ERROR: Unable to process line\n");
#endif /* ifdef DEBUG */
  free(pline_token);
  return NULL;
}
/**
 * @brief Free memory from the line_token struct
 *
 * @param line_token struct
 *
 * @return int 0=Success, -1=Error
 */
int free_line_token(line_token *tokens) {
  if (tokens == NULL) {
#ifdef DEBUG
    printf("ERROR at trying to free memory\n");
#endif /* ifdef DEBUG */
    return -1;
  } else {
    free(tokens->value);
    free(tokens->parameter);
    free(tokens);
    return 0;
  }
}
/**
 * @brief Get a line of an string
 *
 * @param char* An string with the contents of the input file
 * @param int* Index of the string to start to iterate
 *
 * @return char* N line string
 */
char *get_each_line_of_file_string(char *string_file, int *offset) {
  char temp_line_buffer[50] = {0};
  int offset_pline_buffer = 0;
  // loop to get the n line
  while (string_file[*offset] != '\n') {
    temp_line_buffer[offset_pline_buffer] = string_file[*offset];
    offset_pline_buffer++;
    *offset = *offset + 1;
  }
  *offset = *offset + 1;                        // jump \n character
  temp_line_buffer[offset_pline_buffer] = '\0'; // add string terminate character

  int size_of_temp_line_buffer = strlen(temp_line_buffer);

  char *pline_buffer = malloc(sizeof(char) * (size_of_temp_line_buffer + 1));
  if (pline_buffer == NULL) {
    printf("Can't allocate memory for line buffer");
    return NULL;
  }
  strcpy(pline_buffer, temp_line_buffer);
  return pline_buffer;
}
/**
 * @brief Get all the tokens of string
 *
 * @param char* An string with the contents of the input file
 *
 * @return line_token** A pointer array of line tokens
 */
line_token **get_file_tokens(char *string_file) {
  // Create an array of line tokens with the size of numbers of lines of the files
  int number_of_lines = find_number_of_lines(string_file);
  line_token **plines_to_tokenize = malloc(sizeof(line_token) * number_of_lines);
  line_token *array_of_lines_tokenize[number_of_lines];
  char *p_array_of_lines[number_of_lines];
  // Getting each line and save at p_array_of_lines
  int offsets = 0;
  for (int i = 0; i < number_of_lines; i++) {
    p_array_of_lines[i] = get_each_line_of_file_string(string_file, &offsets);
    if (p_array_of_lines[i] == NULL) {
      printf("Error\n");
      free(p_array_of_lines[i]);
    }
  }
  // Getting all the tokens from each line
  for (int i = 0; i < number_of_lines; i++) {
    array_of_lines_tokenize[i] = get_line_tokens(p_array_of_lines[i]);
    if (array_of_lines_tokenize[i] == NULL) {
      printf("Error in string:[%s]\n", p_array_of_lines[i]);
      free_line_token(*plines_to_tokenize);
    }
  }
  // copy pointers to plines_to_tokenize
  for (int i = 0; i < number_of_lines; i++) {
    plines_to_tokenize[i] = array_of_lines_tokenize[i];
  }

  for (int i = 0; i < number_of_lines; i++) {
    free(p_array_of_lines[i]);
  }
  return plines_to_tokenize;
}

/**
 * @brief Free all the array pointers generated by get_file_tokens
 * 
 * @param line_token** Struct with all the tokens of each line
 * @param int Number of lines of the given file
 * 
 * @return int 
 *  - 0 free memry successfully
 *  - -1 line_token** is NULL
 */
int free_memory_tokens(line_token **tokens, int number_of_lines) {
  if (tokens != NULL) {
    for (int i = 0; i < number_of_lines; i++) {
      free_line_token(tokens[i]);
    }
    free(tokens);
    return 0;
  }
  return -1;
}
