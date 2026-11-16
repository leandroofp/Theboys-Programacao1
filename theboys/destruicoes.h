#ifndef destruicoes_h
#define destruicoes_h
#include "entidades.h"

/*função libera o espaço da memoria referente a cada heroi*/
void destroiheroi (struct heroi_t *heroi);

/*função libera o espaço da memoria referente a cada base*/
void destroibase (struct base_t *base);

/*função libera o espaço da memoria referente a cada missao*/
void destroimissao (struct missao_t *missao);

/*função libera o espaço da memoria referente a cada invasao*/
void destroiinvasao (struct invasao_t *invasao);

/*função libera o espaço da memoria referente a todas as inicilizações feitas ao criar 
o mundo, todas as entidades presentes*/
void destroimundo (struct mundo_t *mundo);

#endif