///////////////lista.h/////////////////

struct nodoc{
       char atributo[50];
       int tipo;
       int longitud;
       char restriccion;
       int llave;
       struct nodoc* sig;
       };
     
struct cabecerac{
       struct nodoc* I;
       int NE;
};

//apodos
typedef struct nodoc NODOC;
typedef struct cabecerac CABECERAC;
typedef NODOC* nc;
typedef CABECERAC* listac;
typedef enum bn{FALSO,VERDADERO} booleanoc;
typedef enum mn{NO_MEMORIA,BIEN,NUM_INVALIDO} mensajec;

//Prototipos

mensajec crearlistac(listac *L);
void limpiarlistac(listac L);
void destruirlistac(listac *L);
void copiac(nc D, NODOC O);
mensajec agregarc(listac L, NODOC E, int p);
mensajec borrarc(listac L, int p);
mensajec leerc(listac L,nc D, int p);
mensajec modificarc(listac L,NODOC E, int p);
booleanoc vaciac(listac L);
void busqueda_impresionc(listac L,char *c, int tipo);
