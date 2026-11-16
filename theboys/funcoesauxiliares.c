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
    return (sqrt (dx*dx + dy*dy));
}

void remove_lef (struct mundo_t *mundo, int tipo, int heroi)
{
    struct fpnodo_t *ant = NULL;
    struct fpnodo_t *aux = mundo->lef->prim;
    struct fpnodo_t *remover;
    struct evento_t *ev;

    while (aux)
    {
        ev = aux->item;

        if (ev->heroi == heroi && (!tipo || aux->tipo == tipo)) //se o evento e do heroi, e é do tipo q foi passado ou tipo =0, remove
        {
            remover = aux;
            aux = aux->prox;
            /*se tem anterior, ele agora vai apontar pro proximo do removido, se nao, o proximo do removido passa a ser o primeiro*/
            if (ant)
                ant->prox = aux;
            else
                mundo->lef->prim = aux;
            // se for remover o ultimo evento da fila, o anteroir dele passa a ser o ultimo
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
