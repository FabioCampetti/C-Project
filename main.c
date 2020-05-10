#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <tgmath.h>
#include "colacp.h"
#include "lista.h"
#define FALSE 0
#define TRUE 1

typedef struct ciudad{
    char *nombre;
    float pos_x;
    float pos_y;
}*TCiudad;

TLista cityList;
float act_x,act_y;
void leerOpcion();
void mostrar(int opc);
void reducirHoras();
void salir();

int funcion_prioridad_mayor(TEntrada e1, TEntrada e2){
    int *valor1,*valor2,res;
    valor1= (int*)e1->valor;
    valor2= (int*)e2->valor;
    if (*valor1==*valor2)
        res=0;
    else if(*valor1>*valor2)
        res=1;
    else
        res=-1;
    return res;
}

int funcion_prioridad_menor(TEntrada e1, TEntrada e2){
    int *valor1,*valor2,res;
    valor1= (int*)e1->valor;
    valor2= (int*)e2->valor;
    if (*valor1==*valor2)
        res=0;
    else if(*valor1<*valor2)
        res=1;
    else
        res=-1;
    return res;
}

int main(int args, char *argv[]){


    char *line,*token,*aux;
    FILE *cityFile;
    TCiudad cityActual;

    cityFile= fopen(argv[1],"r");

    if (cityFile==NULL){
        perror("Error al abrir el archivo.\n");
        exit(FALSE);
    }

    if (feof(cityFile)==FALSE){
        line= (char*) malloc( sizeof(char) * 50);
        line= fgets(line, 50, cityFile);

        token= strtok(line,";");
        act_x= atof(token);
        token= strtok(NULL,";");
        act_y= atof(token);

        free(line);
        }

    crear_lista(&cityList);

    while (feof(cityFile)==FALSE){
        line= (char*) malloc( sizeof(char) * 50);
        line= fgets(line, 50, cityFile);

        cityActual= (TCiudad) malloc(sizeof(TCiudad));

        token=strtok(line,";");
        aux=malloc(sizeof(char)*50);
        strcpy(aux,token);
        cityActual->nombre=aux;

        token= strtok(NULL,";");
        cityActual->pos_x= atof(token);

        token= strtok(NULL,";");
        cityActual->pos_y=atof(token);

        l_insertar(&cityList, cityList, cityActual);
        free(line);
    }

    free(cityFile);

    leerOpcion();

    return 0;
}

void leerOpcion(){
    int opcion;
    opcion=-1;

    printf("Elija la opción que requiera.\n");
    printf("1: mostrar ascendente.\n");
    printf("2: mostrar descedente.\n");
    printf("3: reducir horas de manejo. \n");
    printf("4: salir.\n");
    do{
        scanf("%d",&opcion);
        if(opcion<1||opcion>4)
            printf("Error: opcion incorrecta, elija una entre 1 y 4.\n");
    }while(opcion<1||opcion>4);

    printf("Eligió %d. \n",opcion);
    printf("------------------------------------------------------------------\n");
    printf("\n");

    switch(opcion){
        case 1: mostrar(0);
        case 2: mostrar(1);
        case 3: reducirHoras();
        case 4: salir();
    }
}

float *distancia(float x1, float y1, float x2, float y2){
    float *res;
    res= malloc(sizeof(float));
    *res=(fabs(x2-x1) + fabs(y2-y1));
    return res;
}

void mostrar(int opc){
    TColaCP cola;
    TCiudad city;
    TPosicion p;
    TEntrada entry;
    char *cityName;
    int i;
    int (*func)(TEntrada,TEntrada);
    cola=NULL;

    if (opc==0){
        func=funcion_prioridad_menor;
    }
    else{
        func=funcion_prioridad_mayor;
    }

    crear_cola_cp(&cola, func);
    p=cityList;
    while(p!=NULL){
        city=p->elemento;
        entry=(TEntrada)malloc(sizeof(TEntrada));
        entry->clave= city->nombre;
        entry->valor= distancia(act_x, act_y, city->pos_x, city->pos_y);
        cp_insertar(cola,entry);
        p=l_siguiente(cityList,p);
    }

    i=1;
    while (cp_size(cola)>0){
       entry=cp_eliminar(cola);
       cityName=(char*)entry->clave;
       printf("%d. %s.\n",i,cityName);
       i++;
    }
    cp_destruir(cola);
    free(entry);

    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("\n");

    leerOpcion();
}


void reducirHoras(){
    TPosicion pos_aux;
    TLista auxList;
    TColaCP cola_de_comparacion;
    TCiudad ciudad_actual;
    TEntrada entry;
    int i;
    float x_aux, y_aux;
    float  dist_total, *dist_actual;

    cola_de_comparacion=NULL;
    pos_aux=cityList;
    crear_lista(&auxList);

    while (pos_aux!=NULL){
        l_insertar(&auxList, auxList, pos_aux->elemento);
        pos_aux=l_siguiente(cityList,pos_aux);
    }

    x_aux=act_x;
    y_aux=act_y;

    pos_aux=l_primera(auxList);

    dist_total=0;
    i=1;
    while (l_size(auxList)>0){
        crear_cola_cp(&cola_de_comparacion,funcion_prioridad_menor);
        while(pos_aux!=NULL){
            ciudad_actual=(TCiudad)pos_aux->elemento;
            entry=(TEntrada) malloc(sizeof(TEntrada));
            entry->clave= pos_aux;
            entry->valor= distancia(x_aux, y_aux, ciudad_actual->pos_x, ciudad_actual->pos_y);
            cp_insertar(cola_de_comparacion,entry);
            pos_aux=l_siguiente(auxList, pos_aux);
            }
        entry=cp_eliminar(cola_de_comparacion);
        pos_aux= entry->clave;
        dist_actual= entry->valor;
        dist_total+= *dist_actual;
        ciudad_actual= (TCiudad) pos_aux->elemento;
        x_aux= ciudad_actual->pos_x;
        y_aux= ciudad_actual->pos_y;
        printf("%d. %s .\n", i, ciudad_actual->nombre);
        i++;
        l_eliminar(&auxList,pos_aux);
        pos_aux=l_primera(auxList);
    }

    printf("Total recorrido: %f.\n",dist_total);
    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("\n");
    leerOpcion();
}

void salir() {
    l_destruir(&cityList);
}
