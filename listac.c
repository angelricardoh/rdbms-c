///////////////lista.c//////////////////
#include <stdio.h>
#include <stdlib.h>
#include "listac.h"

mensajec crearlistac(listac *L){
        listac temp;
        temp=(listac)malloc(sizeof(CABECERAC));
        if(temp==NULL)
               return NO_MEMORIA;
        temp->NE=0;
        temp->I=NULL;
        *L=temp;
        return BIEN;
}

void limpiarlistac(listac L){
        while(!vaciac(L)){
               borrarc(L,1);
        }
}

void destruirlistac(listac *L){
        limpiarlistac(*L);
        free(*L);
        *L=NULL;
}

booleanoc vaciac(listac L){
        if(L!=NULL&&L->NE==0)
               return VERDADERO;
        return FALSO;
}

void copiac(nc D, NODOC O){
        strcpy(D->atributo, O.atributo);
        D->tipo = O.tipo;
        D->longitud = O.longitud;
        D->restriccion = O.restriccion;
        D->llave = O.llave;
}

mensajec agregarc(listac L, NODOC E, int p){
        nc temp, aux;
        int i;
        
        temp=(nc)malloc(sizeof(NODOC));
        if(temp==NULL)
               return NO_MEMORIA;
        copiac(temp,E);
        
        if(p<1)
               return NUM_INVALIDO;
        if(p>L->NE)
               p=(L->NE+1);
        if(p==1||vaciac(L)){
               temp->sig=L->I;
               L->I=temp;
        }else{
               for(aux=L->I,i=1; i<p-1; i++,aux=aux->sig);
                     temp->sig=aux->sig;
                     aux->sig=temp;
        }
        L->NE++;
        return BIEN;
}

mensajec borrarc(listac L, int p){
        nc aux, temp;
        int i;
        if(!(p>0&&p<=L->NE))
                return NUM_INVALIDO;
               
        if(p==1)
        {
                aux=L->I->sig;
                free(L->I);
                L->I=aux;
        }else{
                for(i=1, aux=L->I; i<p-1; i++,aux=aux->sig);
                        temp=aux->sig->sig;
                        free(aux->sig);
                        aux->sig=temp;
                }
                L->NE--;
                return BIEN;
}
        
mensajec modificarc(listac L,NODOC E, int p){
        nc aux;
        int i;
        if(!(p>0&&p<=L->NE))
                return NUM_INVALIDO;
                
        for(i=1, aux=L->I; i<p; i++,aux=aux->sig);
                copiac(aux,E);
        return BIEN;
}

//void busqueda_impresion(lista L,char *c, int tipo){
        //int i;
        //int encontrado=0;
        //n aux;
        //system("cls");
        //printf(" i        Artista           Titulo                Album\n");
        //for(i=1, aux=L->I; i<=L->NE; i++,aux=aux->sig)
        //{
        //        if(tipo==1&&strcmp(c,aux->Artista)==0){
        //                printf("%-3d  %-15s  %-20.20s  %-20.25s\n", i, aux->Artista,aux->Titulo,aux->Album);
        //                encontrado=1;
        //        }
        //        if(tipo==2&&strcmp(c,aux->Titulo)==0){
               //         printf("%-3d  %-15s  %-20.20s  %-20.25s\n", i, aux->Artista,aux->Titulo,aux->Album);
               //         encontrado=1;        
             //   }
             //  if(tipo==3&&strcmp(c,aux->Album)==0){
               //         printf("%-3d  %-15s  %-20.20s  %-20.25s\n", i, aux->Artista,aux->Titulo,aux->Album);
              //          encontrado=1;        
             //   }
        //}
       // if(!encontrado){
       //         system("cls");
       //         printf("No se encontro o no existe el nombre de artista, titulo o album\n");
       // }               
//}
//
mensajec leerc(listac L, nc D,int p){
        nc aux;
        int i;
        if(!(p>0&&p<=L->NE))
                return NUM_INVALIDO;
                
        for(i=1, aux=L->I; i<p; i++,aux=aux->sig);
                copiac(D,*aux);
        return BIEN;
}

