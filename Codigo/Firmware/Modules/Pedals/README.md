# Notas para la siguiente versión de pcb

- Exponer todos los buses de comunicación(SPI,I2c,UART,CAN)
- Cambiar el tipo de boton usados para reset y boot 
- Agregar leds de diferntes colores, para indicar estados
- Conectar los propios leds del conector rj45 a MiSO y MOSI
- Agregar un circuito para aplicar las señales correspondientes a el pin BOOT y RESET, de esa forma actualizar el firmware sin acceder directamente a la PCB
- Tener en cuenta el el diseño de PCB para el case impreso en 3D y viciversa


## Compilación del firmware
Para compilar el proyecto es necesario tener el siguiente paquete

**En debian**
```sh
sudo apt install gcc-arm-none-eabi
```

Ahora es el momento de crear el binario (archivo.elf)

```sh
cd Debug
make all
```

