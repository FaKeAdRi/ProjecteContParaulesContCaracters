#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "rlutil.h"
#include <windows.h>
#include "llibreriaPropia.h"
#include "llibreriaExercici.h"
#include <string.h>

int main()
{
	SetConsoleCP(1252);
	SetConsoleOutputCP(1252);
	srand(time(NULL));
	
	int opcio = 100;

	remove("./fitxers/loremContParaules.txt");

	while (opcio != 0)
	{
		mostrarOpcions(); 

		printf("\n\nEscriu quina opcio vols:\n");
		opcio = demanaNumeroEntreDosValors(0, 2);

		switch(opcio)
		{
			case SORTIR: printf("\nEl programa ha finalitzat."); break;
			case CONTARCARACTERS: contarCaracters(); break;
			case CONTARPARAULES: contarParaules();
		}

		printf("\n\n");
	}
	
	acabament();
	return 0;
}