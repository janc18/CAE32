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
    int cursor = 0;
    while (string_file[cursor] != '\0') {
      cursor++;
      if (string_file[cursor] == '\n') {
        number_of_lines++;
      }
    }
    return number_of_lines + 1;
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
  char param[50] = {0};
  char value[50] = {0};
  int delimiter_ocurrence = number_of_delimiter(line, ':');
  int result = sscanf(line, "%49[^:]: %49[^\n]", param, value);

  if (result == 2 && delimiter_ocurrence == 1) {
    remove_extra_spaces(param);
    remove_extra_spaces(value);
    if (strcmp(param, "") == 0 | strcmp(value, "") == 0) { // One string Empty
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
#ifdef DEBUG
  printf("ERROR parsing line:%s\n", temp_line_buffer);
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
 * @return char* An allocated string
 */
char *get_each_line_of_file_string(char *string_file, int *offset) {
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

  int size_of_temp_line_buffer = strlen(temp_line_buffer);

  char *pline_buffer = malloc(sizeof(char) * (size_of_temp_line_buffer));
  if (pline_buffer == NULL) {
#ifdef DEBUG
    printf("Can't allocate memory for line buffer");
#endif /* ifdef DEBUG */
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
lines_tokenize *get_file_tokens(char *string_file) {
  int number_of_lines = find_number_of_lines(string_file);
  // Getting each line and save at array_of_lines
  char **array_of_strings = get_array_of_strings(string_file);
  // Getting all the tokens from each line

  /*
   line_token **plines_to_tokenize = calloc(sizeof(line_token), ne_index);
   // copy pointers to plines_to_tokenize
   lines_tokenize *after_process;
   int index_nn = 0;
   for (int i = 0; i < number_of_lines; i++) {
     if (array_of_lines_tokenize == NULL) {
     } else {
       plines_to_tokenize[index_nn] = array_of_lines_tokenize;
       index_nn++;
     }
   }
   for (int i = 0; i < index_nn; i++) {
     if (plines_to_tokenize[i] != NULL) {
       after_process->all_tokens[i] = plines_to_tokenize[i];
       printf("Asigned memory of plines_to_tokenize:%p an after_process struct:%p in index:%d\n", plines_to_tokenize[i], after_process->all_tokens[i],
              i);

     } else {
       printf("NULL %d\n", i);
     }
   }
   //
   for (int i = 0; i < number_of_lines; i++) {
     if (p_array_of_lines[i] != NULL) {
       free(p_array_of_lines[i]);
     }
   }
   // for (int i = 0; i < ne_index; i++) {
   //   free_line_token(after_process->all_tokens[i]);
   // }
   printf("address of %p at index %d\n", after_process->all_tokens[24], 24);
   printf("Value of index 24:%s", after_process->all_tokens[24]->parameter);
   after_process->number_of_lines = ne_index;
   printf("%d\n", after_process->number_of_lines);
   return NULL;
   */
  return NULL;
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

int remove_extra_spaces(char *line) {
  int i, x,index;
  for (i = x = 0; line[i]; ++i)
    if (!isspace(line[i]) || (i > 0 && !isspace(line[i - 1])))
      line[x++] = line[i];
  line[x] = '\0';
  int last_size_line = strlen(line);
  for (index = last_size_line; index >= 0; index--) {
    if (isspace(line[index]) || (index < 0 && !isspace(line[index - 1]))) {
      break;
    }
  }
  line[index]='\0';
  return 0;
}

int number_of_delimiter(char *line, char delimiter) {
  int counter = 0;
  while (*line) {
    if (*line == delimiter) {
      counter++;
    }
    line++;
  }
  return counter;
}

char **get_array_of_strings(char *string_file) {
  int offsets = 0;
  int number_of_lines = find_number_of_lines(string_file);
  char temporal_array_lines[number_of_lines][50];
  for (int i = 0; i < number_of_lines; i++) {
    char *line = get_each_line_of_file_string(string_file, &offsets);
    strcpy(temporal_array_lines[i], line);
  }
  char **p_array_lines = calloc(sizeof(char), number_of_lines * 50);

  for (int i = 0; i < number_of_lines; i++) {
    p_array_lines[i] = strdup(temporal_array_lines[i]);
  }

  return p_array_lines;
}

lines_tokenize *get_array_of_tokens_from_an_string_array(char **array_of_strings, int number_of_lines) {
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
#ifdef DEBUG
      printf("Error in string:[%s], at line %d\n", array_of_strings[i], i);
#endif /* ifdef DEBUG */
      // #TODO take in consideration the kind of error, and give information about to the user
      continue;
    }
  }

  lines_tokenize *p_string_tokenize = malloc((sizeof(line_token) * token_with_correct_syntax) + sizeof(int));

  p_string_tokenize->number_of_lines = token_with_correct_syntax;
  p_string_tokenize->all_tokens = p_array_of_lines_tokenize;

  return p_string_tokenize;
}
