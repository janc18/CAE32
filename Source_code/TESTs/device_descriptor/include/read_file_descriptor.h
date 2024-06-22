#ifndef READ_FILE_DESCRIPTOR
#define READ_FILE_DESCRIPTOR
#include <stdbool.h>
extern unsigned char usage_id_axis_values[6];
bool existInArray(unsigned char value, unsigned char array_to_compare[], int array_size);
char *generatePath(char *path, int number_device);
int getFd(char *path_device, char *compare_device_name);
char *searchDevice(char *path_device);
struct hidraw_report_descriptor *getReportDescriptor(char *path_device);
#endif
