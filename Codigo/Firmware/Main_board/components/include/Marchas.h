
void IniciarPinesMarchas(unsigned int  Pines[6] );//Configura los pines de la transmision como entradas y pulldown

void ImprimirVelocidadActual(short int *VelocidadActal);//Imprime en que marcha se encuentra la transmision
/*----------------------------Tareas a ejecutar constantemente--------------------------------*/
void LecturaMarcha(short int *VelocidadActual);//Escanea todos los pines en busca del pin activo si no encuentra ninguno se considera la marcha neutral
/*---------------------------------------------------------------------------------------------*/
extern unsigned int Marchas[6];
extern short int Velocidad;
