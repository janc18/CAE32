/**
 * @file device_descriptor_tester.c
 * @brief Device descriptor tester
 *
 * @brief Checks if the desiered features are included at the device descriptor
 *
 * - To check if the device descriptor works correctly, it will tested after it's
 *   parser from the kernel
 *
 * - it require an input file to automate a little bit the test process
 */

#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  char *contents_file = file_to_string(argv[1]);
  if (contents_file == NULL) {
    printf("ERROR");
    return EXIT_FAILURE;
  }
  line_token *token;
  token=get_line_tokens("Start:locl");
  if (token!=NULL){
  printf("Parameter:%s, Value:%s\n",token->parameter,token->value);
  free_line_token(token);
  }
  // while loop to implement at get_file_tokens function
  int offsets=0;
  char *test_1_line=get_each_line_of_file_string(contents_file,&offsets);
  if(test_1_line!=NULL){
    printf("%s\noffset:%d\n",test_1_line,offsets);
    free(test_1_line);
  }
  
  char *test_2_line=get_each_line_of_file_string(contents_file,&offsets);
  if(test_2_line!=NULL){
    printf("%s\noffset:%d\n",test_1_line,offsets);
    free(test_2_line);
  }
 
  // while loop to implement at get_file_tokens function
  free(contents_file);
  return EXIT_SUCCESS;
}
// Check how to read joystick devices
