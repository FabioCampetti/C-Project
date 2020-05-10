#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#define FALSE  0 //valor logico falso
#define TRUE  1 //valor logico verdadero
#define LST_NO_INI  2 //intento de acceso invalido sobre lista sin inicializar
#define LST_VAC  3 //intento de acceso invalido sobre lista vacia
#define POS_NULA  NULL //posicion nula
#define ELE_NULO  NULL //elemento nulo

typedef void * TElemento;
struct celda{
    TElemento elemento;
    struct celda *celda_anterior;
    struct celda *celda_siguiente;
    };
typedef struct celda * TLista;
typedef struct celda * TPosicion;
void crear_lista(TLista * lista);
int l_insertar(TLista * lista, TPosicion pos,TElemento elem);
int l_eliminar(TLista * lista, TPosicion pos);
TPosicion l_primera(TLista lista);
TPosicion l_ultima(TLista lista);
TPosicion l_anterior(TLista lista, TPosicion pos);
TPosicion l_siguiente(TLista l, TPosicion pos);
TElemento l_recuperar(TLista l, TPosicion pos);
int l_size(TLista l);
int l_destruir(TLista * lista);

#endif // LISTA_H_INCLUDED
