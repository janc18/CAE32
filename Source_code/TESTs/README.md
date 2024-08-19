# Unit Tests

## Device descriptor tester

At the folder ```device_descriptor``` is the source code to check if the device descriptor
is correctly configured.

The executable can be found at ```device_descriptor/build/bin``` this is compile automatically
when you build the whole project (**Instructions at the main README**), 

## How it works
This executable needs an input file with all the information about the device to search, an 
example of this file can be found at ```device_descriptor/build/bin```, it requires a sudo 
permission to read the incoming data from the device.

This program is paired with another program, that program create a virtual device that 
simulates inputs and it's verify with the input file give (**Example at device_descriptor/build/bin**)


## TODO

- [ ] Input analysis (Virtual Device)
    - [ ] Get the step increment
    - [ ] Get from file the actuation range
    - [ ] Create a log than can be saved in a file
    - [ ] 

- [ ] Free resources (memory) when the device is desconnected
    - [ ] Know whe the device was disconnected
