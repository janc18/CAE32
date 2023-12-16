# Change log PCB Pedals

## Issues
* Fix silkscreen text at UART port TX->RX RX->TX 
* Change diameter pcb holes for M3
* Route correctly the boot and reset buttons
* Round pcb corners
* Change the female headers for block connectors or quick connectors
* The IC ADC require extra components at his inputs 

## PCB Testing behavior

- Check the noise and data acquisition time without a single pole filter

## TDD(Test Driven Development)

To know if the GUI it's working correctly, one way, can be tested with the use of a virtual device than can be created with the 
uhid library for the linux system, the functionalities that could be tested will be the next:

- Device detection (Connection)
- Device descriptor
- Visual representation (axis and steering wheel)
- Emulation of device console(sending and reciving data for configuration behavior)

