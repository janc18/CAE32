extern "C" {
#include "parser.h"
}
#include <gtest/gtest.h>
TEST(ParserTests, ParsesWithOutExtraSpaces) {
  // Arrange
  line_token *object;
  char token[30] = "Start:Object_1";

  //Act
  object = get_line_tokens(token);

  //Assert
  EXPECT_STREQ("Start", object->parameter)<< "Parameter parsing failed.";
  
  EXPECT_STREQ("Object_1", object->value)<< "Value parsing failed";
}
TEST(ParserTests, ParsesWithExtraSpaces) {
  // Arrange
  line_token *object;
  char token[30] = "Start:Object_1    ";

  //Act
  object = get_line_tokens(token);

  //Assert
  EXPECT_STREQ("Start", object->parameter)<< "Parameter parsing failed.";
  
  EXPECT_STREQ("Object_1", object->value)<< "Value parsing failed";
}
