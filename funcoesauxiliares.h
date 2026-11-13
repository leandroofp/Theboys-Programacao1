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

#endif
