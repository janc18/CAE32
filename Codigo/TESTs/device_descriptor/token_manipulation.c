/**
 * @file token_manipulation.c
 *
 * @brief Get all the tokens of an input file
 *
 * - Get all objects of an input file with the correct sintax
 *   and saved to iterate for each token to check if the new
 *   device descriptor work as is supossed
 *
 */

#include "token_manipulation.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

object_index **get_objects_index(line_token **token_file, int number_of_lines) {
  object_index *index[number_of_lines];
  index[0] = find_object(token_file, number_of_lines, 0);
  int index_array = 0;
  if (index[index_array] != NULL) {
#ifdef DEBUG
    print_contents_of_n_object(token_file, *index[index_array]);
#endif /* ifdef DEBUG */
  } else {
    printf("ERROR at index[%d]\n", 0);
    return NULL;
  }

  while (index[index_array] != NULL) {
    bool are_the_same = index[index_array]->end & index[index_array - 1]->end;
    index_array++;
    if (are_the_same == 1)
      break;
    index[index_array] = find_object(token_file, number_of_lines, index[index_array - 1]->end);
    if (index[index_array] != NULL) {
#ifdef DEBUG
      print_contents_of_n_object(token_file, *index[index_array]);
#endif /* ifdef DEBUG */
    } else {
      printf("%d\n", index_array);
      printf("ERROR at index[%d]\n", index_array);
      index[index_array] = NULL;
    }
  }
  object_index **p_index = malloc(sizeof(object_index *) * index_array + 1);
  for (int i = 0; i < index_array + 1; i++) {
    p_index[i] = index[i];
  }
  return p_index;
}

int verify_object(line_token **token_file, object_index index) {
  if (strcmp(token_file[index.start]->value, token_file[index.end]->value) == 0) {
#ifdef DEBUG
    printf("Are the same object\n");
#endif /* ifdef DEBUG */
    return 0;
  } else {
    printf("index.start:%s,index.end:%s\n", token_file[index.start]->value, token_file[index.end]->value);
#ifdef DEBUG
    printf("Are not same object\n");
#endif /* ifdef DEBUG */
    return -1;
  }
}

int search_for_word(line_token *token_file, const char *parameter, int index) {
  if (strcmp(parameter, token_file->parameter) == 0) {
#ifdef DEBUG
    printf("Word: [%s] with [%s] value, found at index:%d\n", token_file->parameter, token_file->value, index);
#endif /* ifdef DEBUG */
    return 0;
  } else {
    return -1;
  }
}

int print_contents_of_n_object(line_token **token_file, object_index content_index) {
  printf("Contents of the [%s] object\n", token_file[content_index.start]->value);
  for (int i = content_index.start + 1; i <= content_index.end - 1; i++) {
    printf("Parameter:[%s],Value:[%s]\n", token_file[i]->parameter, token_file[i]->value);
  }
  return 0;
}

object_index *find_object(line_token **token_file, int number_of_lines, int start_index) {
  object_index *index = malloc(sizeof(object_index) * number_of_lines);
  int array_index_n_object = 0;
  // TODO if the values of the parameter are not equal keep searching
  while (start_index <= number_of_lines) {
    if (search_for_word(token_file[start_index], "Start", start_index) == 0) { // start found
      // printf("START:%d, parameter[%s], value[%s]\n", start_index, token_file[start_index]->parameter, token_file[start_index]->value);
      index->start = start_index;
      break;
    }
    start_index++;
  }
  // cp_start_index++;
  while (start_index <= number_of_lines) {
    if (search_for_word(token_file[start_index], "End", start_index) == 0) { // END found
      // printf("End:%d, parameter[%s], value[%s]\n", start_index, token_file[start_index]->parameter, token_file[start_index]->value);
      index->end = start_index;
      break;
    }
    start_index++;
  }
  if (verify_object(token_file, *index) == 0) {
    return index;
  } else {
    printf("DAmm\n");
    return NULL;
  }
}
