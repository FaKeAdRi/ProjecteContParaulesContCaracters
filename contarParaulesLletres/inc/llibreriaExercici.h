#ifndef D8E5564E_A998_46E6_9A70_0B73488F1AF3
#define D8E5564E_A998_46E6_9A70_0B73488F1AF3
//incloure les llibreries que es necessiten
#include <stdbool.h>
    
#define MAXVECTOR 100
#define MAXLLETRE 27 

enum OPCIOMENUEX12
{
    SORTIR,
    CONTARCARACTERS,
    CONTARPARAULES
};

void mostrarOpcions();
void contarCaracters();
void mostrarCaracters(char[]);
void guardarCaracters(int[], char);
void pintarCaracters(int[]);


#endif /* D8E5564E_A998_46E6_9A70_0B73488F1AF3 */
