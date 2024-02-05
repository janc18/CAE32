/**
 * @file token_manipulation.c
 *
 * @brief Get objects from tokens previously proceded
 *
 * - Build objects gived by an struct with each line tokenize
 *   and saved to compare to the device descriptor and check if work as
 *   is supossed
 *
 */

#include "token_manipulation.h"
#include "parser.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

const int max_number_objects = 10;

enum TOKENS_ERRORS { OUTSIDE_ARRAY = 1, NOT_THE_SAME };
/**
 * @brief Verify if the start and end value are the same
 *
 * @param *lines_tokenize Struct with all the tokens of a given file
 * @param object_index Struct with the start and end index number
 *
 * @return int
 *  - 0 if the values objects are the same
 *  - 1 if is trying to access outide of the token array
 *  - 2 if the values are not the same
 */
int verify_object(lines_tokenize *token_file, object_index index) {
  if (index.start > token_file->number_of_correct_tokens) {
    return 1;
  } else if (strcmp(token_file->all_tokens[index.start]->value, token_file->all_tokens[index.end]->value) == 0) {
#ifdef DEBUG
    printf("Are the same object\n");
#endif /* ifdef DEBUG */
    return 0;
  } else {
    fprintf(stderr, "index.start:%s,index.end:%s\tAre not the same\n", token_file->all_tokens[index.start]->value,
            token_file->all_tokens[index.end]->value);
    return 2;
  }
}

/**
 * @brief Search for "x" word from a line_token struct
 *
 * @param line_token* Struct pointer with the parameter and value
 * @param const char* Word to be compared
 * @param int Index to be printed when found a match
 *
 * @return int
 *  - 0 Word found
 *  - -1 Word not found or line_token is null
 */
int search_for_word(line_token *token_file, const char *parameter, int index) {
  if (token_file == NULL) {
    return -1;
  }
  if (strcmp(parameter, token_file->parameter) == 0) {
#ifdef DEBUG
    printf("Word: [%s] with [%s] value, found at index:%d\n", token_file->parameter, token_file->value, index);
#endif /* ifdef DEBUG */
    return 0;
  } else {
    return -1;
  }
}
/**
 * @brief Print the contents of an object
 *
 * @param *lines_tokenize A struct with all the tokens of a given input file
 * @param *object_index Struct with the start and end index of an object
 *
 * @return void
 */
void print_contents_of_n_object(lines_tokenize *token_file, object_index *content_index) {
  if (content_index!= NULL) {
  if (content_index->end < token_file->number_of_correct_tokens) {
    printf("Contents of the [%s] object\n", token_file->all_tokens[content_index->start]->value);
    for (int i = content_index->start + 1; i <= content_index->end - 1; i++) {
      printf("Parameter:[%s],Value:[%s]\n", token_file->all_tokens[i]->parameter, token_file->all_tokens[i]->value);
    }
  }
  }
}
/**
 * @brief Find an object starting with the start index
 * 
 * @param *lines_tokenize A struct with all the tokens of a given input file
 * @param int Start index
 *
 * @return *object_index or NULL if can't find any object
 */

object_index *find_object(lines_tokenize *token_line, int start_index) {
  object_index *p_index = search_start_and_end_index(token_line, start_index);
  int object_result = verify_object(token_line, *p_index);
  if (object_result == 0) {
    return p_index;
  } else {
    fprintf(stderr, "ERROR:%s\n", token_error(object_result));
    free(p_index);
    return NULL;
  }
  return NULL;
}

char *token_error(int error_result) {
  switch (error_result) {
  case OUTSIDE_ARRAY:
    return "Trying to read token outside array";
    break;
  case NOT_THE_SAME:
    return "Tokens values are not the same";
    break;
  }
  return "";
}
/**
 * @brief Search for the start and End Parameter
 *
 * Get the start and end index of the given lines_tokenize struct
 * not compare if it is the same object.
 * Example:
 *
 * Start: CAE32
 * ..n characteristics
 * End: CAE32
 * ^^^^^^^^^^^^^^^^^^^
 * This it the same object
 *
 * @param *lines_tokenize Pointer struct with all the tokens
 * @param int index to start to search an object 
 * @return 
 *  - *object_index Allocated Pointer struct with start and end index of an object
 *  - NULL if didn't find any object
 */

object_index *search_start_and_end_index(lines_tokenize *token_line, int start_index) {
  object_index *index = malloc(sizeof(object_index)); // Saving space for one struct
  while (start_index <= token_line->number_of_correct_tokens) {
    if (search_for_word(token_line->all_tokens[start_index], "Start", start_index) == 0) { // start found
      index->start = start_index;
      break;
    }
    start_index++;
  }
  while (start_index <= token_line->number_of_correct_tokens) {
    if (search_for_word(token_line->all_tokens[start_index], "End", start_index) == 0) { // END found
      index->end = start_index;
      break;
    }
    start_index++;
  }
  return index;
}

/**
 * @brief Free Memory for any objects created
 *
 * @param object_index** Struct with all the pointers of generated by the function get_objects_index
 * @return int 0 in success
 */
int free_memory_object(object_index **objects) {
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
