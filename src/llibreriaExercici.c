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

        while (feof(f) == 0)
        {
            guardarCaracters(caracters, car);

            car = fgetc(f);
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
    FILE *f;
    char alfabeto[MAXLLETRE] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'ñ', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    f = fopen("./fitxers/loremContCar.txt", "wt");

    for (int i = 0; i < sizeof(alfabeto); i++)
    {
        if (caracters[i] > 0)
        {
            if (i > 0)
            {
                fputc('\n', f);
                printf("\n");
            }

            fprintf(f, "%c = %d", alfabeto[i], caracters[i]);
            printf("%c = %d", alfabeto[i], caracters[i]);
        }
    }

    fclose(f);
}

void contarParaules()
{
    char fitxer[MAXVECTOR], ruta[MAXVECTOR] = "./fitxers/";

    printf("\nIntrodueix el nom del fitxer: ");
    entrarCadena(fitxer, sizeof(fitxer));
    strcat(ruta, fitxer);

    crearFitxerTextSenseSignes(ruta);
    fitxerDesglosatParaules();
    mostrarParaules();
    pintarParaules();

    remove("./fitxers/loremAux.txt");
    remove("./fitxers/loremDesglosat.txt");
    remove("./fitxers/loremSenseRepetir.txt");
}

void crearFitxerTextSenseSignes(char ruta[])
{
    FILE *f;
    char car;

    f = fopen(ruta, "rt");

    if (f == NULL)
    {
        printf("\nEl fitxer %s no existeix.", ruta);
    }
    else
    {
        car = fgetc(f);

        while (feof(f) == 0)
        {
            crearFitxerSenseSignes(car);
            car = fgetc(f);
        }
    }

    fclose(f);
}

void crearFitxerSenseSignes(char car)
{
    FILE *f;

    f = fopen("./fitxers/loremAux.txt", "at");

    if (car != '.' && car != ',')
    {
        fputc(car, f);
    }

    fclose(f);
}

void fitxerDesglosatParaules()
{
    FILE *f;
    char car;

    f = fopen("./fitxers/loremAux.txt", "rt");

    car = fgetc(f);

    while (feof(f) == 0)
    {
        crearFitxerDesglsat(car);
        car = fgetc(f);
    }

    fclose(f);
}

void crearFitxerDesglsat(char car)
{
    FILE *f;

    f = fopen("./fitxers/loremDesglosat.txt", "at");

    if (car == ' ')
    {
        fputc('\n', f);
    }
    else
    {
        fputc(car, f);
    }

    fclose(f);
}

void mostrarParaules()
{
    FILE *f;
    char car, paraula[MAXPARAULA];
    bool existeix = false, enter = false;

    f = fopen("./fitxers/loremDesglosat.txt", "rt");

    if (f == NULL)
    {
        printf("\nEl fitxer loremDesglosat.txt no existeix.");
    }
    else
    {
        while (feof(f) == 0)
        {
            fgets(paraula, sizeof(paraula), f);
            eliminarEnter(paraula, sizeof(paraula));

            existeix = comprobarParaulaExisteix(paraula);

            if (existeix == false)
            {
                enter = fitxerParaulesSenseRepetir(paraula, enter);
            }
        }

        creacioFitxerContarParaules();

        fclose(f);
    }
}

bool comprobarParaulaExisteix(char paraula[])
{
    FILE *f;
    bool paraulaExisteix = false, trobat = false;
    char paraulaComp[MAXPARAULA];

    f = fopen("./fitxers/loremSenseRepetir.txt", "rt");

    if (f == NULL)
    {
        paraulaExisteix = false;
    }
    else
    {
        while (feof(f) == 0 && trobat == false)
        {
            fgets(paraulaComp, sizeof(paraulaComp), f);
            eliminarEnter(paraulaComp, sizeof(paraulaComp));

            if (stricmp(paraulaComp, paraula) == 0)
            {
                paraulaExisteix = true;
                trobat = true;
            }
            else
            {
                paraulaExisteix = false;
            }
        }
    }

    fclose(f);

    return paraulaExisteix;
}

bool fitxerParaulesSenseRepetir(char paraula[], bool enter)
{
    FILE *f;

    f = fopen("./fitxers/loremSenseRepetir.txt", "at");

    if (enter == true)
    {
        fputc('\n', f);
    }

    fputs(paraula, f);
    enter = true;

    fclose(f);

    return enter;
}

void creacioFitxerContarParaules()
{
    FILE *f;
    char paraula[MAXPARAULA];
    int contParaules = 0;
    bool enter = false;

    f = fopen("./fitxers/loremSenseRepetir.txt", "rt");

    while (feof(f) == 0)
    {
        fgets(paraula, sizeof(paraula), f);
        eliminarEnter(paraula, sizeof(paraula));

        contParaules = contarParaulesVector(paraula);
        enter = afegirInformacioFitxerContParaules(paraula, contParaules, enter);
        contParaules = 0;
    }

    fclose(f);
}

int contarParaulesVector(char paraula[])
{
    char paraulaComp[MAXPARAULA];
    int contParaules = 0;

    FILE *f;

    f = fopen("./fitxers/loremDesglosat.txt", "rt");

    while (feof(f) == 0)
    {
       fgets(paraulaComp, sizeof(paraulaComp), f);
       eliminarEnter(paraulaComp, sizeof(paraulaComp));

       if (strcmp(paraulaComp, paraula) == 0)
       {
            contParaules++;
       } 
    }

    fclose(f);

    return contParaules;
}

bool afegirInformacioFitxerContParaules(char paraula[], int contParaules, bool enter)
{
    FILE *f;

    f = fopen("./fitxers/loremContParaules.txt", "at");

    if (enter == true)
    {
        fputc('\n', f);
    }

    fprintf(f, "%-20s%d", paraula, contParaules);
    enter = true;

    fclose(f);

    return enter;
}

void pintarParaules()
{
    FILE *f;
    char frase[MAXVECTOR];

    f = fopen("./fitxers/loremContParaules.txt", "rt");

    while (feof(f) == 0)
    {
        fgets(frase, sizeof(frase), f);
        printf("%s", frase);
    }

    fclose(f);
}