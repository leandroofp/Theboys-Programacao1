#ifndef entidades_h
#define entidades_h
#include "conjunto.h"
#include "fila.h"
#define t_inicio 0
#define t_fim_do_mundo 525600 
#define n_tamanho_mundo 20000
#define n_habilidades 10
#define n_herois (n_habilidades * 5)
#define n_bases (n_herois / 5)
#define n_missoes (t_fim_do_mundo / 100)
#define n_invasoes ( t_fim_do_mundo / 10000)

//Structs do projeto
struct posicao_t
{
    int x;
    int y;
};
struct heroi_t
{
    int id;   //identificacao do heroi
    struct cjto_t *habilidades;  //conjunto de habilidades do heroi
    int estado;   //heroi esta vivo ou morto
    int paciencia; //nivel de paciencia
    int velocidade; //nivel de velocidade
    int exp; //nivel de experiencia
    int base;  //id da base onde o heroi se encontra
};
struct base_t
{
    int id; //id da base
    int lotacao; //
    struct cjto_t *presentes;
    int estado;
    struct fila_t *espera;
    struct posicao_t local;
};
struct missao_t 
{
    int id;
    struct cjto_t *habilidades;
    int perigo;
    struct posicao_t local;
};
struct invasao_t
{
    int id;
    struct posicao_t local;
    int tpbase; //tempo de penalidade depois da base ser destruida
    int tpheroi; //tempo de penalidade depois da heroi ser destruida
};
struct mundo_t
{
   int qtndherois;
   struct heroi_t *herois[n_herois];
   int qtndbases;
   struct base_t *bases[n_bases];
   int qtndmissoes;
   struct missao_t *missoes[n_missoes];
   int qtndinvasoes;
   struct invasao_t *invasoes[n_invasoes];
   int qtndhabilidades;
   struct posicao_t tam_mundo;
   int relogio;
   struct fprio_t *lef; //lista de eventos futuros
};

/*função responsável por inicializar o herói.
- caso de erro de alocação de memoria, retorna NULL
-se não, inicializa e retorna um ponteiro para aquele herói*/
struct heroi_t *criaheroi (int num_heroi);

/*inicializa as bases que estarao espalhadas pelo mundo, atribuindo a ela
uma localizacao aleatoria no mapa, um numero aleatorio entre 3 e 10 de lotacao
inicializa o conjunto que identificará os presentes e a fila de espera.
-retorna um ponteiro para a base, ou NULL em caso de erro*/
struct base_t *criabase (int num_base);

/*cria as missões que iram aparecer durante a simulação, com local aleatorio, 
habilidades requisitadas para sua realização aleatoria e o nivel de perigo também
de forma aleatoria.
-retorna um ponteiro para a missao, ou NULL em caso de erro */
struct missao_t *criamissao (int num_missao);

/*cria a invasao, em uma base aleatoria, atribuindo um tempo de recuperação
aleatorio ao heroi e a base, ate voltarem a estar ativos
-retorna um ponteiro para essa invasao, ou NULL em caso de erro*/
struct invasao_t *criainvasao(int num_invasao);

/*cria o mundo, com a quantidade definida de herois, bases, missoes e invasoes,
inicializando todos os campos da struct mundo. define as coordenadas maximas,
inicia o tempo em 0, e informa a quantidade de habilidades diferentes
-retorna um ponteiro pro mundo, ou NULL caso de algum erro*/
struct mundo_t *criamundo ();

#endif