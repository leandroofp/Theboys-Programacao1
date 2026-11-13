#include <stdlib.h>
#include "entidades.h"
#include "eventos.h"
#include "fprio.h"


void simulamundo(struct mundo_t *mundo)
{
    struct evento_t *ev = malloc (sizeof(evento_t));
    if (!ev)
        return;
    int final = 0; 
    int tempo, tipo;

    eventosiniciais(mundo);

    while (!final)
    {
        ev = fprio_retira(mundo->lef, &tipo, &tempo);
        if (!ev)
            return;
        mundo->relogio = tempo;
        switch (tipo)
        {
            case 1:
                chega();
                break;

            case 2:
                espera();
                break;

            case 3:
                desiste();
                break;

            case 4:
                avisa();
                break;
            
            case 5:
                entra();
                break;
            
            case 6:
                sai();
                break;
            
            case 7:
                viaja();
                break;

            case 8:
                morre();
                break;

            case 9:
                missao();
                break;

            case 10:
                invade();
                break;

            case 11:
                recupera_heroi();
                break;

            case 12:
                reconstroi_base();
                break;

            case 13:
                fim();
                final = 1;
                break;

        }
    free (ev);
    }
}