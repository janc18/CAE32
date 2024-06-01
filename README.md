# CAE32

CAE32 is a project for building and developing all stages of a gaming wheel for PC, specifically for the GNU/Linux operating system.

If you want to contribute, please read the [CONTRIBUTING-english.md](./docs/CONTRIBUTING-english.md) file.

Si tu quieres contribuir, por favor lee el documento [CONTRIBUTING.md](./CONTRIBUTING.md)  

## Overall current status

Developing the UML diagram of the whole system

### PCBs

![status_pedals](https://badgen.net/badge/Pedals/v2.1.1/blue)

![status_shifter](https://badgen.net/badge/Shifter/v1.1.2/blue)

![status_steering_wheel](https://badgen.net/badge/Steering%20wheel/Development%20has%20not%20started/red)

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

### User Interface

The interface is developed with the GTK 3 framework, which will allow configurations such as:

* Visualization of data graphically and textually (console)
* Transmission type (Manual, Automatic, Sequential, custom) **Natively**
* Pedal limits, sensitivity
* Pedal type
  * Analog input (Potentiometer, Hall effect, and load cell)
  * SPI, I2C input (Custom sensor)
* Firmware update

## How to compile the project

1. Install all the dependencies
```bash
sudo apt install cmake make gcc pkgconf libevdev-dev libgtk-3-dev libgtk-3-0
```

2. Run the script to check if all the dependencies was successfully installed
```bash
./Source Code/checking_dependency.sh
```
3. Execute the Makefile to build the graphic interface and the unit tests
```sh
make -C Source\ Code/
```

