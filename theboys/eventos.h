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

/*agenda os eventos iniciais da simulacao, incluindo a chegada dos herois,
as missoes, as invasoes e o fim do mundo.
-retorna 1 em caso de sucesso e 0 em caso de erro*/
int eventosiniciais(struct mundo_t *mundo);

/*trata a chegada de um heroi em uma base, verificando se ele pode esperar
para entrar ou se deve desistir e procurar outra base*/
void chega (struct mundo_t *mundo, struct evento_t *ev);

/*coloca o heroi na fila de espera da base e avisa o porteiro para verificar
se existe vaga disponivel*/
void espera (struct mundo_t *mundo, struct evento_t *ev);

/*registra a desistencia do heroi em uma base e agenda sua viagem para
outra base escolhida aleatoriamente*/
void desiste (struct mundo_t *mundo, struct evento_t *ev);

/*avisa o porteiro da base para verificar a fila de espera e admitir os
herois enquanto houver vagas disponiveis*/
void avisa (struct mundo_t *mundo, struct evento_t *ev);

/*registra a entrada do heroi na base e agenda sua saida de acordo com
seu tempo de permanencia*/
void entra (struct mundo_t *mundo, struct evento_t *ev);

/*registra a saida do heroi da base, libera sua vaga e agenda sua viagem
para outra base, alem de avisar o porteiro sobre a vaga liberada*/
void sai (struct mundo_t *mundo, struct evento_t *ev);

/*calcula a distancia e o tempo de viagem do heroi entre duas bases,
registrando sua chegada na base de destino*/
void viaja (struct mundo_t *mundo, struct evento_t *ev);

/*registra a morte do heroi durante uma missao, atualiza os contadores,
remove seus eventos futuros e libera sua vaga na base*/
void morre (struct mundo_t *mundo, struct evento_t *ev);

/*verifica se existe alguma base capaz de realizar a missao com os herois
presentes, considerando suas habilidades. Caso seja cumprida, atualiza
as estatisticas e verifica o risco de morte dos herois durante a realização da missao*/
void missao (struct mundo_t *mundo, struct evento_t *ev);

/*realiza uma invasao em uma base, tornando-a inativa e deixando inativos
os herois presentes, alem de agendar suas recuperacoes e a reconstrucao da base*/
void invade (struct mundo_t *mundo, struct evento_t *ev);

/*reativa o heroi apos o termino do seu periodo de recuperacao*/
void recupera_heroi (struct mundo_t *mundo, struct evento_t *ev);

/*reativa a base apos o termino do periodo de reconstrucao*/
void reconstroi_base (struct mundo_t *mundo, struct evento_t *ev);

/*encerra a simulacao e imprime a situacao final dos herois, as estatisticas
das bases e os resultados gerais dos eventos, missoes, invasoes e mortalidade*/
void fim (struct mundo_t *mundo);

#endif