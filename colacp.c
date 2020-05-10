#include <stdlib.h>
#include <stdio.h>
#include "colacp.h"
#include "enums.h"
#define FALSE 0
#define TRUE 1
#define CCP_NO_INIT 4
#define POS_NULA NULL
#define ELE_NULO NULL

int (*funcionPrioridad) (TEntrada,TEntrada);

void crear_cola_cp(TColaCP *cola, int (*f)(TEntrada,TEntrada)){
    *cola=malloc(sizeof(struct cola_con_prioridad));
    (*cola)->cantidad_elementos= 0;
    (*cola)->raiz= NULL;
    funcionPrioridad=f;
}

void intercambiarEntradas (TNodo a, TNodo b){
    TEntrada aux;
    aux=a->entrada;
    a->entrada=b->entrada;
    b->entrada=aux;
}

void burbujearArriba(TColaCP cola, TNodo act){
    int resDePrioridad;

    if (act!=(cola->raiz)){
        resDePrioridad= funcionPrioridad(act->entrada,(act->padre)->entrada);
        if (resDePrioridad==1){
            intercambiarEntradas(act,act->padre);
            burbujearArriba(cola,act->padre);
            }
    }
}

TNodo buscarPadre(TColaCP *cola, int pos){
    TNodo padre;
    if (pos==1)
        padre=(*cola)->raiz;
    else{
        padre=buscarPadre(cola,pos/2);

        if(pos%2==0)
            padre=padre->hijo_izquierdo;
        else
            padre=padre->hijo_derecho;
        }
    return padre;
}

void insertarCascara(TColaCP cola, TNodo nodo_insertar){
        int cant;
        (cola->cantidad_elementos)++;
        cant=cola->cantidad_elementos;

        TNodo padre= buscarPadre(&cola, cant/2);

        nodo_insertar->padre=padre;
        if (cant%2==0){
            padre->hijo_izquierdo=nodo_insertar;
            padre->hijo_derecho=NULL;
            }
        else{
            padre->hijo_derecho=nodo_insertar;
            }
        burbujearArriba(cola,nodo_insertar);
}

int cp_insertar(TColaCP cola, TEntrada ent){
    TNodo nodo_insertar;
    if (cola==NULL)
            exit(CCP_NO_INIT);
    else{
        nodo_insertar=(TNodo)malloc(sizeof(TNodo));
        if (nodo_insertar == ELE_NULO)
            return FALSE;
        else{
            (nodo_insertar->entrada)= ent;
            if ((cola->cantidad_elementos)==0){
                nodo_insertar->padre=NULL;
                (cola->raiz)=nodo_insertar;
                (cola->cantidad_elementos)++;
                }
            else
                insertarCascara(cola,nodo_insertar);
            }
        }
    return TRUE;
}

void burbujearAbajo(TColaCP cola, TNodo act){
    TNodo hijo_mayor_prioridad;
    int res_prioridad_hijos,res_prioridad_fin;
    /*
        Busco el hijo con mayor prioridad, lo comparo con su padre,
        si el hijo tiene mayor prioridad que el padre, intercambio
        sus entradas y sigo burbujeando hacia arriba,
        sino termino la recursión.
    */

    if (act->hijo_izquierdo!=NULL){
        if (act->hijo_derecho!=NULL){
            res_prioridad_hijos=funcionPrioridad((act->hijo_izquierdo)->entrada,(act->hijo_derecho)->entrada);
            if (res_prioridad_hijos<0)
                hijo_mayor_prioridad=act->hijo_derecho;
            else
                hijo_mayor_prioridad=act->hijo_izquierdo;
                }
        else{
            hijo_mayor_prioridad=act->hijo_izquierdo;
            }
        res_prioridad_fin=funcionPrioridad(hijo_mayor_prioridad->entrada,act->entrada);
        if(res_prioridad_fin==1){
            intercambiarEntradas(act,hijo_mayor_prioridad);
            burbujearAbajo(cola,hijo_mayor_prioridad);
            }
    }
}

TEntrada cp_eliminar(TColaCP cola){
    /*
        Idea del algoritmo: Copiar la entrada de la raiz(la que quiero retornar),
        buscar el ultimo nodo de la heap (es decir, el de la derecha del ultimo nivel),
        intercambiar la entrada de este con la de la raiz, eliminar este ultimo nodo,
        y luego burbujear para abajo la raiz para acomodar la prioridad.
     */

    TEntrada res;
    TNodo padre,hijo;

    if (cola==NULL)
        exit(CCP_NO_INIT);

    res=(TEntrada)malloc(sizeof(TEntrada));
    *res=*((cola->raiz)->entrada);


    hijo=buscarPadre(&cola,cola->cantidad_elementos);

    if (cola->cantidad_elementos!=1){
        padre=hijo->padre;
        intercambiarEntradas(hijo,cola->raiz);
        if ((cola->cantidad_elementos)%2!=0){
            padre->hijo_derecho=NULL;
        }
        else{
            padre->hijo_izquierdo=NULL;
        }
    }
    else{   //caso quiero borrar la raiz
        cola->raiz=NULL;
    }

    (cola->cantidad_elementos)--;
    if (cola->cantidad_elementos>0)
        burbujearAbajo(cola,cola->raiz);
    return res;
}

int cp_size(TColaCP cola){
    if (cola==NULL)
        exit(CCP_NO_INIT);
    return cola->cantidad_elementos;
}

void cp_destruir_aux(TNodo act){
    /* Si el nodo actual tiene hijo izquierdo, llama recursivamente con este.*/
    if (act->hijo_izquierdo!=NULL)
        cp_destruir_aux(act->hijo_izquierdo);
    /* Si el nodo actual tiene hijo derecho, llama recursivamente con este.*/
    if (act->hijo_derecho!=NULL)
        cp_destruir_aux(act->hijo_derecho);
    free(act);
}

int cp_destruir(TColaCP cola){
    if (cola==NULL)
        exit(CCP_NO_INIT);
    if(cola->raiz!=NULL)
        cp_destruir_aux(cola->raiz);
    free(cola);
    return TRUE;

}
