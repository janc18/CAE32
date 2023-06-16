#include "ComunicacionUSB.h"
#include <stdio.h>
#include "Encoders.h"
#include "esp_log.h"
struct TramaUSB USBdatos={
    .Acelerador=0,
    .Freno=0,
    .Clutch=0,
    .Volante=0,
    .CajaDeCambio=0,
    .ErroresCAE32=0,
    .Comandos=0
};
struct TramaUSB *datos=&USBdatos;
void UnionDeTrama(struct TramaUSB *USB,short int *Velocidad){
//Las primeras 4 partes provienen del valor mapeado de cada encoder
    USB->Acelerador=ptr_acelerador->ValorMapeado;
    USB->Freno=ptr_freno->ValorMapeado;
    USB->Clutch=ptr_clutch->ValorMapeado;
    USB->Volante=ptr_volante->ValorMapeado;
    USB->CajaDeCambio=*Velocidad;
    USB->ErroresCAE32=0;
    USB->Comandos=0;


}

void limpiartrama(struct TramaUSB *USB){
    
    USB->Acelerador=0;
    USB->Freno=0;
    USB->Clutch=0;
    USB->Volante=0;
    USB->CajaDeCambio=0;
    USB->ErroresCAE32=0;
    USB->Comandos=0;

}
void EnvioDatosUSB(struct TramaUSB *USB){
    ESP_LOGI("Datos USB","%d,%d,%d,%d,%d,%d,%d\n",USB->Acelerador,USB->Freno,USB->Clutch,USB->Volante,USB->CajaDeCambio,USB->ErroresCAE32,USB->Comandos);
    }   