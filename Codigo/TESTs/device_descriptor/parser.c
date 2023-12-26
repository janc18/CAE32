
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct device_object{
  int start;
  int end;
  char name[30]; 
}device_object;

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

int find_number_of_lines(char *string_file){
  int number_of_lines=0;
  int cursor=0;
  while(string_file[cursor]!='\0'){
    cursor++;
    if(string_file[cursor]=='\n') number_of_lines++;
    }
  return number_of_lines;
}

// Find the object size
// Create an array with the contents of each line
// compare the start and end of common names
// Create a new array just with the contents of the block 
// Tokenize with the ":" delimiter
//
