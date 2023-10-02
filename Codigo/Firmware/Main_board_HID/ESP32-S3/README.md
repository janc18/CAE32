# ESP32-S3
This is the source code for the main microcontroller, and it performs the following tasks:

- Communication with the host (PC), connecting via a USB cable and appearing in the system as an HID device (Joystick).

- Collection of all data from the modules, such as their position and status, through SPI communication.

- Firmware updates for modules via SPI, thus avoiding the use of firmware programmers for the module.

## Steps for Building the Project (in case you're not using the Docker container)

1. Install ESP-IDF.

2. In this directory, execute the following commands:

```sh
get-idf
idf.py build
```

3. Upload the new firmware.

## SPI Register for each module

### Pedals

|Command (HEX)|Name|Detalles|
|-|-|-|
|0x01|VERSION|Installed Firmware Version|
|0x02|CONFIG_RESOLUTION|Configure ADC Resolution|
|0x03|ACCE|Accelerator Value|
|0x04|BRAKE|Brake Value|
|0x05|CLUTCH|Clutch Value|
|0x06|STATUS|Error Status|


