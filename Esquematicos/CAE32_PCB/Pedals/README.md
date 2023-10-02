# PCB Changelog

In this file, I will add the issues encountered with the development of each PCB 
and how they will be addressed in the next interation

## Key Issues with V1

1. The connectors used are challenging to work with and require meticulous assembly for proper functioning.

2. The buttons used for **Reset** and **Boot** are very small, so if a case is used, they could be difficult to access.

3. The MCU's **HAL** API has unresolved issues related to analog readings.

4. Debugging and programming ports are not efficiently distributed.

5. Despite having a maximum resolution of 14 bits, there is noise that disrupts readings,
resulting in a poorer gaming experience.

6. Uploading new firmware will not be possible without physically pressing the buttons.

## Troubleshooting for V1

1. Replace the connectors with "pin sockets" and add a footprint for soldering a cable directly,
as well as adding the necessary silkscreen.

2. Choose taller buttons and position them in an easily accessible area.

3. Use the LL (Low Level) layer for more precise control of analog readings.

4. Rearrange the ports to a more accessible area, such as placing them side by side.

5. Implement an analog software filter.

6. Connect the Reset and Boot inputs to the RJ45 port.

## Version 2 Upgrades

- 8-channel multiplexer with ADC 

- Add hardware for 3 load cells
  - Possible load cell model [Aliexpress](https://www.aliexpress.com/item/1005004518830741.html)

- Add pins for SPI and I2C connections

- USB Type-C

- A more powerful microcontroller (STM32F0 family) with HID connection support,
potentially allowing it to function without the mainboard.
