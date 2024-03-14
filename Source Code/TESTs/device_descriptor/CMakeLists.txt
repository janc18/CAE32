cmake_minimum_required(VERSION 3.10)
project(DeviceDescriptorTest)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
#Udev
find_package(PkgConfig REQUIRED)
pkg_search_module(EVDEV REQUIRED libevdev)
include_directories(${EVDEV_INCLUDE_DIRS})
#
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.c")
list(APPEND SOURCES "${PROJECT_SOURCE_DIR}/device_descriptor_tester.c")
configure_file(${PROJECT_SOURCE_DIR}/devices.c32 ${CMAKE_BINARY_DIR}/bin/devices.c32 COPYONLY)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${EVDEV_LIBRARIES})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${PROJECT_SOURCE_DIR}/devices.c32"
    $<TARGET_FILE_DIR:${PROJECT_NAME}>)

add_custom_target(run
    COMMAND $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_BINARY_DIR}/bin/devices.c32
    DEPENDS ${PROJECT_NAME})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
