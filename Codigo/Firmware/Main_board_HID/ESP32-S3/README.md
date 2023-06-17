# ESP32-S3
Este es el código fuente del microcontralor principal, las tareas que ejecuta son:

- Comunicación con el host(PC), conectandose por medio de cable usb y mostrandose en el sistema como un dispositivo HID(Joystick).

- Recolección de todos los datos de los modulos, como su posición y estado, por medio de comunicación SPI.

- Actualización de firmware de los modulos por SPI, de esta manera evitando usar programadores de firmware para el modulo.


## Pasos para la construcción del proyecto(en dado caso que no uses el contenedor docker)

1. Instalar ESP-IDF

2. En este directorio ejecutar 
```sh
get-idf
idf.py build
```

3. Subir el nuevo firmware

## Registros SPI de cada modulo

### Pedales

|Comando (HEX)|Nombre|Detalles|
|-|-|-|
|0x01|VERSION|Versión de Firmware instalada|
|0x02|CONFIG_n_RESOLUTION|Configura la resolución del ADC|
|0x03|ACCE|Valor del Acelerador|
|0x04|BRAKE|Valor del Freno|
|0x05|CLUTCH|Valor del Clutch|
|0x06|STATUS|Valor de un Error|


