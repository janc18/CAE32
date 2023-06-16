# Revisión de PCB

## Principales problemas con la V1

1. Los conectores usados son difíciles de usar, requieren de un ensamble meticuloso
para que funcione correctamente.

2. Los botones usados para el **Reset** y **Boot** son muy pequeños, por lo que si se
usa un case, podrian ser de dificil acceso.

3. La Api **HAL** del MCU tiene problemas que aún no he podido resolver de manera 
correcta, estos están relacionados con la lectura analogica.

4. Los puertos para la depuración y programación no están distribuidos eficientemente.

5. Aunque tiene una resolución máxima de 14bits, tiene ruido que altera las lecturas
ocasionando una peor experiencia de juego.

6. Cuando se suba el nuevo firmware no se logrará actualizar a menos de que se presionen
los botones físicamente

## Solución de problemas para la V1

1. Cambiar los conectores usados por unos "pin sockets", y agregar una huella para soldar
directamente un cable, ademas añadir la serigrafia necesaria.

2. Elegir botones mas altos y acomodarlos en una zona de fácil acceso 

3. Usar la capa LL(Low Level) para tener un control más preciso de las lecturas análogicas

4. Acomodar los puertos a una zona más accesible, como a un costado, uno al lado del otro

5. Agregar un filtro por software

6. Conectar las entras de Reset y Boot al puerto rj45

## Recomendación

- Quizá sea mejor opción agregar un Multiplexor de 8 canales con ADC, además que será posible 
agregar más sensores, pero no estoy seguro si el MCU será lo suficiente rápido para leer 
todos los datos

- Añadir hardware para 3 células de carga
	- Posible modelo de celda de carga [Aliexpress](https://es.aliexpress.com/item/1005004518830741.html)


- Añadir pines para conexión SPI y I2c
