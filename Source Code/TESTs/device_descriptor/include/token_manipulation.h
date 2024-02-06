#ifndef TOKEN_MANIPULATION_H
#define TOKEN_MANIPULATION_H
#include "parser.h"

typedef struct object_index {
  int start;
  int end;
} object_index;

object_index **get_all_objects(lines_tokenize *array_of_objects);
int free_get_all_object(object_index **all_objects_indexes, int number_of_correct_objects);
int free_memory_object(object_index **objects);
object_index *find_object(lines_tokenize *token_line, int start_index);
int verify_object(lines_tokenize *token_file, object_index index);
void print_all_the_objects(object_index **all_objects_indexes, lines_tokenize *token_file, int number_of_correct_objects);
object_index *search_start_and_end_index(lines_tokenize *token_line, int start_index);
void print_contents_of_n_object(lines_tokenize *token_file, object_index *content_index);
int search_for_word(line_token *token_file, const char *parameter, int index);
char *token_error(int error_result);
int find_number_of_objects(lines_tokenize *token_file);
// Token verication
int verify_parameters_of_object(lines_tokenize *token_file, object_index *object);
int verify_parameters_of_all_objects(lines_tokenize *token_file, object_index **objects, int number_of_correct_objects);
// Misc functions
void print_colors(int color);
#endif // !TOKEN_MANIPULATION_H
