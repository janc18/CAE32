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
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const char Keywords[][30] = {"Start",   "End", "Size_bits", "Logical_Minimum", "Logical_Maximum", "Physical_Minumum", "Physical_Maximum",
                             "Buttons", "Axis"};

/**
 * @brief Convert input file to an string
 *
 *  Reads a file at a path given by the user and converts it
 *  to an string saved at the heap.
 *
 *  @param char* File path to *.c32
 *  @return char* On success, a string allocated at heap, or NULL if an error occurs
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
 *  Counts the number lines of an string_files until reaching the end of the string character '\0'
 *
 *  @param char* A string with the contents of file
 *
 *  @return int Number of lines or -1 if a the string file is null
 */
int find_number_of_lines(char *string_file) {
  if (string_file != NULL) {
    int number_of_lines = 0;
    int cursor = 0;
    while (string_file[cursor] != '\0') {
      if (string_file[cursor] == '\n') {
        number_of_lines++;
      }
      cursor++;
    }
    return number_of_lines + 1;
  } else {
    return -1;
  }
}
/**
 *  @brief Get a line token
 *
 *  Parser a line by seperating it with the ":" delimiter and return the values in a struct
 *
 *  @param char* Line to be parsed
 *
 *  @return line_token* A pointer to a struct with the value an parameter, or NULL if parsing get an error
 */
line_token *get_line_tokens(char *line) {
  if (line == NULL) {
    fprintf(stderr, "ERROR: NULL input line\n");
    return NULL;
  }
  line_token *pline_token = calloc(1, sizeof(line_token));
  if (pline_token == NULL) {
    fprintf(stderr, "ERROR: Unable to allocate memory for line_token\n");
    return NULL;
  }
  char param[50], value[50] = {0};
  int delimiter_ocurrence = number_of_delimiter(line, ':');
  int result = sscanf(line, " %49[^:]: %49[^\n]", param, value);

  if (result == 2 && delimiter_ocurrence == 1) {
    remove_extra_spaces(param);
    remove_extra_spaces(value);
    if (param[0] == '\0' || value[0] == '\0') { // string Empty
      free(pline_token);
      return NULL;
    }
    pline_token->parameter = strdup(param);
    pline_token->value = strdup(value);
    return pline_token;
  } else {
    free(pline_token);
    return NULL;
  }
  fprintf(stderr, "ERROR parsing line:%s\n", line);
  free(pline_token);
  return NULL;
}
/**
 * @brief Free memory from the line_token struct
 *
 * @param *line_token struct
 *
 * @return int 0=Success, -1=Error
 */
int free_line_token(line_token *tokens) {
  if (tokens == NULL) {
    fprintf(stderr, "WARNING: Trying to free a line_token struct that already is NULL\n");
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
 * @return char* An allocated string or NULL if char* string_file is NULL
 */
char *get_each_line_of_file_string(char *string_file, int *offset) {
  if (string_file == NULL)
    return NULL;
  char temp_line_buffer[50] = {0};
  int offset_pline_buffer = 0;
  // loop to get the n line or end of string
  while (string_file[*offset] != '\n') {
    if (string_file[*offset] != '\0') {
      temp_line_buffer[offset_pline_buffer] = string_file[*offset];
      offset_pline_buffer++;
      *offset = *offset + 1;
    } else {
      break;
    }
  }
  *offset = *offset + 1;                        // jump \n character
  temp_line_buffer[offset_pline_buffer] = '\0'; // add string terminate character

  int size_of_temp_line_buffer = strlen(temp_line_buffer) + 1;
  if (size_of_temp_line_buffer > sizeof(temp_line_buffer)) {
    return NULL;
  }
  char *pline_buffer = calloc(sizeof(char), size_of_temp_line_buffer);
  if (pline_buffer == NULL) {
    fprintf(stderr, "Can't allocate memory for line buffer\n");
    return NULL;
  }
  memcpy(pline_buffer, temp_line_buffer, size_of_temp_line_buffer);
  return pline_buffer;
}
/**
 * @brief Get all the tokens of string
 *
 * @param char* An string with the contents of the input file
 *
 * @return line_token** A pointer array of line tokens
 */
lines_tokenize *get_file_tokens(char *string_file) {
  if (string_file == NULL)
    return NULL;
  int number_of_lines = find_number_of_lines(string_file);
  // Getting each line and save at array_of_lines
  char **array_of_strings = get_array_of_strings(string_file);
  // Getting all the tokens from each line
  lines_tokenize *array_of_tokens = get_array_of_tokens_from_an_string_array(array_of_strings, number_of_lines);

  return array_of_tokens;
}

/**
 * @brief Free all the array pointers generated by get_file_tokens
 *
 * @param line_token** Struct with all the tokens of each line
 * @param int Number of lines of the given file
 *
 * @return int
 *  - 0 memory successfully free
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
/**
 * @brief Remove extra spaces than can cause issues
 *
 * For example don't is the same "Start: Name" to " Start:Name "
 * To adress that problem this function remove a space if it is more than one
 * and remove space at the start and the end of the line
 *
 * This function manipulate directly the string
 *
 * @param char* Line to remove extra spaces
 *
 * @return 0 if success or -1 if line is NULL
 */
int remove_extra_spaces(char *line) {
  if (line == NULL)
    return -1;

  int i, x, index = 0;
  for (i = x = 0; line[i]; ++i)
    if (!isspace(line[i]) || (i > 0 && !isspace(line[i - 1])))
      line[x++] = line[i];
  line[x] = '\0';
  int last_size_line = strlen(line);
  for (index = last_size_line; index >= 0; index--) {
    if (isspace(line[index]) || (!isspace(line[index - 1]))) {
      break;
    }
  }
  line[index] = '\0';
  return 0;
}
/**
 * @brief Count the number of delimeter matches at the input line
 *
 * @param char* Line to count the number of delimiters
 * @param char Delimiter character
 *
 * @return int with the number of matched delimiter
 */
int number_of_delimiter(char *line, char delimiter) {
  if (line == NULL)
    return -1;
  int counter = 0;
  while (*line) {
    if (*line == delimiter) {
      counter++;
    }
    line++;
  }
  return counter;
}
/**
 * @brief Get an array of string from an input string
 *
 * @param char* An String to separete in more string each new line
 *
 * @return char ** An array o string pointer or NULL if the string_file is NULL
 */
char **get_array_of_strings(char *string_file) {
  if (string_file == NULL)
    return NULL;
  int offsets = 0;
  int number_of_lines = find_number_of_lines(string_file);
  char temporal_array_lines[number_of_lines][50];
  for (int i = 0; i < number_of_lines; i++) {
    char *line = get_each_line_of_file_string(string_file, &offsets);
    strcpy(temporal_array_lines[i], line);
    free(line);
  }
  char **p_array_lines = calloc(sizeof(char), number_of_lines * 50);

  for (int i = 0; i < number_of_lines; i++) {
    p_array_lines[i] = strdup(temporal_array_lines[i]);
  }

  return p_array_lines;
}
/**
 * @brief Get all the tokens from each line
 *
 * @param char** Array of strings to search for tokens
 * @param int Number of lines from the file
 *
 * @return lines_tokenize AN Struct pointer with all the correct parsed lines and number of correct lines or NULL if
 * have an error in array_of_string
 */
lines_tokenize *get_array_of_tokens_from_an_string_array(char **array_of_strings, int number_of_lines) {
  if (array_of_strings == NULL)
    return NULL;
  line_token *array_of_lines_tokenize[number_of_lines];
  line_token **p_array_of_lines_tokenize = malloc(sizeof(line_token) * number_of_lines);

  int token_with_correct_syntax = 0;
  for (int i = 0; i < number_of_lines; i++) {
    array_of_lines_tokenize[i] = get_line_tokens(array_of_strings[i]);

    if (array_of_lines_tokenize[i] != NULL) { // Because a syntax error
      p_array_of_lines_tokenize[token_with_correct_syntax] = array_of_lines_tokenize[i];
      token_with_correct_syntax++;
      // #TODO check if its an empty line, if isn't, return null
    } else {
      fprintf(stderr, "ERROR: in string:[%s], at line %d\t", array_of_strings[i], i);
      analize_line(array_of_strings[i]);
      free_line_token(array_of_lines_tokenize[i]);
      continue;
    }
  }

  lines_tokenize *p_string_tokenize = malloc((sizeof(line_token) * token_with_correct_syntax) + sizeof(int));

  p_string_tokenize->number_of_lines = token_with_correct_syntax;
  p_string_tokenize->all_tokens = p_array_of_lines_tokenize;

  return p_string_tokenize;
}
/**
 * @brief Free memory allocated by the function get_array_of_strings
 *
 * @param char** Lines allocated
 * @param int Number of lines allocated
 * @return int 0 in success, -1 in Error
 */
int free_array_of_lines(char **lines_allocated, int number_of_lines) {
  if (lines_allocated != NULL) {
    for (int i = 0; i < number_of_lines; i++) {
      free(lines_allocated[i]);
      if (lines_allocated[i] == NULL)
        return -1;
    }
    free(lines_allocated);
  } else {
    return -1;
  }
  return 0;
}
/**
 * @brief Free memory allocated by the function get_array_of_tokens_from_an_string_array
 *
 * @param lines_tokenize* Struct pointer with all the lines tokenize
 * @return int 0 in success, -1 in Error
 */
int free_line_tokenize_struct(lines_tokenize *p_lines_tokenize) {
  if (p_lines_tokenize != NULL) {
    for (int i = 0; i < p_lines_tokenize->number_of_lines; i++) {
      if (p_lines_tokenize->all_tokens[i] == NULL)
        return -1;
      free_line_token(p_lines_tokenize->all_tokens[i]);
    }
    free(p_lines_tokenize->all_tokens);
    free(p_lines_tokenize);
  } else {
    return -1;
  }
  return 0;
}
int analize_line(char *line) {
  if (strcmp("", line) == 0) {
    fprintf(stderr, "Empty line\n");
  }
  return 0;
}
