#ifndef TOKEN_MANIPULATION_H
#define TOKEN_MANIPULATION_H
#include "parser.h"

typedef struct object_index {
  int start;
  int end;
} object_index;

object_index **getAllObjects(lines_tokenize *array_of_objects);
int freeGetAllObject(object_index **all_objects_indexes, int number_of_correct_objects);
int freeMemoryObject(object_index **objects);
object_index *findObject(lines_tokenize *token_line, int start_index);
int verifyObject(lines_tokenize *token_file, object_index index);
void printAllTheObjects(object_index **all_objects_indexes, lines_tokenize *token_file, int number_of_correct_objects);
object_index *searchStartAndEndIndex(lines_tokenize *token_line, int start_index);
void printContentsOfNObject(lines_tokenize *token_file, object_index *content_index);
int searchForWord(line_token *token_file, const char *parameter, int index);
char *tokenError(int error_result);
int findNumberOfObjects(lines_tokenize *token_file);
// Token verication
int verifyParametersOfObject(lines_tokenize *token_file, object_index *object);
int verifyParametersOfAllObjects(lines_tokenize *token_file, object_index **objects, int number_of_correct_objects);
// Misc functions
void printColors(int color);
#endif // !TOKEN_MANIPULATION_H
