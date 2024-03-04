/**
 * @file read_file_descriptor.c
 *
 * @brief Get all the hid device related information

 * - To get all the information about the hid device, it can be acomplish using
 *   linux libraries like hidraw, getting for example the next values:
 *    - Device name
 *    - Device descriptor
 *    - Hid features
 *  All ioctl commands are explain in the next link:https://www.kernel.org/doc/html/latest/hid/hidraw.html
 *
 */
#include <linux/hidraw.h>
#include <linux/input.h>
#include <linux/types.h>

#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "read_file_descriptor.h"

unsigned char usuage_id_axis_values[6] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35};
char hid_path[] = "/dev/hidraw";

/**
 * @brief Check if a hexadecimal value exist in an unsigned char array
 *
 *  @param char Value to search
 *  @param unsigned char[] Array to search the value
 *  @param int Array size
 *  @return bool true if found or false if didn't
 */
bool exist_in_array(unsigned char value, unsigned char array_to_compare[], int array_size) {
  for (int i = 0; i < array_size; i++) {
    if (array_to_compare[i] == value) {
      return true;
    }
  }
  return false;
}

/**
 * @brief Generate an allocated string with the hid path 
 *
 * @param char* Hid path to be concatenate
 * @param int Number to concatenate with the hid path
 *
 * Example: /dev/hidraw 0
 *          ^^^^^^^^^^^ ^
 *          |         | |
 *          path         number
 * @return char* Allocated string with the hid pad generated
 */
char *generate_hid_path(char *path, int number_device) {
  int buffersize = 30;
  char *p_buffer = malloc(buffersize * sizeof(char));
  snprintf(p_buffer, buffersize, "%s%d", path, number_device);
  return p_buffer;
}

/**
 * @brief Get the file descriptor of a given device name
 *
 * @param char* Hid path, Example(/dev/hidraw1)
 * @param char* Device name to be compared with the hid device name
 *
 * @return int 
 *  -1 Unable to open device or an error occour when getting the name
 *  -2 Compared name it's the correct one
 *  >0 If it was find, return the actual file descriptor number
 */
int get_fd(char *path_device, char *compare_device_name) {
  int fd, res;
  char buffer[50] = {0};

  fd = open(path_device, O_RDWR | O_NONBLOCK);

  if (fd < 0) {
    perror("Unable to open device");
    close(fd);
    return -1;
  }

  res = ioctl(fd, HIDIOCGRAWNAME(256), buffer);

  if (res < 0) {
    perror("HIDIOCGRAWNAME");
    return -1;
  }

  if (strcmp(compare_device_name, buffer) != 0) {
    printf("Don't found at %s\n", path_device);
    return -2;
  }

  if (strcmp(compare_device_name, buffer) == 0) {
    printf("Found %s device at %s with an fd at %d\n", compare_device_name, path_device, fd);
    close(fd);
    return fd;
  }
  return -1;
}


/**
 * @brief Search in all hid device connected for the given device name
 *
 * @param char* Hid path, Example(/dev/hidraw1)
 * @param int* File descriptor number
 *
 * @return bool true when it's found or false if din't
 */ 
bool search_device(char *path_device, int *fd) {
  char *newpath;
  int iteration = 0;
  *fd = 0;
  while (*fd != -1) {
    newpath = generate_hid_path(hid_path, iteration);
    *fd = get_fd(newpath, path_device);
    if (*fd > 0) {
      free(newpath);
      return true;
    }
    iteration++;
  }
  free(newpath);
  return false;
}
