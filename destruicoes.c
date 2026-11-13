#include <stdlib.h>
#include "entidades.h"
#include "destruicoes.h"
#include "fprio.h"

void destroiheroi (struct heroi_t *heroi)
{
    if (!heroi)
        return;
    cjto_destroi(heroi->habilidades);
    free(heroi);
}

void destroibase (struct base_t *base)
{
    if (!base)
        return;
    while (fila_retira(base->espera));
    fila_destroi(base->espera);     
    free(base);
}

void destroimissao (struct missao_t *missao)
{
    if (!missao)
        return;
    cjto_destroi(missao->habilidades);
    free(missao);
}

void destroiinvasao (struct invasao_t *invasao)
{
    free(invasao); //caso seja null so atualiza o null em cima dele mesmo
}

void destroimundo (struct mundo_t *mundo)
{
    if (!mundo)
        return;

    for (int i = 0; i < mundo->qtndherois; i++)
        destroiheroi(mundo->herois[i]);
    for (int i = 0; i < mundo->qtndbases; i++)
        destroibase(mundo->bases[i]);
    for (int i = 0; i < mundo->qtndmissoes; i++)
        destroimissao(mundo->missoes[i]);
    for (int i = 0; i < mundo->qtndinvasoes; i++)
        destroiinvasao(mundo->invasoes[i]);

    fprio_destroi (mundo->lef);

    free(mundo);
}