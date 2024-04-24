#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definición de la estructura Tarea
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

Nodo *crearListaVacia()
{
    return NULL;
}

Tarea crearTarea(int *n)
{

    char *buff = malloc(sizeof(char) * 100);

    Tarea *NuevaTarea = (Tarea *)malloc(sizeof(Tarea));

    NuevaTarea->TareaID = (*n)++;

    printf("\nIngrese la descripcion: ");
    fflush(stdin);
    gets(buff);

    NuevaTarea->Descripcion = (char *)malloc((strlen(buff) + 1) * sizeof(char));
    strcpy(NuevaTarea->Descripcion, buff);
    fflush(stdin);
    NuevaTarea->Duracion = 10 + rand() % 91;

    free(buff);

    return *NuevaTarea;
}

Nodo *crearNodo(int *i)
{

    Nodo *nuevoNodo = malloc(sizeof(Nodo));

    nuevoNodo->T = crearTarea(i);
    nuevoNodo->Siguiente = NULL;

    return nuevoNodo;
}

void mostrarLista(Nodo **start)
{
    Nodo *aux = *start;

    while (aux != NULL)
    {

        printf("\nEl id es: %d", aux->T.TareaID);
        printf("\nLa descripcion: %s", aux->T.Descripcion);
        printf("\nLa duracion:%d\n", aux->T.Duracion);
        aux = aux->Siguiente;
    }
}

void InsertarNodo(Nodo **Start, Nodo *NuevoNodo)
{
    NuevoNodo->Siguiente = *Start;
    *Start = NuevoNodo;
}

Nodo buscarTareayMoverla(Nodo **startPendiente, int idBuscado)
{
    Nodo *Aux = *startPendiente;

    while (Aux && Aux->T.TareaID != idBuscado)
    {
        Aux = Aux->Siguiente;
    }

    return *Aux;
}

void EliminarNodo(Nodo **Start, int idBuscado)
{
    Nodo **aux = &(*Start);
    // Iteramos sobre la lista hasta encontrar el dato o alcanzar el final de la lista.

    while (*aux != NULL && (*aux)->T.TareaID != idBuscado)
    {
        aux = &(*aux)->Siguiente;
    }
    // Si encontramos el nodo con el dato especificado, lo eliminamos.

    if (*aux)
    {
        Nodo *temp = *aux;        // Guardamos el nodo a eliminar en una variable temporal.
        *aux = (*aux)->Siguiente; // Desvinculamos el nodo de la
        free(temp);               // Liberamos la memoria ocupada por el nodo.
    }
}

void buscarPorId(Nodo **T1, Nodo **T2, int id)
{

    Nodo *tarea = *T1;
    int bandera = 0;

    while (tarea != NULL && bandera == 0)
    {
        if (tarea->T.TareaID == id)
        {
            printf("\nEstamos en tareas pendientes\n");
            printf("\nEl id es: %d\n", tarea->T.TareaID);
            printf("\nLa descripcion es: \n");
            puts(tarea->T.Descripcion);
            printf("\nLa duracion:%d\n", tarea->T.Duracion);
            bandera = 1;
        }

        tarea = tarea->Siguiente;
    }

    tarea = *T2;

    while (tarea != NULL && bandera == 0)
    {
        if (tarea->T.TareaID == id)
        {
            printf("\nEstamos en tareas pendientes\n");
            printf("\nEl id es: %d\n", tarea->T.TareaID);
            printf("\nLa descripcion es: \n");
            puts(tarea->T.Descripcion);
            printf("\nLa duracion:%d\n", tarea->T.Duracion);
            bandera = 1;
        }

        tarea = tarea->Siguiente;
    }

    if (bandera == 0)
    {
        printf("\nNo se encontro\n");
    }

}

int main()
{

    int num = 1000;
    int agregarTarea;
    int buscarTarea;
    int idBuscado;

    srand(time(NULL));

    Nodo *startPendientes = crearListaVacia();
    Nodo *startRealizados = crearListaVacia();

    printf("Desea agregar nueva tarea? 1:si, 0:no: ");
    scanf("%d", &agregarTarea);

    while (agregarTarea == 1)
    {
        InsertarNodo(&startPendientes, crearNodo(&num));

        printf("Quiere agregar otra nueva tarea? 1:si, 0:no:");
        scanf("%d", &agregarTarea);
    }

    printf("\nAqui se muestra lo ingresado a tareas pendientes\n");
    mostrarLista(&startPendientes);

    printf("\nIngrese el id de la tarea que quiera pasar a realizada:\n ");
    scanf("%d", &idBuscado);

    Nodo auxNodo = buscarTareayMoverla(&startPendientes, idBuscado);
    InsertarNodo(&startRealizados, &auxNodo);

    EliminarNodo(&startPendientes, idBuscado);
    printf("\nSe mostrara sin el nodo id que buscamos\n");
    mostrarLista(&startPendientes);
    printf("\nSe transfirio a realizados\n");
    mostrarLista(&startRealizados);

    printf("\nIngresa un id para mostrar tarea: \n");
    scanf("%d",&idBuscado);

    buscarPorId(&startPendientes,&startRealizados,idBuscado);

    return 0;
    
}