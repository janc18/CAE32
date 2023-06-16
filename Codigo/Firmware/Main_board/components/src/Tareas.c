/*
*   Para ejecutar las diferentes tareas de una manera facil, rapida y eficiente se hara uso de las llamadas Tasks, proporcionadas por el sistema freertos
*   La manera de ejecucion sera la siguiente
*       *Lectura de valores analogicos y marcha
*       *Calculo de valor mapeado para que sea enviado por usb
*       *Union de todos los valores mapeados y marchas para ser enviados por usb
*       *Lectura de datos provenientes del pc
*
*
*/
#include "Encoders.h"

#include "freertos/FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "freertos/task.h"
#include "Marchas.h"
void vTareaLeerValorBruto(void *pvParameters){
   struct Encoder *pcm;
  //ES posible hacer aritmetica de puntero para iterar ? 
   pcm=(struct Encoder *)pvParameters;
   //pcm[0]=(struct Encoder *[0] ){pvParameters[0]};
   //pcm[1]=&(struct Encoder * [1]){pvParameters[1]};
//   pcm[2]=(struct Encoder * [2]){pvParameters[2]};
//   pcm[3]=(struct Encoder * [3]){pvParameters[3]};
   for(;;){

    vTaskDelay(10 / portTICK_PERIOD_MS);//Contraresta el debounce propio del boton
    LeerValorBrutoADC(pcm);
   }
   /* while (1){
        for(int i=0;i<=4;i++){ 
            LeerValorBrutoADC(pcm[i]);
        }
    }
    */
}

void vTareaLeerMarcha(void *pvParameters){
    short int *Velocidad;
    Velocidad=(short int *)pvParameters;
    for(;;){

    vTaskDelay(10 / portTICK_PERIOD_MS);//Contraresta el debounce propio del boton
    LecturaMarcha(&Velocidad);
    }
}
 void vTareaCalcularValor(void *pvParameters){
   struct Encoder *pcm;

   pcm=(struct Encoder *)pvParameters;
    for(;;){

    vTaskDelay(10 / portTICK_PERIOD_MS);//Contraresta el debounce propio del boton
    CalcularValorMapeado(pcm);
    }
 }