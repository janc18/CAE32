#ifndef READ_FILE_DESCRIPTOR
#define READ_FILE_DESCRIPTOR
#include <libudev.h>
void read_hidraw_devices(int max_number_of_devices);
void enumerate_block_devices(struct udev *udev);
#endif
