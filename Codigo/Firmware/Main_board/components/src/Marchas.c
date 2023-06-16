//*****************************Configuración de marcha********************//
// Este código tiene como proposito capturar el cambio en el que se encuentra la trasmisión
// además esta pensado para una transmision en H, aunque facilmente puede configurarse para cambio secuencial
// Por ejemplo: Primera, Segunda, Neutral, etc.
// >>*****Por el momento se conectara cada pin de un boton con una entrada del ESP-32 pero en el futuro se usara un multiplexor o algo similar
// Las tareas que se deben de ejecutar son:
//      *Seleccion de pines como entradas
//      *Lectura de Velocidad actual(Ejemplo: primera)


#include "Marchas.h"
#include "driver/gpio.h"
#include "esp_log.h"




const unsigned int PRIMERA=19;     /*Pines que corresponden con una marcha*/
const unsigned int SEGUNDA=18;
const unsigned int TERCERA=5;
const unsigned int CUARTA=17;
const unsigned int QUINTA=16;
const unsigned int SEXTA=4;



unsigned int Marchas[6]={PRIMERA,SEGUNDA,TERCERA,CUARTA,QUINTA,SEXTA};     //Matrix para iterar el numero de pin y añadirlo como entrada y leer su nivel
short int Velocidad=0;                                                     //Se almacena un numero que coincide con la marcha igual exeptuando neutral que equivale a "0"  


void IniciarPinesMarchas(unsigned int  Pines[6] ){                         //Se declaran los pines como salida
    
    for (int i = 0; i <=5 ; i++){
    gpio_set_direction(Pines[i],GPIO_MODE_INPUT);
    gpio_set_pull_mode(Pines[i],GPIO_PULLDOWN_ONLY);
    }
    
}
//La lectura se podría realizar con interrupciones
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
void LecturaMarcha(short int *VelocidadActual){                             //Se lee el nivel de cada pin si alguno se encuentra en alto lo guarda en la variable marcha
    unsigned char Marcha=0;

    for (unsigned int i = 0; i <=6 ; i++)
    {

        if (gpio_get_level(Marchas[i])==1){                                 //Si encuentra un pin en alto carga el index del pin, al valor de la marcha
            *VelocidadActual=Marcha+1;                                      //que se obtuvo usando un contador y se le suma 1 debido que C empieza a contar desde 0
            break;
    }   
    Marcha++;
    }
   if(*VelocidadActual>6){                                                  //si no se encuentra nungun pin en alto la variable marcha cuenta hasta 7,
    *VelocidadActual=0;                                                     //significando que no esta acoplada ninguna marcha lo que equivale a neutral
   } 
}

void ImprimirVelocidadActual(short int *VelocidadActual){
    char nombreVelocidad[7][10]={"Neutral","Primera","Segunda","Tercera","Cuarta","Quinta","Sexta"};
   printf("La marcha actual esta en %s con el numero %d\n",nombreVelocidad[*VelocidadActual],*VelocidadActual);

}