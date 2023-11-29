## Packages

- UI
  - UI Updater
  - Status console
  - Firmware Updater::Stm cube programmer
  - Data values display
  - Configuration pcb values(soft stops, hard stops, sensibility, etc)

- Devices configuration
    - Steering wheel configuration
      - Serial terminal
    - Pedals configuration
      - Serial terminal
    - Shifter configuration 
      - Serial terminal
  
_With the Serial terminal it's posible to send values witout the necessity of firmware update_

- Hardware(PCBs)
    - Steering wheel
    - Pedals
    - Shifter

## Use cases diagram

- Hardware
- USB
- HID
- Game
- UI

## Pedals (draft::States,task,structs,etc)

- Get analog readings
  - i2c communication with ADC chip
    - initial IC configuration (Resolution, speed, one shot,etc)
    - *Get data*
  - getting the data stream from the load cell IC 
    - Configure a pwm channel to generate the clock signal
    - *Get data*

- Compact or mergue all the data for usb HID protocol
  * After the analog readings send the usb data stream

- Load pre-configuration using the dip switch 
  * if it's not posible to load a new configuration to the pcb because it's imposible to access to the GUI it will have some profiles pre-loaded

- Define a HID device descriptor
  - 3 to 11 channels
  - 14 bits each
  - serial terminal for pcb status
  - bit stream for configuration

- PCB Status
  - Check if ICs ADC and load cell return an acknowledge
  - show the status with the serial terminal and leds

- apply filter to any analog signal
  * before to send the data, it will apply a function to change the data to the correponding behavior (low filter, high filter)

- Calibration function or algorithm
  - choose the start and stop position
  - sensibility
  - select what pedal correspond to certain input

- UI config file (.txt | .config | .cae32)

- add function to check system stability (low resorces or not enough speed, etc)

- all task or functions need to return finish status (SUCCESS, ERROR, [custom errors messages]) 
