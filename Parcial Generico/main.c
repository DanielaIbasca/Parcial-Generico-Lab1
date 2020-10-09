#include <stdio.h>
#include <stdlib.h>

#include "Gen_FBasic.h"

#define T 100

int main()
{
    int comprobarInicializacion;

    eGenerica lista[T];
    comprobarInicializacion = generica_inicializar(lista, T);

    if (comprobarInicializacion == 0)
    {
        printf("Todos los estados se han inicializado.\n\n");
    }
    else
    {
        printf("Ha ocurrido un error al inicializar estados.\n\n\n");
    }


    generica_inicializarConDatos(lista, T);

    system("pause");
    system("cls");


    char opcion;

    do
    {
        printf("(1) ALTA\n");
        printf("(2) BAJA\n");
        printf("(3) MODIFICACION\n");
        printf("(4) MOSTRAR\n");
        printf("(5) ORDENAR\n");
        printf("(6) Salir\n");

        printf("Debe elegir una opcion a realizar: ");
        fflush(stdin);
        scanf("%c", &opcion);

        while (opcion!='1' && opcion!='2' && opcion!='3' && opcion!='4' && opcion!='5' && opcion!='6')
        {
            printf("Error. Ha ingresado una opcion erronea!\n\n");
            printf("Debe elegir una opcion a realizar: ");
            fflush(stdin);
            scanf("%c", &opcion);
        }

        switch (opcion)
        {
        case '1':
            generica_alta(lista, T);
            break;

        case '2':
            generica_baja(lista, T);
            break;

        case '3':
            generica_modificacion(lista, T);
            break;

        case '4':
            generica_mostrarTodos(lista, T);
            break;

        case '5':
            generica_ordenar(lista, T, 0);
            break;

        case '6':
            break;

        default:
            printf("Error. Ha ingresado una opcion erronea.\n\n");
        }

        system("pause");
        system("cls");
    }
    while (opcion!= '6');

    return 0;
}
