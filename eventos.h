#ifndef eventos_h
#define eventos_h
#include "entidades.h"

struct evento_t {
    int id; //identificacao de cada tipo de evento
    int heroi; //identifica qual heroi esta realizando esse evento
    int base; //identifica em qual base esse evento acontece
    int missao; //identifica qual missao sera feita, caso seja evento missao
    int invasao; //identifica qual invasao feita, caso evento seja invasao
};

int eventosiniciais(struct mundo_t *mundo);

void chega (struct mundo_t *mundo, struct evento_t *ev);

void espera (struct mundo_t *mundo, struct evento_t *ev);

void desiste (struct mundo_t *mundo, struct evento_t *ev);

void avisa (struct mundo_t *mundo, struct evento_t *ev);

void entra (struct mundo_t *mundo, struct evento_t *ev);

void sai (struct mundo_t *mundo, struct evento_t *ev);

void viaja (struct mundo_t *mundo, struct evento_t *ev);

void morre (struct mundo_t *mundo, struct evento_t *ev);

void missao (struct mundo_t *mundo, struct evento_t *ev);

void invade (struct mundo_t *mundo, struct evento_t *ev);

void recupera_heroi (struct mundo_t *mundo, struct evento_t *ev);

void reconstroi_base (struct mundo_t *mundo, struct evento_t *ev);

void fim (struct mundo_t *mundo);

#endif