#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

/*funções auxiliares*/

int filavazia (struct fila_t *f)
{
    if (!f->num)
        return (1);
    return (0);
}

/*Funções do header*/
struct fila_t *fila_cria ()
{
    struct fila_t *filanova = malloc (sizeof(struct fila_t));

    if (!filanova)
        return (NULL);
    
    memset (filanova, 0, sizeof (struct fila_t));
    return (filanova);
}

struct fila_t *fila_destroi (struct fila_t *f)
{
    if (!f)
        return (NULL);

    struct fila_nodo_t *aux;
    for (int i=0; i<f->num; i++)
    {
        aux = f->prim;
        f->prim = aux->prox;
        free (aux->item);
        free(aux);
    }
    free(f);
    return (NULL);
}

int fila_insere (struct fila_t *f, void *item)
{
    /*Verifica possíveis erros, como erro de alocação da estrutura 
    da fila, do novo item, ou a inserção do mesmo item*/
    if (!f || !item)
        return (-1);

    struct fila_nodo_t *aux = f->prim;
    for (int i = 0; i<f->num; i++)
    {
        if (item == aux->item)
        return (-1);
        aux = aux->prox;
    }

    struct fila_nodo_t *novonodo = malloc (sizeof(struct fila_nodo_t));
    if (!novonodo)
        return(-1);


    novonodo->item = item;
    novonodo->prox = NULL;

    /*se a fila estiver vazia, o novo é tanto
    o primeiro quanto o ultimo*/
    if (filavazia(f))
        f->prim = novonodo;
        
    else
        f->fim->prox = novonodo;

    f->fim = novonodo;
    (f->num)++;
    return (f->num);
}

// Retira o primeiro item da fila e o devolve
// Retorno: ponteiro para o item retirado ou NULL se fila vazia ou erro.
void *fila_retira (struct fila_t *f)
{
    if (!f || filavazia(f))
        return (NULL);

    /*o primeiro se torna o proximo item apos o retirado*/
    struct fila_nodo_t *aux = f->prim;
    void *item = aux->item;
    f->prim = aux->prox;

    /*atualiza o tamanho e verifica se a fila esvaziou apos isso*/
    (f->num)--;
    if(!f->num)
        f->fim = NULL;

    free(aux);
    return(item);
}

// Informa o número de itens na fila.
// Retorno: N >= 0 ou -1 se erro.
int fila_tamanho (struct fila_t *f)
{
    if (!f)
        return (-1);
    return(f->num);
}

// Imprime o conteúdo da fila 
void fila_imprime (struct fila_t *f)
{
    if (!f)
        return;
    struct fila_nodo_t *aux = f->prim;
    
    /*enquanto aux nao for null, ainda é um item
    da lista, quando o prox de aux for null, saira 
    da funcao, isso impede acesso invalido a memoria*/
    while (aux)
    {
        printf ("%p", aux->item);
        /*verificação para formatacao da impressao*/
        if (aux->prox)
            printf (" ");
        aux = aux->prox;
    }
}