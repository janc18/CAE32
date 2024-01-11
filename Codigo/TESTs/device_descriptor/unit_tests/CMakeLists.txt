cmake_minimum_required(VERSION 3.10)
project(Tests)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(DEBUG)
  message("In DEBUG mode")
    add_definitions(-DDEBUG)
endif()
include_directories(${PROJECT_SOURCE_DIR}/../include)

set(SOURCES "${PROJECT_SOURCE_DIR}/../src/parser.c" "${PROJECT_SOURCE_DIR}/../src/token_manipulation.c")

file(GLOB TEST_SOURCES "${PROJECT_SOURCE_DIR}/*.cpp")

 add_executable(${PROJECT_NAME} ${SOURCES} ${TEST_SOURCES} main.cpp)

target_link_libraries(${PROJECT_NAME} gtest gtest_main)

enable_testing()
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
