#include <stdio.h>
#include <stdlib.h>
#include "entidades.h"
#include "funcoesauxiliares.h"
#include "fprio.h"
#include "destruicoes.h"
#include "eventos.h"
#include "conjunto.h"


int eventosiniciais (struct mundo_t *mundo)
{
    /* cada heroi chega em uma base em ate 3 dias */
    for (int i = 0; i < n_herois; i++)
    {
        int base = aleatorio (0, n_bases - 1);
        mundo->herois[i]->base = base;
        if (!insere_lef (mundo, 1, aleatorio (0, 4320), i, base, 0 , 0))
            return (0);
    }

    /* missoes ao longo de toda a simulacao */
    for (int i = 0; i < n_missoes; i++)
        if (!insere_lef (mundo, 9, aleatorio (0, t_fim_do_mundo), 0, 0, i, 0))
            return (0);

    /* invasoes depois dos 3 dias iniciais */
    int baseinvadida;
    for (int i = 0; i < n_invasoes; i++)
    {
        baseinvadida = mundo->invasoes[i]->local;
        if (!insere_lef (mundo, 10, aleatorio (4321, t_fim_do_mundo), 0, baseinvadida, 0, i))
            return (0);
    }

    /* fim do mundo */
    if (!insere_lef (mundo, 13, t_fim_do_mundo, 0, 0, 0, 0))
        return(0);

    return (1);
}

void chega (struct mundo_t *mundo, struct evento_t *ev)
{
    struct heroi_t *heroi = mundo->herois[ev->heroi];
    struct base_t *base = mundo->bases[ev->base];
    int tempoatual = mundo->relogio;
    int presentes = cjto_card (base->presentes);
    int tamfila = fila_tamanho (base->espera);
    int espera;

    heroi->base = base->id;

    if (presentes < base->lotacao && !tamfila)
        espera = 1;
    else
        espera = heroi->paciencia > (10 * tamfila);

    if (espera && base->estado)
    {
        printf ("%6d: CHEGA  HEROI %2d BASE %d (%2d/%2d) ESPERA\n",
             tempoatual, heroi->id, base->id, presentes, base->lotacao);
        insere_lef (mundo, 2, tempoatual, heroi->id, base->id, 0, 0);
    }
    else
    {
        printf ("%6d: CHEGA  HEROI %2d BASE %d (%2d/%2d) DESISTE\n",
             tempoatual, heroi->id, base->id, presentes, base->lotacao);
        insere_lef (mundo, 3, tempoatual, heroi->id, base->id, 0, 0);
    }
}

void espera (struct mundo_t *mundo, struct evento_t *ev)
{
    struct heroi_t *heroi = mundo->herois[ev->heroi];
    struct base_t *base = mundo->bases[ev->base];
    int tempoatual = mundo->relogio;

    printf ("%6d: ESPERA HEROI %2d BASE %d (%2d)\n",
         tempoatual, heroi->id, base->id, fila_tamanho (base->espera));

    /*a fila guarda o ponteiro do heroi*/
    fila_insere (base->espera, heroi);
    if (fila_tamanho (base->espera) > base->fila_max)
        base->fila_max = fila_tamanho (base->espera);
    insere_lef (mundo, 4, tempoatual, 0, base->id, 0, 0);
}

void desiste (struct mundo_t *mundo, struct evento_t *ev)
{
    int tempoatual = mundo->relogio;
    int destino = aleatorio (0, n_bases - 1);

    printf ("%6d: DESIST HEROI %2d BASE %d\n", tempoatual, ev->heroi, ev->base);
    insere_lef (mundo, 7, tempoatual, ev->heroi, destino, 0, 0);
}

void avisa (struct mundo_t *mundo, struct evento_t *ev)
{
    struct base_t *base = mundo->bases[ev->base];
    struct fila_nodo_t *nodo;
    struct heroi_t *heroi;
    int tempoatual = mundo->relogio;

    printf ("%6d: AVISA  PORTEIRO BASE %d (%2d/%2d) FILA [",
         tempoatual, base->id, cjto_card (base->presentes), base->lotacao);
    for (nodo = base->espera->prim; nodo; nodo = nodo->prox)
        printf (" %2d", ((struct heroi_t *) nodo->item)->id);
    printf (" ]\n");

    while (cjto_card (base->presentes) < base->lotacao && fila_tamanho (base->espera) > 0)
    {
        heroi = fila_retira (base->espera);
        cjto_insere (base->presentes, heroi->id);
        printf ("%6d: AVISA  PORTEIRO BASE %d ADMITE %2d\n", tempoatual, base->id, heroi->id);
        insere_lef (mundo, 5, tempoatual, heroi->id, base->id, 0, 0);
    }
}

void entra (struct mundo_t *mundo, struct evento_t *ev)
{
    struct heroi_t *heroi = mundo->herois[ev->heroi];
    struct base_t *base = mundo->bases[ev->base];
    int tempoatual = mundo->relogio;
    int tpb = 15 + heroi->paciencia * aleatorio (1, 20);

    printf ("%6d: ENTRA  HEROI %2d BASE %d (%2d/%2d) SAI %d\n",
         tempoatual, heroi->id, base->id, cjto_card (base->presentes), base->lotacao, tempoatual + tpb);
    insere_lef (mundo, 6, tempoatual + tpb, heroi->id, base->id, 0, 0);
}

void sai (struct mundo_t *mundo, struct evento_t *ev)
{
    struct base_t *base = mundo->bases[ev->base];
    int tempoatual = mundo->relogio;
    int destino = aleatorio (0, n_bases - 1);

    cjto_retira (base->presentes, ev->heroi);

    printf ("%6d: SAI    HEROI %2d BASE %d (%2d/%2d)\n",
         tempoatual, ev->heroi, base->id, cjto_card (base->presentes), base->lotacao);

    insere_lef (mundo, 7, tempoatual, ev->heroi, destino, 0, 0);
    insere_lef (mundo, 4, tempoatual, 0, base->id, 0, 0);
}

void viaja (struct mundo_t *mundo, struct evento_t *ev)
{
    struct heroi_t *heroi = mundo->herois[ev->heroi];
    struct base_t *origem = mundo->bases[heroi->base];
    struct base_t *destino = mundo->bases[ev->base];
    int tempoatual = mundo->relogio;
    int dist = distancia (origem->local, destino->local);
    int duracao = dist / heroi->velocidade;

    printf ("%6d: VIAJA  HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n",
         tempoatual, heroi->id, origem->id, destino->id, dist, heroi->velocidade, tempoatual + duracao);
    insere_lef (mundo, 1, tempoatual + duracao, heroi->id, destino->id, 0, 0);
}

void morre (struct mundo_t *mundo, struct evento_t *ev)
{
    struct heroi_t *heroi = mundo->herois[ev->heroi];
    struct base_t *base = mundo->bases[heroi->base];
    int tempoatual = mundo->relogio;

    printf ("%6d: MORRE  HEROI %2d missAO %d\n", tempoatual, heroi->id, ev->missao);

    cjto_retira (base->presentes, heroi->id);
    heroi->estado = 0;
    mundo->mortes++;

    /*morto nao tem mais eventos: isso inclui o recupera_heroi, entao ele nunca volta a ficar ativo*/
    remove_lef (mundo, 0, heroi->id);
    insere_lef (mundo, 4, tempoatual, 0, base->id, 0, 0);
}

void missao (struct mundo_t *mundo, struct evento_t *ev)
{
    struct missao_t *missao = mundo->missoes[ev->missao];
    struct heroi_t *heroi;
    struct base_t *base;
    struct cjto_t *uniao;
    struct cjto_t *aux;
    struct cjto_t *uniaoescolhida = NULL;
    int tempoatual = mundo->relogio;
    int dist[n_bases];
    int visitada[n_bases];
    int escolhida = -1;
    int prox;
    int risco;

    missao->tentativas++;
    printf ("%6d: MISSAO %d TENT %d HAB REQ: ", tempoatual, missao->id, missao->tentativas);
    printf ("[ ");
    cjto_imprime (missao->habilidades);
    printf (" ]\n");

    for (int i = 0; i < n_bases; i++)
    {
        dist[i] = distancia (mundo->bases[i]->local, missao->local);
        visitada[i] = 0;
    }

    /*analisa as bases da mais proxima para a mais distante, ate achar uma apta*/
    for (int k = 0; k < n_bases && escolhida < 0; k++)
    {
        prox = -1;
        for (int i = 0; i < n_bases; i++)
            if (!visitada[i] && (prox < 0 || dist[i] < dist[prox]))
                prox = i;
        visitada[prox] = 1;

        base = mundo->bases[prox];
        if (!base->estado)
            continue;

        printf ("%6d: MISSAO %d BASE %d DIST %d HEROIS [", tempoatual, missao->id, base->id, dist[prox]);
        for (int id = 0; id < n_herois; id++)
            if (cjto_pertence (base->presentes, id) == 1)
                printf (" %d", id);
        printf ("\n");

        uniao = cjto_cria (n_habilidades);
        if (!uniao)
            return;

        for (int id = 0; id < n_herois; id++)
        {
            if (cjto_pertence (base->presentes, id) != 1)
                continue;
            heroi = mundo->herois[id];
            printf ("%6d: MISSAO %d HAB HEROI %2d: ", tempoatual, missao->id, id);
            printf ("[ ");
            cjto_imprime (heroi->habilidades);
             printf (" ]\n");

            /*so herois ativos entram na uniao*/
            if (heroi->estado)
            {
                aux = cjto_uniao (uniao, heroi->habilidades);
                if (aux)
                {
                    cjto_destroi (uniao);
                    uniao = aux;
                }
            }
        }

        printf ("%6d: MISSAO %d UNIAO HAB BASE %d: ", tempoatual, missao->id, base->id);
        printf ("[");
        cjto_imprime (uniao);
        printf ("]\n");

        if (cjto_contem (uniao, missao->habilidades) == 1)
        {
            escolhida = prox;
            uniaoescolhida = uniao;
        }
        else
            cjto_destroi (uniao);
    }

    if (escolhida >= 0)
    {
        base = mundo->bases[escolhida];
        mundo->missoes_cumpridas++;
        base->missoes++;

        printf ("%6d: MISSAO %d CUMPRIDA BASE %d HABS: ", tempoatual, missao->id, base->id);
        printf ("[");
        cjto_imprime (uniaoescolhida);
        printf ("]\n");
        cjto_destroi (uniaoescolhida);

        for (int id = 0; id < n_herois; id++)
        {
            if (cjto_pertence (base->presentes, id) != 1)
                continue;
            heroi = mundo->herois[id];
            if (!heroi->estado)
                continue;

            risco = missao->perigo / (heroi->paciencia + heroi->exp + 1);
            if (risco > aleatorio (0, 30))
                insere_lef (mundo, 8, tempoatual, heroi->id, base->id, missao->id, 0);
            else
                heroi->exp++;
        }
    }
    else
    {
        printf ("%6d: MISSAO %d IMPOSSIVEL\n", tempoatual, missao->id);
        insere_lef (mundo, 9, tempoatual + 24 * 60, 0, 0, missao->id, 0);
    }
}

void invade (struct mundo_t *mundo, struct evento_t *ev)
{
    struct invasao_t *invasao = mundo->invasoes[ev->invasao];
    struct base_t *base = mundo->bases[ev->base];
    struct heroi_t *heroi;
    int tempoatual = mundo->relogio;
    int primeiro = 1;

    /*invasao em base inativa e ignorada*/
    if (!base->estado)
        return;
    
    mundo->invasoes_realizadas++;

    printf ("%6d: INVADE   BASE %d   INVADE %d\n", tempoatual, base->id, invasao->id);
    printf ("%6d: INVADE %d BASE %d HEROIS INATIVOS [", tempoatual, invasao->id, base->id);

    for (int id = 0; id < n_herois; id++)
    {
        if (cjto_pertence (base->presentes, id) != 1)
            continue;
        heroi = mundo->herois[id];

        printf ("%s%d", primeiro ? "" : ", ", id);
        primeiro = 0;

        heroi->estado = 0;
        insere_lef (mundo, 11, tempoatual + invasao->tpheroi, heroi->id, 0, 0, 0);

        /*cancela a saida (e a entrada, se ainda nao aconteceu) e manda o heroi sair tempoatual*/
        remove_lef (mundo, 6, heroi->id);
        remove_lef (mundo, 5, heroi->id);
        insere_lef (mundo, 6, tempoatual, heroi->id, base->id, 0, 0);
    }
    printf ("]\n");

    base->estado = 0;
    insere_lef (mundo, 12, tempoatual + invasao->tpbase, 0, base->id, 0, 0);
    printf ("%6d: INVADE %d BASE %d INATIVA\n", tempoatual, invasao->id, base->id);
}

void recupera_heroi (struct mundo_t *mundo, struct evento_t *ev)
{
    mundo->herois[ev->heroi]->estado = 1;
}

void reconstroi_base (struct mundo_t *mundo, struct evento_t *ev)
{
    mundo->bases[ev->base]->estado = 1;
}

void fim (struct mundo_t *mundo)
{
    struct heroi_t *heroi;
    struct base_t *base;
    int min = 0;
    int max = 0;
    int soma = 0;
    int tentadas = 0;
    int t;

    printf ("%6d: FIM\n\n", mundo->relogio);

    for (int i = 0; i < n_herois; i++)
    {
        heroi = mundo->herois[i];
        printf ("HEROI %2d %s PAC %3d VEL %4d EXP %4d HABS [ ",
                heroi->id, heroi->estado ? "VIVO " : "MORTO", heroi->paciencia,
                heroi->velocidade, heroi->exp);
        cjto_imprime (heroi->habilidades);
        printf (" ]\n");
    }
    printf (" ]\n");

    for (int i = 0; i < n_bases; i++)
    {
        base = mundo->bases[i];
        printf ("BASE %2d LOT %2d FILA MAX %2d MISSOES %d\n",
                base->id, base->lotacao, base->fila_max, base->missoes);
    }
    printf (" ]\n");

    /*so entram na conta as missoes que foram tentadas pelo menos uma vez*/
    for (int i = 0; i < n_missoes; i++)
    {
        t = mundo->missoes[i]->tentativas;
        if (!t)
            continue;
        if (!tentadas || t < min)
            min = t;
        if (t > max)
            max = t;
        soma += t;
        tentadas++;
    }

    printf ("EVENTOS TRATADOS: %d\n", mundo->eventos_tratados);
    printf ("MISSOES CUMPRIDAS: %d/%d (%.1f%%)\n", mundo->missoes_cumpridas,
            n_missoes, 100.0 * mundo->missoes_cumpridas / n_missoes);
    printf ("INVASÕES REALIZADAS: %d/%d (%.1f%%)\n", mundo->invasoes_realizadas,
            n_invasoes, 100.0 * mundo->invasoes_realizadas / n_invasoes);
    printf ("TENTATIVAS/MISSAO: MIN %d, MAX %d, MEDIA %.1f\n", min, max,
            tentadas ? (double) soma / tentadas : 0.0);
    printf ("TAXA MORTALIDADE: %.1f%%\n", 100.0 * mundo->mortes / n_herois);
}
