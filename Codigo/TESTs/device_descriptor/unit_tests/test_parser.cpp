#include <cstdio>
#include <cstdlib>
extern "C" {
#include "./device_input_file.h"
#include "parser.h"
}
#include <gtest/gtest.h>

TEST(ParserTests, ParsesWithOutExtraSpaces) {
  // Arrange
  line_token *object;
  char token[30] = "Start:Object_1";

  // Act
  object = get_line_tokens(token);

  // Assert
  EXPECT_STREQ("Start", object->parameter) << "Parameter parsing failed.";

  EXPECT_STREQ("Object_1", object->value) << "Value parsing failed";

  // Post Act
  free_line_token(object);
}

TEST(ParserTests, ParsesWithExtraSpacesNumVariation0) {
  // Arrange
  line_token *object;
  char line[30] = "   Start:Object_1 ";

  // Act
  object = get_line_tokens(line);

  // Assert
  EXPECT_STREQ("Start", object->parameter) << "Parameter parsing failed.";

  EXPECT_STREQ("Object_1", object->value) << "Value parsing failed";

  // Post Act
  free_line_token(object);
}

TEST(ParserTests, ParsesWithExtraSpacesNum1) {
  // Arrange
  line_token *object;
  char line[30] = "Start: Object_1 ";

  // Act
  object = get_line_tokens(line);

  // Assert
  EXPECT_STREQ("Start", object->parameter) << "Parameter parsing failed.";

  EXPECT_STREQ("Object_1", object->value) << "Value parsing failed";

  // Post Act
  free_line_token(object);
}

TEST(ParserTests, IncorrectSyntax) {
  // Arrange
  char incorrect_line[][30] = {"\n", "Start:LS:Object_1:asd", "Start", "", "Start:", ":End", "  :value", "Start:  "};
  int number_of_line_elements = sizeof(incorrect_line) / sizeof(*incorrect_line);
  line_token *lines_tokens[number_of_line_elements];

  // Act
  for (int i = 0; i < number_of_line_elements; i++) {
    lines_tokens[i] = get_line_tokens(incorrect_line[i]);
  }

  // Assert
  for (int i = 0; i < number_of_line_elements; i++) {
    EXPECT_EQ(NULL, lines_tokens[i]) << "Error at index" << i;
  }

  // Post Act
  for (int i = 0; i < number_of_line_elements; i++) {
    free_line_token(lines_tokens[i]);
  }
}

TEST(ParserTests, GettingEachLineOfString) {
  // Arrange
  char input_file[] = "Line 1\nLine 2\nLine 3\nLine 4\n";
  char correct_output_of_input_file[][30] = {"Line 1", "Line 2", "Line 3", "Line 4", ""};
  char **p_array_of_string = (char **)malloc(sizeof(correct_output_of_input_file));
  int offsets = 0;

  // Act
  int number_of_lines = find_number_of_lines(input_file);
  for (int i = 0; i < number_of_lines; i++) {
    p_array_of_string[i] = get_each_line_of_file_string(input_file, &offsets);
  }

  // Assert
  for (int i = 0; i < number_of_lines; i++) {
    EXPECT_STREQ(correct_output_of_input_file[i], p_array_of_string[i]);
  }

  // Post Act
  for (int i = 0; i < number_of_lines; i++) {
    free(p_array_of_string[i]);
  }
  free(p_array_of_string);
}

TEST(ParserTests, GetEachLineOfFileString) {
  // Arrange
  char input_file[] = "Line 1\nLine 2\nLine 3\nLine 4\n";
  char *line_1;
  int offset = 0;
  // Act
  line_1 = get_each_line_of_file_string(input_file, &offset);

  // Assert
  EXPECT_STREQ("Line 1", line_1);

  // Post Act
  free(line_1);
}

TEST(ParserTests, GetArrayOfStrings) {
  // Arrange
  char input_file[] = "Line 1\nLine 2\nLine 3\nLine 4\n";
  char correct_output_of_input_file[][30] = {"Line 1", "Line 2", "Line 3", "Line 4", ""};
  char **array_of_lines = {0};

  // Act
  array_of_lines = get_array_of_strings(input_file);
  int number_of_lines = find_number_of_lines(input_file);

  // Assert
  for (int i = 0; i < number_of_lines; i++) {
    EXPECT_STREQ(array_of_lines[i], correct_output_of_input_file[i]);
  }

  // Post Act
  for (int i = 0; i < number_of_lines; i++) {
    free(array_of_lines[i]);
  }
  free(array_of_lines);
}

TEST(ParserTests, GetArrayOfTokens) {
  // Arrange
  int number_of_lines = 0;
  lines_tokenize *array_of_objects;
  char **array_of_strings;
  // Act
  number_of_lines = find_number_of_lines(string_file_c);
  array_of_strings = get_array_of_strings(string_file_c);
  array_of_objects = get_array_of_tokens_from_an_string_array(array_of_strings, number_of_lines);

  // Assert
  EXPECT_NE(nullptr, array_of_objects);
  EXPECT_EQ(26, array_of_objects->number_of_lines);
  

  // Post Act
  
  for(int i=0; i<number_of_lines;i++){
    free(array_of_strings[i]);
  }
  
  free(array_of_strings);

  for (int i = 0; i < array_of_objects->number_of_lines; i++) {
    free_line_token(array_of_objects->all_tokens[i]);
  }
  free(array_of_objects->all_tokens);

  // Liberar la estructura lines_tokenize
  free(array_of_objects);
}

TEST(FileTest, FileNotFound) {
  // Arrange
  char file_path[] = "./easy.c32";
  char *file_string;

  // Act
  file_string = file_to_string(file_path);

  // Assert
  EXPECT_EQ(NULL, file_string);
}

TEST(NumberOfLines, CorrectlyParsed) {
  // Arrange
  char test_file[] = "Line 1\nLine 2\nLine 3\nLine 4";
  int number_of_lines = 0;

  // Act
  number_of_lines = find_number_of_lines(test_file);

  // Assert
  EXPECT_EQ(4, number_of_lines);
}

TEST(NumberOfLines, WhitOutNewLine) {
  // Arrange
  char test_file[] = "Line 1";
  int number_of_lines = 0;

  // Act
  number_of_lines = find_number_of_lines(test_file);

  // Assert
  EXPECT_EQ(1, number_of_lines);
}

// All the Free memory test are tested with valgrind
TEST(FreeMemory, FreeLineTokensStruct) {
  // Arrange
  line_token *valid_object;
  line_token *invalid_object;
  char correct_token[30] = "Start:Object_1";
  char incorrect_token[30] = "_::::";

  // Act
  valid_object = get_line_tokens(correct_token);
  // When an object have an incorrect syntaxis will return a NULL pointer
  invalid_object = get_line_tokens(incorrect_token);

  // Assert
  EXPECT_NE(valid_object, nullptr);
  EXPECT_EQ(invalid_object, nullptr);

  // Post Act
  free_line_token(valid_object);
  free_line_token(invalid_object); // free_line_token check first if is NULL
}
