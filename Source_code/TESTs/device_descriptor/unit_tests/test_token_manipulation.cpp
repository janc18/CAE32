
extern "C" {
#include "parser.h"
#include "token_manipulation.h"
}
#include <gtest/gtest.h>

char one_object[] = "Start: CAE32 Pedals\nAxis: 12\nButtons: 5\nEnd: CAE32 Pedals";
TEST(TokenManipulation, SearchingStartAndEndIndex) {
  // Arrange
  object_index *index_one_object;
  lines_tokenize *object;
  int number_of_lines = 0;
  char **array_of_strings;

  // Act
  number_of_lines = findNumberOfLines(one_object);
  array_of_strings = getArrayOfStrings(one_object);
  object = getArrayOfTokensFromAnStringArray(array_of_strings, number_of_lines);
  index_one_object = searchStartAndEndIndex(object, 0);

  // Assert
  EXPECT_EQ(index_one_object->start, 0);
  EXPECT_EQ(index_one_object->end, 3);
  // Post act
  freeArrayOfLines(array_of_strings, number_of_lines);
  freeLineTokenizeStruct(object);
  // object_index free memory
  free(index_one_object);
}
TEST(TokenManipulation, FindJustOneObject) {
  // Arrange
  object_index *index_one_object;
  lines_tokenize *object;
  int number_of_lines = 0;
  char **array_of_strings;

  // Act
  number_of_lines = findNumberOfLines(one_object);
  array_of_strings = getArrayOfStrings(one_object);
  object = getArrayOfTokensFromAnStringArray(array_of_strings, number_of_lines);
  index_one_object = findObject(object, 0);

  // Assert
  EXPECT_NE(nullptr, index_one_object); // Object found

  // Post act
  freeArrayOfLines(array_of_strings, number_of_lines);
  freeLineTokenizeStruct(object);
  free(index_one_object);
}
TEST(TokenManipulation, ObjectNotFound) {
  // Arrange
  char incorrect_object[] = "Start: CAE32 Brake\nAxis: 12\nButtons: 5\nEnd: CAE32 Pedals";
  object_index *index;
  lines_tokenize *object;
  int number_of_lines = 0;
  char **array_of_strings;

  // Act
  number_of_lines = findNumberOfLines(incorrect_object);
  array_of_strings = getArrayOfStrings(incorrect_object);
  object = getArrayOfTokensFromAnStringArray(array_of_strings, number_of_lines);
  index = findObject(object, 0);
  if (index != nullptr) {
    printf("Value of Start:[%s]\tValue of End:[%s]\n", object->all_tokens[index->start]->value, object->all_tokens[index->end]->value);
  }
  // Assert
  EXPECT_EQ(nullptr, index); // Object not found

  // Post act
  freeArrayOfLines(array_of_strings, number_of_lines);
  if (object != nullptr) {
    freeLineTokenizeStruct(object);
  }
  if (index != nullptr) {
    free(index);
  }
}
