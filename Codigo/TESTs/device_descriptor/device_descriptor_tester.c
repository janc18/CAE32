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

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include <string.h>

int main(int argc, char *argv[])
{
  char *contents_file=file_to_string(argv[1]);
  if(contents_file==NULL){
    printf("ERROR");
    return EXIT_FAILURE;
  }
  int last_cursor=find_word(contents_file,"Start",0);
  
  for (int i=0;i<18;i++){
    last_cursor=find_word(contents_file,"Start",last_cursor);
    if (last_cursor==-1) break;
  }

  free(contents_file);

  return EXIT_SUCCESS;
}
//Check how to read joystick devices
