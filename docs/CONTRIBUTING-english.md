# Contributing to CAE32

Thank you for considering contributing to the CAE32 project! Here are some guidelines and recommendations to help you make effective contributions.

## Development Environment

This project has been tested on Debian Bullseye, and there shouldn't be any compatibility issues when building the components (GUI and Firmware) 
since Docker containers are used. However, there might be issues when running the GUI. 
In case you encounter any problems, please create an issue following the steps described below.

## Code Style

Please follow the camel case code style when making changes to the project.

Example:
```c

int convertRawValuesToRadians(int fd) {

}
```
Also, configure your IDE to use clang-format.

## Language

Comments, variable names, and function names should be written in English.

Bug reports can be written in English or Spanish.

## Building the GUI and ESP32S3 Firmware

We recommend using the provided Docker images to build the GUI and ESP firmware. Detailed instructions can be found in the construction guide available at the following links:

[Building the GUI](../Codigo/Interfaz_grafica/README.md)

[Building the ESP-IDF Firmware](../Codigo/Firmware/Main_board_HID/ESP32-S3/README.md)

## Reporting Issues

If you encounter any problems or errors in the project, we encourage you to create an issue in the repository. Make sure to include the following elements:

Steps to reproduce the issue.
Detailed description of the expected behavior and the observed behavior.

## Pull Requests

Before submitting a pull request, make sure to follow these steps:

Run the tests to ensure the correct behavior.
Describe the changes made and provide relevant information in the pull request description.

## GitHub Projects

If you're unsure where to start, check the [Projects](https://github.com/users/janc18/projects/1/views/1), tab. It lists all the ongoing 
actions in the project, and you can also view them grouped by [difficulty](https://github.com/users/janc18/projects/1/views/5?groupedBy%5BcolumnId%5D=47717354).

## PCB

The software used to create the PCB is KiCAD 6.

When selecting components, make sure to obtain the part numbers from [LCSC](https://www.lcsc.com/).

Thank you again for your interest in contributing to the CAE32 project! We look forward to receiving your contributions and improving the project together.
