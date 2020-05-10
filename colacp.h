#ifndef COLACP_H_INCLUDED
#define COLACP_H_INCLUDED

typedef void *TClave;
typedef void *TValor;

typedef struct entrada{
    TClave clave;
    TValor valor;
} *TEntrada;

typedef struct nodo {
    TEntrada entrada;
    struct nodo *padre;
    struct nodo *hijo_izquierdo;
    struct nodo *hijo_derecho;
} *TNodo;

typedef struct cola_con_prioridad{
    unsigned int cantidad_elementos;
    TNodo raiz;
} *TColaCP;
/**
*   Crea una cola vacia, utilizando como funcion de prioridad a f.
*   param int (*f)(TEntrada,TEntrada) funcion de prioridad, retorna -1
*   si el primer parámetro tiene menor prioridad que el segundo,
*   0 si ambos tienen la misma prioridad, y 1 si el segundo parámetro
*   tiene mayor prioridad que el primero.
*/
void crear_cola_cp(TColaCP *cola, int (*f)(TEntrada,TEntrada));

/**
*   Inserta la entrada ent de acuerdo a su prioridad en la cola.
*   param TColaCP cola La cola donde se insertará la entrada.
*   param TEntrada ent La entrada a insertar
*/
int cp_insertar(TColaCP cola, TEntrada ent);

/**
*   Elimina la entrada con mayor prioridad de la cola y la ordena adecuadamente.
*   param TColaCP cola La cola de donde se eliminará la entrada.
*   returns TEntrada La entrada de mayor prioridad eliminada.
*/
TEntrada cp_eliminar(TColaCP cola);

/**
*   Devuelve el tamaño de la cola.
*   param TColaCP cola La cola de la que se quiere saber el tamaño.
*/
int cp_size(TColaCP cola);

/**
*   Destruye toda la cola liberando su espacio en memoria.
*   param TColaCP La cola a destruir.
*/
int cp_destruir(TColaCP cola);

#endif // COLACP_H_INCLUDED
