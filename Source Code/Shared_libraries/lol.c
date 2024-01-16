#include "lol.h"
#include <stdlib.h>

char name[]="String test\n";

char *string_test(char *test){
  size_t longitud = 0;
    while (test[longitud] != '\0') {
        longitud++;
    }

    // Crea un nuevo arreglo para almacenar la cadena de salida
    char *salida = (char *)malloc((longitud + 1) * sizeof(char));

    // Copia la cadena de entrada a la cadena de salida
    for (size_t i = 0; i <= longitud; i++) {
        salida[i] =test[i];
    }

    // Devuelve la cadena de salida
    return salida;
}


