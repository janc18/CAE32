extern "C" {
#include "parser.h"
}
#include "device_input_file.cpp"
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

TEST(ParserTests, ParsesWithExtraSpaces) {
  // Arrange
  line_token *object;
  char token[30] = "Start:Object_1 ";

  // Act
  object = get_line_tokens(token);

  // Assert
  EXPECT_STREQ("Start", object->parameter) << "Parameter parsing failed.";

  EXPECT_STREQ("Object_1", object->value) << "Value parsing failed";
}

TEST(ParserTests, IncorrectSyntax) {
  // Arrange
  char incorrect_line[][30] = {"Start:LS:Object_1:asd", "Start", "", "Start:", ":End", "  :value", "Start:  "};
  int number_of_line_elements = sizeof(incorrect_line) / sizeof(*incorrect_line);
  line_token *lines_tokens[number_of_line_elements];
  // Act
  for (int i = 0; i < number_of_line_elements; i++) {
    lines_tokens[i] = get_line_tokens(incorrect_line[i]);
  }
  // Assert
  for (int i = 0; i < number_of_line_elements; i++) {
    EXPECT_EQ(NULL, lines_tokens[i]);
  }
}

TEST(GetTokens, tokens) {
  // Arrange
  line_token **all_tokens;
  int number_of_lines = find_number_of_lines(string_file_c);
  int number_of_know_empty_lines = 2;
  // Act
  all_tokens = get_file_tokens(string_file_c);
  // Assert
  for (int i = 0; i < number_of_lines - number_of_know_empty_lines; i++) {
    EXPECT_NE(nullptr, all_tokens[i]);
  }
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
  char test_file[] = "Line 1\nLine 2\nLine 3\nLine 4\n";
  int number_of_lines = 0;

  // Act
  number_of_lines = find_number_of_lines(test_file);

  // Assert
  EXPECT_EQ(4, number_of_lines);
}

TEST(NumberOfLines, EmptyLine) {
  // Arrange
  char test_file[] = "";
  int number_of_lines = 0;

  // Act
  number_of_lines = find_number_of_lines(test_file);

  // Assert
  EXPECT_EQ(0, number_of_lines);
}
