cmake_minimum_required(VERSION 3.10)
project(DeviceDescriptorTest)

set(DEVICE_DESCRIPTOR_C ../../configs/device_descriptor.c)
set(DEVICE_DESCRIPTOR_H ../../configs/)
set(SOURCE_FILE_MAIN ../../Device_simulation/src/uhid-HID.c)


add_executable(device_descriptor ${SOURCE_FILE_MAIN} ${DEVICE_DESCRIPTOR_C})

target_include_directories(device_descriptor PRIVATE ${DEVICE_DESCRIPTOR_H})
