#ifndef PARSER_H
#define PARSER_H

extern const char Keywords[][30];
typedef struct line_token {
  char *parameter;
  char *value;
} line_token;

typedef struct lines_tokenize{
line_token **all_tokens;
int number_of_lines;
}lines_tokenize;

char *get_each_line_of_file_string(char *string_file, int *offset);
char *file_to_string(char *file_path);
int find_number_of_lines(char *string_file);
line_token *get_line_tokens(char *line);
int free_line_token(line_token *tokens);
lines_tokenize *get_file_tokens(char *string_file);
line_token **get_array_of_tokens(char *string_file,int *correct_syntax_number);
int free_memory_tokens(line_token **tokens, int number_of_lines);
int remove_extra_spaces(char *line);
int number_of_delimiter(char *line, char delimiter);
char **get_array_of_strings(char *string_file);
lines_tokenize *get_array_of_tokens_from_an_string_array(char **array_of_strings, int number_of_lines);
int free_array_of_lines(char **lines_allocated, int number_of_lines);
int free_line_tokenize_struct(lines_tokenize *p_lines_tokenize);
#endif // !PARSER_H
