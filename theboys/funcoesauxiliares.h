#ifndef funcoesauxiliares_h
#define funcoesauxiliares_h

#include "eventos.h"
#include "entidades.h"

/*devolve um numero aleatorio entre min e max*/
int aleatorio(int min, int max);

/*atribui ao evento todos seus campos correspondentes, ao caso de nao ser utilizado 
nesse evento especifico, por exemplo, campo missao em um evento chega, é passado como
parametro um 0, para inicializar  e evitar lixo de memoria nesses campos. 
alem disso, insere na lef o evento, alocando-o na memoria. 
-Retorna  1 em caso de sucesso de inserção e 0 em caso de erro*/
int insere_lef (struct mundo_t *mundo, int tipo, int tempo, int heroi, int base, int missao, int invasao);

/*devolve a distancia cartesiana entre dois pontos, truncada para inteiro*/
int distancia (struct posicao_t a, struct posicao_t b);

/*remove da lef, liberando a memoria, os eventos futuros do heroi.
tipo = 0 remove todos os eventos do heroi (chega, espera, desiste, entra, sai, viaja,
morre e recupera_heroi); tipo != 0 remove so os eventos daquele tipo*/
void remove_lef (struct mundo_t *mundo, int tipo, int heroi);

#endif
