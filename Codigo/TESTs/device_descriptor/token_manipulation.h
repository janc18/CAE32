#ifndef TOKEN_MANIPULATION_H
#define TOKEN_MANIPULATION_H
#include "parser.h"

typedef struct object_index{
int start;
int end;
}object_index;

object_index get_object(line_token **token_file, int number_of_lines);
int search_for_word(line_token *token_file,const char *parameter, int index);
int get_contents_of_object(line_token **token_file, object_index content_index);
#endif // !TOKEN_MANIPULATION_H
