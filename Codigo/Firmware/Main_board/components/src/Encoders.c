//**************Configuraciones para los encoders AS5600******************//
//  Este código tiene como objetivo realizar las configuraciones necesarias
//  para lograr utilizar los encoders y las tareas que deben de ejecutarse son
//      
//
//      * Inicialización de todos los pines para lecturas analogicas
//      * Configuracion del canal ADC de los pines
//      * Escritura y lectura de los encoders usando comunicación i2c
//      * Manejo de activación de cada encoder, esto por que el AS5600 no se puede cambiar su dirección
//***********************************************************************//
//  EL CÓDIGO SE ENCUENTRA SEPARADO EN 3 PARTES: ADC,GPIO Y COMUNICACIÓN I2C


/*======================================================================*/
//     _    ____   ____
//    / \  |  _ \ / ___|
//   / _ \ | | | | |    
//  / ___ \| |_| | |___ 
// /_/   \_\____/ \____|
/*======================================================================*/

//************************Uso********************//
//
//
//
//************************************************//


//************************Mantenimiento de errores*******//
//
//
//
//
//*******************************************************//

#include "Encoders.h"
#include "hal/adc_types.h"
#include "esp_adc/adc_oneshot.h"
#include "driver/i2c.h"
#include "esp_log.h"
#include <stdlib.h>


void CalcularValorMapeado(struct Encoder *Pedal);
/*<<<<<<<<<<<<<<<<<<<<Declaración de pedales>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
struct Encoder Freno={
    .ResolucionBits=255,
    .TPedal={'F'},
    .ValorBrutoADC=1,
    .ValorMapeado=0,
    .Error=0,
    .PinADC=0,
    .Giro=0,
    .ValorInicial={0,0},
    .ValorFinal={0,0},
    .PinActivacion=27,
    .CanalADC=7,
    .GradosDeGiro=1  
};


struct Encoder Acelerador={
    .ResolucionBits=255,
    .TPedal={'A'},
    .ValorBrutoADC=1,
    .ValorMapeado=0,
    .Error=0,
    .PinADC=0,
    .Giro=0,
    .ValorInicial={0,0},
    .ValorFinal={0,0},
    .PinActivacion=26,
    .CanalADC=6,
    .GradosDeGiro=1

};


struct Encoder Clutch={
    .ResolucionBits=255,
    .TPedal={'C'},
    .ValorBrutoADC=0,
    .ValorMapeado=0,
    .Error=0,
    .PinADC=0,
    .Giro=0,
    .ValorInicial={0,0},
    .ValorFinal={0,0},
    .PinActivacion=21,
    .CanalADC=5,
    .GradosDeGiro=1
};

struct Encoder Volante={
    .ResolucionBits=255,
    .TPedal={'V'},
    .ValorBrutoADC=0,
    .ValorMapeado=0,
    .Error=0,
    .PinADC=0,
    .Giro=0,
    .ValorInicial={0,0},
    .ValorFinal={0,0},
    .PinActivacion=14,
    .CanalADC=4,
    .GradosDeGiro=900 //Valor estandar para los volantes de entrada
};
//<<<<<<<<<<<<<<<<<<<<<<<<<<<------->>>>>>>>>>>>>>>>>>>>>>>>




/*<<<<<<<<<<<<<<<<<<<<Declaración de Pointers ADC y asignación de memoria>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
struct Encoder *ptr_volante;
struct Encoder *ptr_freno;
struct Encoder *ptr_acelerador;
struct Encoder *ptr_clutch;
struct Encoder *matrix_ptr_encoders[4];




void IniciarAsignacionMemoriaEncoder(){
ptr_volante=malloc(sizeof(struct Encoder));
ptr_volante=&Volante;
ptr_freno=malloc(sizeof(struct Encoder*));
ptr_freno=&Freno;
ptr_acelerador=malloc(sizeof(struct Encoder*));
ptr_acelerador=&Acelerador;
ptr_clutch=malloc(sizeof(struct Encoder*));
ptr_clutch=&Clutch;
matrix_ptr_encoders[0]=ptr_volante;
matrix_ptr_encoders[1]=ptr_freno;
matrix_ptr_encoders[2]=ptr_acelerador;
matrix_ptr_encoders[3]=ptr_clutch;
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<------->>>>>>>>>>>>>>>>>>>>>>>>


/*<<<<<<<<<<<<<<<<<<<<Declaración de handles ADC>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/

//-------------ADC1 Init---------------//
adc_oneshot_unit_init_cfg_t inicializacionConfig= {
    .unit_id = ADC_UNIT_1,
    };

adc_oneshot_unit_handle_t adc_handle_general=NULL;
adc_oneshot_chan_cfg_t configuracion ={
    .bitwidth=ADC_BITWIDTH_11, 
    .atten=ADC_ATTEN_DB_6,
};

//<<<<<<<<<<<<<<<<<<<<<<<<<<<------->>>>>>>>>>>>>>>>>>>>>>>>


void InicializacionCanalADC (struct Encoder *Pedal1){
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_handle_general,Pedal1->CanalADC,&configuracion));
    ESP_ERROR_CHECK(adc_oneshot_channel_to_io(inicializacionConfig.unit_id,Pedal1->CanalADC,&Pedal1->PinADC));
    }



void InicializacionPedalesVolante(){
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&inicializacionConfig, &adc_handle_general));
    for (int i=0; i<=3; i++){               //Ciclo para iniciar la configuracion del ADC a todos los canales (pines) 
        InicializacionCanalADC(matrix_ptr_encoders[i]);
        }
}
void LeerValorBrutoADC (struct Encoder *Pedal){ //En base del canal de la estructura, ejecuta una lectura y lo guarda en su estructura
    ESP_ERROR_CHECK(adc_oneshot_read(adc_handle_general,Pedal->CanalADC,&Pedal->ValorBrutoADC));
    //Cambiar por adc continuos read
}



void imprimirValoresEncoder(struct Encoder *Pedal){ //imprime todos las variables de una estructura dada con el proposito de hacer debuggin
    printf("------------------------\nPedal %s \n",Pedal->TPedal);
    printf("Valores iniciales | Lectura ADC:%d\t Valor Superior:%d|%d\t Valor Inicial:%d|%d\t Valor Mapeado:%d\t",Pedal->ValorBrutoADC,Pedal->ValorFinal[0],Pedal->ValorFinal[1],Pedal->ValorInicial[0],Pedal->ValorInicial[1],Pedal->ValorMapeado);
    printf("Grados:%d \n",Pedal->GradosDeGiro);
    printf("Canal %d y pin correspondiente %d\n------------------------\n",Pedal->CanalADC,Pedal->PinADC);
}

void CalcularValorMapeado(struct Encoder *Pedal){ //Carga el valor calculado a la estructura que servira para ser enviada por usb
    if (Pedal->ValorBrutoADC<=0||Pedal->ValorBrutoADC>=2047){
       // ESP_LOGE("[ERROR]","Valor fuera de rango\n");
    } 
    else{
    Pedal->ValorMapeado=((float)Pedal->ResolucionBits/2048.0)*Pedal->ValorBrutoADC;
    }
}


/*======================================================================*/
//     _    ___    ____ 
//    / \  |  _ \ / ___|
//   / _ \ | | | | |    
//  / ___ \| |_| | |___ 
// /_/   \_\____/ \____|
/*======================================================================*/



/*======================================================================*/
//   ____ ____ ___ ___      Para leer y calibrar el encoder se tiene que añadir una forma de desactivar los demas encoders, y esto secede por que todos  
//  / ___|  _ \_ _/ _ \     tienen la misma dirección i2c y no hay forma de cambiarlos
// | |  _| |_) | | | | |
// | |_| |  __/| | |_| |    El plan es tener un transistor que desconecte el scl de los demas encoders que no se esten programando
//  \____|_|  |___\___/     Los pines de activación se encuentran en el la estructura Encoder 
/*======================================================================*/


#include "driver/gpio.h"
const unsigned int PinBoton=13; //Pin para confirmar acciones

// Declaracion de configuracion de pines//
gpio_config_t configuracionPines={
    .mode= GPIO_MODE_OUTPUT,
    .pull_up_en=GPIO_PULLUP_DISABLE,
    .pull_down_en=GPIO_PULLDOWN_ENABLE,
    .intr_type=GPIO_INTR_DISABLE
};

//-------------------------------------//

void DireccionPines(struct Encoder *Pedal){ //Declara los pines de activacion correspondientes de cada encoder como salida
    ESP_ERROR_CHECK(gpio_set_direction(Pedal->PinActivacion,configuracionPines.mode));
}

void IniciarPinesActivacionEncoder(){                        //Ciclo for para seleccionar los pines que se usaran como salida
    for (int i =0; i<=3; i++){               
        DireccionPines(matrix_ptr_encoders[i]);
    }
}

void ActivarODesactivarEncoder(struct Encoder *Pedal,uint8_t estado){ //Habilita o desabilita la comunicación con un encoder
  int matrixPines[4];
    for (int i =0; i<=3; i++){               
        matrixPines[i]=matrix_ptr_encoders[i]->PinActivacion; //Carga el numero de pin de cada encoder a la matrixPines
    }
    
  if (estado==1){ //Activar el transistor en todos los demas para evitar que no choque el bus, menos en el que se esta calibrando
    for(int i=0;i<=3;i++){
        if(matrixPines[i]==Pedal->PinActivacion){ 
            gpio_set_level(matrixPines[i],0);
        }
        else{
            gpio_set_level(matrixPines[i],1);
        }
    }
    }
    else{//Desactiva el transistor en todos los pines
    
    for (int i =0; i<=3; i++){               
    gpio_set_level(matrixPines[i],1);
    }
    }
}

void IniciarPinConfiguracion(){ //Este pin tiene la utilidad de servir como boton de confirmación en diferentes procesos
    ESP_ERROR_CHECK(gpio_set_direction(PinBoton,GPIO_MODE_INPUT));
    gpio_set_pull_mode(PinBoton,GPIO_PULLDOWN_ONLY);
}

/*======================================================================*/
//   ____ ____ ___ ___  
/*  / ___|  _ \_ _/ _ \  */
// | |  _| |_) | | | | |
// | |_| |  __/| | |_| |
//  \____|_|  |___\___/ 
/*======================================================================*/



/*======================================================================*/
//  _ ____      
// (_)___ \ ___ 
// | | __) / __|
// | |/ __/ (__ 
// |_|_____\___|
/*======================================================================*/
#include "driver/i2c.h"

//Tomado del ejemplo de ESP-IDF de comunicación i2c
//https://github.com/espressif/esp-idf/blob/master/examples/peripherals/i2c/i2c_simple/main/i2c_simple_main.c

const int I2C_MASTER_SCL_IO=22;                         /*!< GPIO number used for I2C master clock */
const int I2C_MASTER_SDA_IO=21;                         /*!< GPIO number used for I2C master data  */
const int I2C_MASTER_NUM=0;                          /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
const int I2C_MASTER_FREQ_HZ=400000;                     /*!< I2C master clock frequency */
const int I2C_MASTER_TX_BUF_DISABLE=0;                          /*!< I2C master doesn't need buffer */
const int I2C_MASTER_RX_BUF_DISABLE=0;                          /*!< I2C master doesn't need buffer */
const int I2C_MASTER_TIMEOUT_MS=1000;

esp_err_t i2c_Master_Init(void)
{
    int i2c_master_port = I2C_MASTER_NUM;

    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };

    i2c_param_config(i2c_master_port, &conf);

    return i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}


void i2c_Master_Inicio(){
    i2c_Master_Init();
}

esp_err_t i2c_lectura(uint8_t slave_addr, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
    //desarrollar una funcion varidica para meterle como parametros todos los registros que quiera leer 
     esp_err_t ret;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (slave_addr<<1), 1);
    i2c_master_write_byte(cmd, reg_addr, 1);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
    if (ret != ESP_OK) {
        return ret;
    }
    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (slave_addr<<1)|1, 1);
    i2c_master_read(cmd, data, len,  I2C_MASTER_LAST_NACK);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}

void i2c_escritura(uint8_t addr,uint8_t reg_addr,uint8_t data){
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd,(addr<<1),0x0);
    i2c_master_write(cmd,&reg_addr,1,0x0);
    i2c_master_write(cmd,&data,1,0x0);
    i2c_master_stop(cmd); 
    i2c_master_cmd_begin(I2C_MASTER_NUM,cmd,I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
}



/*Registros relacionados a la configuracion y estado del encoder*/
const uint8_t ADDR=0x36;
const uint8_t CONF_REG=0x08;
const uint8_t RAW_ANGLE_L=0x0C;
const uint8_t RAW_ANGLE_M=0x0D;
const uint8_t ZPOS_L=0x01;
const uint8_t ZPOS_M=0x02;
const uint8_t MANG_L=0x05;
const uint8_t MANG_M=0x06;
const uint8_t MPOS_L=0x03;
const uint8_t MPOS_M=0x04;
const uint8_t STATUSENCODER=0x0B;
/*---------------------------------------------------------------*/



//Para leer el valor del estado del encoder aka AS5600 es nesesario usar la comunicación i2c
int LeerEstadoAS5600 (struct Encoder *Pedal){
const char Estado[3][30]={"No se detecto imán","Imán demasiado cerca","Imán demasiado lejos"};//Mensajes que se muestran cuando existe algun error
unsigned char valorRegistro;

i2c_lectura(ADDR,STATUSENCODER,&valorRegistro,1); //Se lee el registro que contiene el status del encoder y se guarda en la variable valorRegistro
valorRegistro=valorRegistro<<2; //Se hace una manipulación de bits para solo evaluar los bits que nos interesan representados con (-) ejemplo (0b**---***) 
valorRegistro=valorRegistro>>5;

switch (valorRegistro) // Se compara el valorRegistro con el valor mostrado en la hoja de datos 
{
case 0b000:     
    ESP_LOGE("[ERROR]","%s \n",Estado[0]);
    return -1;
    break;
case 0b100: 
    ESP_LOGE("[ERROR]","%s \n",Estado[1]);
    return -2;
    break;
case 0b010:
    ESP_LOGE("[ERROR]","%s \n",Estado[2]);
    return -3;
    break;

default:
    ESP_LOGI("[OK]","%s, Imán correctamente posicionado\n",Pedal->TPedal);
    return 0;
    break;
}


}


void CalcularRangoMovimiento(struct Encoder *Pedal){ //Calcula cuantos grados de movimento tiene un pedal 0°-360° y >360, tambien depende del sentido en el que se gira se puede configurar con el pin <DIR> del encoder
    int Grados[2];
    Grados[0]=Pedal->ValorFinal[0]-Pedal->ValorInicial[0];//149-82
    Grados[1]=Pedal->ValorFinal[1]-Pedal->ValorInicial[1];//13-6
    Grados[1]=Grados[1]*24;//*********************Es necesario cambiar esta formula por que trunca los datos**************************
    Grados[0]=Grados[0]/24;//*********************************************************************************************************
    
    Pedal->GradosDeGiro=Grados[0]+Grados[1];
    i2c_escritura(ADDR,ZPOS_L,Pedal->ValorFinal[1]);
    i2c_escritura(ADDR,ZPOS_M,Pedal->ValorFinal[0]);
    i2c_escritura(ADDR,MPOS_L,Pedal->ValorInicial[1]);
    i2c_escritura(ADDR,MPOS_M,Pedal->ValorInicial[0]);
    i2c_escritura(ADDR,MANG_L,Grados[1]);
    i2c_escritura(ADDR,MANG_M,Grados[0]);
    

}


void CargaDePosiciones(struct Encoder *Pedal){
//Carga los valores finales e iniciales del encoder estos se encuentran en la estructura ValorFinal y ValorInicial
//******************************IMPORTANTE***************************************************************************************************************//
//Los Valores que son leidos en la funcion CalibracionEncoder se incrementan o decrementan dependiendo del pin DIR del Encoder
//Ya que si esta conectado a GND aumentaran los valores cuando gire en el sentido horario, y si esta en VCC este aumenta cuando gire en sentido antihorario
//Así que este puede ser un problema al momento de calcular el rango de moviento 
//*******************************************************************************************************************************************************//
    
    i2c_escritura(ADDR,ZPOS_L,Pedal->ValorFinal[1]);
    i2c_escritura(ADDR,ZPOS_M,Pedal->ValorFinal[0]);
    i2c_escritura(ADDR,MPOS_L,Pedal->ValorInicial[1]);
    i2c_escritura(ADDR,MPOS_M,Pedal->ValorInicial[0]);


}

int CalibracionEncoder(struct Encoder *Pedal){ //Con esta funcion se calibran los topes fisícos de cada Encoder exeptuando el Volante
    ESP_LOGI("I","Intentando calibrar el encoder identificado como %s\n",Pedal->TPedal);
    
    //Primero hay que comprobar el estado del encoder, ya que es necesario que este tenga el íman colocado, si no se encuentra no tiene sentido continuar con la calibracion
    if (LeerEstadoAS5600(Pedal)<0){
        ESP_LOGE("ERROR","No se logro calibrar el encoder, por un error en la posicion del imán\n");
        return -1;
    }
    //----------------------------------------------------------------------------

    //Se capturan los datos del encoder en la posicion inicial y final para despues configurar el maximo angulo de acción en el encoder y aprobechar la maxima resolución

    ESP_LOGI("I","Presiona o mueve el pedal hasta la posicion final (a fondo) y presiona el Botón de configuración\n");

do
{
    
    vTaskDelay(10 / portTICK_PERIOD_MS);//Necesario si no se crashea el ESP32 sera remplazado por una interrupcion o otro algoritmo
            i2c_lectura(ADDR,RAW_ANGLE_M,&Pedal->ValorFinal[0],1);
            i2c_lectura(ADDR,RAW_ANGLE_L,&Pedal->ValorFinal[1],1);

} while (gpio_get_level(PinBoton)==0);

    vTaskDelay(500 / portTICK_PERIOD_MS);//Contraresta el debounce propio del boton

    ESP_LOGI("I","Suelta o mueve el pedal hasta la posicion inicial (en reposo) y presiona el Botón de configuración\n");
do
{
    
    vTaskDelay(10 / portTICK_PERIOD_MS);//Necesario si no se crashea el ESP32 sera remplazado por una interrupcion o otro algoritmo
            i2c_lectura(ADDR,RAW_ANGLE_M,&Pedal->ValorInicial[0],1);//2
            i2c_lectura(ADDR,RAW_ANGLE_L,&Pedal->ValorInicial[1],1);//240

} while (gpio_get_level(PinBoton)==0);
    //------------------------------------------------------------------------------
    //*****************Importante****************************************************
    //Es necesario grabar estos valores recien capturados en la eemprom o nvm para que no sea necesario calibrar cada vez que se inicia 
    //
    //----------------------------------------------------------------------------
    CalcularRangoMovimiento(Pedal); //Calcula cuantos grados de movimento tiene un pedal 0°-360° y >360, tambien depende del sentido en el que se gira se puede configurar con el pin <DIR> del encoder
    imprimirValoresEncoder(Pedal);
    return 0;

}

 
