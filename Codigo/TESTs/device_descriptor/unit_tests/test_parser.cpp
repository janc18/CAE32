extern "C" {
#include "parser.h"
#include "./device_input_file.h"
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
}

TEST(ParserTests, GettingEachLineOfString) {
  // Arrange
  char input_file[] = "Line 1\nLine 2\nLine 3\nLine 4\n";
  char correct_output_of_input_file[][30] = {"Line 1", "Line 2", "Line 3", "Line 4", ""};
  int offsets = 0;

  // Act
  int number_of_lines = find_number_of_lines(input_file);

  // Assert
  for (int i = 0; i < number_of_lines; i++) {
    EXPECT_STREQ(correct_output_of_input_file[i], get_each_line_of_file_string(input_file, &offsets));
  }
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
  EXPECT_EQ(26,array_of_objects->number_of_lines);
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
