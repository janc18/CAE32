#ifndef TOKEN_MANIPULATION_H
#define TOKEN_MANIPULATION_H
#include "parser.h"

typedef struct object_index{
int start;
int end;
}object_index;

int free_memory_object(object_index **objects);
object_index *find_object(lines_tokenize *token_line,int start_index);
// object_index **get_objects_index(lines_tokenize *token_lines);
object_index *search_start_and_end_index(lines_tokenize *token_line,int start_index);
int search_for_word(line_token *token_file,const char *parameter, int index);
int print_contents_of_n_object(line_token **token_file, object_index content_index);
int verify_object(line_token **token_file,object_index index);
#endif // !TOKEN_MANIPULATION_H
