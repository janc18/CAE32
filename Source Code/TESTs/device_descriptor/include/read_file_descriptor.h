#ifndef READ_FILE_DESCRIPTOR
#define READ_FILE_DESCRIPTOR
#include <stdbool.h>
bool exist_in_array(unsigned char value, unsigned char array_to_compare[], int array_size);
char *generate_hid_path(char *path, int number_device);
int get_fd(char *path_device, char *compare_device_name);
bool search_device(char *path_device, int *fd);
struct hidraw_report_descriptor *get_report_descriptor(char *path_device);
#endif
