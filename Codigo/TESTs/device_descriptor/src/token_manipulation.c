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

const int max_number_objects = 10;
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
  object_index **p_index = calloc(sizeof(object_index*), index_array + 1);
  for (int i = 0; i < index_array + 1; i++) {
    if (p_index != NULL) {
      p_index[i] = index[i];
    }else{
    printf("[%d]\tindex array NULL\n",i);
    }
  }
  printf("Number of objects %d\n", index_array);
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
  while (start_index <= number_of_lines) {
    if (search_for_word(token_file[start_index], "Start", start_index) == 0) { // start found
      index->start = start_index;
      break;
    }
    start_index++;
  }
  while (start_index <= number_of_lines) {
    if (search_for_word(token_file[start_index], "End", start_index) == 0) { // END found
      index->end = start_index;
      break;
    }
    start_index++;
  }
  if (verify_object(token_file, *index) == 0) {
    return index;
  } else {
    printf("ERROR: Tokens values are not the same\n");
    return NULL;
  }
}

int free_memory_object(object_index **objects){
  if (objects != NULL) {
    for (int i = 0; i < max_number_objects; i++) {
      if (objects[i] != NULL) {
        free(objects[i]);
      } else {
        break;
      }
    }
  }
  return 0;
}
