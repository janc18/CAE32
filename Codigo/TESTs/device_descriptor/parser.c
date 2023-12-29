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
/*  @brief Get the number of lines
 *
 *  Counts the number lines of an string_files until reach a escape secuence '\0'
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
      cursor++;
      if (string_file[cursor] == '\n')
        number_of_lines++;
    }
    return number_of_lines;
  } else {
    return -1;
  }
}
/*  @brief Get a line token
 *
 *  Get a token in a string, this function separate that string with the
 *  ":" delimiter and return that values in a struct;
 *
 *  @param line char to try to separate
 *
 *  @return line_token A struct with the value an parameter or null if can't parser
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
  int result = sscanf(line, "%49[^:]:%49s", param, value);
  if (result == 2) {
    pline_token->parameter = strdup(param);
    pline_token->value = strdup(value);
    return pline_token;
  } else {
    printf("ERROR parsing:%s\n", temp_line_buffer);
    free(pline_token);
    return NULL;
  }
#ifdef DEBUG
  printf("ERROR: Unable to process line\n");
#endif /* ifdef DEBUG */
  free(pline_token);
  return NULL;
}
/*
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
//This function needs to iterare from each line of the file
char *get_each_line_of_file_string(char *string_file, int *offset) {
  char *pline_buffer = malloc(sizeof(char) * 50);
  if (pline_buffer == NULL) {
    printf("Can't allocate memory for line buffer");
    return NULL;
  }
  int offset_pline_buffer=0;
  //loop to get the n line
  while(string_file[*offset]!='\n'){
  pline_buffer[offset_pline_buffer]=string_file[*offset];
  offset_pline_buffer++;
  *offset=*offset+1;
  }
  *offset=*offset+1;//jump \n character
  pline_buffer[offset_pline_buffer]='\0';//add string terminate character
  printf("size of string [%s] -is- %lu\n",pline_buffer,strlen(pline_buffer));
  return pline_buffer;
}
int get_file_tokens(char *string_file) {
  // Create an array of line tokens with the size of numbers of lines of the files
  int number_of_lines = find_number_of_lines(string_file);
  line_token *file_token[number_of_lines];
  return 0;
}
