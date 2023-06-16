
/*Definición de pines de activacion de los encoders
 int PIN_ENABLE_ACELERADOR=12;
 int PIN_ENABLE_FRENO=14;
 int PIN_ENABLE_CLUTCH=26;
 int PIN_ENABLE_VOLANTE=27;
*/


struct Encoder
{
  int ResolucionBits;		  /*Valor necesario para obtener el valor mapeado */
  char TPedal[1];		      /*Variable para identificar el pedal, Ejemplo: A=Acelerador F=Freno, C=Clutch */
  int ValorBrutoADC;		  /*Aquí se almacena la lectura bruta del pin que */
  int ValorMapeado;		    /*Aquí se almacena el valor el cual se concatenara con la trama que se enviara al bus de datos USB */
  int Error;			        /*Se guarda el error para que sea verificado y reportado al kernel */
  int PinADC;			        /*Pin que se usa para la lectura analogica */
  int Giro;			          /*>>>>>ESTE VALOR SOLO SE USA EN EL VOLANTE, PARA INDENTIFICAR EN CUANTOS GIROS DE 360° SE HAN REALIZADO<<<<< */
  unsigned int ValorInicial[2];		    /*Estos valores deben guardarse en la EEPROM del ESP-32 para no tener que reprogramarlos cada vez que se encienden*/ 
  unsigned int ValorFinal[2];		      /*Valores para identificar el tope físico de cada pedal aka:Hardlock*/  
  int PinActivacion;	    /*Pin para activar y desactivar cada encoder para evitar choques en el bus ADC */
  int CanalADC;           /*El canal corresponde a un pin y se mostrara en la terminal al ejecutar InicializacionCanalADC*/
  int GradosDeGiro;       /*Corresponde a la configuración de los grados maximos de giro*/
  
};


extern struct Encoder *ptr_acelerador;
extern struct Encoder *ptr_freno;
extern struct Encoder *ptr_clutch;
extern struct Encoder *ptr_volante;

extern struct Encoder *matrix_ptr_encoders[4];

//<<<<<<<<<<<<<<<<<<<ADC>>>>>>>>>>>>>>>>>>>>
void imprimirValoresEncoder(struct Encoder *Pedal);     //Imprime toda la informacion de un encoder 
void IniciarAsignacionMemoriaEncoder();                        //Asigna memoria dinamica a cada estructura de cada pedal
void InicializacionCanalADC (struct Encoder *Pedal1);   //Carga valores de configuracion a los diferentes canales como resolucion y atenuacion 
void InicializacionPedalesVolante();                    //Carga la configuracion anterior a cada pedal 
//<<<<<<<<<<<<<<<<<<<ADC>>>>>>>>>>>>>>>>>>>>


//<<<<<<<<<<<<<<<<<<<GPIO>>>>>>>>>>>>>>>>>>>
void IniciarPinesActivacionEncoder();                                                        //Habilita los pines como salida provenietes de la estructura Encoder
void ActivarODesactivarEncoder(struct Encoder *Pedal,unsigned char estado); //Habilita o desabilita la comunicación con un encoder
void IniciarPinConfiguracion(); //Este pin tiene la utilidad de servir como boton de confirmación en diferentes procesos
void DireccionPines(struct Encoder *Pedal); 
//<<<<<<<<<<<<<<<<<<<GPIO>>>>>>>>>>>>>>>>>>>


//<<<<<<<<<<<<<<<<<<<i2c>>>>>>>>>>>>>>>>>>>>
int LeerEstadoAS5600 (struct Encoder *Pedal);               /*Lee los registros del encoder relacionados a la posición del imán y si exiten algun error lo reporta a la estructura error*/
void i2c_Master_Inicio();                                   //Inicia un puerto i2c como maestro
int CalibracionEncoder(struct Encoder *Pedal);             //Calibra el encoder, grabando los limites fisicos del pedal
void CalcularRangoMovimiento(struct Encoder *Pedal);
void CargaDePosiciones(struct Encoder *Pedal);
//<<<<<<<<<<<<<<<<<<<i2c>>>>>>>>>>>>>>>>>>>>





/*----------------------------Tareas a ejecutar constantemente--------------------------------*/
//<<<<<<<<<<<<<<<<<<<ADC>>>>>>>>>>>>>>>>>>>>
void LeerValorBrutoADC (struct Encoder *Pedal);             //Lee el voltaje de un que corresponde a la salida de un encoder
void CalcularValorMapeado(struct Encoder *Pedal);           //Calcula el valor que se debe enviar por usb, en base a la lectura del voltaje
//<<<<<<<<<<<<<<<<<<<ADC>>>>>>>>>>>>>>>>>>>>
/*---------------------------------------------------------------------------------------------*/
