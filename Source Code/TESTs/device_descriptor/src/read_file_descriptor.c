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

bool exist_in_array(unsigned char value, unsigned char array_to_compare[], int array_size) {
  for (int i = 0; i < array_size; i++) {
    if (array_to_compare[i] == value) {
      return true;
    }
  }
  return false;
}

char *generate_hid_path(char *path, int number_device) {
  int buffersize = 30;
  char *p_buffer = malloc(buffersize * sizeof(char));
  snprintf(p_buffer, buffersize, "%s%d", path, number_device);
  return p_buffer;
}

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
