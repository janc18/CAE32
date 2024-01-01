#ifndef TOKEN_MANIPULATION_H
#define TOKEN_MANIPULATION_H
#include "parser.h"

typedef struct object_index{
int start;
int end;
}object_index;

object_index *find_object(line_token **token_file, int number_of_lines, int start_index);
object_index **get_objects_index(line_token **token_file, int number_of_lines);
int search_for_word(line_token *token_file,const char *parameter, int index);
int print_contents_of_n_object(line_token **token_file, object_index content_index);
int verify_object(line_token **token_file,object_index index);
#endif // !TOKEN_MANIPULATION_H
