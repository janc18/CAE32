# Contribuciones a CAE32

¡Gracias por considerar contribuir al proyecto CAE32! 
Aquí tienes algunas pautas y recomendaciones para ayudarte a hacer contribuciones de manera efectiva.

[English contribution file](./docs/CONTRIBUTING-english.md)

## Entorno de desarrollo

Este proyecto esta probado en Debian Bullseye, aunque no debería de existir problemas de compatibilidad al **construir** los elementos(GUI y Firmware), ya que se usan
contenedores Docker,sin embargo es posible que al ejecutar la GUI existan problemas, en dado caso crea un issue, siguiendo los pasos que muestran a continuación

## Estilo de código

Por favor, sigue el estilo de código camel case al realizar cambios en el proyecto.

**Ejemplo**

```c
int convertRawValuesToRadians(int fd){

}
```
Además configura tu IDE para usar clang-format

## Idioma

Los comentarios, nombres de variables y funciones deben estar escritos en Inglés

Los reportes de problemas pueden redactarse tanto en Inglés como Español

## Construcción de la interfaz gráfica y el firmware para el ESP32S3

Recomendamos utilizar las imágenes de Docker proporcionadas para construir la interfaz gráfica y el firmware de ESP-IDF. 
Puedes encontrar instrucciones detalladas en la guía de construcción disponible en el siguiente enlace:

[Guía para construir la GUI](./Codigo/Interfaz_grafica/README.md)
[Guía para construir el firmware ESP-IDF](./Codigo/Firmware/Main_board_HID/ESP32-S3/)

## Reporte de problemas

Si encuentras algún problema o error en el proyecto, te animamos a crear un issue en el repositorio. Asegúrate de incluir los siguientes elementos:

1. Pasos para reproducir el problema.
2. Descripción detallada del comportamiento esperado y del comportamiento observado.

## Pull Requests

Antes de enviar un pull request, asegúrate de seguir estos pasos:

1. Ejecuta las pruebas para garantizar que el comportamiento sea el adecuado.
2. Describe los cambios realizados y proporciona información relevante en la descripción del pull request.

## Projects Github

Si no sabes por dónde empezar, revisa la pestaña [Projects](https://github.com/users/janc18/projects/1/views/1), aquí encontrarás todas las acciones en las que se esta trabajando
actualmente en el proyecto, ademas aquí puedes verlas agrupadas por [dificultad](https://github.com/users/janc18/projects/1/views/5?groupedBy%5BcolumnId%5D=47717354)

## PCB

El Sofware utilizado para crear la PCB es KiCAD 6

Al elegir los componentes, el número de parte se tiene que obtenerse de la pagina [LCSC](https://www.lcsc.com/)

¡Gracias nuevamente por tu interés en contribuir al proyecto CAE32! Esperamos recibir tus contribuciones y mejorar juntos el proyecto.
