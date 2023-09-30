
# CAE32

CAE32 is a project for building and developing all stages of a gaming wheel for PC, specifically for the GNU/Linux operating system.

If you want to contribute, please read the [CONTRIBUTING.md](./CONTRIBUTING.md) file.

## The stages include:

* PCB Design
* Firmware
* Driver (Kernel module if necessary)
* Configuration and calibration through a graphical user interface (GTK-3)
* Design of mechanisms for pedals, gear lever, and wheel
* Power PCB design for feedback motor control (FFB)

## Pedals

### Version 1.0

- Board for capturing analog signals (STM32G070KBT6)

![Signals](./Esquematicos/CAE32_PCB/Pedals/Pedals_1_V1.png)

### Version 2.0

- Board for capturing analog signals (STM32F072RBT6)

It has several improvements compared to the first version. For more information, visit the following [file](./Esquematicos/CAE32_PCB/Pedals/README.md)

![Signals version 2](./Esquematicos/CAE32_PCB/Pedals/Pedals_1_V2.png)

## Shifter

### Version 1.0

- Board for capturing digital signals form gear shifts (RP2040)

![shifter](./Esquematicos/CAE32_PCB/Shifter/Shifter.png)

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

Current interface design

![Interface](./Codigo/Interfaz_grafica/Previa.png)
