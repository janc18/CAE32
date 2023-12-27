/**
 * @file parser.c
 * @brief device.c32 File parser
 *
 * @brief Parser for automatic device descriptor test
 *
 * - To quickly test new device descriptors and tested in a row,
 *   the input file "device.c32", has a technical description of how
 *   will be represent the new HID device(Pedals, Shifter, Steering Wheel)
 */

#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct device_object{
  char name[30]; 
  int axis;
  int buttons;
}device_object;

const char Keywords[][30]={
  "Start",
  "End",
  "Size_bits",
  "Logical_Minimum",
  "Logical_Maximum",
  "Physical_Minumum",
  "Physical_Maximum"
};

typedef struct token{
  char parameter;
  void* value;
}token;

char *file_to_string(char *file_path){
  FILE *fptr_devices;
  fptr_devices=fopen(file_path,"r");

  if(fptr_devices==NULL) return NULL;

  fseek(fptr_devices, 0, SEEK_END);
  int lenght=ftell(fptr_devices);
  fseek(fptr_devices, 0, SEEK_SET);

  char *string=malloc(sizeof(char)*(lenght+1));

  char c;
  int i=0;

  while( (c = fgetc(fptr_devices))!=EOF){
    string[i]=c;
    i++;
  }
  string[i]='\0';
  fclose(fptr_devices);
  return string;
}

void find_object(char *string_file,device_object device){
  // 
}

int find_word(char *string_file, char *word, int offset){
  //TODO: Allocate memory for the line_buffer
  if(string_file==NULL) return -1;
  char line_buffer[1024]="0";
  int line_buffer_off=0;
  while(string_file[offset]!='\n'){ // Run for each character at line
    //save line contents to a temporary buffer
    line_buffer[line_buffer_off]=string_file[offset];
    offset++;
    line_buffer_off++;
    if(string_file[offset]=='\0'){
      //End of File string
      return -1;
    }  
  }
  line_buffer[offset]='\0';
  if(strcmp(line_buffer,"0")!=0){
  char **token=get_line_tokens(line_buffer);
  if(strcmp(token[0],word)==0 && token!=NULL){
    printf("Word found: %s\n",token[0]);
    } 
  }else {
    printf("Error Procesing line, or empty line\n");
  }
  return offset+1;//jump the last new line escape secuence
}

int find_number_of_lines(char *string_file){
  if(string_file!=NULL){
    int number_of_lines=0;
    int cursor=0;
    while(string_file[cursor]!='\0'){
      cursor++;
      if(string_file[cursor]=='\n') number_of_lines++;
      }
    return number_of_lines;
  }else {
  return -1;
  }
}



// Found the object size
// Create an array with the contents of each line
// compare the start and end of common names
// Create a new array just with the contents of the block 
// Tokenize with the ":" delimiter
//
char **get_line_tokens(char *line){
  //The line needs to follow the next structure
  //|Parameter|:|Value|\n
  char *parameter;
  char *value;
  char **token=malloc(sizeof(char *)*2);
  if(line!=NULL){
      parameter=strtok(line, ":");
      value=strtok(NULL, ":\n");
      if(parameter!=NULL && value!=NULL){
      token[0]=strdup(parameter);
      token[1]=strdup(value);
      return token;
      }
  }
  printf("token address:%p\n",token);
  free(token);
  return NULL;
}
