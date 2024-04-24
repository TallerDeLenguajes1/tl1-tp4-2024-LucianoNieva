#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct Tarea Tarea;
typedef struct Nodo Nodo;

typedef struct Tarea
{
    int TareaID;       // Número autoincremental comenzando en 1000
    char *Descripcion; // Descripción de la tarea (cadena de caracteres)
    int Duracion;      // Duración de la tarea (entre 10 y 100)
} Tarea;

typedef struct Nodo
{
    Tarea T;
    struct Nodo *Siguiente;

} Nodo;

// Funciones

Nodo *crearListaVacia();
Tarea cargarTarea(int *n);
void mostrarListaPendiente(Nodo **start);
void mostrarListaRealizada(Nodo **start);
Nodo *crearNodo(int *n);
void insertarNodo(Nodo **start, Nodo *nuevoNodo);
Nodo buscarTarea(Nodo **start, int id);
void eliminarNodo(Nodo **start, int id);

int main()
{

    int numero = 1000;
    int condicion = 0;
    int cambiarTarea;

    Nodo *startPendientes = crearListaVacia();
    Nodo *startRealizadas = crearListaVacia();

    do
    {

        insertarNodo(&startPendientes, crearNodo(&numero));
        puts("\nDeseas agregar otra Tarea Pendiente:");
        puts("1) SI");
        puts("2) NO");
        fflush(stdin);
        scanf("%d", &condicion);

    } while (condicion == 1);

    mostrarListaPendiente(startPendientes);

    puts("\nElija la tarea de la Lista de Pendientes que desea pasar a la Lista de Realizadas(Ingrese ID): ");
    fflush(stdin);
    scanf("%d", &cambiarTarea);

    Nodo tareaEncontrada = buscarTarea(&startPendientes, cambiarTarea);
    insertarNodo(startRealizadas, &tareaEncontrada);
    eliminarNodo(startPendientes, cambiarTarea);

    mostrarListaPendiente(startPendientes);
    mostrarListaRealizada(startRealizadas);

    return 0;
}

Nodo *crearListaVacia()
{
    return NULL;
    // return NULL; Si lo hago asi, se rompe, pero asi esta en la teoria
}

Tarea cargarTarea(int *n)
{

    Tarea nuevaTarea;

    nuevaTarea.TareaID = (*n)++;

    nuevaTarea.Descripcion = (char *)malloc(sizeof(char) * MAX);
    printf("\nIngrese la descripcion de la tarea: ");
    fflush(stdin);
    gets(nuevaTarea.Descripcion);
    nuevaTarea.Descripcion = (char *)realloc(nuevaTarea.Descripcion, sizeof(char) * strlen(nuevaTarea.Descripcion + 1));

    nuevaTarea.Duracion = 10 + rand() % 91;

    // printf("\nDatos de la tarea ingresada\n");
    // printf("\nID: %d", (*n)++);
    // printf("\nDescripcion: %s", nuevaTarea.Descripcion);
    // printf("\nDuracion: %d", nuevaTarea.Duracion);

    return nuevaTarea;
}

Nodo *crearNodo(int *n)
{

    Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));

    nuevoNodo->T = cargarTarea(n);
    nuevoNodo->Siguiente = NULL;

    return nuevoNodo;
}

void insertarNodo(Nodo **start, Nodo *nuevoNodo)
{

    nuevoNodo->Siguiente = *start;
    *start = nuevoNodo;
}

void mostrarListaPendiente(Nodo **start)
{

    Nodo *aux = *start;

    while (aux != NULL)
    {

        printf("\nInformacion de Tarea Pendiente\n");
        printf("\nID: %d", aux->T.TareaID);
        printf("\nDescripcion: %s", aux->T.Descripcion);
        printf("\nDuracion: %d", aux->T.Duracion);

        aux = aux->Siguiente;
    }
}

void mostrarListaRealizada(Nodo **start)
{

    Nodo *aux = *start;

    while (aux != NULL)
    {

        printf("\n\nInformacion de Tarea Realizada\n");
        printf("\nID: %d", aux->T.TareaID);
        printf("\nDescripcion: %s", aux->T.Descripcion);
        printf("\nDuracion: %d", aux->T.Duracion);

        aux = aux->Siguiente;
    }
}

Nodo buscarTarea(Nodo **start, int id)
{

    Nodo *aux = *start;

    while (aux && aux->T.TareaID != id)
    {
        aux = aux->Siguiente;
    }

    return *aux;
}

void eliminarNodo(Nodo **start, int id)
{

    Nodo **aux = start;

    while (*aux && (*aux)->T.TareaID != id)
    {
        aux = &(*aux)->Siguiente;
    }

    if (*aux)
    {
        Nodo *temp = *aux;
        *aux = (*aux)->Siguiente;
        free(temp);
    }
}