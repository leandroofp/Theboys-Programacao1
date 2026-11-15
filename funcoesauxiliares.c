/*funções auxiliares*/

#include <stdlib.h>
#include <math.h>
#include "funcoesauxiliares.h"
#include "fprio.h"
#include "eventos.h"
#include "entidades.h"

int aleatorio(int min, int max)
{
    return (rand()%(max-min+1)+min);
}

int insere_lef (struct mundo_t *mundo, int tipo, int tempo, int heroi, int base, int missao, int invasao)
{
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

int distancia (struct posicao_t a, struct posicao_t b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return ((int) sqrt (dx*dx + dy*dy));
}

void remove_lef (struct mundo_t *mundo, int tipo, int heroi)
{
    struct fpnodo_t *ant = NULL;
    struct fpnodo_t *aux = mundo->lef->prim;
    struct fpnodo_t *remover;
    struct evento_t *ev;
    int doheroi;

    while (aux)
    {
        ev = aux->item;

        /*so os tipos 1,2,3,5,6,7,8 e 11 carregam um heroi de verdade no campo heroi.
        os outros (avisa, missao, invade...) tem 0 nesse campo*/
        doheroi = (aux->tipo >= 1 && aux->tipo <= 8 && aux->tipo != 4) || aux->tipo == 11;

        if (doheroi && ev->heroi == heroi && (!tipo || aux->tipo == tipo))
        {
            remover = aux;
            aux = aux->prox;
            if (ant)
                ant->prox = aux;
            else
                mundo->lef->prim = aux;
            if (remover == mundo->lef->fim)
                mundo->lef->fim = ant;
            mundo->lef->num--;
            free (remover->item);
            free (remover);
        }
        else
        {
            ant = aux;
            aux = aux->prox;
        }
    }
}
