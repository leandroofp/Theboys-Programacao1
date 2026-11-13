#include "entidades.h"
#include "funcoesauxiliares.h"
#include "fprio.h"

/*ARRUMAR FORMATACAO E DESTRUI CASO FPRIOINSERE*/
void eventosiniciais(struct mundo_t *mundo)
{
    mundo = criamundo();
    if (!mundo)
        return;
    struct evento_t *ev = malloc (sizeof (struct evento_t);
    if (!ev)
    { 
        destroimundo();
        return;
    }
    int tempo;
    /*cada heroi chega na base em até 3 dias*/
    for (int i = 0; i<n_herois; i++)
    {
        ev.heroi = mundo->herois[i]; //recebe id do heroi q chegara a base
        mundo->herois[i].base = aleatorio(0, n_bases - 1); //na struct heroi, define em qual base chegara
        ev.base = mundo->herois[i]->base; //recebe id da base q chegara
        tempo = aleatorio (0,4320);
        ev.id = 1; //chega

       //insere na lef o evento chega
        if (fprio_insere(mundo->lef; ev; &ev.id; tempo) == -1)
        { 
            destroimundo();
            return;
        }
    }


  /*missoes sao agendadas durante toda simulacao*/
    for (int i = 0; i<n_missoes; i++)
    {
        tempo = aleatorio (0, t_fim_do_mundo);
        ev.id = 9; //missao
        if (fprio_insere(mundo->lef; ev; &ev.id; tempo) == -1)
        { 
            destroimundo();
            return;
        }
    }

  /*invasoes sao agendadas para após os 3 dias iniciais*/
    for (int i = 0; i<n_invasoes; i++)
    {
        tempo = aleatorio (4321, t_fim_do_mundo);
        ev.id = 10; //invade
        if (fprio_insere(mundo->lef; ev; ev.id; tempo) == -1)
        {
            destroimundo();
            return;
        }
    }

    tempo = t_fim_do_mundo;
    ev.id = 13; //fim;
    if (fprio_insere(mundo->lef; ev; ev.id; tempo) == -1)
    {
        destroimundo();
        return;
    }
}