#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fprio.h"



// descreve um nodo da fila de prioridades
struct fpnodo_t
{
  void *item ;          // item associado ao nodo
  int   tipo ;          // tipo do item
  int   prio ;          // prioridade do item
  struct fpnodo_t *prox;    // próximo nodo
};

// descreve uma fila de prioridades
struct fprio_t
{
  struct fpnodo_t *prim ;   // primeiro nodo da fila
  int num ;         // número de itens na fila
} ;

struct fprio_t *fprio_cria ()
{
  struct fprio_t *fila = malloc (sizeof (struct fprio_t));
  if (fila == NULL)
    return (NULL);
  memset (fila, 0, sizeof (struct fprio_t));

  return (fila);
}

struct fprio_t *fprio_destroi (struct fprio_t *f)
{
  struct fpnodo_t *aux;
  if (f == NULL)
    return(NULL);
  for ( int i = 0; i<f->num; i++)
  {
    aux = f->prim;
    f->prim = f->prim->prox;
    free(aux->item);
    free (aux);
  }
  free (f);
  return (NULL);
}

int fprio_insere (struct fprio_t *f, void *item, int tipo, int prio)
{
  // verifica possiveis erros
  if (f == NULL || item == NULL)
    return (-1);
  struct fpnodo_t *aux = f->prim;
  for (int i = 0; i<f->num; i++)
  {
    if (item == aux->item)
      return (-1);
    aux = aux->prox;
  }

  //aloca novo nodo
  struct fpnodo_t *novo = malloc(sizeof(struct fpnodo_t));
  if (novo == NULL)
    return (-1);

  //inicializa novo nodo
  novo->item = item;
  novo->tipo = tipo;
  novo->prio = prio;


  //se a fila é vazia ou a inserção e no inicio, o primeiro sera o novo item
  if ( f->prim == NULL || f->prim->prio > novo->prio)
  {
    novo->prox = f->prim;
    f->prim = novo;
  }

  //inserção em demais partes da fila
  else
  {
    aux = f->prim;
    while (aux->prox != NULL && aux->prox->prio <= prio)
    {
      aux = aux->prox;
    }
    novo->prox = aux->prox;
    aux->prox = novo;
  }

  //atualiza e retorna a quantidade de elementos na fila
  f->num++;
  return(f->num);

}

// Retira o primeiro item da fila e o devolve; o tipo e a prioridade
// do item são devolvidos nos parâmetros "tipo" e "prio".
// Retorno: ponteiro para o item retirado ou NULL se fila vazia ou erro.
void *fprio_retira (struct fprio_t *f, int *tipo, int *prio)
{
  //verifica se a fila e vazia ou erro
  if (f==NULL || tipo == NULL || prio == NULL || !f->num)
    return (NULL);

  void *item_retirado;
  struct fpnodo_t *aux = f->prim;

  /*primeiro da fila passa a ser o segundo,
  tipo e prio recebem o tipo e prioridade do primeiro item
  da fila, que sera retirado. item retirado recebe o ponteiro
  que aponta pro item daquele nodo.*/
  f->prim = aux->prox;
  *tipo = aux->tipo;
  *prio = aux->prio;
  item_retirado = aux->item;

  f->num--;
  free (aux);
  return (item_retirado);
}

int fprio_tamanho (struct fprio_t *f)
{
  if (f == NULL)
    return (-1);
  return(f->num);
}

// Imprime o conteúdo da fila no formato "(tipo prio) (tipo prio) ..."
// Para cada item deve ser impresso seu tipo e sua prioridade, com um
// espaço entre valores, sem espaços antes ou depois e sem nova linha.
void fprio_imprime (struct fprio_t *f)
{
  if (f==NULL)
    return;
  struct fpnodo_t *aux = f->prim;
   for (int i = 0; i<f->num; i++)
   {
    printf("(%d %d)", aux->tipo, aux->prio);
    if (i<(f->num) - 1)
      printf(" ");
    aux = aux->prox;
   }
}