cmake_minimum_required(VERSION 3.10)
project(CheckGoogleTest)

# Configura Google Test
find_package(GTest)

# Muestra un mensaje indicando si Google Test está instalado
if(GTEST_FOUND)
    string(ASCII 27 Esc)
    set(Green "${Esc}[32m")
    set(Reset "${Esc}[m")
    message(STATUS "${Green}Google Test found.${Reset}")
else()
    message(FATAL_ERROR "Google Test not found. Please install it.")
endif()



set(DEVICE_DESCRIPTOR_C ../configs/lol.c)
set(DEVICE_DESCRIPTOR_H ../configs/)
set(SOURCE_FILE_MAIN ../Device_simulation/src/nombre.c)
set(SOURCE_FILE_TEST ./unit_tests/string.c)

include(CTest)


add_executable(device_sim ${SOURCE_FILE_MAIN} ${DEVICE_DESCRIPTOR_C})

target_include_directories(device_sim PRIVATE ${DEVICE_DESCRIPTOR_H})

add_executable(prueba ${SOURCE_FILE_TEST} ${DEVICE_DESCRIPTOR_C})
target_include_directories(prueba PRIVATE ${DEVICE_DESCRIPTOR_H})
add_test(NAME funcion COMMAND prueba)
