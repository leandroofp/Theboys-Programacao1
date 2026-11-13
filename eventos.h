#ifndef eventos_h
#define eventos_h

struct evento_t {
    int id; //identificacao de cada tipo de evento
    int heroi; //identifica qual heroi esta realizando esse evento
    int base; //identifica em qual base esse evento acontece
    int missao; //identifica qual missao sera feita, caso seja evento missao
    int invasao; //identifica qual invasao feita, caso evento seja invasao
};

void eventosiniciais(struct mundo_t *mundo);

#endif