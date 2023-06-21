# Pasos para compilar la interfaz grafica usando docker

1. Contruir la imagen docker
```bash
docker build -t cae32/bullseye:1.0 .
```
2. Ejecutar el archivo Makefile

```bash
make gui #compila la GUI
```

