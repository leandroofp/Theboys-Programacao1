#include "conjunto.h"
#include "fila.h"

//Structs do projeto
struct posicao_t
{
    int x;
    int y;
}
struct heroi_t
{
    int id;
    struct cjto_t *habilidades; 
    int estado;
    int paciencia;
    int velocidade;
    int exp;
    int base;
}
struct base_t
{
    int id;
    int lotacao;
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