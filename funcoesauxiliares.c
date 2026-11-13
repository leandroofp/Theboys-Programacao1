/*funções auxiliares*/

#include <stdlib.h>
#include "funcoesauxiliares.h"
#include "fprio.h"

int aleatorio(int min, int max)
{
    return (rand()%(max-min+1)+min);
}

int insere_lef (struct mundo_t *mundo, int tipo, int tempo, int heroi, int base, int missao, int invasao)
    struct evento_t *ev = malloc (sizeof (struct evento_t));
    if (!ev)
        return (0);

    ev->id = tipo;
    ev->heroi = heroi;
    ev->base = base;
    ev->missao = missao;
    ev->invasao = invasao;
    if (fprio_insere (mundo->lef, ev, tipo, tempo) == -1)
    {
        free (ev);
        return (0);
    }
    return (1);
}
