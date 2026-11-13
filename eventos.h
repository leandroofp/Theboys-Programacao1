#ifndef eventos_h
#define eventos_h
#include "entidades.h"

struct evento_t {
    int id; //identificacao de cada tipo de evento
    int tempo; //quanto tempo é o do ev
    int heroi; //identifica qual heroi esta realizando esse evento
    int base; //identifica em qual base esse evento acontece
    int missao; //identifica qual missao sera feita, caso seja evento missao
    int invasao; //identifica qual invasao feita, caso evento seja invasao
};

void eventosiniciais(struct mundo_t *mundo);

void chega();

void espera();

void desiste();

void avisa();

void entra();

void sai();

void viaja();

void morre();

void missao();

void invade();

void recupera_heroi();

void reconstroi_base ();

void fim();

#endif