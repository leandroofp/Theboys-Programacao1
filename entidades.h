#include "conjunto.h"
#include "fila.h"
#define t_inicio = 0
#define t_fim_do_mundo = 525600 
#define n_tamanho_mundo = 20000
#define n_habilidades = 10
#define n_herois = N_HABILIDADES * 5
#define n_bases = N_HEROIS / 5
#define n_missoes = T_FIM_DO_MUNDO / 100
#define n_invasoes = T_FIM_DO_MUNDO / 10000

//Structs do projeto
struct posicao_t
{
    int x;
    int y;
}
struct heroi_t
{
    int id;   //identificacao do heroi
    struct cjto_t *habilidades;  //conjunto de habilidades do heroi
    int estado;   //heroi esta vivo ou morto
    int paciencia; //nivel de paciencia
    int velocidade; //nivel de velocidade
    int exp; //nivel de experiencia
    int base;  //id da base onde o heroi se encontra
}
struct base_t
{
    int id; //id da base
    int lotacao; //
    struct cjto_t *presentes;
    int estado;
    struct fila_t *espera;
    struct posicao_t local;
}
struct missao_t 
{
    int id;
    struct cjto_t *habilidades;
    int perigo;
    struct posicao_t local;
}
struct invasao_t
{
    int id;
    struct posicao_t local;
    int tpbase; //tempo de penalidade depois da base ser destruida
    int tpheroi; //tempo de penalidade depois da heroi ser destruida
}
struct mundo_t
{
   int Nherois;
   int herois[Nherois];
   int Nbase;
   int base[Nbase];
   int Nmissoes;
   int missoes[Nmissoes];
   int Ninvasoes;
   int invasoes[Ninvasoes];
   int Nhabilidades;
   struct posicao_t tam_mundo;
   int relogio;

}

/*função responsável por inicializar o herói.
- caso de erro de alocação de memoria, retorna NULL
-se não, inicializa e retorna um ponteiro para aquele herói*/
struct heroi_t *criaheroi ();
