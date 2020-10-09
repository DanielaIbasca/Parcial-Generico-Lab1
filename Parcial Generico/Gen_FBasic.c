#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Gen_FBasic.h"


int generica_inicializar(eGenerica* list, int len)
{
    int estado;
    int i;
    if (list != NULL)
    {
        for (i=0; i<len; i++)
        {
            list[i].estado = 0;
        }

        estado = 0;
    }
    else
    {
        estado = -1;
    }

    return estado;
}



void generica_inicializarConDatos (eGenerica* list, int len)
{
    int i;

    int id[5] = {1,2,3,4,5};
    char nombre[5][50] = {"Agustin","Lautaro","Bruno","Cristian","Gonzalo"};
    char apellido[5][50] = {"Gomez","Coronel","Lopez","Diaz","Romero"};
    float salario[5] = {1800,2500,2400,1000,2000};
    int sector[5] = {3,8,6,4,7};

    for (i=0; i<5; i++)
    {
        list[i].id = id[i];
        strcpy (list[i].nombre, nombre[i]);
        strcpy (list[i].apellido, apellido[i]);
        list[i].salario = salario[i];
        list[i].sector = sector[i];
        list[i].estado = 1; // OCUPADO.
    }
}


int generica_buscarEspacio (eGenerica* list, int len)
{
    int indice = -1;
    int i;

    for (i=0; i<len; i++)
    {
        if (list[i].estado == 0)
        {
            indice = i;
            break;
        }
    }
    return indice;
}



int generica_encontrarPorId(eGenerica* list, int len, int id)
{
    for(int i=0; i<len; i++)
    {
        if(list[i].estado==1 && list[i].id==id)
        {
            return i;
        }
    }

    return -1;
}



void generica_mostrarUno (eGenerica list)
{
    printf("%d -- %10s %15s %15.2f %13d\n\n", list.id, list.nombre, list.apellido, list.salario, list.sector);
}



int generica_mostrarTodos(eGenerica* list, int len)
{
    int i;
    printf("\n\nID -- \t NOMBRE \t APELLIDO \t SALARIO \t SECTOR\n\n");
    for(i=0; i<len; i++)
    {
        if (list[i].estado == 1)
        {
            generica_mostrarUno(list[i]);
        }

    }
}



int generica_idAutoIncremental(eGenerica* list, int len)
{
    int retorno = 0;
    int i;
    if(len > 0 && list != NULL)
    {
        for(i=0; i<len; i++)
        {
            if(list[i].estado == 1)
            {
                if(list[i].id > retorno)
                {
                    retorno = list[i].id;
                }
            }
        }
    }
    return retorno+1;
}



int generica_alta(eGenerica* list,int len)
{
    int retorno = -1;

    int i;
    int k;

    char auxiliarNombre[50];
    char auxiliarApellido[50];
    char auxiliarSalario[50];
    char auxiliarSector[50];

    float salario;
    int sector;

    int id;

    i = generica_buscarEspacio(list, len);
    id = generica_idAutoIncremental(list, len);

    if(i>=0)
    {
        printf("Ingrese el nombre:");
        fflush(stdin);
        gets(auxiliarNombre);
        strcpy(list[i].nombre, auxiliarNombre);

        printf("Ingrese el apellido:");
        fflush(stdin);
        gets(list[i].apellido);

        printf("Ingrese el salario: ");
        fflush(stdin);
        gets(auxiliarSalario);
        //Valida que se permitan enteros y flotantes.
        while(esNumericoFloat(auxiliarSalario)==0)
        {
            printf("Usted ha ingresado un tipo de salario incorrecto. Ingrese nuevamente: ");
            fflush(stdin);
            gets(auxiliarSalario);
        }
        salario=atof(auxiliarSalario);
        list[i].salario = salario;

        printf("Ingrese el sector: ");
        fflush(stdin);
        gets(auxiliarSector);
        sector=atoi(auxiliarSector);
        list[i].sector=sector;

        list[i].estado=1;
        list[i].id=id;
        retorno=0;
    }
    return retorno;
}



int generica_baja(eGenerica* list,int len)
{
    int i;
    int id;
    char auxiliarId[50];
    int scanId;

    int opcion;

    int estado = -1; // No se encontro ID

    generica_mostrarTodos(list, len);


    printf("Ingrese la ID del empleado a remover: ");
    fflush(stdin);
    gets(auxiliarId);
    while(esNumerico(auxiliarId)==0)
    {
        printf("Usted ha ingresado un tipo de ID incorrecta. Ingrese nuevamente: ");
        fflush(stdin);
        gets(auxiliarId);
    }
    scanId=atoi(auxiliarId);


    for(i=0; i<len; i++)
    {
        if(scanId==list[i].id)
        {
            printf("\nDesea dar de baja el usuario? Ingrese 1 para SI // Ingrese 2 para NO.\n");
            scanf("%d",&opcion);

            switch(opcion)
            {
            case 1:
                list[i].estado = 0;
                list[i].id= 0;
                estado = 0; // Se modifico el empleado.
                break;

            case 2:
                estado = -2; // Se cancelo la baja.
                break;

            default:
                printf("\n\nUsted ingreso una opcion invalida. Vuelva a intentarlo nuevamente.\n");
                estado = -2;
                break;
            }
        }
    }

    return estado;
}



int generica_modificacion(eGenerica* list,int len)
{
    int id;
    int indice;
    int rt;

    int retorno=-2;

    char auxiliarId[20];

    if(len > 0 && list != NULL)
    {
        retorno=-1;

        generica_mostrarTodos(list, len);

        printf("Ingrese la ID del empleado: ");
        fflush(stdin);
        gets(auxiliarId);
        while(esNumerico(auxiliarId)==0)
        {
            printf("Usted ha ingresado un tipo de ID incorrecta. Ingrese nuevamente: ");
            fflush(stdin);
            gets(auxiliarId);
        }
        id=atoi(auxiliarId);


        indice=generica_encontrarPorId(list, len, id);


        if(indice>=0)
        {
            rt=generica_menuModificacion(list,indice);
            retorno=rt;
        }
        else
        {
            retorno = -2;
        }
    }
    return retorno;
}



int generica_menuModificacion(eGenerica* list,int indice)
{
    char auxiliarOpcion[30];
    int opcion;

    char auxiliarNombre[30];
    char auxiliarApellido[30];
    char auxiliarSalario[30];
    char auxiliarSector[30];

    float salario;
    int sector;


    int retorno=-1;


    printf("\nMENU DE MODIFICAR: \n\n");
    printf("(1) Nombre\n");
    printf("(2) Apellido\n");
    printf("(3) Salario\n");
    printf("(4) Sector\n");
    printf("Ingrese la opcion: ");
    fflush(stdin);
    gets(auxiliarOpcion);


    while(esNumerico(auxiliarOpcion)==0)
    {
        printf("Usted ha ingresado una opcion incorrecta. Ingrese nuevamente: ");
        fflush(stdin);
        gets(auxiliarOpcion);
    }
    opcion=atoi(auxiliarOpcion);



    if(opcion>=1&&opcion<=6)
    {
        switch(opcion)
        {
        case 1:

            printf("Ingrese el nuevo nombre del empleado:");
            fflush(stdin);
            gets(auxiliarNombre);
            while(esSoloLetras(auxiliarNombre)==0)
            {
                printf("Usted ha ingresado un tipo de nombre incorrecto. Ingrese nuevamente: ");
                fflush(stdin);
                gets(auxiliarNombre);
            }

            stringToUpper(auxiliarNombre);
            strcpy(list[indice].nombre, auxiliarNombre);
            printf("\n\nEL EMPLEADO HA SIDO MODIFICADO!\n\n");
            retorno=indice;
            break;

        case 2:

            printf("Ingrese el nuevo apellido del empleado:");
            fflush(stdin);
            gets(auxiliarApellido);
            while(esSoloLetras(auxiliarApellido)==0)
            {
                printf("Usted ha ingresado un tipo de apellido incorrecto. Ingrese nuevamente: ");
                fflush(stdin);
                gets(auxiliarApellido);
            }

            stringToUpper(auxiliarApellido);
            strcpy(list[indice].apellido, auxiliarApellido);
            printf("\n\nEL EMPLEADO HA SIDO MODIFICADO!\n\n");
            retorno=indice;
            break;

        case 3:

            printf("Ingrese el nuevo salario del empleado:");
            fflush(stdin);
            gets(auxiliarSalario);
            while(esNumerico(auxiliarSalario)==0)
            {
                printf("Usted ha ingresado un tipo de salario incorrecto. Ingrese nuevamente: ");
                fflush(stdin);
                gets(auxiliarSalario);
            }

            salario = atoi(auxiliarSalario);
            list[indice].salario = salario;
            printf("\n\nEL EMPLEADO HA SIDO MODIFICADO!\n\n");
            retorno=indice;
            break;

        case 4:

            printf("Ingrese el nuevo sector del empleado:");
            fflush(stdin);
            gets(auxiliarSector);
            while(esNumerico(auxiliarSector)==0)
            {
                printf("Usted ha ingresado un tipo de sector incorrecto. Ingrese nuevamente: ");
                fflush(stdin);
                gets(auxiliarSector);
            }
            sector = atoi(auxiliarSector);
            list[indice].sector = sector;
            printf("\n\nEL EMPLEADO HA SIDO MODIFICADO!\n\n");
            retorno=indice;
            break;

        default:
            retorno = -3;
            break;
        }
    }
    else
    {
        retorno = -3;
    }

    return retorno;
}


int generica_ordenar(eGenerica* list, int len, int order)
{
    eGenerica auxiliarGenerico;
    int i;
    int j;

    char auxiliarOpcion[50];
    int opcion;


    printf("\n\nComo desea ordenar la lista? 1 - POR APELLIDO / 2 - POR SECTOR: \n");
    fflush(stdin);
    gets(auxiliarOpcion);


    while(esNumerico(auxiliarOpcion)==0)
    {
        printf("Usted ha ingresado una opcion incorrecta. Ingrese nuevamente: ");
        fflush(stdin);
        gets(auxiliarOpcion);
    }
    opcion=atoi(auxiliarOpcion);


    switch(opcion)
    {
    case 1:
        for(i=0; i<len-1; i++)
        {
            for(j=i+1; j<len; j++)
            {

                if(strcmp(list[i].apellido,list[j].apellido)>order)
                {
                    auxiliarGenerico=list[i];
                    list[i]=list[j];
                    list[j]=auxiliarGenerico;
                }

            }
        }
        break;

    case 2:
        for(i=0; i<len-1; i++)
        {
            for(j=i+1; j<len; j++)
            {

                if(list[i].sector > list[j].sector)
                {
                    auxiliarGenerico=list[i];
                    list[i]=list[j];
                    list[j]=auxiliarGenerico;
                }
            }
        }
        break;

    default:
        printf("\n\nNO SE REALIZARON MODIFICACIONES. Se mostrara la lista sin ordenar.\n");
        break;

    }
}
