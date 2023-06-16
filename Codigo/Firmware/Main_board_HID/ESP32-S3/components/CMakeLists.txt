set(component_srcs "src/Spi_communication.c" "src/Usb_communication.c" "src/Wheel_task.c")

idf_component_register(SRCS "${component_srcs}"
                       INCLUDE_DIRS "include" "."
                       PRIV_INCLUDE_DIRS ""
                       PRIV_REQUIRES "driver" REQUIRES "tinyusb")
