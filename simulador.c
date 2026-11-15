#include <stdlib.h>
#include "entidades.h"
#include "eventos.h"
#include "fprio.h"
#include "simulador.h"


void simulamundo(struct mundo_t *mundo)
{
    struct evento_t *ev;
    int final = 0; 
    int tempo, tipo;

    if (!eventosiniciais(mundo))
        return;

    while (!final)
    {
        ev = fprio_retira(mundo->lef, &tipo, &tempo);
        if (!ev)
            return;
        mundo->relogio = tempo;
        switch (tipo)
        {
            case 1:
                chega(mundo,ev);
                break;

            case 2:
                espera(mundo,ev);
                break;

            case 3:
                desiste(mundo,ev);
                break;

            case 4:
                avisa(mundo,ev);
                break;
            
            case 5:
                entra(mundo,ev);
                break;
            
            case 6:
                sai(mundo,ev);
                break;
            
            case 7:
                viaja(mundo,ev);
                break;

            case 8:
                morre(mundo,ev);
                break;

            case 9:
                missao(mundo,ev);
                break;

            case 10:
                invade(mundo,ev);
                break;

            case 11:
                recupera_heroi(mundo,ev);
                break;

            case 12:
                reconstroi_base(mundo,ev);
                break;

            case 13:
                fim(mundo);
                final = 1;
                break;

        }
    free (ev);
    }
}