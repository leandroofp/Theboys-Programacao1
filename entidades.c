#include <stdlib.h>
#include "entidades.h"
#include "destruicoes.h"

/*funções auxiliares*/

int aleatorio(int min, int max)
{
    return (rand()%(max-min+1)+min);
}

/*funções do header*/

struct heroi_t *criaheroi (int num_heroi)
{
    struct heroi_t *novoheroi = malloc (sizeof(struct heroi_t));
    if (!novoheroi)
        return(NULL);

    novoheroi->id = num_heroi;
    novoheroi->exp = 0;
    novoheroi->paciencia = aleatorio(0,100);
    novoheroi->velocidade = aleatorio(50,5000);

    /*cria um conjunto de um a tres elementos, onde cada 
    um desses elementos é um número aleatorio entre as habilidades possiveis*/
    novoheroi->habilidades = cjto_aleat(aleatorio(1,3),n_habilidades);
    if (!novoheroi->habilidades)
    {
        free(novoheroi);
        return(NULL);
    }

    return (novoheroi);

}

struct base_t *criabase (int num_base)
{
    struct base_t *novabase = malloc (sizeof(struct base_t));
    if (!novabase)
        return(NULL);

    novabase->id = num_base;
    novabase->local.x = aleatorio(0,n_tamanho_mundo - 1);
    novabase->local.y = aleatorio(0,n_tamanho_mundo - 1);
    novabase->lotacao = aleatorio (3,10);
    novabase->presentes = cjto_cria (n_herois); //todos os herois podem estar nessa base, e seus ids variam de 0 até n_herois
    if (!novabase->presentes)
    {
        free(novabase);
        return(NULL);
    }
    novabase->espera = fila_cria();
    if (!novabase->espera)
    {
         cjto_destroi(novabase->presentes);
          free(novabase);
        return(NULL);
    }

    return (novabase);
}

struct missao_t *criamissao (int num_missao)
{
    struct missao_t *novamissao = malloc (sizeof(struct missao_t));
    if (!novamissao)
        return (NULL);
    novamissao->id = num_missao;
    novamissao->local.x = aleatorio(0,n_tamanho_mundo - 1);
    novamissao->local.y = aleatorio(0,n_tamanho_mundo - 1);
    novamissao->habilidades = cjto_aleat(aleatorio(6,10), n_habilidades);
    if (!novamissao->habilidades)
    {
        free (novamissao);
        return (NULL);
    }
    novamissao->perigo = aleatorio (0,100);
    return (novamissao);
}

struct invasao_t *criainvasao(int num_invasao)
{
    struct invasao_t *novainvasao = malloc (sizeof(struct invasao_t));
    if (!novainvasao)
        return (NULL);
    novainvasao->id = num_invasao;
    novainvasao->local.x = aleatorio(0,n_bases - 1);
    novainvasao->local.y = aleatorio(0,n_bases - 1);
    novainvasao->tpheroi = aleatorio(0,4320);
    novainvasao->tpbase = aleatorio (0,7200);
    return (novainvasao);
}

struct mundo_t *criamundo ()
{
    struct mundo_t *mundo = malloc (sizeof(struct mundo_t));
    if (!mundo)
        return(NULL);

    //inicializações
    mundo->relogio = 0; //tempo inicia em 0
    mundo->tam_mundo.x = n_tamanho_mundo - 1;
    mundo->tam_mundo.y = n_tamanho_mundo -1;
    mundo->qtndhabilidades = n_habilidades;
    mundo->qtndherois = 0;
    mundo->qtndbases = 0;
    mundo->qtndmissoes = 0;
    mundo->qtndinvasoes = 0;


     /*criação dos herois*/
    for (int i = 0; i<n_herois; i++)
    {
        mundo->herois[i] = criaheroi(mundo->qtndherois);
        if (!mundo->herois[i])
        {
            destroimundo(mundo);
            return(NULL);
        }
        mundo->herois[i]->estado = 1;
        mundo->qtndherois++;
    }

    /*criação das bases*/
      for (int i = 0; i<n_bases; i++)
    {
        mundo->bases[i] = criabase(mundo->qtndbases);
        if (!mundo->bases[i])
        {
            destroimundo(mundo);
            return(NULL);
        }
        mundo->bases[i]->estado = 1;
        mundo->qtndbases++;
    }

    /*cria missoes*/
      for (int i = 0; i<n_missoes; i++)
    {
        mundo->missoes[i] = criamissao(mundo->qtndmissoes);
        if (!mundo->missoes[i])
        {
            destroimundo(mundo);
            return(NULL);
        }
        mundo->qtndmissoes++;
    }

    /*cria invasoes*/
      for (int i = 0; i<n_invasoes; i++)
    {
        mundo->invasoes[i] = criainvasao(mundo->qtndinvasoes);
        if (!mundo->invasoes[i])
        {
            destroimundo(mundo);
            return(NULL);
        } 
        mundo->qtndinvasoes++;
    }
    
    return (mundo);

}