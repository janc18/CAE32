
extern "C" {
#include "parser.h"
#include "token_manipulation.h"
}
#include <gtest/gtest.h>

TEST(TokenManipulation, SearchingStartAndEndIndex) {
  // Arrange
  char one_object[] = "Start: CAE32 Pedals\nAxis: 12\nButtons: 5\nEnd: CAE32 Pedals";
  object_index *index_one_object;
  lines_tokenize *object;
  int number_of_lines = 0;
  char **array_of_strings;

  // Act
  number_of_lines = find_number_of_lines(one_object);
  array_of_strings = get_array_of_strings(one_object);
  object = get_array_of_tokens_from_an_string_array(array_of_strings, number_of_lines);

  // Act
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
