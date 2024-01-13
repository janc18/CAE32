# Code // Codigo

In this folder, you can find the entire project code, which can be built by executing:

```sh 
make
```

*Now, a brief explanation of the files and folder content*

## config_file

File necessary to build all the documentation using the _Sphinx_ programm

## checking_dependency.sh 

A small bash script to check if all the dependencies are already installed, in case
someone isn't installed, it will print what is missing.

## Shared_libraries/

Files shared between the Firmare, TESTs, and Device_simulation folders for quick 
access and modifications.

## Desktop_files/

A bash script to execute when the GUI is select in the system menu

## Firmare/

Firmware for the modules(Pedals, shifter and steering wheel) and main board.

## Interfaz_grafica/

GUI(GTK) Source code 

## TESTs/

GUI and Device simulation unit tests
