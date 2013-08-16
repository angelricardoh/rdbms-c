///////////////lista.h/////////////////

struct nodo{
       char dato[50];
       struct nodo* sig;
       };
     
struct cabecera{
       struct nodo* I;
       int NE;
};

//apodos
typedef struct nodo NODO;
typedef struct cabecera CABECERA;
typedef NODO* n;
typedef CABECERA* lista;
typedef enum b{FALSE,TRUE} booleano;
typedef enum m{NO_MEMORY,OK,POS_INVALIDA} mensaje;

//Prototipos

mensaje crearlista(lista *L);
void limpiarlista(lista L);
void destruirlista(lista *L);
void copia(n D, NODO O);
mensaje agregar(lista L, NODO E, int p);
mensaje borrar(lista L, int p);
mensaje leer(lista L,n D, int p);
mensaje modificar(lista L,NODO E, int p);
booleano vacia(lista L);
void busqueda_impresion(lista L,char *c, int tipo);
