#ifndef PARSER_H
#define PARSER_H

extern const char Keywords[7][30];
typedef struct line_token {
  char *parameter;
  char *value;
} line_token;

typedef struct lines_tokenize{
line_token **all_tokens;
int number_of_correct_tokens;
}lines_tokenize;

char *getEachLineOfFileString(char *string_file, int *offset);
char *fileToString(char *file_path);
int findNumberOfLines(char *string_file);
line_token *getLineTokens(char *line);
int freeLineToken(line_token *tokens);
lines_tokenize *getFileTokens(char *string_file);
line_token **getArrayOfTokens(char *string_file,int *correct_syntax_number);
int freeMemoryTokens(line_token **tokens, int number_of_lines);
int removeExtraSpaces(char *line);
int numberOfDelimiter(char *line, char delimiter);
char **getArrayOfStrings(char *string_file);
lines_tokenize *getArrayOfTokensFromAnStringArray(char **array_of_strings, int number_of_lines);
int freeArrayOfLines(char **lines_allocated, int number_of_lines);
int freeLineTokenizeStruct(lines_tokenize *p_lines_tokenize);
int analizeLine(char *line);
char *statusMessage(int error);
#endif // !PARSER_H
