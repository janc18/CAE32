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
  object = getLineTokens(token);

  // Assert
  EXPECT_STREQ("Start", object->parameter) << "Parameter parsing failed.";

  EXPECT_STREQ("Object_1", object->value) << "Value parsing failed";

  // Post Act
  freeLineToken(object);
}

TEST(ParserTests, ParseParameterTwoWords) {
  // Arrange
  line_token *object;
  char token[30] = "Start:Object_1 second";

  // Act
  object = getLineTokens(token);

  // Assert
  EXPECT_STREQ("Start", object->parameter) << "Parameter parsing failed.";

  EXPECT_STREQ("Object_1 second", object->value) << "Value parsing failed";

  // Post Act
  freeLineToken(object);
}

TEST(ParserTests, ParsesWithExtraSpacesNumVariation0) {
  // Arrange
  line_token *object;
  char line[30] = "   Start:Object_1 ";

  // Act
  object = getLineTokens(line);

  // Assert
  EXPECT_STREQ("Start", object->parameter) << "Parameter parsing failed.";

  EXPECT_STREQ("Object_1", object->value) << "Value parsing failed";

  // Post Act
  freeLineToken(object);
}

TEST(ParserTests, ParsesWithExtraSpacesNum1) {
  // Arrange
  line_token *object;
  char line[30] = "Start: Object_1 ";

  // Act
  object = getLineTokens(line);

  // Assert
  EXPECT_STREQ("Start", object->parameter) << "Parameter parsing failed.";

  EXPECT_STREQ("Object_1", object->value) << "Value parsing failed";

  // Post Act
  freeLineToken(object);
}

TEST(ParserTests, IncorrectSyntax) {
  // Arrange
  char incorrect_line[][30] = {"\n", "Start:LS:Object_1:asd", "Start", "", "Start:", ":End", "  :value", "Start:  "};
  int number_of_line_elements = sizeof(incorrect_line) / sizeof(*incorrect_line);
  line_token *lines_tokens[number_of_line_elements];

  // Act
  for (int i = 0; i < number_of_line_elements; i++) {
    lines_tokens[i] = getLineTokens(incorrect_line[i]);
  }

  // Assert
  for (int i = 0; i < number_of_line_elements; i++) {
    EXPECT_EQ(NULL, lines_tokens[i]) << "Error at index" << i;
  }

  // Post Act
  for (int i = 0; i < number_of_line_elements; i++) {
    freeLineToken(lines_tokens[i]);
  }
}

TEST(ParserTests, GettingEachLineOfString) {
  // Arrange
  char input_file[] = "Line 1\nLine 2\nLine 3\nLine 4\n";
  char correct_output_of_input_file[][30] = {"Line 1", "Line 2", "Line 3", "Line 4", ""};
  char **p_array_of_string = (char **)malloc(sizeof(correct_output_of_input_file));
  int offsets = 0;

  // Act
  int number_of_lines = findNumberOfLines(input_file);
  for (int i = 0; i < number_of_lines; i++) {
    p_array_of_string[i] = getEachLineOfFileString(input_file, &offsets);
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
  line_1 = getEachLineOfFileString(input_file, &offset);

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
  array_of_lines = getArrayOfStrings(input_file);
  int number_of_lines = findNumberOfLines(input_file);

  // Assert
  for (int i = 0; i < number_of_lines; i++) {
    EXPECT_STREQ(array_of_lines[i], correct_output_of_input_file[i]);
  }

  //Post act
  freeArrayOfLines(array_of_lines, number_of_lines);
}

TEST(ParserTests, GetArrayOfTokens) {
  // Arrange
  int number_of_lines = 0;
  lines_tokenize *array_of_objects;
  char **array_of_strings;
  // Act
  number_of_lines = findNumberOfLines(string_file_c);
  array_of_strings = getArrayOfStrings(string_file_c);
  array_of_objects = getArrayOfTokensFromAnStringArray(array_of_strings, number_of_lines);

  // Assert
  EXPECT_NE(nullptr, array_of_objects);
  EXPECT_EQ(26, array_of_objects->number_of_correct_tokens);
  

  // Post Act
  freeArrayOfLines(array_of_strings, number_of_lines);
  freeLineTokenizeStruct(array_of_objects);
}

TEST(FileTest, FileNotFound) {
  // Arrange
  char file_path[] = "./easy.c32";
  char *file_string;

  // Act
  file_string = fileToString(file_path);

  // Assert
  EXPECT_EQ(NULL, file_string);
}

TEST(NumberOfLines, CorrectlyParsed) {
  // Arrange
  char test_file[] = "Line 1\nLine 2\nLine 3\nLine 4";
  int number_of_lines = 0;

  // Act
  number_of_lines = findNumberOfLines(test_file);

  // Assert
  EXPECT_EQ(4, number_of_lines);
}

TEST(NumberOfLines, WhitOutNewLine) {
  // Arrange
  char test_file[] = "Line 1";
  int number_of_lines = 0;

  // Act
  number_of_lines = findNumberOfLines(test_file);

  // Assert
  EXPECT_EQ(1, number_of_lines);
}

// All the Free memory test are tested with valgrind
TEST(FreeMemory, freeLineTokensStruct) {
  // Arrange
  line_token *valid_object;
  line_token *invalid_object;
  char correct_token[30] = "Start:Object_1";
  char incorrect_token[30] = "_::::";

  // Act
  valid_object = getLineTokens(correct_token);
  // When an object have an incorrect syntaxis will return a NULL pointer
  invalid_object = getLineTokens(incorrect_token);

  // Assert
  EXPECT_NE(valid_object, nullptr);
  EXPECT_EQ(invalid_object, nullptr);

  // Post Act
  freeLineToken(valid_object);
  freeLineToken(invalid_object); // free_line_token check first if is NULL
}
