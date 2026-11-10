#include <stdlib.h>
#include "entidades.h"

/*funções auxiliares*/

int n_aleatorio(int min, int max)
{
    return (rand()%(max-min+1)+min);
}

/*funções do header*/

struct heroi_t *criaheroi (int num_heroi)
{
    struct heroi_t *novoheroi = malloc (sizeof(struct heroi_t))
    if (!novoheroi)
        return(NULL);

    novoheroi->id = num_heroi;
    novoheroi->exp = 0;
    novoheroi->paciencia = n_aleatorio(0,100);
    novoheroi->velocidade = n_aleatorio(50,5000);

    /*cria um conjunto de um a tres elementos, onde cada 
    um desses elementos é um número aleatorio entre as habilidades possiveis*/
    novoheroi->habilidades = cjto_aleat(n_aleatorio(1,3),n_habilidades);
    if (!novoheroi->habilidades)
        return(NULL);

    //perguntar pro professor se é necessario inicializar estado e base;

}