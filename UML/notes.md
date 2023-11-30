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

### Variables to allocate memory
```c

unsigned char Profile;

```

### Enum

```c
typedef enum {
    TASK_SUCCESS,
    TASK_ERROR_GENERIC,
    TASK_ERROR_TIMEOUT
}TaskStatus;

typedef enum {
    ADC_CHANNEL_0,
    ADC_CHANNEL_1,
    ADC_CHANNEL_2,
    ADC_CHANNEL_3,
    ADC_CHANNEL_4,
    ADC_CHANNEL_5,
    ADC_CHANNEL_6,
    ADC_CHANNEL_7,
}AdcChannel

typedef enum {
    LC_CHANNEL_1=8,
    LC_CHANNEL_2,
    LC_CHANNEL_3,
}LoadCellChannel

```

### Structs

```c
typedef struct{
  void *funtion-to-execute-in-case-of-error;
  void *generic-function-to-text-through-serial-console;
  uint32 RetryCount;
  
}StatusTask;

/*
- The value correspond to the channel to use 
- Example
    - Clutch channel ADC 3 = Clutch=ADC_CHANNEL_3;
    - Throttle Load cell 1 = Throttle=LC_CHANNEL_1;
    - The channels than don't be use its value is = -1
    - All customs channels without use = Custom_0 = -1;
*/

typedef struct{
    char Throttle;
    char Clutch;
    char Brake;
    char Custom_0;
    char Custom_1;
    char Custom_2;
    char Custom_3;
    char Custom_4;
    char Custom_5;
    char Custom_6;
    char Custom_7;
    char Custom_8;
    char Custom_9;
}ProfileConfigPedal;

typedef struct{

}LowPassFilterValues;

typedef struct{
    uint16 Low;
    uint16 Top;
    bool inverted;
}HardwareConfig

```


### Tasks (FreeRTOS)

- StatusMonitorTask
- I2cAdcReading
- LoadCellDataAdquisition
- SendingUsbPackage
- SerialTerminalInUsbData
- SerialTerminalOutUsbData
- ApplyAdcFilter
- ShowLedStatus
- LoadProfile (use an interruption in the case of any change at switches states)

### Functions
- ConfigAdcIc (Set resolution and configs)
- ConfigLoadCell 
- SetConfigValues (set, top and low limits, inverted axis)
- GetConfigValues (get, top and low limits, inverted axis)
- LoadProfile (Load all the values from the ROM)
- CreateProfile
  - Save the limits and what function do every channel, example(ADC channel 1 its the brake,Load cell 1 is the clutch, etc.)
  - Depending of the dip switch state located at the pcb will save the already create profile in a different location to save until 7 profiles    
  - Save values at ROM
- ConfigUsbStream (depending of the profile select change the device descriptor)
- Reboot
- LimitsCalibration (With the GUI or serial terminal, pressing the pedal to define in real time the limits)
- ReadSwitchValue (Get the value depending of the 3 switch inputs) 
-  
