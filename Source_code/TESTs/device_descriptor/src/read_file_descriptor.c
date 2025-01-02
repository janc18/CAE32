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
char hid_path[] = "/dev/hidraw";

 enum axis { AXIS_X = 0x30, AXIS_Y, AXIS_Z, AXIS_RX, AXIS_RY, AXIS_RZ };
 unsigned char usage_id_axis_values[6] = {AXIS_X, AXIS_Y, AXIS_Z, AXIS_RX, AXIS_RY, AXIS_RZ};
/**
 * @brief Check if a hexadecimal value exist in an unsigned char array
 *
 *  @param char Value to search
 *  @param unsigned char[] Array to search the value
 *  @param int Array size
 *  @return bool true if found or false if didn't
 */
bool existInArray(unsigned char value, unsigned char array_to_compare[], int array_size) {
  for (int i = 0; i < array_size; i++) {
    if (array_to_compare[i] == value) {
      printf("found %x",value);
      return true;
    }
  }
  return false;
}

/**
 * @brief Generate an allocated string with the hid path
 *
 * @param char* path to be concatenate
 * @param int Number to concatenate with the path
 *
 * Example: /dev/input/event 0
 *          ^^^^^^^^^^^^^^^^ ^
 *          |                |
 *          path              number
 * @return char* Allocated string with the path generated
 */
char *generatePath(char *path, int number_device) {
  if (path == NULL) {
    fprintf(stderr, "ERROR: Path paramater NULL\n");
    return NULL;
  }
  int buffersize = 30;
  char *p_buffer = calloc(sizeof(char), buffersize);
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
 *  -3 Parameters NULLs
 *  >0 If it was find, return the actual file descriptor number
 */
int getFd(char *path_device, char *compare_device_name) {
  if (path_device == NULL || compare_device_name == NULL) {
    fprintf(stderr, "ERROR: Path device or compare device name is NULL\n");
    return -3;
  }
  int fd, res = 0;
  char buffer[50] = {0};

  fd = open(path_device, O_RDWR | O_NONBLOCK);

  if (fd < 0) {
    perror("Unable to open device");
    return -1;
  }

  res = ioctl(fd, HIDIOCGRAWNAME(256), buffer);

  if (res < 0) {
    perror("HIDIOCGRAWNAME");
    return -1;
  }

  if (strcmp(compare_device_name, buffer) != 0) {
    printf("Don't found at %s\n", path_device);
    close(fd);
    return -2;
  }

  if (strcmp(compare_device_name, buffer) == 0) {
    printf("Found %s device at %s\n", compare_device_name, path_device);
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
 * @return bool true when it's found or false if didn't or path_device is null
 */
char *searchDevice(char *path_device) {
  if (path_device == NULL) {
    fprintf(stderr, "ERROR: Path device is NULL\n");
    return NULL;
  }
  int device_number = 0, fd = 0;
  while (fd != -1) {
    char *newpath;
    newpath = generatePath(hid_path, device_number);
    fd = getFd(newpath, path_device);
    if (fd > 0) {
      return newpath;
    } else {
      free(newpath);
    }
    device_number++;
  }
  return NULL;
}

struct hidraw_report_descriptor *getReportDescriptor(char *path_device) {
  char *hid_path;

    hid_path = searchDevice(path_device);

  if (hid_path == NULL) {
    return NULL;
  }

  int fd;
  int res, desc_size = 0;
  char buf[256];
  struct hidraw_report_descriptor *rpt_desc = malloc(sizeof(struct hidraw_report_descriptor));
  fd = open(hid_path, O_RDWR | O_NONBLOCK);
  if (fd < 0) {
    perror("Unable to open device");
    free(rpt_desc);
    return NULL;
  }
  memset(buf, 0x0, sizeof(buf));

  /* Get Report Descriptor Size */
  res = ioctl(fd, HIDIOCGRDESCSIZE, &desc_size);
  if (res < 0) {
    perror("HIDIOCGRDESCSIZE");
    free(rpt_desc);
  }
  /* Get Report Descriptor */
  rpt_desc->size = desc_size;
  res = ioctl(fd, HIDIOCGRDESC, rpt_desc);
  if (res < 0) {
    perror("HIDIOCGRDESC");
    free(rpt_desc);
  } else {
    free(hid_path);
    return rpt_desc;
  }
  return NULL;
}
