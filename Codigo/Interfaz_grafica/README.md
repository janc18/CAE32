# Pasos para compilar la interfaz grafica

Para compilar el proyecto es necesario todos los requisitos para GTK y **CMake**

Estos los puedes encontrar [aquí (GTK)](https://www.gtk.org/docs/installations/)

Sigue los pasos para instalar CMake dependiendo de tu distro

Instrucciones

```bash
cd Interfaz_gtk/
mkdir build
cd build
cmake .. && make
```

# Pasos para compilar la interfaz grafica usando docker

1. Contruir la imagen docker
```bash
docker build -t cae32/bullseye:1.0 .
```
2. Ejecutar el archivo Makefile
```bash
make
```
