# Makefile to configure and create all the CMakeLists.txt build folders

.PHONY: all

all: GUI Testing

GUI:
	@echo "Creating build files for the GUI"
	cmake -B ./Interfaz_grafica/Interfaz_gtk/build/ ./Interfaz_grafica/Interfaz_gtk/
	make -C ./Interfaz_grafica/Interfaz_gtk/build/

Testing:
	@echo "Creating build files for testing"
	cmake -B ./TESTs/device_descriptor/build ./TESTs/device_descriptor/
	make -C ./TESTs/device_descriptor/build/

build_gui:
	@echo "Building GUI"
	$(MAKE) -C ./Interfaz_grafica/Interfaz_gtk/build/

build_tests:
	@echo "Building test cases"
	$(MAKE) -C ./TESTs/build/

clean:
	rm -r ./Interfaz_grafica/Interfaz_gtk/build/
	rm -r ./TESTs/device_descriptor/build/
