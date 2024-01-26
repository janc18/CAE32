
# CAE32

CAE32 is a project for building and developing all stages of a gaming wheel for PC, specifically for the GNU/Linux operating system.

If you want to contribute, please read the [CONTRIBUTING.md](./CONTRIBUTING.md) file.

## Overall current status

Developing the UML diagram of the whole system

### PCBs

![status_pedals](https://badgen.net/badge/Pedals%20v2.0.3/PCB%20received/green)

![status_shifter](https://badgen.net/badge/Shifter%20v1.1.3/Needed%20revision/red)

![status_steering_wheel](https://badgen.net/badge/Steering%20wheel%20v1.0.0/Needed%20creation%20of%20schematics/red)

### Firmware

Working on the development of the UML diagram for the pedals  firmware

### Software

Needed the improvement of compilation and flags for the user interface

## The stages include:

* PCB Design
* Firmware
* Driver (Kernel module if necessary)
* Configuration and calibration through a graphical user interface (GTK-3)
* Design of mechanisms for pedals, gear lever, and wheel
* Power PCB design for feedback motor control (FFB)

### PCB Sponsored by PCBWay

![4](https://github.com/janc18/CAE32/assets/43817922/fe6902e4-3c9f-44c4-b9a3-a8754ca71d63)

The PCB quality is excellent, the contact with the support service is good, they responded very quickly in the case of any issue, 
and it has a good PCB finish using the STM assembly service,  all the IC pads are correctly soldered. Overall, the total cost of 5 PCBs 
and 2 PCBs with the assembly service is a very accessible, so I will keep using PCBWAY to build the next PCB iterations

[PCBWay Webpage](https://www.pcbway.com/)

## Programming Frameworks and Tools

* Espressif (ESP-IDF)

* STM32CubeIDE
* STM32CubeProgrammer
* USB-UART bridge

### User Interface

The interface is developed with the GTK 3 framework, which will allow configurations such as:

* Visualization of data graphically and textually (console)
* Transmission type (Manual, Automatic, Sequential, custom) **Natively**
* Pedal limits, sensitivity
* Pedal type
  * Analog input (Potentiometer, Hall effect, and load cell)
  * SPI, I2C input (Custom sensor)
* Firmware update

**To compile the project, you can use the container or build it on your system (meeting the dependencies). Check the directory: Code -> Graphical_Interface**
