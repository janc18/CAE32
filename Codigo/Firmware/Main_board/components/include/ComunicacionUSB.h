struct TramaUSB{
int Acelerador;
int Freno;
int Clutch;
int Volante;
int CajaDeCambio;
int ErroresCAE32;
int Comandos;
};
extern struct TramaUSB *datos;

void UnionDeTrama(struct TramaUSB *USB,short int *Velocidad);

void EnvioDatosUSB(struct TramaUSB *USB);

void limpiartrama(struct TramaUSB *USB);