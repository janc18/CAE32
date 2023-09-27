# CAE32

CAE32 es un proyecto de construcción y desarrollo de todas las etapas de un volante para videojuegos de PC,
para el sistema operativo de GNU/Linux.

Si quiere contribuir revisa el archivo [CONTRIBUTING.md](./CONTRIBUTING.md)

If you want to contribute, please read the [CONTRIBUTING.md](./docs/CONTRIBUTING-english.md) file.

## Las etapas son:

* Diseño PCB
* Firmware
* Driver (Kernel module en caso que sea necesario)
* Configuración y calibración por medio de una interfaz de usuario (GTK-3)
* Diseño de mecanismos para pedales, palanca de cambios y volante
* Diseño PCB de potencia para el control del motor de retroalimentación (FFB)

## Pedales

### Version 1.0

- Placa para la captura de señales analogicas (STM32G070KBT6)

![Señales](./Esquematicos/CAE32_PCB/Pedals/Pedals_1_V1.png)

### Version 2.0

- Placa Para la captura de señales analogicas (STM32F072RBT6)

Tiene varias mejoras en comparación a la primera versión para mas información visita
el siguiente [archivo](./Esquematicos/CAE32_PCB/Pedals/README.md)

![Señales version 2](./Esquematicos/CAE32_PCB/Pedals/Pedals_1_V2.png)

## Palanca de cambios

### Version 1.0

- Placa para la captura de las señales digitales de los cambios de velocidad (RP2040)

![shifter](./Esquematicos/CAE32_PCB/Shifter/Shifter.png)

## Frameworks y herramientas de programación

* Espressif (ESP-IDF)

* STM32CubeIDE
* STM32CubeProgrammer
* USB-UART bridge

### Interfaz de usuario

La interfaz está desarrollada con el framework (GTK 3), esta permitirá hacer configuraciones, como por ejemplo:

* Visualización de los datos gráficamente y textual (consola)
* Tipo de transmisión (Manual, Automática, Secuencial, custom) **De forma nativa**
* Límites de los pedales, sensibilidad 
* Tipo de pedal
	* Entrada analógica (Potenciómetro, efecto hall y célula de carga)
	* Entrada SPI,I2c (Sensor personalizado)
* Actualización de firmware


**Para compilar el proyecto puedes usar el contenedor o construirlo en tu sistema(cumpliendo con las dependencias),
revisa el directorio: Codigo -> Interfaz_grafica**

Diseño de interfaz actual

![interfaz](./Codigo/Interfaz_grafica/Previa.png)
