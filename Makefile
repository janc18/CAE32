.PHONY: gui

gui:
	#docker start cae32/bullseye
	docker run --rm -it -v /home/jose/Documentos/CAE32/Codigo/Interfaz_grafica/Interfaz_gtk/:/home/CAE32 cae32/bullseye:1.0 mkdir -p build
	docker run --rm -it -v /home/jose/Documentos/CAE32/Codigo/Interfaz_grafica/Interfaz_gtk/:/home/CAE32 cae32/bullseye:1.0 cmake -S /home/CAE32/ -B /home/CAE32/build
	docker run --rm -it -v /home/jose/Documentos/CAE32/Codigo/Interfaz_grafica/Interfaz_gtk/:/home/CAE32 cae32/bullseye:1.0 make -C /home/CAE32/build/

clean:
	rm -rf ./Codigo/Interfaz_grafica/Interfaz_gtk/build
