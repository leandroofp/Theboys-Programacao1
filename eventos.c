#include <stdio.h>
#include <stdlib.h>
#include "entidades.h"
#include "funcoesauxiliares.h"
#include "fprio.h"
#include "destruicoes.h"
#include "eventos.h"


void eventosiniciais (struct mundo_t *mundo)
{
    /* cada heroi chega em uma base em ate 3 dias */
    for (int i = 0; i < n_herois; i++)
    {
        int base = aleatorio (0, n_bases - 1);
        mundo->herois[i]->base = base;
        if (!insere_lef (mundo, 1, aleatorio (0, 4320), i, base, 0 , 0))
            return;
    }

    /* missoes ao longo de toda a simulacao */
    for (int i = 0; i < n_missoes; i++)
        if (!insere_lef (mundo, 9, aleatorio (0, t_fim_do_mundo), 0, 0, i, 0))
            return;

    /* invasoes depois dos 3 dias iniciais */
    for (int i = 0; i < n_invasoes; i++)
        if (!insere_lef (mundo, 10, aleatorio (4321, t_fim_do_mundo), 0, 0, 0, i))
            return;

    /* fim do mundo */
    if (!insere_lef (mundo, 13, t_fim_do_mundo, 0, 0, 0, 0))
        return;

    return;
}

void chega()
{
    printf("chega");
}

void espera()
{
    printf("espera");
}


void desiste()
{
    printf("desiste");
}


void avisa()
{
    printf("avisa");
}


void entra()
{
    printf("entra");
}


void sai()
{
    printf("sai");
}


void viaja()
{
    printf("viaja");
}


void morre()
{
    printf("morre");
}


void missao()
{
    printf("missao");
}


void invade()
{
    printf("invade");
}


void recupera_heroi()
{
    printf("recupera heroi");
}


void reconstroi_base ()
{
    printf("reconstroi base");
}

void fim()
{
    printf("chega");
}
