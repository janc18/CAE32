# Compiling the Graphical Interface Using Docker

To compile the graphical interface, follow these steps:

1. Build the Docker image
```bash
docker build -t cae32/bullseye:1.0 .
```
2. Execute the Makefile to compile the GUI
```
make gui
```
