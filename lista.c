#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void crear_lista(TLista * lista){
    *lista=NULL;
}

int l_insertar(TLista * lista,TPosicion pos, TElemento elem){
    TPosicion p,nueva,sig;
    nueva=(TPosicion)malloc(sizeof(struct celda));
    if(nueva==NULL)
        return FALSE;
    nueva->elemento=elem;
    p=pos;
    if(pos==NULL)
        if(*lista==NULL)
            {nueva->celda_anterior=NULL;
            nueva->celda_siguiente=NULL;
            *lista=nueva;
           }
        else
            {p=*lista;
            p->celda_anterior=nueva;
            nueva->celda_siguiente=p;
            nueva->celda_anterior=NULL;
            *lista=nueva;}
    else
        if(p->celda_siguiente!=NULL)
            {
            sig=p->celda_siguiente;
            nueva->celda_siguiente=sig;
            sig->celda_anterior=nueva;
            p->celda_siguiente=nueva;
            nueva->celda_anterior=p;}
        else
            {
            nueva->celda_siguiente=NULL;
            nueva->celda_anterior=p;
            p->celda_siguiente=nueva;}

    return TRUE;
}

int l_eliminar(TLista * lista,TPosicion pos){
    if(*lista==NULL || pos==NULL)
        return FALSE;
    TPosicion p;
    TPosicion ant;
    TPosicion sig;
    p=pos;
    ant=p->celda_anterior;
    sig=p->celda_siguiente;
    if (pos==*lista){
        if (sig!=NULL){
            p=sig;
            p->celda_anterior=NULL;
            *lista=p;
        }
        else{
            *lista=NULL;
        }
    }
    else{
         if(sig==NULL)
            ant->celda_siguiente=NULL;
        else{
            sig->celda_anterior=ant;
            ant->celda_siguiente=sig;
        }
    }
    /*if(pos==*lista)
        {p=sig;
        p->celda_anterior=NULL;
        *lista=p;}
    else
        if(sig==NULL)
            ant->celda_siguiente=NULL;
        else
            {sig->celda_anterior=ant;
            ant->celda_siguiente=sig;}
*/
    free(pos);
    return TRUE;

}


TPosicion l_primera(TLista lista){
    TPosicion p;
    if(lista==NULL)
        return POS_NULA;
    p=lista;
    return p;
}

TPosicion l_ultima(TLista lista){
    TPosicion p;
    if(lista==NULL)
        return POS_NULA;
    p=lista;
    while(p->celda_siguiente!=NULL){
            p=p->celda_siguiente;
    }
    return p;
}

TPosicion l_anterior(TLista lista,TPosicion pos){
    if(lista==NULL || lista==pos || pos==NULL)
        return POS_NULA;

    return pos->celda_anterior;
}

TPosicion l_siguiente(TLista lista,TPosicion pos){
    if(lista==NULL || pos==NULL || pos==l_ultima(lista))
        return POS_NULA;
    return pos->celda_siguiente;
}

TElemento l_recuperar(TLista lista,TPosicion pos){
    if(lista==NULL || pos==NULL)
        return ELE_NULO;

    return pos->elemento;
}

int l_size(TLista lista){
    int cantidad;
    cantidad=0;
    if(lista==NULL)
        return cantidad;
    TPosicion p;
    p=lista;
    while(p!=NULL){
        p=p->celda_siguiente;
        cantidad++;
    }
    return cantidad;
}

int l_destruir(TLista * lista){
    if(*lista==NULL)
        return FALSE;
    TPosicion p;
    p=l_ultima(*lista);
    while(p!=NULL){
        TPosicion aux;
        aux=p;
        p=p->celda_anterior;
        free(aux);
    }
    return TRUE;
}
