#include "entidades.h"
#include "eventos.h"
#include "fprio.h"

void simulamundo(struct mundo_t *mundo)
{
    struct evento_t *ev;
    int fim = 0;
    eventosiniciais(mundo);

    while (!fim)
    {
        ev = fprio_retira(mundo->lef; ev.id; ev.tempo);
        mundo->relogio = ev.tempo;
        switch (ev.id)
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
                fim = 1;
                break;

        }

    }
}