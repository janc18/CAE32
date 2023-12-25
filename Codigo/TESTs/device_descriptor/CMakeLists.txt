cmake_minimum_required(VERSION 3.10)
project(DeviceDescriptorTest)

set(DEVICE_DESCRIPTOR_C ../../Shared_libraries/Device_descriptors/src/device_desc_pedals.c)
set(DEVICE_DESCRIPTOR_H ../../Shared_libraries/Device_descriptors/include/)
set(SOURCE_FILE_MAIN ../../Device_simulation/src/Joystick.c)


add_executable(device_descriptor ${SOURCE_FILE_MAIN} ${DEVICE_DESCRIPTOR_C})

target_include_directories(device_descriptor PRIVATE ${DEVICE_DESCRIPTOR_H})
