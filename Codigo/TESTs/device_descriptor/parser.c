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

const char Keywords[][30] = {"Start", "End", "Size_bits", "Logical_Minimum", "Logical_Maximum", "Physical_Minumum", "Physical_Maximum"};

/* @brief Convert input file to an string
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
/*  @brief Find a word in a given string
 *
 *   Reads a line until a new line and search for any match and print if the word was founded
 *
 *   @param *string_file String with all the file content
 *   @param *word Word for searching
 *   @param offset int with the character array value to start to read
 *
 *   @return new offset until new line or -1 if its the end of the string
 */
int **find_word(char *string_file, char *word, int offset) { // and return a flag of word found
  int **cursor_and_flag = (int **)malloc(2 * sizeof(int *));
  cursor_and_flag[0] = (int *)malloc(sizeof(int));
  cursor_and_flag[1] = (int *)malloc(sizeof(int));
  *(cursor_and_flag[0]) = offset;
  *(cursor_and_flag[1]) = 0;
  if (string_file == NULL) {
    // return -1;
    *(cursor_and_flag[0]) = -1;
    return cursor_and_flag;
  }
  char *line_buffer = malloc(sizeof(char) * 50);
  strcpy(line_buffer, "0");
  int line_buffer_off = 0;

  while (string_file[offset] != '\n') {                 // Run for each character at line
    line_buffer[line_buffer_off] = string_file[offset]; // save line contents to a temporary buffer
    offset++;                                           // String File offset
    line_buffer_off++;
    if (string_file[offset] == '\0') {
#ifdef DEBUG
      printf("End of File string_file");
#endif /* ifdef DEBUG */
      free(line_buffer);
      *(cursor_and_flag[0]) = -1;
      return cursor_and_flag;
      // return -1;
    }
  }

  line_buffer[offset] = '\0';
  if (strcmp(line_buffer, "0") != 0) { // Checking if line buffer is empty
    char **token = get_line_tokens(line_buffer);
    if (strcmp(token[0], word) == 0 && token != NULL) { // Checking if the token its the same as word and not null
      printf("Word found: %s\n", token[0]);
      // return 0; // Success
    }
  }
#ifdef DEBUG
  else {
    printf("Empty line\n");
  }
#endif /* ifdef DEBUG */
  free(line_buffer);

  *(cursor_and_flag[0]) = offset + 1;
  return cursor_and_flag;
  // return offset + 1; // jump the last new line escape secuence
}

int find_number_of_lines(char *string_file) {
  if (string_file != NULL) {
    int number_of_lines = 0;
    int cursor = 0;
    while (string_file[cursor] != '\0') {
      cursor++;
      if (string_file[cursor] == '\n')
        number_of_lines++;
    }
    return number_of_lines;
  } else {
    return -1;
  }
}

// Found the object size
// Create an array with the contents of each line
// compare the start and end of common names
// Create a new array just with the contents of the block
// Tokenize with the ":" delimiter
//
/*  @brief Get a line token
 *
 *  Get a token in a string, this function separate that string with the
 *  delimiter of ":" and create two strings
 *
 *  @param line char to try to be separate
 *
 *  @return A double char pointer or NULL
 */
char **get_line_tokens(char *line) {
  // The line needs to follow the next structure
  //|Parameter|:|Value|\n
  char *parameter;
  char *value;
  char **token = malloc(sizeof(char *) * 2);
  if (line != NULL) {
    parameter = strtok(line, ":");
    value = strtok(NULL, ":\n");
    if (parameter != NULL && value != NULL) {
      token[0] = strdup(parameter);
      token[1] = strdup(value);
      return token;
    }
  }
#ifdef DEBUG
  printf("ERROR at processing line");
#endif /* ifdef DEBUG */
  free(token);
  return NULL;
}
/* @brief Save all the contents of an object
 *
 * This save all the parameters of an object included his values
 * searching for the start an end,
 *
 */
int find_object(char *string_file) {
  // 1. find start and save value
  // 2. find end and save value
  // 3. compare the values saved
  //    - if are the same, save the cursors
  //    - if not throw an Error (return)
  // 4. Save all the tokens between the cursors
  // 5. build an struct with the tokens with malloc
  // 6 return pointer with the struct

  // int tokens_line=find_number_of_lines(string_file)+1;

  // int cursors[tokens_line]; //Getting the number of tokens

  int number_of_keywords = 7; // TODO: do automatic

  for (int i = 0; i < number_of_keywords; i++) {
    printf("\033[32mOcurrence of the word: %s\n\033[0m", Keywords[i]);
    int **cursor_and_flag = find_word(string_file, (char *)Keywords[i], 0);
    while (*(cursor_and_flag)[0] != -1) {
      cursor_and_flag = find_word(string_file, (char *)Keywords[i], *(cursor_and_flag)[0]);
    }
    printf("\033[32mEND\n\033[0m");
  }
  return 1;
}
