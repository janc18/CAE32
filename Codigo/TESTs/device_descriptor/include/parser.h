#ifndef PARSER_H
#define PARSER_H

extern const char Keywords[][30];
typedef struct line_token {
  char *parameter;
  char *value;
} line_token;

char *get_each_line_of_file_string(char *string_file, int *offset);
char *file_to_string(char *file_path);
int find_number_of_lines(char *string_file);
line_token *get_line_tokens(char *line);
int free_line_token(line_token *tokens);
line_token **get_file_tokens(char *string_file);
int free_memory_tokens(line_token **tokens, int number_of_lines);
int remove_extra_spaces(char *line);
int number_of_delimiter(char *line, char delimiter);
#endif // !PARSER_H
