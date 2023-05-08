#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "rlutil.h"
#include <windows.h>
#include "llibreriaPropia.h"
#include "llibreriaExercici.h"
#include <string.h>

void mostrarOpcions()
{
    printf("0.-Sortir del programa\n");
    printf("1.-Contar els caracters\n");
    printf("2.-Contar paraules");
}

void contarCaracters()
{
    char fitxer[MAXVECTOR], ruta[MAXVECTOR] = "./fitxers/";

    printf("\nIntrodueix el nom del fitxer: ");
    entrarCadena(fitxer, sizeof(fitxer));
    strcat(ruta, fitxer);

    mostrarCaracters(ruta);
}

void mostrarCaracters(char ruta[])
{
    FILE *f;
    char car;
    int caracters[MAXLLETRE] = {0};

    f = fopen(ruta, "rt");

    if (f == NULL)
    {
        printf("\nEl fitxer %s no existeix.", ruta);
    }
    else
    {
        car = fgetc(f);
        car = tolower(car);

        while(feof(f) == 0)
        {
            guardarCaracters(caracters, car);

            car = fgetc(f);
            car = tolower(car);
        }

        pintarCaracters(caracters);
    }

    fclose(f);
}

void guardarCaracters(int caracters[], char car)
{
    char alfabeto[MAXLLETRE] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'ñ', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'}; 
    int i = 0;
    bool sortir = false;

    while (sortir == false)
    {
        if (car == alfabeto[i])
        {
            caracters[i]++;
            sortir = true;
        }

        i++;
    }
}

void pintarCaracters(int caracters[])
{
    char alfabeto[MAXLLETRE] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'ñ', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'}; 

    for (int i = 0; i < sizeof(alfabeto); i++)
    {
        if (caracters[i] > 0)
        {
            if (i > 0)
            {
                printf("\n");
            }

            printf("%c = %d", alfabeto[i], caracters[i]);
        }
    }
}

