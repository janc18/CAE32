# Placa de constrol principal CAE32

## Como microcontrolador principal se usará el ESP-32-S3

Debido a que este cuenta con la funcionalidad OTG "On The Go", con lo cual ya no es necesario hardware extra 
para hacer la conexión.

## Elementos

* Puerto Usb tipo C para conectarlo a la Pc.

* Alimentación proveniente de Pc.

* Multiplexores.
	- Para conmutar entre las entradas analógicas y digitales, provenientes de los sensores de posicion de pedales e
interruptores correspondientes al valor de la marcha.

* ADC
	- Para obtener una mayor presición se usara un ADC externo en conjunto con el multiplexor y leer las entradas
analógicas una a la vez.

* Pines sobrantes expuestos, debido que aún es un prototipo. 

## Microcontrolador secundario

Este MCU se conectara con el microcontrolador principal por medio de UART, para controlar accesorios o incluso 
reducirle la carga al ESP32-S3, manipulando y formateando valores.

Ademas de tener todos los pines expuestos. 

## Controlador de potencia para el nema 34

Este se encontrara en otra PCB, y las señales seran producidas por el ESP32-S3 o por el MCU secundario.

## PCBs para los pedales

Se cambiara el AS5600 por un sensor de efecto Hall, así que será necesario fabricar una pequeña PCB, para sujetarlo
en su lugar y filtrar la señal en caso que se requiera

## Descripción detallada de componentes

* PCB
Para programar los dos MCU, se usará un USB-UART en caso del ESP32-S3 y Stlink para el MCU de STM

1. ESP32-S3-WROOM-1-N4 [Guía para diseño del hardware del ESP32-S3](https://www.espressif.com/sites/default/files/documentation/esp32-s3_hardware_design_guidelines_en.pdf)





 

