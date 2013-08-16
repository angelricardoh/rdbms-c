///////////////lista.c//////////////////
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

mensaje crearlista(lista *L){
        lista temp;
        temp=(lista)malloc(sizeof(CABECERA));
        if(temp==NULL)
               return NO_MEMORY;
        temp->NE=0;
        temp->I=NULL;
        *L=temp;
        return OK;
}

void limpiarlista(lista L){
        while(!vacia(L)){
               borrar(L,1);
        }
}

void destruirlista(lista *L){
        limpiarlista(*L);
        free(*L);
        *L=NULL;
}

booleano vacia(lista L){
        if(L!=NULL&&L->NE==0)
               return TRUE;
        return FALSE;
}

void copia(n D, NODO O){
        strcpy(D->dato, O.dato);
}

mensaje agregar(lista L, NODO E, int p){
        n temp, aux;
        int i;
        
        temp=(n)malloc(sizeof(NODO));
        if(temp==NULL)
               return NO_MEMORY;
        copia(temp,E);
        
        if(p<1)
               return POS_INVALIDA;
        if(p>L->NE)
               p=(L->NE+1);
        if(p==1||vacia(L)){
               temp->sig=L->I;
               L->I=temp;
        }else{
               for(aux=L->I,i=1; i<p-1; i++,aux=aux->sig);
                     temp->sig=aux->sig;
                     aux->sig=temp;
        }
        L->NE++;
        return OK;
}

mensaje borrar(lista L, int p){
        n aux, temp;
        int i;
        if(!(p>0&&p<=L->NE))
                return POS_INVALIDA;
               
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
                return OK;
}
        
mensaje modificar(lista L,NODO E, int p){
        n aux;
        int i;
        if(!(p>0&&p<=L->NE))
                return POS_INVALIDA;
                
        for(i=1, aux=L->I; i<p; i++,aux=aux->sig);
                copia(aux,E);
        return OK;
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
mensaje leer(lista L, n D,int p){
        n aux;
        int i;
        if(!(p>0&&p<=L->NE))
                return POS_INVALIDA;
                
        for(i=1, aux=L->I; i<p; i++,aux=aux->sig);
                copia(D,*aux);
        return OK;
}

