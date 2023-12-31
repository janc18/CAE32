#include "token_manipulation.h"
#include "parser.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>

object_index get_object(line_token **token_file, int number_of_lines) {
  // search for start and end and save both index
  object_index index = {0};
  for (int i = 0; i < number_of_lines; i++) {
    if (search_for_word(token_file[i], Keywords[0], i) == 0) { // searching start
      index.start = i;
      break;
    }
  }
  for (int i = 0; i < number_of_lines; i++) {
    if (search_for_word(token_file[i], Keywords[1], i) == 0) { // searching end
      index.end = i;
      break;
    }
  }
  return index;
}

int search_for_word(line_token *token_file, const char *parameter, int index) {
  if (strcmp(parameter, token_file->parameter) == 0) {
#ifdef DEBUG
    printf("Word: [%s] with [%s] value, found at index:%d\n", Keywords[0], token_file->value, index);
#endif /* ifdef DEBUG */
    return 0;
  } else {
    return -1;
  }
}

int get_contents_of_object(line_token **token_file, object_index content_index) {
  printf("Contents of the [%s] object\n",token_file[content_index.start]->value);
  for (int i = content_index.start+1; i <= content_index.end-1; i++) {
    printf("Parameter:[%s],Value:[%s]\n", token_file[i]->parameter, token_file[i]->value);
  }
  return 0;
}
