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
  free(contents_file);
  return EXIT_SUCCESS;
}
// Check how to read joystick devices
