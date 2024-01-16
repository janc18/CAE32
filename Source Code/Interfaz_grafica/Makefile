.PHONY: gui

gui:
	docker run --rm -it -v $(shell pwd)/Interfaz_gtk/:/home/CAE32 cae32/bullseye:1.0 mkdir -p build
	docker run --rm -it -v $(shell pwd)/Interfaz_gtk/:/home/CAE32 cae32/bullseye:1.0 cmake -S /home/CAE32/ -B /home/CAE32/build
	docker run --rm -it -v $(shell pwd)/Interfaz_gtk/:/home/CAE32 cae32/bullseye:1.0 make -C /home/CAE32/build/

clean:
	rm -rf $(shell pwd)/Interfaz_gtk/build
