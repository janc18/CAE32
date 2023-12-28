#ifndef PARSER_H
#define PARSER_H
char *file_to_string(char *file_path);
// int find_number_objects(char *string_file);
int find_number_of_lines(char *string_file);
int **find_word(char *string_file, char *word, int offset);
char **get_line_tokens(char *line);
int find_object(char *string_file);
#endif // !PARSER_H
