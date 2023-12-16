# Draft structure of functions 

This is a firmware draft of how can be develop the code for the pedals.

This file will include the posible functions, struct, enums that will be used for the UML diagram


## Tasks (FreeRTOS)

- StatusMonitorTask
- IcAdcReading
- LoadCellDataAdquisition
- SendingUsbPackage
- SerialTerminalInUsbData
- SerialTerminalOutUsbData
- ApplyAdcFilter
- ShowLedStatus
- LoadProfile (use an interruption in the case of any change at switches states)

## Functions
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
- ParserCommand (build a struct that can be used to modify values)  

## Enum

```c
typedef enum {
    TASK_SUCCESS,
    TASK_ERROR_GENERIC,
    TASK_ERROR_TIMEOUT
}TaskStatus;

typedef enum{
    INVALID_PARAMETER,

}err_t

typedef enum {
    ADC_CHANNEL_0,
    ADC_CHANNEL_1,
    ADC_CHANNEL_2,
    ADC_CHANNEL_3,
    ADC_CHANNEL_4,
    ADC_CHANNEL_5,
    ADC_CHANNEL_6,
    ADC_CHANNEL_7,
    LC_CHANNEL_1,
    LC_CHANNEL_2,
    LC_CHANNEL_3,
}Channel


```

## Structs

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
}ChannelFunction;

typedef struct{

}LowPassFilterValues;

typedef struct{
    uint16 Low;
    uint16 Top;
    bool inverted;
}HardwareConfig

```
