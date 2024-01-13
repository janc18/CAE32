
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
  number_of_lines = find_number_of_lines(one_object);
  array_of_strings = get_array_of_strings(one_object);
  object = get_array_of_tokens_from_an_string_array(array_of_strings, number_of_lines);
  index_one_object = search_start_and_end_index(object, 0);

  // Assert
  EXPECT_EQ(index_one_object->start, 0);
  EXPECT_EQ(index_one_object->end, 3);
  // Post act
  free_array_of_lines(array_of_strings, number_of_lines);
  free_line_tokenize_struct(object);
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
  number_of_lines = find_number_of_lines(one_object);
  array_of_strings = get_array_of_strings(one_object);
  object = get_array_of_tokens_from_an_string_array(array_of_strings, number_of_lines);
  index_one_object = find_object(object, 0);

  // Assert
  EXPECT_NE(nullptr, index_one_object); // Object found

  // Post act
  free_array_of_lines(array_of_strings, number_of_lines);
  free_line_tokenize_struct(object);
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
  number_of_lines = find_number_of_lines(incorrect_object);
  array_of_strings = get_array_of_strings(incorrect_object);
  object = get_array_of_tokens_from_an_string_array(array_of_strings, number_of_lines);
  index = find_object(object, 0);
  if (index != nullptr) {
    printf("Value of Start:[%s]\tValue of End:[%s]\n", object->all_tokens[index->start]->value, object->all_tokens[index->end]->value);
  }
  // Assert
  EXPECT_EQ(nullptr, index); // Object not found

  // Post act
  free_array_of_lines(array_of_strings, number_of_lines);
  if (object != nullptr) {
    free_line_tokenize_struct(object);
  }
  if (index != nullptr) {
    free(index);
  }
}
