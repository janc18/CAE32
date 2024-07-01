#include "setup.h"
#include <stdio.h>
#include <unistd.h>
/**
 * @brief Check if was executed with sudo permissions
 *
 *  @return bool True if has sudo permission or false if wasn't
 */
bool hasSudoPermissions() {
  if (getuid()) {
    fprintf(stderr, "Doesn't have sudo permissions to read the events, Want to continue? Y/n\n");
    return false;
  } else {
    return true;
  }
}
/**
 * @brief Read the input(one character) of the user
 *
 * Check if the user wants to keep executing the program without sudo permission,
 * this function verify if the input was(y,Y,\n)
 * @return bool True if the user wants to continue without sudo permission and false if wasn't
 */
bool continueWithoutSudoPermissions() {
  char response[9];
  fgets(response, 3, stdin);
  switch (response[0]) {
  case '\n':
    return true;
    break;
  case 'y':
    return true;
    break;
  case 'Y':
    return true;
    break;
  default:
    return false;
  }
}
/**
 * @brief Check if the program was executed as sudo user
 *
 * If the program wasn't executed as sudo or the given path for the device is invalid
 * the program would close
 *
 * @param char* device information path *.c32
 *
 * @return int -1 Doesn't want to continue or the path is invalid
 *              0 The program was executed as sudo and the given path is correct
 */
bool itHasSudoPermissions(char *device_information_path) {
  bool sudoPermission = false;
  // Check if it has sudo permission to read the report descriptor
  sudoPermission = hasSudoPermissions();
  if (!sudoPermission) {
    if (continueWithoutSudoPermissions() == false) {
      fprintf(stderr, "Isn't posible to read events without sudo permission, execute with sudo access\n");
      return false; // Quit program
    }
  }
  // Checking if a path was given
  if (device_information_path == NULL) {
    fprintf(stderr, "ERROR: Doesn't give any input path\n");
    return false;
  }
  return true;
}
