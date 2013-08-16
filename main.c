#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lista.h"
#include "listac.h"

#define KEY_UP 72//define codigo ASCII de tecla especial
#define KEY_LEFT 75//define codigo ASCII de tecla especial
#define KEY_RIGHT 77//define codigo ASCII de tecla especial
#define KEY_DOWN 80//define codigo ASCII de tecla especial
#define ESCAPE 27//define codigo ASCII de tecla especial
#define BACKSPACE 8//define codigo ASCII de tecla especial
#define ENTER 13 //define codigo ASCII de tecla especial
#define SPACE 32//define codigo ASCII de tecla especial

int start(void);//inicia la pantalla principal
int pantalla_administrador(void);//ejecuta el menu del administrador
void ejecutar_administrador(int opcionad);//ejecuta accion del administrador
int pantalla_usuario(void);//ejecuta el menu del usuario
void ejecutar_usuario(int opcionus);//ejecuta accion del usuario
int obtenerbasededatos(int permiso);//obtiene la base de datos almacenada
int obtenercampos(void);//obtiene los campos del fichero metadatos
int obtenerdatos(void);//obtiene la informacion del fichero almacen
int guardarcampos(void);//guarda los campos en el fichero metadatos
int guardardatos(void);//guarda la informacion en el fichero almacen
int buscaesquema(char *nomesquema);
int agregar_registro();
void modificar_registro();
void procesa_consultas();
int algoritmo_seleccion(char * condicion, char * esquema);
int algoritmo_proyeccion(char * atributos, char * esquema);
int algoritmo_planocartesiano(char * esquema1, char * esquema2);
int algoritmo_union(char * esquema1, char * esquema2);
int algoritmo_diferencia(char * esquema1, char * esquema2);
int algoritmo_equijoin(char * esquema1, char * esquema2, char * esquema3);

int numcampos=0;//numero de campos totales
int numregistros=0;//numero de registros totales
int numesquemas=0;
int numconsulta=1;
char esquema[100];

lista datos[100];//lista que almacena la informacion del archivo almacen
//empieza desde datos[1]
listac campos;//lista dinamica que almacena los campos del archivo metadatos
lista esquemas;// lista que almacena los esquemas

struct bloque{
       char clave[50];
       lista sigu;
};

int main(int argc, char *argv[])
{
    
    
       NODO A;
       
       int i;//variable contador
       int modo;//variable que escoge modo administrador o usuario
       int opcionad;//variable para la opcion del menu administrador
       int opcionus;//variable para la opcion del menu usuario
       char regresar;//variable que regresa al menu anterior
       char archivodatos[100];
       char archivometadatos[100];
       crearlista(&esquemas);
       crearlistac(&campos);
       for(i=1; i<=20; i++)
             crearlista(&datos[i]);
       
       for(;;){
             modo=start();//muestra el menu principal para escoger entre modo usuario y
             //modo administrador
             switch(modo){
                   case 1://modo administrador
                   do{
                          opcionad=pantalla_administrador();
                          if(opcionad==10)
                                break;
                          ejecutar_administrador(opcionad);
                          printf("\n\tDesea regresar al menu anterior? (s\\n): \n");
                          fflush(stdin);
                          scanf("%c", &regresar);
                          fflush(stdin);
                                if((((tolower(regresar))!='s')&&(tolower(regresar))!='n')){
                                do{
                                   printf("\nTecla incorrecta\n");
                                   printf("\n\tDesea regresar al menu anterior? (s\\n): \n");
                                   scanf("%c", &regresar);
                                   fflush(stdin);
                                }while((tolower(regresar)!='s')&&(tolower(regresar)!='n'));
                         }
                         fflush(stdin);
                   }while(tolower(regresar)=='s');
                   if(tolower(regresar)=='n')
                         return 1;
                   break;
                    
                   case 2://modo usuario
                   do{
                         opcionad=pantalla_usuario();
                         if(opcionad==5)
                               break;
                         ejecutar_usuario(opcionad);
                         printf("\n\tDesea regresar al menu anterior? (s\\n): \n");
                         fflush(stdin);
                         scanf("%c", &regresar);
                         fflush(stdin);
                         if((((tolower(regresar))!='s')&&(tolower(regresar))!='n')){
                             do{
                                 printf("\nTecla incorrecta\n");
                                 printf("\n\tDesea regresar al menu anterior? (s\\n): \n");
                                 scanf("%c", &regresar);
                                 fflush(stdin);
                         }while((tolower(regresar)!='s')&&(tolower(regresar)!='n'));
                         }
                         fflush(stdin);
                    }while(tolower(regresar)=='s');
                    if(tolower(regresar)=='n')
                         return 2;
                    break;
                    
               case 3:// consultas
                    procesa_consultas();     
                    break;
               
               case 4:// salir
                    return 4;
                    break;
               
               default:
                    printf("Opcion incorrecta\n");
                    break;
                    
                    return 1;
             }      
       }
       gotoxy(10,24);
       
       system("PAUSE");	
       return 0;
}

int start(void){
        int opcion = 1;
        int x = 17;
        int y = 13;
        char c;
        system("cls");
        printf("*******************************************************\n");
        printf("*                                                     *\n");
        printf("*              Sistema de Base de datos               *\n");
        printf("*                                                     *\n");
        printf("*                                                     *\n");
        printf("*                                                     *\n");
        printf("*                  Base de datos II                   *\n");
        printf("*                                                     *\n");
        printf("*                                                     *\n");
        printf("*                       Menu                          *\n");
        printf("*                                                     *\n");
        printf("*                                                     *\n");
        printf("*                 Administrador                       *\n");
        printf("*                 Usuario                             *\n");
        printf("*                 Realizar consulta                   *\n");
        printf("*                 Salir                               *\n");
        printf("*                                                     *\n");
        printf("*                                                     *\n");
        printf("*******************************************************\n");
        printf("Eliga una de las siguientes opciones con las teclas de direccionamiento\n");
        printf("Pulse enter para escoger seleccion\n");
        gotoxy(x,y);
        printf("%c", 26);
        do{
        c=getch();
        if(c==-32){
            c=getch();
            if(c==KEY_UP){
                 if(opcion!=1){
                      opcion--;
                      gotoxy(x,y);
                      printf(" ");
                      y--;
                      gotoxy(x,y);
                      printf("%c", 26);
                 }
            }
            else if(c==KEY_DOWN){
                 if(opcion!=4){
                      opcion++;
                      gotoxy(x,y);
                      printf(" ");
                      y++;
                      gotoxy(x,y);
                      printf("%c", 26);
                 }
            }
        }
        }while(c!=ENTER);
        return opcion;
}

int pantalla_administrador(void){
     int opcion = 1;
     int x = 16;
     int y = 10;
     char c;
     system("cls");
     obtenerbasededatos(1);
     system("cls");
     printf("*******************************************************\n");
     printf("*                                                     *\n");
     printf("*              Sistema de Base de datos               *\n");
     printf("*                                                     *\n");
     printf("*                                                     *\n");
     printf("*               Modo administrador                    *\n");
     printf("*                                                     *\n");
     printf("*                     Menu                            *\n");
     printf("*                                                     *\n");
     printf("*                 Anadir esquema                      *\n");
     printf("*                 Cambiar esquema                     *\n");
     printf("*                 Ver campos                          *\n");
     printf("*                 Agregar campo                       *\n");
     printf("*                 Borrar campo                        *\n");
     printf("*                 Ver registros                       *\n");
     printf("*                 Agregar registro                    *\n");
     printf("*                 Borrar registro                     *\n");
     printf("*                 Modificar registro                  *\n");
     printf("*                 Regresar al menu anterior           *\n");
     printf("*                                                     *\n");    
     printf("*******************************************************\n");
     printf("Eliga una de las siguientes opciones con las teclas de direccionamiento\n");
     printf("Pulse enter para escoger seleccion\n");
     gotoxy(x,y);
     printf("%c", 26);
     do{
        c=getch();
        if(c==-32){
            c=getch();
            if(c==KEY_UP){
                 if(opcion!=1){
                      opcion--;
                      gotoxy(x,y);
                      printf(" ");
                      y--;
                      gotoxy(x,y);
                      printf("%c", 26);
                 }
            }
            else if(c==KEY_DOWN){
                 if(opcion!=10){
                      opcion++;
                      gotoxy(x,y);
                      printf(" ");
                      y++;
                      gotoxy(x,y);
                      printf("%c", 26);
                 }
            }
        }
        }while(c!=ENTER);
        return opcion;
}

void ejecutar_administrador(int opcionad){
      NODOC E;
      NODO F;
      NODO A;
      int i, j;
      char nomcampo[50]; // variable auxiliar para el nombre del campo
      int numerocampo;  // contador de atributos
      int numeroregistro; // contador de registros
      int encontrado=0; // se encuentra el esquema de relacion
      int datovalido=1;
      int agregarregistros=0;
      FILE * pf;
      char met[30]; // nuevo archivo de metadatos
      char dat[30]; // nuevo archivo de datos
      system("cls");
      switch(opcionad){
           case 1://opcion de añadir esquema                
               
                numesquemas++;
                printf("Digite el nombre del esquema a agregar\n");
                gets(nomcampo);
                strcpy(A.dato,nomcampo);
                fflush(stdin);
                strcpy(met, nomcampo);
                strcpy(dat, nomcampo);
                strcat(met, "m.txt");
                strcat(dat, ".txt");
                pf = fopen(met, "w");
                fclose(pf);
                pf = fopen(dat, "w");
                fclose(pf);
                agregar(esquemas, A, numesquemas);
                guardaresquemas();
                break;
           case 2://opcion de cambiar esquema
                printf("Digite el nombre del esquema a agregar\n");
                gets(nomcampo);
                encontrado = buscaesquema(nomcampo);
                if(encontrado){
                     printf("Si Cambiando esquema a %s\n", nomcampo);
                     strcpy(esquema,nomcampo);
                     limpiarlistac(campos);
                     for(j=0; j<numregistros; j++)
                            limpiarlista(datos[i]);
                     numcampos=0;
                     numregistros=0;
                     obtenercampos();
                     obtenerdatos();
                }
                else
                     printf("No se encuentra el esquema proporcionado\n");
                     printf("%s", esquema);
                break;
           case 3://opcion de ver campos actuales
                printf(" -----------------------------------------------\n");
                printf("                  %s                            \n", esquema);
                printf(" -----------------------------------------------\n");
                printf("Los campos actuales son:\n");
                for(i=1; i<=numcampos; i++){
                     NODOC E;
                     leerc(campos, &E, i);
                     printf("%d. %s\n", i, E.atributo);
                }
                break;
                
           case 4://opcion de agregar campo
                printf("\n\n\tNombre del nuevo campo: \n\n\t");
                printf("\n\n\tUse solamente caracteres alfanumericos [a-z] [A-Z] [0-9]\n\n\t");
                fflush(stdin);
                gets(nomcampo);
                datovalido = 1;
                for(i=0; i<strlen(nomcampo); i++)
                {
                       if((nomcampo[i]>='0' && nomcampo[i]<='9')|| (nomcampo[i]>='a' && nomcampo[i]<='z')
                            || (nomcampo[i]>='A' && nomcampo[i]<='Z'))
                       {
                            datovalido = 1;
                       }
                       
                       else
                       {
                            datovalido = 0;
                            break;
                       }
                }
                while(!datovalido)
                {
                     printf("\n\n\tNombre no valido\n\n\t");
                     printf("\n\n\tNombre del nuevo campo: \n\n\t");
                     printf("\n\n\tUse solamente caracteres alfanumericos [a-z] [A-Z] [0-9]\n\n\t");
                     fflush(stdin);
                     gets(nomcampo);
                     while(strcmp(nomcampo,"\n")==0)
                     {
                          printf("No tecleo ningun dato\n");
                          printf("Vuelva a escribir\n");
                          fflush(stdin);
                          gets(nomcampo);
                     }
                     for(i=0; i<strlen(nomcampo); i++)
                     {
                       if((nomcampo[i]>='0' && nomcampo[i]<='9')|| (nomcampo[i]>='a' && nomcampo[i]<='z')
                            || (nomcampo[i]>='A' && nomcampo[i]<='Z'))
                       {
                           datovalido = 1;
                       }
                       
                       else
                       {
                            datovalido = 0;
                            break;
                       }
                     }
                }
                numcampos++;
                strcpy(E.atributo,nomcampo);
                printf("\tDigite el tipo de campo: \n");
                printf("\t1. int\n");
                printf("\t2. float\n");
                printf("\t3. char\n");
                printf("\t4. string\n");
                scanf("%d", &E.tipo);
                while(E.tipo < 1 || E.tipo > 5)
                {
                     printf("Tipo incorrecto\n");
                     printf("\tDigite el tipo de campo: \n");
                     printf("1. int\n");
                     printf("2. float\n");
                     printf("3. char\n");
                     printf("4. string\n");
                     fflush(stdin);
                     scanf("%d", &E.tipo);
                }
                if(E.tipo!=3)
                {              
                     printf("\tDigite la longitud\n");
                     scanf("%d", &E.longitud);
                     while(E.longitud <= 0 || E.longitud >= 200)
                     {
                           printf("\tNo pueden haber longitudes negativas\n");
                           printf("\tDigite la longitud\n");
                           fflush(stdin);
                           scanf("%d", &E.longitud);
                     }
                }
                else
                {
                     E.longitud=1;
                }
                     printf("\tDigite el tipo de restricción");
                
                {
                     int key;
                     printf("\tEs llave primaria?\n");
                     printf("\t1. Si\n");
                     printf("\t2. No\n");
                     scanf("%d", &key);
                     while(key < 1 || key > 2)
                     {
                          printf("\tOpcion incorrecta\n");
                          printf("\t1. Si\n");
                          printf("\t2. No\n");
                          fflush(stdin);
                          scanf("%d", &key);
                     }
                     if(key == 1)
                          E.llave = 1;
                     else
                          E.llave = 0;     
                }
                if(E.llave == 1)
                {
                     E.restriccion = 'T';
                }
                else
                { // bloque para insertar restriccion
                     int restriccion;
                     printf("\tTipo de restriccion");
                     printf("\t1.NULL\n");
                     printf("\t2.NOT NULL\n");
                     scanf("%d", &restriccion);
                     while(restriccion < 1 || restriccion > 2)
                     {
                          printf("\tOpcion incorrecta\n");
                          printf("\t1.NULL\n");
                          printf("\t2.NOT NULL\n");
                          fflush(stdin);
                          scanf("%d", &restriccion);
                     }
                     if(restriccion == 1)
                          E.restriccion = 'N';
                     else
                          E.restriccion = 'T'; 
                }
                agregarc(campos,E,numcampos);
                printf("%d\n", numcampos);
                fflush(stdin);
                for(i=1; i<=numregistros; i++){
                     NODO F;
                     strcpy(F.dato,"Vacio");
                     agregar(datos[numcampos],F,i);
                }
                printf("\n\t...Campo agregado...\n");
                if(E.restriccion == 'T')
                {
                    printf("Se introdujo un campo con restricción NOT NULL\n");
                    printf("Se debe llenar el campo de los registros:\n");
                    for(i=1; i<=numregistros; i++){
                        NODO A;
                        printf("No. de registro: %d", i);
                        printf("\n");
                        for(j=1; j<numcampos; j++){
                            NODOC E;
                            NODO F;
                            leerc(campos,&E, j);
                            leer(datos[j], &F, i);
                            printf("%s: %s",E.atributo,F.dato);
                            printf("\n");
                        }
                        printf("%s: ", E.atributo);
                        scanf("%s", A.dato);
                        agregar(datos[j], A, i); 
                        printf("\n\n");
                     }
                }
                guardarcampos();
                guardardatos();
                break;
                
           case 5://opcion de borrar campo
                if(numcampos>0){
                     printf("Los campos actuales son:\n");
                     for(i=1; i<=numcampos; i++){
                           leerc(campos,&E,i);
                           printf("%d. %s\n",i,E.atributo);
                     }
                     printf("\n\tDigite el numero de campo a borrar: ");
                     scanf("%d",&numerocampo);
                  
                     printf("\n\t...Campo borrado...\n");
                     borrarc(campos,numerocampo);
                
                     fflush(stdin);
                     numcampos--;
                     for(i=numerocampo; i<=numcampos; i++)
                           datos[i]=datos[i+1];
                     guardarcampos();
                     guardardatos();
                     }
                else{
                     printf("No hay campos para borrar\n");
                }
                break;
                
           case 6://opcion de visualizar todos los registros
                printf(" -----------------------------------------------\n");
                printf("                  %s                            \n", esquema);
                printf(" -----------------------------------------------\n");
                printf("Se presentan todos los registros almacenados\n\n");
                for(i=1; i<=numregistros; i++){
                      printf("No. de registro: %d", i);
                      printf("\n");
                      for(j=1; j<=numcampos; j++){
                            NODOC E;
                            NODO F;
                            leerc(campos,&E, j);
                            leer(datos[j], &F, i);
                            printf("%s: %s",E.atributo,F.dato);
                            printf("\n");
                      }
                      printf("\n");
                }
                break;
           
           case 7://opcion de agregar registro
                printf("Digite el numero de registros a agregar MAX[200]:\n");
                scanf("%d", &agregarregistros);
                while(agregarregistros <= 0)
                {
                     printf("Numero erroneo\n");
                     printf("Digite el numero de registros a agregar MAX[200]:\n");
                     scanf("%d", &agregarregistros);
                }
                for(i=0; i<=agregarregistros; i++)
                {
                     printf("Se agregara el registro No. %d", numregistros+1);
                     if(agregar_registro() == 1)
                          printf("\n\t...Registro no agregado");
                     else
                          printf("\n\t...Registro agregado\n");
                }
                guardardatos();
                break;
                
           case 8://opcion de borrar un registro
                printf("Se presentan todos los registros almacenados\n\n");
                for(i=1; i<=numregistros; i++){
                      printf("No. de registro: %d", i);
                      printf("\n");
                      for(j=1; j<=numcampos; j++){
                            leerc(campos,&E, j);
                            leer(datos[j], &F, i);
                            printf("%s: %s",E.atributo,F.dato);
                            printf("\n");
                      }
                      printf("\n");
                }
                
                if(numregistros>0){
                     printf("\n\tPor favor digite el numero de registro a borrar: ");
                     scanf("%d", &numeroregistro);
                     for(i=1; i<=numcampos; i++){
                          NODO A,B;
                          borrar(datos[i], numeroregistro);
                     }
                     numregistros--;
                     guardardatos();
                     printf("\n\t...Registro borrado...\n");
                }
                else{
                     printf("No hay registros para borrar\n");
                }
                break;
                
           case 9://opcion de modificar un registro
                modificar_registro();
                break;
                
                default:
                     printf("Opcion incorrecta");
           }
           
           
}

int obteneresquemas(){
        FILE *pf;
        char c;
        NODO E;
        pf=fopen("esquemas.txt","r");
        if(pf==NULL)
        {
               printf("Error al abrir el archivo\n");
               return 1;
        }
        c=getc(pf);
        if(feof(pf))
             return 1;
        fseek(pf,0,0);
        while(!feof(pf)){
                         int i=0;
                         c = getc(pf);
                         while((c!='\\')&&(!(feof(pf)))){
                         E.dato[i]=c;
                         i++;
                         c=getc(pf);
                         }
                         E.dato[i]='\0';
                         numesquemas++;
                         agregar(esquemas,E,numesquemas);
        }
        fclose(pf);
}

int obtenercampos(){
        FILE *pf;
        char c;
        NODOC E;
        char nombre[100];
        int z=0;
        strcpy(nombre,esquema);
        strcat(nombre,"m.txt");
        pf=fopen(nombre,"r");
        if(pf==NULL)
        {
                printf("Error al abrir el archivo\n");
                return(1);
        }
        c=getc(pf);
        if(feof(pf))
            return 1;
        fseek(pf,0,0);
        while(!feof(pf)){
                        c=getc(pf);
                        int i=0;
                        char longitud[10];
                        while(c!='\\'){
                        E.atributo[i]=c;
                        i++;
                        c=getc(pf);
                        }
                        E.atributo[i]='\0';
                        E.atributo[i]='\0';
                             c=getc(pf);
                             E.tipo = (int)c;
                             E.tipo -= 48;
                             c=getc(pf); // lee '\'
                             while((longitud[z] = getc(pf))!='\\')
                                z++;
                             longitud[z]='\0';
                             E.longitud = atoi(longitud);
                             z=0; // reinicia la cadena longitud
                             strcpy(longitud,"");
                             c=getc(pf); // lee restriccion
                             E.restriccion = c;
                             c=getc(pf); // lee '\'
                             c=getc(pf);
                             if(c=='*')
                                    E.llave = 1;
                             else
                                    E.llave = 0; 
                        numcampos++;
                        agregarc(campos,E,numcampos);
                        c=getc(pf);
        }
        fclose(pf);
        //free(nombre);
}

int obtenerdatos(){
        FILE *pf;
        char c;
        int j;
        char nombre[100];
        strcpy(nombre,esquema);
        strcat(nombre,".txt");
        pf=fopen(nombre,"r");
       
        if(pf==NULL)
        {
                printf("Error al abrir el archivo\n");
                return(1);
        }
        c=getc(pf);
        if(feof(pf))
             return 1;
        fseek(pf,0,0);
        while(!feof(pf)){ 
                        for(j=1; j<=numcampos; j++){ 
                             c=getc(pf);
                             NODO F;
                             int i=0; 
                             while((c!='\\')&&(!feof(pf))&&(c!='\n')){
                                 F.dato[i]=c;
                                 i++;
                                 c=getc(pf);
                               
                             }
                             F.dato[i]='\0';
                             agregar(datos[j], F, numregistros+1);
                             if(feof(pf))
                                 break;
                        }
                        numregistros++;
        }
        fclose(pf);
        //free(nombre);
}

int guardaresquemas(void){
    NODO T;
    FILE *pf;
    char c;
    int i, j;
    pf=fopen("esquemas.txt","w");
    if(pf==NULL)
    {
        printf("Error al abrir el archivo\n");
        return(1);
    }
    for(i=1; i<=numesquemas; i++){
        leer(esquemas, &T, i);
        fprintf(pf,T.dato);
        if(i!=numesquemas)
             fprintf(pf,"\\");
    }
        fclose(pf);
        //free(nombre);   
}

int guardarcampos(void){
    NODOC T;
    FILE *pf;
    char c;
    int i, j;
    char nombre[100];
    char cadena[100];
    strcpy(nombre,esquema);
    strcat(nombre,"m.txt");
    pf=fopen(nombre,"w");
    if(pf==NULL)
    {
        printf("Error al abrir el archivo\n");
        return(1);
    }
    for(i=1; i<=numcampos; i++){
        leerc(campos, &T, i);
        fprintf(pf,T.atributo);
        fprintf(pf,"\\");
        itoa(T.tipo, cadena, 10);
        fprintf(pf,cadena);
        fprintf(pf,"\\");
        itoa(T.longitud, cadena, 10);
        fprintf(pf,cadena);
        fprintf(pf,"\\");
        fprintf(pf,"%c", T.restriccion);
        fprintf(pf,"\\");
        if(T.llave)
              fprintf(pf,"*");
        else
              fprintf(pf,"-");
        if(i!=numcampos)
              fprintf(pf, "\n");
    }
        fclose(pf);
        //free(nombre);
}

int guardardatos(void){
    NODO P;
    FILE *pf;
    char c;
    int i, j;
    char nomb[100];
    strcpy(nomb,esquema);
    strcat(nomb,".txt");
    pf=fopen(nomb,"w");
    if(pf==NULL)
    {
        printf("Error al abrir el archivo\n");
        return(1);
    }
    for(i=1; i<=numregistros; i++){
        for(j=1; j<=numcampos; j++){
            leer(datos[j], &P, i);
            fprintf(pf,P.dato);
            if(j!=numcampos)
            fprintf(pf,"\\");
        }
        if(((i!=numregistros)&&(j!=numcampos)))
        fprintf(pf,"\n");
    }
    
        fclose(pf);
        //free(nomb);
}

int obtenerbasededatos(int permiso){
     
     NODO A;
     FILE *pf,*pfa, *pfb;
     int i, j;
     char archivodatos[100];
     char archivometadatos[100];
     for(i=1; i<numesquemas; i++)
         borrar(esquemas, i);
     for(i=1; i<numcampos; i++)
                              borrarc(campos, i);
                     for(i=1; i<=numregistros; i++)
                              for(j=1; j<=numcampos; j++)
                                       borrar(datos[i], 1);
     numesquemas=0;
     numcampos=0;
     numregistros=0;
     obteneresquemas();
     system("cls");
       if(numesquemas==0)
       {
            printf("\n\n");
            if(permiso == 1) // Permiso para el administrador
            {
                printf("\tNo se encuentran esquemas en esta base de datos\n");
                printf("\tEscriba el nombre de un nuevo esquema de relacion\n");
                scanf("%s", esquema);
                pf = fopen("esquemas.txt", "w");
                if(pf == NULL)
                {
                  printf("No memory allocation\n");
                  return 1;
                }
                fprintf(pf, "%s", esquema);
                fclose(pf);
            
                strcpy(archivodatos, esquema);
                strcpy(archivometadatos, esquema);
                strcat(archivodatos, ".txt");
                pfa = fopen(archivodatos, "w");
                if(pfa == NULL)
                {
                  printf("No memory allocation\n");
                  return 1;
                }
                fclose(pfa);
                strcat(archivometadatos, "m.txt");
                pfb = fopen(archivometadatos, "w");
                if(pfb == NULL)
                {
                   printf("No memory allocation\n");
                   return 1;
                }
                fclose(pfb);
            }
             
            else if(permiso == 2){ // Permiso para el usuario
                if(numesquemas==0);
                {
                    printf("\tNo hay tablas en la base de datos\n");
                    printf("\tNo puede realizar ninguna operacion\n");
                    return 0;
                }
            }
            
            else // Permiso para realizar consultas
            {
                printf("\tNo hay tablas en la base de datos\n");
                printf("\tNo puede realizar ninguna consulta si no hay datos\n");
                return 0;
            }
       }
       else
       {
            if(strlen(esquema) == 0){
                leer(esquemas, &A,1);
                strcpy(esquema,A.dato);
            }
            obtenercampos();
            obtenerdatos();
       }
       return 1;
}

int pantalla_usuario(){
    int opcion = 1;
     int x = 16;
     int y = 12;
     int n = 0;
     char c;
     system("cls");
     n = obtenerbasededatos(2);
     if(n == 0)
     {
          system("pause");
          return 5;
     }
     printf("*******************************************************\n");
     printf("*                                                     *\n");
     printf("*              Sistema de Base de datos               *\n");
     printf("*                                                     *\n");
     printf("*                                                     *\n");
     printf("*                                                     *\n");
     printf("*                  Modo usuario                       *\n");
     printf("*                                                     *\n");
     printf("*                     Menu                            *\n");
     printf("*                                                     *\n");
     printf("*                                                     *\n");
     printf("*                 Ver registros                       *\n");
     printf("*                 Agregar registro                    *\n");
     printf("*                 Borrar registro                     *\n");
     printf("*                 Modificar registro                  *\n");
     printf("*                 Regresar al menu anterior           *\n");
     printf("*                                                     *\n");
     printf("*                                                     *\n");    
     printf("*******************************************************\n");
     printf("Eliga una de las siguientes opciones con las teclas de direccionamiento\n");
     printf("Pulse enter para escoger seleccion\n");
     gotoxy(x,y);
     printf("%c", 26);
     do{
        c=getch();
        if(c==-32){
            c=getch();
            if(c==KEY_UP){
                 if(opcion!=1){
                      opcion--;
                      gotoxy(x,y);
                      printf(" ");
                      y--;
                      gotoxy(x,y);
                      printf("%c", 26);
                 }
            }
            else if(c==KEY_DOWN){
                 if(opcion!=5){
                      opcion++;
                      gotoxy(x,y);
                      printf(" ");
                      y++;
                      gotoxy(x,y);
                      printf("%c", 26);
                 }
            }
        }
        }while(c!=ENTER);
        return opcion;
}

void ejecutar_usuario(opcionus){
     int i, j;
     char nomcampo[50];
     int numerocampo;
     int numeroregistro;
     int agregarregistros;
     system("cls");
     switch(opcionus){
            case 1://opcion de visualizar todos los registros
                printf("Se presentan todos los registros almacenados\n\n");
                for(i=1; i<=numregistros; i++){
                      printf("No. de registro: %d", i);
                      printf("\n");
                      for(j=1; j<=numcampos; j++){
                            NODOC E;
                            NODO F;
                            leerc(campos,&E, j);
                            leer(datos[j], &F, i);
                            printf("%s: %s",E.atributo,F.dato);
                            printf("\n");
                      }
                      printf("\n");
                }
                break;
           
           case 2://opcion de agregar registro
               
                printf("Digite el numero de registros a agregar MAX[200]:\n");
                scanf("%d", &agregarregistros);
                while(agregarregistros <= 0)
                {
                     printf("Numero erroneo\n");
                     printf("Digite el numero de registros a agregar MAX[200]:\n");
                     scanf("%d", &agregarregistros);
                }
                for(i=0; i<=agregarregistros; i++)
                {
                     printf("Se agregara el registro No. %d", numregistros+1);
                     if(agregar_registro() == 1)
                          printf("\n\t...Registro no agregado");
                     else
                          printf("\n\t...Registro agregado\n");
                }
                guardardatos();
                break;
                
           case 3://opcion para borrar un registro
                printf("Se presentan todos los registros almacenados\n\n");
                for(i=1; i<=numregistros; i++){
                      printf("No. de registro: %d", i);
                      printf("\n");
                      for(j=1; j<=numcampos; j++){
                            NODOC E;
                            NODO F;
                            leerc(campos,&E, j);
                            leer(datos[j], &F, i);
                            printf("%s: %s",E.atributo,F.dato);
                            printf("\n");
                      }
                      printf("\n");
                }
                if(numregistros>0){
                     printf("Por favor digite el numero de registro a borrar: ");
                     scanf("%d", &numeroregistro);
                     for(i=1; i<=numcampos; i++){
                          NODO A,B;
                          borrar(datos[i], numeroregistro);
                     }
                     numregistros--;
                     guardardatos();
                     printf("\n\t...Registro borrado...\n");
                     printf("\n");
                }
                else{
                     printf("No hay registros para borrar\n");
                }
                break;
                
           case 4://opcion para modificar un registro
                
                modificar_registro();
                break;
                
           default:
                printf("Opcion incorrecta");
           
     }
}

int buscaesquema(char *nomesquema)
{
    int i;
    int encontrado=0;
    for(i=1; i<=numesquemas; i++)
    {
             NODO E;
             leer(esquemas, &E, i);
             if(strcmp(nomesquema,E.dato)==0)
                  encontrado=1;
    }
    return encontrado;
}

int agregar_registro()
{
     
     int i, j,k, datovalido;
                
                printf("\n\nPor favor digite:\n\n");
                for(i=1; i<=numcampos; i++){
                     NODOC A;
                     NODO B;
                     leerc(campos,&A,i);
                     printf("%s: ", A.atributo);
                     switch(A.tipo)
                     {
                            case 1:
                                 printf("(int ,");
                                 break;
                            case 2:
                                 printf("(float ,");
                                 break;
                            case 3:
                                 printf("(char ,");
                                 break;
                            case 4:
                                 printf("(string ,");
                                 break;
                     }
                     printf("(%d) ,", A.longitud);
                     if(A.restriccion=='N')
                           printf("NULL");
                     else
                           printf("NOT NULL");
                     if(A.llave==1)
                           printf(" *");
                     printf(")\n\t");
                     fflush(stdin);
                     gets(B.dato);
                     while(strcmp(B.dato,"\n")==0)
                     {
                          printf("No tecleo ningun dato\n");
                          printf("Vuelva a escribir\n");
                          fflush(stdin);
                          gets(B.dato);
                     }
                     
                     // COMIENZA CODIGO PARA VERIFICACION DE RESTRICCION
                     // No se saben terminos para restriccion y llave
                     
                     if(A.tipo==1 || A.tipo==2)
                     {
                           for(j=0; j<strlen(B.dato); j++)
                           {
                                    if(B.dato[j] < '0' || B.dato[j] > '9')
                                         datovalido = 0;
                           }
                     }
                     if(strlen(B.dato) > A.longitud)
                            datovalido=0;
                     while(!datovalido)
                     {
                            printf("\tDato invalido\n");
                            printf("\tVerifique restricciones\n");
                            datovalido = 1;
                            fflush(stdin);
                            gets(B.dato);
                            if(A.tipo==1 || A.tipo==2)
                            {
                                   for(j=0; j<strlen(B.dato); j++)
                                   {
                                         if(B.dato[j] < '0' || B.dato[j] > '9')
                                               datovalido = 0;
                                   }
                            }
                            if(strlen(B.dato) > A.longitud)
                                datovalido=0;
                     }
                     if(A.llave == 1)
                     {
                           for(k=0; k<numregistros; k++)
                           {
                                    NODO A;
                                    leer(datos[i], &A, k);
                                    if(strcmp(A.dato,B.dato)==0)
                                    {
                                            printf("No puede haber atributos llave iguales\n");
                                            return 1;
                                    }
                           }
                     }
                     // TERMINO DE CODIGO DE VERIFICACION DE RESTRICCION
                     
                     agregar(datos[i], B, numregistros+1);
                }
                numregistros++;
                printf("\n");
                
                return 0;
}

void modificar_registro()
{
     int i, j, datovalido, numeroregistro;
     printf("Se presentan todos los registros almacenados\n\n");
     for(i=1; i<=numregistros; i++){
         printf("No. de registro: %d", i);
         printf("\n");
         for(j=1; j<=numcampos; j++){
             NODOC E;
             NODO F;
             leerc(campos,&E, j);
             leer(datos[j], &F, i);
             printf("%s: %s",E.atributo,F.dato);
             printf("\n");
         }
         printf("\n");
     }
     printf("Por favor digite el numero de registro a modificar:\n");
     scanf("%d", &numeroregistro);
     fflush(stdin);
                
     printf("\n\nPor favor digite:\n\n");
     for(i=1; i<=numcampos; i++){
         NODOC A;
         NODO B;
         leerc(campos,&A,i);
         printf("%s: ", A.atributo);
         switch(A.tipo)
         {
             case 1:
                 printf("(int ,");
                 break;
             case 2:
                 printf("(float ,");
                 break;
             case 3:
                 printf("(char ,");
                 break;
             case 4:
                 printf("(string ,");
                 break;
         }
         printf("(%d) ,", A.longitud);
         if(A.restriccion=='N')
             printf("NULL");
         else
             printf("NOT NULL");
         if(A.llave==1)
             printf(" *");
         printf(")\n\t");
         gets(B.dato);
                     
         // COMIENZA CODIGO PARA VERIFICACION DE RESTRICCION
         // No se saben terminos para restriccion y llave
                     
         if(A.tipo==1 || A.tipo==2)
         {
             for(j=0; j<strlen(B.dato); j++)
             {
                 if(B.dato[j] < '0' || B.dato[j] > '9')
                 datovalido = 0;
             }
         }
         if(strlen(B.dato) > A.longitud)
             datovalido=0;
         while(!datovalido)
         {
             printf("\tDato invalido\n");
             printf("\tVerifique restricciones\n");
             datovalido = 1;
             gets(B.dato);
             if(A.tipo==1 || A.tipo==2)
             {
                 for(j=0; j<strlen(B.dato); j++)
                 {
                     if(B.dato[j] < '0' || B.dato[j] > '9')
                     datovalido = 0;
                 }
             }
             if(strlen(B.dato)+1 > A.longitud)
             datovalido=0;
         }
                     
         // TERMINO DE CODIGO DE VERIFICACION DE RESTRICCION
                     
         modificar(datos[i], B, numeroregistro);
         }
                
         guardardatos();
         printf("\n\t...Registro modificado...\n");
}

void procesa_consultas()
{
     int n = 0;
     char respuesta;
     system("cls");
     n = obtenerbasededatos(3);
     if(n == 0)
     {
           system("pause");
           return;
     }

     printf("\t-----------------------------------------------------------------\n");
     printf("\t              Sistema para realizar consultas                   \n");
     printf("\t-----------------------------------------------------------------\n");
     printf("                            Comandos:                \n\n");
     printf("\tSELECT Seleccion                 PI Proyeccion\n");
     printf("\tEj: (Atributo1 = Atributo2)      Ej: (Atributo1, Atributo2, ...)\n");
     printf("\t     SELECT                           PI\n"); 
     printf("\t    (Relacion)                       (Relacion\n\n");
     printf("\tPC Plano cartesiano              UNION Union de conjuntos\n");
     printf("\tEj: (Relacion1)                  Ej: (Relacion1)\n");
     printf("\t     PC                               UNION\n");
     printf("\t    (Relacion2)                      (Relacion2)\n\n");
     printf("\tMINUS Diferencia de conjuntos    EJ Equijoin\n");
     printf("\tEj: (Relacion1)                  Ej: (Relacion1)\n");
     printf("\t     MINUS                            EJ\n");
     printf("\t    (Relacion2)                      (Relacion2)\n\n");
     printf("\t* = todos los atributos");
     printf("\n\n");
     fflush(stdin);
     do
     {
          char *cad;
          char *separador = "()"; 
          int i;
          char cadena1[50];
          char cadena2[50];
          char cadena3[50];
          char operador[20];
          printf("\tConsulta #%d\n", numconsulta);
          printf("\tR%d <- ", numconsulta);
          fflush(stdin);
          gets(cadena1);
          printf("\t       ");
          fflush(stdin);
          gets(operador);
          printf("\t      ");
          fflush(stdin);
          gets(cadena2);
          fflush(stdin);
         
          for(i=1; i<strlen(cadena1)-1; i++)// filtro de parentesis
               cadena1[i-1] = cadena1[i];
          cadena1[i-1]='\0';
          for(i=1; i<strlen(cadena2)-1; i++)// filtro de parentesis
               cadena2[i-1] = cadena2[i];
          cadena2[i-1]='\0';
          if(strcmp(operador,"SELECT")==0)
              algoritmo_seleccion(cadena1,cadena2);
          else if(strcmp(operador,"PI")==0)
              algoritmo_proyeccion(cadena1,cadena2);
          else if(strcmp(operador,"PC")==0)
              algoritmo_planocartesiano(cadena1,cadena2);
          else if(strcmp(operador,"UNION")==0)
              algoritmo_union(cadena1,cadena2);
          else if(strcmp(operador,"MINUS")==0)
              algoritmo_diferencia(cadena1,cadena2);
          else if(strcmp(operador,"EJ")==0)
          {
              printf("\tElija la condicion para realizar el equijoin\n");
              printf("\tEj: (Atributo1=Atributo2)\n\t");
              fflush(stdin);
              gets(cadena3);
              for(i=1; i<strlen(cadena3)-1; i++)// filtro de parentesis
                   cadena3[i-1] = cadena3[i];
              cadena3[i-1]='\0';
              algoritmo_equijoin(cadena1,cadena2,cadena3);
          }
          else
              printf("\tOperador invalido\n"); 
          numconsulta++;
          printf("\tDesea realizar otra consulta (s/n)\n\t");
          fflush(stdin);
          scanf("%c", &respuesta);
     }while(respuesta=='s');
}

int algoritmo_seleccion(char * condicion, char * esquema)
{
     printf("Seleccion\n");
     FILE *pe;
     FILE *pem;
     FILE *pf;
     FILE *pfm;
     FILE *pg;
     FILE *pgm;
     FILE *ph;
     char c;
     int i;
     int j;
     int k;
     int l;
     int end=1; // bandera para esquema1
     int end2=1; // bandera para esquema2
     int tupla=0;
     int posc=0;
     char** cad;
     clock_t timea;
     clock_t timeb;
     clock_t timec;
     clock_t timed;
     int esq1;
     int esq2;
     char dat[50];
     char clave[50];
     int numcamposA=0;
     int numcamposC=0;
     int numregistrosA=0;
     int numregistrosC=0;
     int claveA;
     int contatributos=1;
     listac metadatosA;
     listac metadatosB;
     listac metadatosC;
     lista *datosA;
     lista *datosC;
     crearlistac(&metadatosA);
     crearlistac(&metadatosC);
     NODO E;
     int contA = 0;
     int contB = 0;
     int pos;
     int *indices;
     char *p = condicion;
     
     char archivo[50];
     char archivom[50];
     char cadena[100];
     
     NODO A;
     
     timea = clock();
     
     esq1 = buscaesquema(esquema);
     
     i=0;
     c = condicion[i];
     while(c!='=')
     {
            clave[i] = c;
            i++;
            c = condicion[i];
     }
     clave[i] = '\0';
     j = 0;
     
     p+=i+1;
     
     strcpy(cadena, p);
     strcpy(dat,cadena);
     
     if(esq1==0)
     {
           printf("No se encontro alguno de los esquemas\n");
           return 1;
     }
     
      strcpy(archivo, esquema);
     strcat(archivo, ".txt");
     pe = fopen(archivo,"r");
     if(pe == NULL)
     {
            printf("Error al abrir archivo\n");
     }
     strcpy(archivo, esquema);
     strcat(archivo, "m.txt");
     pem = fopen(archivo,"r");
     if(pem == NULL)
     {
            printf("Error al abrir archivo\n");
     }

     // obtener datos
     // cargar a memoria
     
      while(!feof(pem)){
                        NODOC E;
                        int i=0;
                        int z=0;
                        char longitud[10];
                        c=getc(pem);
                        while(c!='\\'){
                        E.atributo[i]=c;
                        i++;
                        c=getc(pem);
                        }
                        E.atributo[i]='\0';
                        E.atributo[i]='\0';
                             c=getc(pem);
                             E.tipo = (int)c;
                             E.tipo -= 48;
                             c=getc(pem); // lee '\'
                             while((longitud[z] = getc(pem))!='\\')
                                z++;
                             longitud[z]='\0';
                             E.longitud = atoi(longitud);
                             z=0; // reinicia la cadena longitud
                             strcpy(longitud,"");
                             c=getc(pem); // lee restriccion
                             E.restriccion = c;
                             c=getc(pem); // lee '\'
                             c=getc(pem);
                             if(c=='*')
                                    E.llave = 1;
                             else
                                    E.llave = 0; 
                        numcamposA++;
                        if(c=='*' && ((strcmp(E.atributo,clave)==0)))
                              claveA = numcamposA;
                        agregarc(metadatosA,E,numcamposA);
                        c=getc(pem);
        }
        fclose(pem);
      
      end = 1;
      
      while(!feof(pe))
      {
            c = getc(pe);
            if(c=='\n')
                 numregistrosA++;
      }
      numregistrosA++;
      
    
      datosA = (lista *)malloc(numregistrosA*sizeof(lista *));
      if(datosA == NULL)
      {
            printf("Bad memory allocation for datosA");
      }
      for(i=0; i<numregistrosA; i++)
            crearlista(&datosA[i]);
     
      
      fseek(pe,0,0);
      
      while(!feof(pe)){ 
                        for(j=1; j<numcamposA+1; j++){ 
                             c=getc(pe);
                             NODO F;
                             int i=0; 
                             while((c!='\\')&&(!feof(pe))&&(c!='\n')){
                                 F.dato[i]=c;
                                 i++;
                                 c=getc(pe);
                                 
                             }
                             F.dato[i]='\0';
                             agregar(datosA[contA], F, j);
                             if(feof(pe))
                                 break;
                        }
                        contA++;
        }
        fclose(pe);
        
        
        // Solamente para este algoritmo
        numcamposC = numcamposA;
        numregistrosC = numregistrosA;

     // Empieza ordenacion por algoritmo seleccion
        
        for(i=0; i<numregistrosA-1; i++)
        {
              pos = i;
              for(j = i+1; j<numregistrosA; j++)
              {
                    NODO A, B;
                    leer(datosA[pos], &A, claveA);
                    leer(datosA[j], &B, claveA);
                    if(strcmp(A.dato, B.dato) > 0)
                          pos = j;
              }
              
              if(pos != i)
              {
                     lista aux;
                     aux = datosA[i];
                     datosA[i] = datosA[pos];
                     datosA[pos]=aux;
              }
        }
        
        timeb = clock();
        
        /*for(i=0; i<numregistrosA; i++)
        {
              for(j=1; j<=numcamposA; j++)
              {
                   NODO A;
                   leer(datosA[i], &A, j);
                   printf("%s\n", A.dato);
              }
              printf("\n");
        }*/
        
        
        struct bloque b[numregistrosA];
        for(i=0; i<numregistrosA; i++)
        {
              NODO A;
              leer(datosA[i], &A, claveA);
              b[i].sigu = datosA[i];
              strcpy(b[i].clave, A.dato);
        }
        
        k=1;
        for(i=0; i<numregistrosA; i++)
        {
             if(strcmp(b[i].clave,dat)==0){
                 printf("Registro %d\n", i+1);
                 for(j=1; j<=numcamposA; j++)
                 {
                     NODO A;
                     NODOC B;
                     leer(datosA[i], &A, j);
                     leerc(metadatosA, &B, j);
                     
                     printf("%s: %s\n", B.atributo, A.dato);
                 }
                 printf("\n");
                 k++;
             }
        }
        
        printf("\tTiempo total de algoritmo: %f seg.\n\n\t", (timeb-timea)/(double)CLOCKS_PER_SEC);
        printf("\tTiempo total de algoritmo con memoria: %f seg.\n\n\t", (clock()-timea)/(double)CLOCKS_PER_SEC);
         
}

int algoritmo_proyeccion(char * atributos, char * esquema)
{
     printf("Proyeccion\n");
     
     FILE *pe;
     FILE *pem;
     FILE *pf;
     FILE *pfm;
     FILE *pg;
     FILE *pgm;
     FILE *ph;
     char c;
     int i;
     int j;
     int k;
     int l;
     int end=1; // bandera para esquema1
     int end2=1; // bandera para esquema2
     int tupla=0;
     int posc=0;
     char** cad;
     clock_t timea;
     clock_t timeb;
     clock_t timec;
     int esq1;
     int esq2;
     int numcamposA=0;
     int numcamposC=0;
     int numregistrosA=0;
     int numregistrosC=0;
     int claveA;
     int contatributos=1;
     lista metadatosA;
     lista metadatosB;
     lista metadatosC;
     lista *datosA;
     lista *datosC;
     crearlista(&metadatosA);
     crearlista(&metadatosC);
     NODO E;
     int contA = 0;
     int contB = 0;
     int pos;
     int *indices;
     
     char archivo[50];
     char archivom[50];
     char cadena[100];
     
     NODO A;
     
     timea = clock();
     
     esq1 = buscaesquema(esquema);

     if(esq1==0)
     {
           printf("No se encontro alguno de los esquemas\n");
           return 1;
     }
     
      strcpy(archivo, esquema);
     strcat(archivo, ".txt");
     pe = fopen(archivo,"r");
     if(pe == NULL)
     {
            printf("Error al abrir archivo\n");
     }
     strcpy(archivo, esquema);
     strcat(archivo, "m.txt");
     pem = fopen(archivo,"r");
     if(pem == NULL)
     {
            printf("Error al abrir archivo\n");
     }

     
     // obtener datos
     // cargar a memoria
      while(end==1){
                        int i=0;
                        char longitud[20];
                        c = getc(pem);
                        while(c!='\\'){
                              longitud[i] = c;
                              c = getc(pem);
                              i++;
                        }
                        longitud[i]='\0';
                        strcpy(E.dato, longitud);
                        numcamposA++;
                        agregar(metadatosA,E,numcamposA);
                        while(c!='\n'){
                              c = getc(pem);
                              if(c=='*')
                                   claveA = numcamposA;
                              if(feof(pem)){
                                   end = 0;
                                   break;     
                              }
                        }
      }
      fclose(pem);
      
      end = 1;
      
      while(!feof(pe))
      {
            c = getc(pe);
            if(c=='\n')
                 numregistrosA++;
      }
      numregistrosA++;
      
    
      datosA = (lista *)malloc(numregistrosA*sizeof(lista *));
      if(datosA == NULL)
      {
            printf("Bad memory allocation for datosA");
      }
      for(i=0; i<numregistrosA; i++)
            crearlista(&datosA[i]);
     
      
      fseek(pe,0,0);
      
      while(!feof(pe)){ 
                        for(j=1; j<numcamposA+1; j++){ 
                             c=getc(pe);
                             NODO F;
                             int i=0; 
                             while((c!='\\')&&(!feof(pe))&&(c!='\n')){
                                 F.dato[i]=c;
                                 i++;
                                 c=getc(pe);
                                 
                             }
                             F.dato[i]='\0';
                             agregar(datosA[contA], F, j);
                             if(feof(pe))
                                 break;
                        }
                        contA++;
        }
        fclose(pe);
        
        
        // Solamente para este algoritmo
        numcamposC = numcamposA;
        numregistrosC = numregistrosA;
      
      for(i=0; i<strlen(atributos); i++)
     {
              c=atributos[i];
              if(c==',')
                     contatributos++;
              if(c=='*')
                     contatributos = numcamposA;
     }
     
     cad = (char**)malloc(contatributos*sizeof(char *));
     if(cad == NULL)
     {
            puts("No memory allocation\n");
            return 1;
     }
     for(i=0; i<contatributos; i++)
     {
            cad[i]=(char *)malloc(100 * sizeof(char));
            if(cad[i]==NULL)
            {
                      puts("No memory allocation\n");
                      return 1;      
            }
     }
     
     indices = (int *)malloc(contatributos*sizeof(int));
     if(indices==NULL)
     {
           printf("No memory allocation\n");
           return 1;        
     }
     
     j=0;
     k=0;
     l=0;
     
     if(atributos[i]=='*')
     {
                   for(i=1; i<=numcamposA; i++)
                   {
                          NODO A;
                          leer(metadatosA, &A, i);
                          l=i-1;
                          strcpy(cad[l], A.dato);
                   }
     }
     
     j=0;
     k=0;
     
     
      for(i=0; i<strlen(atributos); i++)
     {

                   if(atributos[i]==',')
                   {
                        cad[j][k]='\0';
                        j++;
                        k=0;
                   }
                   else
                   {
                        cad[j][k] = atributos[i];
                        k++;
                   }
              
     }
     cad[j][k]='\0';
     
     for(i=0; i<contatributos; i++)
     {
           int encontrado=0;
           for(j=1; j<=numcamposA; j++)
           {
                   NODO A;
                   leer(metadatosA, &A, j);
                   if(strcmp(cad[i],A.dato)==0)
                   {
                          indices[i] = j;
                          encontrado = 1;
                          break;
                   }
           }
           if(!encontrado)
           {
                 printf("No se encontro alguno de los atributos\n");
           }
     }
     
     for(i=0; i<contatributos; i++)
     {
           NODO B;
           strcpy(B.dato, cad[i]);
           agregar(metadatosC, B, i+1);
     }
     
     // Empieza ordenacion por algoritmo seleccion
        
        for(i=0; i<numregistrosA-1; i++)
        {
              pos = i;
              for(j = i+1; j<numregistrosA; j++)
              {
                    NODO A, B;
                    leer(datosA[pos], &A, claveA);
                    leer(datosA[j], &B, claveA);
                    if(strcmp(A.dato, B.dato) > 0)
                          pos = j;
              }
              
              if(pos != i)
              {
                     lista aux;
                     aux = datosA[i];
                     datosA[i] = datosA[pos];
                     datosA[pos]=aux;
              }
        }
        
     if(strcmp(atributos,"*")==0)
     {
     for(i=0; i<numregistrosA; i++)
      {
            printf("Registro %d:\n", i+1);
            for(j=1; j<=numcamposA; j++)
            {
                   NODO C;
                   NODO D;
                   leer(datosA[i], &C, j);
                   leer(metadatosA, &D, j); // colacando los mismos metadatos que A
                   printf("%s: %s\n", D.dato, C.dato); 
            }
            printf("\n");
      }
         return;
     }
     
     numregistrosC = numregistrosA;
     
     datosC = (lista *)malloc(numregistrosC*sizeof(lista *));
        if(datosC == NULL)
        {
            printf("Bad memory allocation for datosC");
        }

        for(i=0; i<numregistrosC; i++)
            crearlista(&datosC[i]);

     
     i = 0;
     j = 1;
     numregistrosC = 0;
     
     while(i < numregistrosA)
     {
           int igual = 1;
           NODO A;
        
           for(k=0; k<contatributos; k++)
           {
                 NODO A;
                 leer(datosA[i], &A, indices[k]);
                 agregar(datosC[numregistrosC], A, k+1); // numregistrosC
           }
           numregistrosC++;
           if(i == numregistrosA-1)
                 break;
           for(k=0; k<contatributos; k++)
           {
                 NODO A;
                 NODO B;
                 leer(datosA[i], &A, indices[k]);
                 leer(datosA[j], &B, indices[k]);
           
                 if(strcmp(A.dato,B.dato)!=0)
                 {
                       igual = 0;
                 }
           }
           while((igual==1) && (j < numregistrosA))
           {
                  j++;
                  if(j == numregistrosA)
                       break;
                  for(k=0; k<contatributos; k++)
                  {
                       NODO A;
                       NODO B;
                       leer(datosA[i], &A, indices[k]);
                       leer(datosA[j], &B, indices[k]);
                       printf("%s %s\n", A.dato, B.dato);
                       if(strcmp(A.dato,B.dato)!=0)
                       {
                             igual = 0;
                       }
                 }
                 
           }
           i = j;
           j = i + 1;
     }
     
      timeb = clock();
     
       for(i=0; i<numregistrosC; i++)
      {
            printf("Registro %d:\n", i+1);
            for(j=1; j<=contatributos; j++)
            {
                   NODO C;
                   NODO D;
                   leer(datosC[i], &C, j);
                   leer(metadatosC, &D, j); // colacando los mismos metadatos que A
                   printf("%s: %s\n", D.dato, C.dato); 
            }
            printf("\n");
      }
      
     
     printf("\tTiempo total de algoritmo: %f seg.\n\n\t", (timeb-timea)/(double)CLOCKS_PER_SEC);
     printf("\tTiempo total de algoritmo con memoria: %f seg.\n\n\t", (clock()-timea)/(double)CLOCKS_PER_SEC);
}

int algoritmo_planocartesiano(char * esquema1, char * esquema2)
{
     FILE *pe;
     FILE *pem;
     FILE *pf;
     FILE *pfm;
     FILE *pg;
     FILE *pgm;
     FILE *ph;
     char c;
     int i;
     int j;
     int k;
     int l;
     int z=0;
     int end=1; // bandera para esquema1
     int end2=1; // bandera para esquema2
     int tupla=0;
     int posc=0;
     clock_t timea;
     clock_t timeb;
     clock_t timec;
     int esq1;
     int esq2;
     int numcamposA=0;
     int numcamposB=0;
     int numcamposC=0;
     int numregistrosA=0;
     int numregistrosB=0;
     int numregistrosC=0;
     lista metadatosA;
     lista metadatosB;
     lista metadatosC;
     lista *datosA;
     lista *datosB;
     lista *datosC;
     crearlista(&metadatosA);
     crearlista(&metadatosB);
     crearlista(&metadatosC);
     NODO E;
     int contA = 0;
     int contB = 0;
     
     char archivo[50];
     char archivom[50];
     char cadena[100];
     
     NODO A;
     
     timea = clock();
     
     esq1 = buscaesquema(esquema1);
     esq2 = buscaesquema(esquema2);

     if(esq1==0 || esq2==0)
     {
           printf("No se encontro alguno de los esquemas\n");
           return 1;
     }
     
     strcpy(archivo, esquema1);
     strcat(archivo, ".txt");
     pe = fopen(archivo,"r");
     if(pe == NULL)
     {
            printf("Error al abrir archivo\n");
     }
     strcpy(archivo, esquema1);
     strcat(archivo, "m.txt");
     pem = fopen(archivo,"r");
     if(pem == NULL)
     {
            printf("Error al abrir archivo\n");
     }
     
     strcpy(archivo, esquema2);
     strcat(archivo, ".txt");
     pf = fopen(archivo,"r");
     if(pf == NULL)
     {
            printf("Error al abrir archivo\n");
     }
     strcpy(archivo, esquema2);
     strcat(archivo, "m.txt");
     pfm = fopen(archivo,"r");
     if(pfm == NULL)
     {
            printf("Error al abrir archivo\n");
     }
     
     // obtener datos
     // cargar a memoria
      while(end==1){
                        int i=0;
                        char longitud[20];
                        c = getc(pem);
                        while(c!='\\'){
                              longitud[i] = c;
                              c = getc(pem);
                              i++;
                        }
                        longitud[i]='\0';
                        strcpy(E.dato, longitud);
                        numcamposA++;
                        agregar(metadatosA,E,numcampos);
                        while(c!='\n'){
                              c = getc(pem);
                              if(feof(pem)){
                                   end=0;
                                   break;     
                              }
                        }
      }
      fclose(pem);
      end=1;
      while(end==1){
                        int i=0;
                        char longitud[20];
                        c = getc(pfm);
                        while(c!='\\'){
                              longitud[i] = c;
                              c = getc(pfm);
                              i++;
                        }
                        longitud[i]='\0';
                        strcpy(E.dato,longitud);
                        for(j=1; j<=numcamposA; j++)
                        {
                              NODO B;
                              leer(metadatosA,&B,j);
                              if(strcmp(B.dato,longitud)==0)
                              {
                                     strcpy(E.dato,esquema2);
                                     strcat(E.dato,".");
                                     strcat(E.dato,longitud);
                                     break;
                              }
                        }
                        numcamposB++;
                        agregar(metadatosB,E,numcamposB);
                        while(c!='\n'){
                              c = getc(pfm);
                              if(feof(pfm)){
                                   end=0;
                                   break;     
                              }
                        }     
      }
      fclose(pfm);
      
      while(!feof(pe))
      {
            c = getc(pe);
            if(c=='\n')
                 numregistrosA++;
      }
      numregistrosA++;
      
      while(!feof(pf))
      {
            c = getc(pf);
            if(c=='\n')
                 numregistrosB++;
      }
      numregistrosB++;
    
      datosA = (lista *)malloc(numregistrosA*sizeof(lista *));
      if(datosA == NULL)
      {
            printf("Bad memory allocation for datosA");
      }
      for(i=0; i<numregistrosA; i++)
            crearlista(&datosA[i]);
      datosB = (lista *)malloc(numregistrosB*sizeof(lista *));
      if(datosB == NULL)
      {
            printf("Bad memory allocation for datosB");
      }
      for(i=0; i<numregistrosB; i++)
            crearlista(&datosB[i]);
      
      fseek(pe,0,0);
      fseek(pf,0,0);
      
      while(!feof(pe)){ 
                        for(j=1; j<numcamposA+1; j++){ 
                             c=getc(pe);
                             NODO F;
                             int i=0; 
                             while((c!='\\')&&(!feof(pe))&&(c!='\n')){
                                 F.dato[i]=c;
                                 i++;
                                 c=getc(pe);
                               
                             }
                             F.dato[i]='\0';
                             agregar(datosA[contA], F, j);
                             if(feof(pe))
                                 break;
                        }
                        contA++;
        }
        fclose(pe);
        
        while(!feof(pf)){ 
                        for(j=1; j<numcamposB+1; j++){ 
                             c=getc(pf);
                             NODO F;
                             int i=0; 
                             while((c!='\\')&&(!feof(pf))&&(c!='\n')){
                                 F.dato[i]=c;
                                 i++;
                                 c=getc(pf);
                               
                             }
                             F.dato[i]='\0';
                             agregar(datosB[contB], F, j);
                             if(feof(pf))
                                 break;
                        }
                        contB++;
        }
        fclose(pf);
        
        // Solamente para este algoritmo
        numcamposC = numcamposA + numcamposB;
        numregistrosC = numregistrosA * numregistrosB;
        
        printf("%d", numregistrosC);
        
        datosC = (lista *)malloc(numregistrosC*sizeof(lista *));
        if(datosC == NULL)
        {
            printf("Bad memory allocation for datosC");
        }
        for(i=0; i<numregistrosC; i++)
            crearlista(&datosC[i]);
        
        tupla=0;
        posc=1;
        
        for(i=1; i<=numcamposA; i++)
        {
            NODO A;
            leer(metadatosA, &A, i);
            agregar(metadatosC, A, i);
        }
        for(j=1; j<=numcamposB; j++)
        {
            NODO B;
            leer(metadatosB, &B, j);
            agregar(metadatosC, B, i);
            i++;
        }
        
        for(i=0; i<numregistrosA; i++)
        {
            for(j=0; j<numregistrosB; j++)
            {     
                  posc=1; 
                  for(k=1; k<=numcamposA; k++)
                  {
                          NODO A;
                          leer(datosA[i], &A, k);
                          agregar(datosC[tupla], A, posc);
                          posc++;
                  }
                  for(l=1; l<=numcamposB; l++)
                  {
                          NODO B;
                          leer(datosB[j], &B, l);
                          agregar(datosC[tupla], B, posc);
                          posc++;
                  }
                  tupla++;
            }
            
        }
        timeb = clock();
        
      for(i=0; i<numregistrosC; i++)
      {
            printf("Registro %d:\n", i+1);
            for(j=1; j<=numcamposC; j++)
            {
                   NODO C;
                   NODO D;
                   leer(datosC[i], &C, j);
                   leer(metadatosC, &D, j);
                   printf("%s: %s\n", D.dato, C.dato); 
            }
            printf("\n");
      }  
            
      for(i=0; i<numregistrosA; i++)
            limpiarlista(datosA[i]);
      for(i=0; i<numregistrosB; i++)
            limpiarlista(datosB[i]);     
     
      printf("\tTiempo total de algoritmo: %f seg.\n\n\t", (timeb-timea)/(double)CLOCKS_PER_SEC);
      printf("\tTiempo total de algoritmo con memoria: %f seg.\n\n\t", (clock()-timea)/(double)CLOCKS_PER_SEC);
     
}

int algoritmo_union(char * esquema1, char * esquema2)
{
     printf("Diferencia\n");
     FILE *pe;
     FILE *pem;
     FILE *pf;
     FILE *pfm;
     FILE *pg;
     FILE *pgm;
     FILE *ph;
     char c;
     int i;
     int j;
     int k;
     int l;
     int end=1; // bandera para esquema1
     int end2=1; // bandera para esquema2
     int tupla=0;
     int posc=0;
     clock_t timea;
     clock_t timeb;
     clock_t timec;
     int esq1;
     int esq2;
     int numcamposA=0;
     int numcamposB=0;
     int numcamposC=0;
     int numcamposD=0;
     int numregistrosA=0;
     int numregistrosB=0;
     int numregistrosC=0;
     int numregistrosD=0;
     int claveA;
     int claveB;
     listac metadatosA;
     listac metadatosB;
     listac metadatosC;
     listac metadatosD;
     lista *datosA;
     lista *datosB;
     lista *datosC;
     lista *datosD;
     crearlistac(&metadatosA);
     crearlistac(&metadatosB);
     crearlistac(&metadatosC);
     crearlistac(&metadatosD);
     NODOC E;
     int contA = 0;
     int contB = 0;
     int contD = 0;
     int pos;
     int igual;
     
     char archivo[50];
     char archivom[50];
     char cadena[100];
     
     NODO A;
     NODO B;
     
     timea = clock();
     
     esq1 = buscaesquema(esquema1);
     esq2 = buscaesquema(esquema2);

     if(esq1==0 || esq2==0)
     {
           printf("No se encontro alguno de los esquemas\n");
           return 1;
     }
     
     strcpy(archivo, esquema1);
     strcat(archivo, ".txt");
     pe = fopen(archivo,"r");
     if(pe == NULL)
     {
            printf("Error al abrir archivo\n");
     }
     strcpy(archivo, esquema1);
     strcat(archivo, "m.txt");
     pem = fopen(archivo,"r");
     if(pem == NULL)
     {
            printf("Error al abrir archivo\n");
     }
     
     strcpy(archivo, esquema2);
     strcat(archivo, ".txt");
     pf = fopen(archivo,"r");
     if(pf == NULL)
     {
            printf("Error al abrir archivo\n");
     }
     strcpy(archivo, esquema2);
     strcat(archivo, "m.txt");
     pfm = fopen(archivo,"r");
     if(pfm == NULL)
     {
            printf("Error al abrir archivo\n");
     }
     
     // obtener datos
     // cargar a memoria
        
        while(!feof(pem)){
                        int i=0;
                        int z=0;
                        char longitud[10];
                        c=getc(pem);
                        while(c!='\\'){
                        E.atributo[i]=c;
                        i++;
                        c=getc(pem);
                        }
                        E.atributo[i]='\0';
                        E.atributo[i]='\0';
                             c=getc(pem);
                             E.tipo = (int)c;
                             E.tipo -= 48;
                             c=getc(pem); // lee '\'
                             while((longitud[z] = getc(pem))!='\\')
                                z++;
                             longitud[z]='\0';
                             E.longitud = atoi(longitud);
                             z=0; // reinicia la cadena longitud
                             strcpy(longitud,"");
                             c=getc(pem); // lee restriccion
                             E.restriccion = c;
                             c=getc(pem); // lee '\'
                             c=getc(pem);
                             if(c=='*')
                                    E.llave = 1;
                             else
                                    E.llave = 0; 
                        numcamposA++;
                        if(c=='*')
                              claveA = numcamposA;
                        agregarc(metadatosA,E,numcamposA);
                        c=getc(pem);
        }
        fclose(pem);
        
        while(!feof(pfm)){
                        int i=0;
                        int z=0;
                        char longitud[10];
                        c=getc(pfm);
                        while(c!='\\'){
                        E.atributo[i]=c;
                        i++;
                        c=getc(pfm);
                        }
                        E.atributo[i]='\0';
                        E.atributo[i]='\0';
                             c=getc(pfm);
                             E.tipo = (int)c;
                             E.tipo -= 48;
                             c=getc(pfm); // lee '\'
                             while((longitud[z] = getc(pfm))!='\\')
                                z++;
                             longitud[z]='\0';
                             E.longitud = atoi(longitud);
                             z=0; // reinicia la cadena longitud
                             strcpy(longitud,"");
                             c=getc(pfm); // lee restriccion
                             E.restriccion = c;
                             c=getc(pfm); // lee '\'
                             c=getc(pfm);
                             if(c=='*')
                                    E.llave = 1;
                             else
                                    E.llave = 0; 
                        numcamposD++;
                        agregarc(metadatosD,E,numcamposD);
                        c=getc(pfm);
        }
        fclose(pfm);
      
      printf("Se obtuvieron metadatosD\n");
    
    ////////////////////////////// Verificando metadatos //////////////////////////////////
      if(numcamposA!=numcamposD)
      {
            printf("No hay el mismo numero de atributos\n");
            printf("No se puede ejecutar el algoritmo\n");
            return 1;
      }
      
      
      while(!feof(pe))
      {
            c = getc(pe);
            if(c=='\n')
                 numregistrosA++;
      }
      numregistrosA++;
      
      while(!feof(pf))
      {
           c = getc(pf);
           if(c=='\n')
                 numregistrosD++;
      }
      numregistrosD++;
      
      printf("Se realizo la correcta verificacion\n");
    
      datosA = (lista *)malloc(numregistrosA*sizeof(lista *));
      if(datosA == NULL)
      {
            printf("Bad memory allocation for datosA");
      }
      for(i=0; i<numregistrosA; i++)
            crearlista(&datosA[i]);
      datosB = (lista *)malloc(numregistrosD*sizeof(lista *));
      if(datosB == NULL)
      {
            printf("Bad memory allocation for datosB");
      }
      for(i=0; i<numregistrosD; i++)
            crearlista(&datosB[i]);
      datosD = (lista *)malloc(numregistrosD*sizeof(lista *));
      if(datosD == NULL)
      {
            printf("Bad memory allocation for datosB");
      }
      for(i=0; i<numregistrosD; i++)
            crearlista(&datosD[i]);      
      
      printf("Obteniendo datos");
      
      fseek(pe,0,0);
      fseek(pf,0,0);
      
      while(!feof(pe)){ 
                        for(j=1; j<numcamposA+1; j++){ 
                             c=getc(pe);
                             NODO F;
                             int i=0; 
                             while((c!='\\')&&(!feof(pe))&&(c!='\n')){
                                 F.dato[i]=c;
                                 i++;
                                 c=getc(pe);
                               
                             }
                             F.dato[i]='\0';
                             agregar(datosA[contA], F, j);
                             if(feof(pe))
                                 break;
                        }
                        contA++;
        }
        fclose(pe);
        
        numregistrosA = contA;
        
        
        contD = 0;
        
        while(!feof(pf)){ 
                        
                        for(j=1; j<numcamposD+1; j++){ 
                             c=getc(pf);
                             NODO F;
                             int i=0; 
                             while((c!='\\')&&(!feof(pf))&&(c!='\n')){
                                 F.dato[i]=c;
                                 i++;
                                 c=getc(pf);
                               
                             }
                             F.dato[i]='\0';
                             agregar(datosD[contD], F, j);
                             if(feof(pf))
                                 break;
                        }
                        contD++;
        }
        fclose(pf);
        
        numregistrosD = contD;
        
        numregistrosB = numregistrosD;
      
        printf("Verificacion del dominio");
        
        igual = 0;
        for(i=1; i<=numcamposA; i++)
        {
            NODOC A;
            leerc(metadatosA, &A, i);
            for(j=1; j<=numcamposD; j++)
            {
                NODOC D;
                leerc(metadatosD, &D, j);
                if(strcmp(A.atributo,D.atributo)==0)
                {
                    if(A.tipo==D.tipo)
                    {
                        if(A.longitud==D.longitud)
                        {
                            if(A.restriccion==D.restriccion)
                            {
                                if(A.llave==D.llave)
                                {
                                    igual = 1;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            if(igual == 0)
            {
                 printf("Los esquemas de relación no cumplen con el mismo dominio\n");
                 return 1;
            }
        }
        
        
        
        
        for(i=1; i<=numcamposA; i++)
        {
            NODOC A;
            leerc(metadatosA, &A, i);
            for(j=1; j<=numcamposD; j++)
            {
                NODOC D;
                leerc(metadatosD, &D, j);
                if(strcmp(A.atributo,D.atributo)==0)
                {
                    for(k=0; k<numregistrosD; k++)
                    {
                        NODO B;
                        leer(datosD[k], &B, j);
                        agregar(datosB[k], B, i);
                    }
                }
            }
        }
        
        numcamposB = numcamposD;
        numregistrosB = numregistrosD;
        
        
        // Solamente para este algoritmo
        numcamposC = numcamposA;
        numregistrosC = numregistrosA + numregistrosB;
        
      // provisional
        
        datosC = (lista *)malloc(numregistrosC*sizeof(lista *));
        if(datosC == NULL)
        {
            printf("Bad memory allocation for datosC");
        }
        
        
        for(i=0; i<numregistrosC; i++)
            crearlista(&datosC[i]);
        
        
        claveB = claveA; // SE IGUALA LA POSICION DE LAS CLAVES EN AMBOS ESQUEMAS
        
        // Empieza ordenacion por algoritmo seleccion
        
        printf("Ordenacion");
        
        for(i=0; i<numregistrosA-1; i++)
        {
              pos = i;
              for(j = i+1; j<numregistrosA; j++)
              {
                    NODO A, B;
                    leer(datosA[pos], &A, claveA);
                    leer(datosA[j], &B, claveA);
                    if(strcmp(A.dato, B.dato) > 0)
                          pos = j;
              }
              
              if(pos != i)
              {
                     lista aux;
                     aux = datosA[i];
                     datosA[i] = datosA[pos];
                     datosA[pos]=aux;
              }
        }
        
        printf("Ordenacion B");
        
       for(i=0; i<numregistrosB-1; i++)
        {
              pos = i;
              for(j = i+1; j<numregistrosB; j++)
              {
                    NODO A, B;
                    leer(datosB[pos], &A, claveA);
                    leer(datosB[j], &B, claveA);
                    if(strcmp(A.dato, B.dato) > 0)
                          pos = j;
              }
              
              if(pos != i)
              {
                     lista aux;
                     aux = datosB[i];
                     datosB[i] = datosB[pos];
                     datosB[pos]=aux;
              }
        }
        
        
        for(i=0; i<numregistrosA; i++)
      {
            printf("Registro %d:\n", i+1);
            for(j=1; j<=numcamposA; j++)
            {
                   NODO C;
                   NODOC D;
                   leer(datosA[i], &C, j);
                   leerc(metadatosA, &D, j); // colacando los mismos metadatos que A
                   printf("%s: %s\n", D.atributo, C.dato); 
            }
            printf("\n");
      }
      
      for(i=0; i<numregistrosB; i++)
      {
            printf("Registro %d:\n", i+1);
            for(j=1; j<=numcamposB; j++)
            {
                   NODO C;
                   NODOC D;
                   leer(datosB[i], &C, j);
                   leerc(metadatosB, &D, j); // colacando los mismos metadatos que A
                   printf("%s: %s\n", D.atributo, C.dato); 
            }
            printf("\n");
      }
        
        i=0;
        j=0;
        numregistrosC=0;
        
        
        
        printf("Desarrollando algoritmo\n");
        
        while(i < numregistrosA && j < numregistrosB)
        {
                igual = 1;
                printf("i:%d j:%d\n", i, j);
                NODO A, B;
                int comp=0;
                leer(datosA[i], &A, claveA);
                leer(datosB[j], &B, claveA);
                printf("datos[A]%s datos[B]%s\n", A.dato, B.dato);
                comp = strcmp(A.dato, B.dato);
                if(comp > 0)
                {
                     printf("A>B datos[A]%s datos[B]%s\n", A.dato, B.dato);
                     for(k=1; k<=numcamposA; k++)
                     {
                           NODO C;
                           leer(datosB[j], &C, k);
                           agregar(datosC[numregistrosC], C, k);
                     }
                     j = j + 1;
                     numregistrosC++;
                }
                else
                {
                    if(comp < 0)
                    {
                        printf("A<B datos[A]%s datos[B]%s\n", A.dato, B.dato);
                        for(k=1; k<=numcamposA; k++)
                        {
                           NODO C;
                           leer(datosA[i], &C, k);
                           agregar(datosC[numregistrosC], C, k);
                        }
                        i = i + 1;
                        numregistrosC++;
                    }
                    
                    else{ // son iguales
                        for(k=1; k<=numcamposA; k++)
                        {
                           NODO A;
                           NODO C;
                           leer(datosA[i], &A, k);
                           leer(datosB[i], &C, k);
                           if(strcmp(A.dato,C.dato)==0)
                                continue;
                           else if(strcmp(A.dato,C.dato) > 0)
                           {
                                printf("A>B datos[A]%s datos[B]%s\n", A.dato, C.dato);
                                for(k=1; k<=numcamposA; k++)
                                {
                                    NODO C;
                                    leer(datosB[i], &C, k);
                                    agregar(datosC[numregistrosC], C, k);
                                }
                                j = j + 1;
                                numregistrosC++;
                                igual = 0;
                                break;
                           }
                           else
                           {
                               printf("A<B datos[A]%s datos[B]%s\n", A.dato, C.dato);
                               for(k=1; k<=numcamposA; k++)
                               {
                                    NODO C;
                                    leer(datosA[i], &C, k);
                                    agregar(datosC[numregistrosC], C, k);
                               }
                               i = i + 1;
                               numregistrosC++;
                               igual = 0;
                               break;
                           }
                           
                        }
                        if(igual == 1)
                        {
                            j = j + 1;   
                        }
                    }
                }
                
                 
        }
         if(i< numregistrosA)
        {
              while(i < numregistrosA)
              {
                      for(k=1; k<=numcamposA; k++)
                      {
                               NODO C;
                               leer(datosA[i], &C, k);
                               agregar(datosC[numregistrosC], C, k);
                      }
                      numregistrosC++;
                      i++;
              }
        }
         if(j< numregistrosB)
        {
              while(j < numregistrosB)
              {
                      for(k=1; k<=numcamposA; k++)
                      {
                               NODO C;
                               leer(datosB[j], &C, k);
                               agregar(datosC[numregistrosC], C, k);
                      }
                      numregistrosC++;
                      i++;
              }
        }
       
       
       timeb = clock();
        
        for(i=0; i<numregistrosC; i++)
      {
            printf("Registro %d:\n", i+1);
            for(j=1; j<=numcamposC; j++)
            {
                   NODO C;
                   NODOC D;
                   leer(datosC[i], &C, j);
                   leerc(metadatosA, &D, j); // colacando los mismos metadatos que A
                   printf("%s: %s\n", D.atributo, C.dato); 
            }
            printf("\n");
      }  
            
      for(i=0; i<numregistrosA; i++)
            limpiarlista(datosA[i]);
      for(i=0; i<numregistrosB; i++)
            limpiarlista(datosB[i]);     
      
      printf("\tTiempo total de algoritmo: %f seg.\n\n\t", (timeb-timea)/(double)CLOCKS_PER_SEC);
      printf("\tTiempo total de algoritmo con memoria: %f seg.\n\n\t", (clock()-timea)/(double)CLOCKS_PER_SEC); 
      
}

int algoritmo_diferencia(char * esquema1, char * esquema2)
{
     printf("Diferencia\n");
     FILE *pe;
     FILE *pem;
     FILE *pf;
     FILE *pfm;
     FILE *pg;
     FILE *pgm;
     FILE *ph;
     char c;
     int i;
     int j;
     int k;
     int l;
     int end=1; // bandera para esquema1
     int end2=1; // bandera para esquema2
     int tupla=0;
     int posc=0;
     clock_t timea;
     clock_t timeb;
     clock_t timec;
     int esq1;
     int esq2;
     int numcamposA=0;
     int numcamposB=0;
     int numcamposC=0;
     int numcamposD=0;
     int numregistrosA=0;
     int numregistrosB=0;
     int numregistrosC=0;
     int numregistrosD=0;
     int claveA;
     int claveB;
     listac metadatosA;
     listac metadatosB;
     listac metadatosC;
     listac metadatosD;
     lista *datosA;
     lista *datosB;
     lista *datosC;
     lista *datosD;
     crearlistac(&metadatosA);
     crearlistac(&metadatosB);
     crearlistac(&metadatosC);
     crearlistac(&metadatosD);
     NODOC E;
     int contA = 0;
     int contB = 0;
     int contD = 0;
     int pos;
     int igual;
     
     char archivo[50];
     char archivom[50];
     char cadena[100];
     
     NODO A;
     NODO B;
     
     timea = clock();
     
     esq1 = buscaesquema(esquema1);
     esq2 = buscaesquema(esquema2);

     if(esq1==0 || esq2==0)
     {
           printf("No se encontro alguno de los esquemas\n");
           return 1;
     }
     
     strcpy(archivo, esquema1);
     strcat(archivo, ".txt");
     pe = fopen(archivo,"r");
     if(pe == NULL)
     {
            printf("Error al abrir archivo\n");
     }
     strcpy(archivo, esquema1);
     strcat(archivo, "m.txt");
     pem = fopen(archivo,"r");
     if(pem == NULL)
     {
            printf("Error al abrir archivo\n");
     }
     
     strcpy(archivo, esquema2);
     strcat(archivo, ".txt");
     pf = fopen(archivo,"r");
     if(pf == NULL)
     {
            printf("Error al abrir archivo\n");
     }
     strcpy(archivo, esquema2);
     strcat(archivo, "m.txt");
     pfm = fopen(archivo,"r");
     if(pfm == NULL)
     {
            printf("Error al abrir archivo\n");
     }
     
     // obtener datos
     // cargar a memoria
        
        while(!feof(pem)){
                        int i=0;
                        int z=0;
                        char longitud[10];
                        c=getc(pem);
                        while(c!='\\'){
                        E.atributo[i]=c;
                        i++;
                        c=getc(pem);
                        }
                        E.atributo[i]='\0';
                        E.atributo[i]='\0';
                             c=getc(pem);
                             E.tipo = (int)c;
                             E.tipo -= 48;
                             c=getc(pem); // lee '\'
                             while((longitud[z] = getc(pem))!='\\')
                                z++;
                             longitud[z]='\0';
                             E.longitud = atoi(longitud);
                             z=0; // reinicia la cadena longitud
                             strcpy(longitud,"");
                             c=getc(pem); // lee restriccion
                             E.restriccion = c;
                             c=getc(pem); // lee '\'
                             c=getc(pem);
                             if(c=='*')
                                    E.llave = 1;
                             else
                                    E.llave = 0; 
                        numcamposA++;
                        if(c=='*')
                              claveA = numcamposA;
                        agregarc(metadatosA,E,numcamposA);
                        c=getc(pem);
        }
        fclose(pem);
        
        while(!feof(pfm)){
                        int i=0;
                        int z=0;
                        char longitud[10];
                        c=getc(pfm);
                        while(c!='\\'){
                        E.atributo[i]=c;
                        i++;
                        c=getc(pfm);
                        }
                        E.atributo[i]='\0';
                        E.atributo[i]='\0';
                             c=getc(pfm);
                             E.tipo = (int)c;
                             E.tipo -= 48;
                             c=getc(pfm); // lee '\'
                             while((longitud[z] = getc(pfm))!='\\')
                                z++;
                             longitud[z]='\0';
                             E.longitud = atoi(longitud);
                             z=0; // reinicia la cadena longitud
                             strcpy(longitud,"");
                             c=getc(pfm); // lee restriccion
                             E.restriccion = c;
                             c=getc(pfm); // lee '\'
                             c=getc(pfm);
                             if(c=='*')
                                    E.llave = 1;
                             else
                                    E.llave = 0; 
                        numcamposD++;
                        agregarc(metadatosD,E,numcamposD);
                        c=getc(pfm);
        }
        fclose(pfm);
      
      printf("Se obtuvieron metadatosD\n");
    
    ////////////////////////////// Verificando metadatos //////////////////////////////////
      if(numcamposA!=numcamposD)
      {
            printf("No hay el mismo numero de atributos\n");
            printf("No se puede ejecutar el algoritmo\n");
            return 1;
      }
      
      
      while(!feof(pe))
      {
            c = getc(pe);
            if(c=='\n')
                 numregistrosA++;
      }
      numregistrosA++;
      
      while(!feof(pf))
      {
           c = getc(pf);
           if(c=='\n')
                 numregistrosD++;
      }
      numregistrosD++;
      
      printf("Se realizo la correcta verificacion\n");
    
      datosA = (lista *)malloc(numregistrosA*sizeof(lista *));
      if(datosA == NULL)
      {
            printf("Bad memory allocation for datosA");
      }
      for(i=0; i<numregistrosA; i++)
            crearlista(&datosA[i]);
      datosB = (lista *)malloc(numregistrosD*sizeof(lista *));
      if(datosB == NULL)
      {
            printf("Bad memory allocation for datosB");
      }
      for(i=0; i<numregistrosD; i++)
            crearlista(&datosB[i]);
      datosD = (lista *)malloc(numregistrosD*sizeof(lista *));
      if(datosD == NULL)
      {
            printf("Bad memory allocation for datosB");
      }
      for(i=0; i<numregistrosD; i++)
            crearlista(&datosD[i]);      
      
      
      fseek(pe,0,0);
      fseek(pf,0,0);
      
      while(!feof(pe)){ 
                        for(j=1; j<numcamposA+1; j++){ 
                             c=getc(pe);
                             NODO F;
                             int i=0; 
                             while((c!='\\')&&(!feof(pe))&&(c!='\n')){
                                 F.dato[i]=c;
                                 i++;
                                 c=getc(pe);
                               
                             }
                             F.dato[i]='\0';
                             agregar(datosA[contA], F, j);
                             if(feof(pe))
                                 break;
                        }
                        contA++;
        }
        fclose(pe);
        
        numregistrosA = contA;
        
        
        contD = 0;
        
        while(!feof(pf)){ 
                        
                        for(j=1; j<numcamposD+1; j++){ 
                             c=getc(pf);
                             NODO F;
                             int i=0; 
                             while((c!='\\')&&(!feof(pf))&&(c!='\n')){
                                 F.dato[i]=c;
                                 i++;
                                 c=getc(pf);
                               
                             }
                             F.dato[i]='\0';
                             agregar(datosD[contD], F, j);
                             if(feof(pf))
                                 break;
                        }
                        contD++;
        }
        fclose(pf);
        
        numregistrosD = contD;
        
        numregistrosB = numregistrosD;
      
        
        igual = 0;
        for(i=1; i<=numcamposA; i++)
        {
            NODOC A;
            leerc(metadatosA, &A, i);
            for(j=1; j<=numcamposD; j++)
            {
                NODOC D;
                leerc(metadatosD, &D, j);
                if(strcmp(A.atributo,D.atributo)==0)
                {
                    if(A.tipo==D.tipo)
                    {
                        if(A.longitud==D.longitud)
                        {
                            if(A.restriccion==D.restriccion)
                            {
                                if(A.llave==D.llave)
                                {
                                    igual = 1;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            if(igual == 0)
            {
                 printf("Los esquemas de relación no cumplen con el mismo dominio\n");
                 return 1;
            }
        }
        
        
        
        
        for(i=1; i<=numcamposA; i++)
        {
            NODOC A;
            leerc(metadatosA, &A, i);
            for(j=1; j<=numcamposD; j++)
            {
                NODOC D;
                leerc(metadatosD, &D, j);
                if(strcmp(A.atributo,D.atributo)==0)
                {
                    for(k=0; k<numregistrosD; k++)
                    {
                        NODO B;
                        leer(datosD[k], &B, j);
                        agregar(datosB[k], B, i);
                    }
                }
            }
        }
        
        numcamposB = numcamposD;
        numregistrosB = numregistrosD;
        
        
        // Solamente para este algoritmo
        numcamposC = numcamposA;
        numregistrosC = numregistrosA + numregistrosB;
        
      // provisional
        
        datosC = (lista *)malloc(numregistrosC*sizeof(lista *));
        if(datosC == NULL)
        {
            printf("Bad memory allocation for datosC");
        }
        
        
        for(i=0; i<numregistrosC; i++)
            crearlista(&datosC[i]);
        
        
        claveB = claveA; // SE IGUALA LA POSICION DE LAS CLAVES EN AMBOS ESQUEMAS
        
        // Empieza ordenacion por algoritmo seleccion
        
        for(i=0; i<numregistrosA-1; i++)
        {
              pos = i;
              for(j = i+1; j<numregistrosA; j++)
              {
                    NODO A, B;
                    leer(datosA[pos], &A, claveA);
                    leer(datosA[j], &B, claveA);
                    if(strcmp(A.dato, B.dato) > 0)
                          pos = j;
              }
              
              if(pos != i)
              {
                     lista aux;
                     aux = datosA[i];
                     datosA[i] = datosA[pos];
                     datosA[pos]=aux;
              }
        }
        
       for(i=0; i<numregistrosB-1; i++)
        {
              pos = i;
              for(j = i+1; j<numregistrosB; j++)
              {
                    NODO A, B;
                    leer(datosB[pos], &A, claveA);
                    leer(datosB[j], &B, claveA);
                    if(strcmp(A.dato, B.dato) > 0)
                          pos = j;
              }
              
              if(pos != i)
              {
                     lista aux;
                     aux = datosB[i];
                     datosB[i] = datosB[pos];
                     datosB[pos]=aux;
              }
        }
        
        i=0;
        j=0;
        numregistrosC=0;
        
        
        while(i < numregistrosA && j < numregistrosB)
        {
                NODO A, B;
                int comp=0;
                leer(datosA[i], &A, claveA);
                leer(datosB[j], &B, claveA);
                comp = strcmp(A.dato, B.dato);
                if(comp == 0)
                {
                     for(k=1; k<=numcamposA; k++)
                     {
                           NODO C, D;
                           leer(datosA[i], &C, k);
                           leer(datosB[j], &D, k);
                           if(strcmp(C.dato,D.dato)!=0)
                           {
                                  comp = strcmp(C.dato,D.dato);
                                  break;
                           }
                     }
                }
                if(comp > 0)
                {
                        j++;
                }
                else
                {
                     if(comp < 0)
                     {
                            for(k=1; k<=numcamposA; k++)
                            {
                                 
                                   NODO C;
                                   leer(datosA[i], &C, k);
                                   agregar(datosC[numregistrosC], C, k);
                            }
                            numregistrosC++;
                            i++;
                     }
                     else
                     {
                         i++;
                         j++;
                     }
                }
                 
        }
        if(i< numregistrosA)
        {
              while(i < numregistrosA)
              {
                      for(k=1; k<=numcamposA; k++)
                      {
                               NODO C;
                               leer(datosA[i], &C, k);
                               agregar(datosC[numregistrosC], C, k);
                      }
                      numregistrosC++;
                      i++;
              }
        }
       
       timeb = clock();
        
        for(i=0; i<numregistrosC; i++)
      {
            printf("Registro %d:\n", i+1);
            for(j=1; j<=numcamposC; j++)
            {
                   NODO C;
                   NODOC D;
                   leer(datosC[i], &C, j);
                   leerc(metadatosA, &D, j); // colacando los mismos metadatos que A
                   printf("%s: %s\n", D.atributo, C.dato); 
            }
            printf("\n");
      }  
            
      for(i=0; i<numregistrosA; i++)
            limpiarlista(datosA[i]);
      for(i=0; i<numregistrosB; i++)
            limpiarlista(datosB[i]);     
      
      printf("\tTiempo total de algoritmo: %f seg.\n\n\t", (timeb-timea)/(double)CLOCKS_PER_SEC);
      printf("\tTiempo total de algoritmo con memoria: %f seg.\n\n\t", (clock()-timea)/(double)CLOCKS_PER_SEC); 
     
}

int algoritmo_equijoin(char* esquema1, char* esquema2, char* esquema3)
{
     FILE *pe;
     FILE *pem;
     FILE *pf;
     FILE *pfm;
     FILE *pg;
     FILE *pgm;
     FILE *ph;
     char c;
     int i;
     int j;
     int k;
     int l;
     int end=1; // bandera para esquema1
     int end2=1; // bandera para esquema2
     int tupla=0;
     int posc=0;
     clock_t timea;
     clock_t timeb;
     clock_t timec;
     int esq1;
     int esq2;
     int salir;
     int numcamposA=0;
     int numcamposB=0;
     int numcamposC=0;
     int numcamposD=0;
     int numregistrosA=0;
     int numregistrosB=0;
     int numregistrosC=0;
     int numregistrosD=0;
     int claveA;
     int claveB;
     int claveD;
     char condicionA[50];
     char condicionD[50];
     listac metadatosA;
     listac metadatosB;
     listac metadatosC;
     listac metadatosD;
     lista *datosA;
     lista *datosB;
     lista *datosC;
     lista *datosD;
     crearlistac(&metadatosA);
     crearlistac(&metadatosB);
     crearlistac(&metadatosC);
     crearlistac(&metadatosD);
     NODOC E;
     int contA = 0;
     int contB = 0;
     int contC = 0;
     int contD = 0;
     int datoA = 0;
     int datoD = 0;
     int pos;
     int igual;
     int encontrado;
     char *p = esquema3;
     char archivo[50];
     char archivom[50];
     char cadena[100];
     char llaveA[100];
     
     NODO A;
     NODO B;
     
     timea = clock();
     
     esq1 = buscaesquema(esquema1);
     esq2 = buscaesquema(esquema2);
     
     

     if(esq1==0 || esq2==0)
     {
           printf("No se encontro alguno de los esquemas\n");
           return 1;
     }
     
     strcpy(archivo, esquema1);
     strcat(archivo, ".txt");
     pe = fopen(archivo,"r");
     if(pe == NULL)
     {
            printf("Error al abrir archivo\n");
     }
     strcpy(archivo, esquema1);
     strcat(archivo, "m.txt");
     pem = fopen(archivo,"r");
     if(pem == NULL)
     {
            printf("Error al abrir archivo\n");
     }
     
     strcpy(archivo, esquema2);
     strcat(archivo, ".txt");
     pf = fopen(archivo,"r");
     if(pf == NULL)
     {
            printf("Error al abrir archivo\n");
     }
     strcpy(archivo, esquema2);
     strcat(archivo, "m.txt");
     pfm = fopen(archivo,"r");
     if(pfm == NULL)
     {
            printf("Error al abrir archivo\n");
     }
     
     
     printf("Condicion -> %s\n", esquema3);
     
     i=0;
     c = esquema3[i];
     while(c!='=')
     {
            condicionA[i] = c;
            i++;
            c = esquema3[i];
     }
     condicionA[i] = '\0';
     j = 0;
     
     p+=i+1;
     
     strcpy(cadena, p);
     strcpy(condicionD,cadena);

     printf("Elemento A: %s\n", condicionA);
     printf("Elemento D: %s\n", condicionD);
     // obtener datos
     // cargar a memoria
     
     encontrado = 0;
        
        while(!feof(pem)){
                        int i=0;
                        int z=0;
                        char longitud[10];
                        c=getc(pem);
                        while(c!='\\'){
                        E.atributo[i]=c;
                        i++;
                        c=getc(pem);
                        }
                        E.atributo[i]='\0';
                        E.atributo[i]='\0';
                             c=getc(pem);
                             E.tipo = (int)c;
                             E.tipo -= 48;
                             c=getc(pem); // lee '\'
                             while((longitud[z] = getc(pem))!='\\')
                                z++;
                             longitud[z]='\0';
                             E.longitud = atoi(longitud);
                             z=0; // reinicia la cadena longitud
                             strcpy(longitud,"");
                             c=getc(pem); // lee restriccion
                             E.restriccion = c;
                             c=getc(pem); // lee '\'
                             c=getc(pem);
                             if(c=='*')
                             {
                                    E.llave = 1;
                             }
                             else
                                    E.llave = 0; 
                        numcamposA++;
                        if(strcmp(condicionA,E.atributo)==0)
                        {
                              claveA = numcamposA;
                              datoA = E.tipo;
                              strcpy(llaveA, E.atributo);
                              encontrado = 1;
                        }
                        agregarc(metadatosA,E,numcamposA);
                        c=getc(pem);
        }
        fclose(pem);
        
        if(!encontrado)
        {
             printf("No existe alguno de los metadatos dados en la condicion\n");
             return 1;
        }
        
        encontrado = 0;
        
        while(!feof(pfm)){
                        int i=0;
                        int z=0;
                        char longitud[10];
                        c=getc(pfm);
                        while(c!='\\'){
                        E.atributo[i]=c;
                        i++;
                        c=getc(pfm);
                        }
                        E.atributo[i]='\0';
                        E.atributo[i]='\0';
                             c=getc(pfm);
                             E.tipo = (int)c;
                             E.tipo -= 48;
                             c=getc(pfm); // lee '\'
                             while((longitud[z] = getc(pfm))!='\\')
                                z++;
                             longitud[z]='\0';
                             E.longitud = atoi(longitud);
                             z=0; // reinicia la cadena longitud
                             strcpy(longitud,"");
                             c=getc(pfm); // lee restriccion
                             E.restriccion = c;
                             c=getc(pfm); // lee '\'
                             c=getc(pfm);
                             if(c=='*')
                                    E.llave = 1;
                             else
                                    E.llave = 0; 
                        numcamposD++;
                        if(strcmp(E.atributo,condicionD)==0)
                        {
                              if(datoA == E.tipo)
                              {
                                   claveD = numcamposD;
                                   encontrado = 1;
                              }
                        }
                        agregarc(metadatosD,E,numcamposD);
                        c=getc(pfm);
        }
        fclose(pfm);
      
      printf("Se obtuvieron metadatosD\n");
    
    ////////////////////////////// Verificando metadatos //////////////////////////////////
      if(encontrado == 0)
      {
            printf("No existe alguno de los metadatos dados en la condicion\n");
            return 1;
      }
      
      while(!feof(pe))
      {
            c = getc(pe);
            if(c=='\n')
                 numregistrosA++;
      }
      numregistrosA++;
      
      while(!feof(pf))
      {
           c = getc(pf);
           if(c=='\n')
                 numregistrosD++;
      }
      numregistrosD++;
      
      printf("Se realizo la correcta verificacion\n");
    
      datosA = (lista *)malloc(numregistrosA*sizeof(lista *));
      if(datosA == NULL)
      {
            printf("Bad memory allocation for datosA");
      }
      for(i=0; i<numregistrosA; i++)
            crearlista(&datosA[i]);
      datosD = (lista *)malloc(numregistrosD*sizeof(lista *));
      if(datosD == NULL)
      {
            printf("Bad memory allocation for datosB");
      }
      for(i=0; i<numregistrosD; i++)
            crearlista(&datosD[i]);      
      
      
      fseek(pe,0,0);
      fseek(pf,0,0);
      
      while(!feof(pe)){ 
                        for(j=1; j<numcamposA+1; j++){ 
                             c=getc(pe);
                             NODO F;
                             int i=0; 
                             while((c!='\\')&&(!feof(pe))&&(c!='\n')){
                                 F.dato[i]=c;
                                 i++;
                                 c=getc(pe);
                               
                             }
                             F.dato[i]='\0';
                             agregar(datosA[contA], F, j);
                             if(feof(pe))
                                 break;
                        }
                        contA++;
        }
        fclose(pe);
        
        numregistrosA = contA;
        
        
        contD = 0;
        
        while(!feof(pf)){ 
                        
                        for(j=1; j<numcamposD+1; j++){ 
                             c=getc(pf);
                             NODO F;
                             int i=0; 
                             while((c!='\\')&&(!feof(pf))&&(c!='\n')){
                                 F.dato[i]=c;
                                 i++;
                                 c=getc(pf);
                               
                             }
                             F.dato[i]='\0';
                             agregar(datosD[contD], F, j);
                             if(feof(pf))
                                 break;
                        }
                        contD++;
        }
        fclose(pf);
        
        numregistrosD = contD;
        
        // Ordenar tablas por algoritmo de seleccion
        for(i=0; i<numregistrosA-1; i++)
        {
              pos = i;
              for(j = i+1; j<numregistrosA; j++)
              {
                    NODO A, B;
                    leer(datosA[pos], &A, claveA);
                    leer(datosA[j], &B, claveA);
                    if(strcmp(A.dato, B.dato) > 0)
                          pos = j;
              }
              
              if(pos != i)
              {
                     lista aux;
                     aux = datosA[i];
                     datosA[i] = datosA[pos];
                     datosA[pos]=aux;
              }
        }
        
       for(i=0; i<numregistrosD-1; i++)
        {
              pos = i;
              for(j = i+1; j<numregistrosD; j++)
              {
                    NODO A, B;
                    leer(datosD[pos], &A, claveD);
                    leer(datosD[j], &B, claveD);
                    if(strcmp(A.dato, B.dato) > 0)
                          pos = j;
              }
              
              if(pos != i)
              {
                     lista aux;
                     aux = datosD[i];
                     datosD[i] = datosD[pos];
                     datosD[pos]=aux;
              }
        }
        
        numcamposC = numcamposA + numcamposD - 1;
        
        
        for(i=1; i<=numcamposA; i++)
        {
            NODOC A;
            leerc(metadatosA, &A, i);
            agregarc(metadatosC, A, i);
        }
        
        for(j=1; j<=numcamposD; j++)
        {
            int repetido = 0;
            NODOC B;
            leerc(metadatosD, &B, j);
            if(j == claveD)
                  continue;
            for(k=1; k<=numcamposA; k++)
            {
               NODOC A;
               leerc(metadatosA, &A, k);
               if(strcmp(A.atributo,B.atributo)==0){
                       NODOC C;
                       strcpy(cadena,esquema2);
                       strcat(cadena,".");
                       strcat(cadena,B.atributo);
                       strcpy(C.atributo,cadena);
                       agregarc(metadatosC, C, i);
                       i++;
                       repetido=1;
                       break;
               }
            }
            if(!repetido)
            {
                agregarc(metadatosC, B, i);
                i++;
            }
            
        }
        
        numregistrosC = numregistrosA + numregistrosD;
        datosC = (lista *)malloc(numregistrosC*sizeof(lista *));
        if(datosC == NULL)
        {
            printf("Bad memory allocation for datosB");
        }
        for(i=0; i<numregistrosC; i++)
            crearlista(&datosC[i]);
      
        
        /*for(i=1; i<=numcamposC; i++)
        {
             NODOC A;
             leerc(metadatosC, &A, i);
             printf("%s\n", A.atributo);
        }
        
        printf("%d %d", claveA, claveD);*/
        
        contA = 0;
        contC = 0;
        contD = 0;
        salir = 0;
       
        timeb = clock();
        
        if(numregistrosA > numregistrosD){
        
        for(i=0; i<numregistrosA; i++)
        {
             NODO B;
             if(i==0)
             {
                 leer(datosD[i], &B, claveD);
             }
             leer(datosA[i], &A, claveA);
             if(strcmp(A.dato,B.dato)==0)
             {
                       for(k=1; k<=numcamposA; k++)
                       {
                           NODO C;
                           leer(datosA[i], &C, k);
                           agregar(datosC[contC], C, k);
                       }
                       for(l=1; l<=numcamposD; l++)
                       {
                           if(l==claveD)
                               continue;
                           NODO C;
                           leer(datosD[contD], &C, l);
                           agregar(datosC[contC], C, k);
                           k++;
                       }
                       contC++;
             }
             while(strcmp(B.dato,A.dato) < 0)
             {
                 contD++;
                 if(contD >= numregistrosD)
                 {
                     salir = 1;
                     break;
                 }
                 leer(datosD[contD], &B, claveD); 
                 if(strcmp(A.dato,B.dato)==0)
                 {
                       for(k=1; k<=numcamposA; k++)
                       {
                           NODO C;
                           leer(datosA[i], &C, k);
                           agregar(datosC[contC], C, k);
                       }
                       for(l=1; l<=numcamposD; l++)
                       {
                           if(l==claveD)
                               continue;
                           NODO C;
                           leer(datosD[contD], &C, l);
                           agregar(datosC[contC], C, k);
                           k++;
                       }
                       contC++;
                 }
             }
             if(salir)
                 break;
          }
        }
        else
        {
            for(i=0; i<numregistrosA; i++)
        {
             NODO B;
             if(i==0)
             {
                 leer(datosD[i], &B, claveD);
             }
             leer(datosA[i], &A, claveA);
             if(strcmp(A.dato,B.dato)==0)
             {
                       for(k=1; k<=numcamposA; k++)
                       {
                           NODO C;
                           leer(datosA[i], &C, k);
                           agregar(datosC[contC], C, k);
                       }
                       for(l=1; l<=numcamposD; l++)
                       {
                           if(l==claveD)
                               continue;
                           NODO C;
                           leer(datosD[contD], &C, l);
                           agregar(datosC[contC], C, k);
                           k++;
                       }
                       contC++;
             }
             while(strcmp(B.dato,A.dato) <= 0)
             {
                 contD++;
                 if(contD >= numregistrosD)
                 {
                     salir = 1;
                     break;
                 }
                 leer(datosD[contD], &B, claveD); 
                 if(strcmp(A.dato,B.dato)==0)
                 {
                       for(k=1; k<=numcamposA; k++)
                       {
                           NODO C;
                           leer(datosA[i], &C, k);
                           agregar(datosC[contC], C, k);
                       }
                       for(l=1; l<=numcamposD; l++)
                       {
                           if(l==claveD)
                               continue;
                           NODO C;
                           leer(datosD[contD], &C, l);
                           agregar(datosC[contC], C, k);
                           k++;
                       }
                       contC++;
                 }
             }
             if(salir)
                 break;
          }
        }
        printf("\n\n");
        for(i=0; i<contC; i++)
        {
            for(j=1; j<=numcamposC; j++)
            {
                NODO E;
                NODOC F;
                leer(datosC[i], &E, j);
                leerc(metadatosC, &F, j);
                printf("%s: %s\n", F.atributo, E.dato);
            }
            printf("\n");
        }
        
        printf("\tTiempo total de algoritmo: %f seg.\n\n", (clock()-timeb)/(double)CLOCKS_PER_SEC);
        printf("\tTiempo total de algoritmo con memoria: %f seg.\n\n\t", (clock()-timea)/(double)CLOCKS_PER_SEC);
}
