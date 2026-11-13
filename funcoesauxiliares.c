/*funções auxiliares*/

#include <stdlib.h>
#include "funcoesauxiliares.h"

int aleatorio(int min, int max)
{
    return (rand()%(max-min+1)+min);
}
