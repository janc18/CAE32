.PHONY: gui

gui:
	docker start cae
	docker run -it -v /home/jose/Documentos/CAE32/Codigo/Interfaz_grafica/Interfaz_gtk/:/home/CAE32 cae32_image mkdir -p build
	docker run -it -v /home/jose/Documentos/CAE32/Codigo/Interfaz_grafica/Interfaz_gtk/:/home/CAE32 cae32_image cmake -S /home/CAE32/ -B /home/CAE32/build
	docker run -it -v /home/jose/Documentos/CAE32/Codigo/Interfaz_grafica/Interfaz_gtk/:/home/CAE32 cae32_image make -C /home/CAE32/build/
