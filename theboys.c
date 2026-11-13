// programa principal do projeto "The Boys - 2026/2"
// Autor: Leandro de França Pereira, GRR 20266150

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "entidades.h"
#include "destruicoes.h"
#include "simulador.h"

 
// minimize o uso de variáveis globais
 
// programa principal
void main ()
{
  
  srand (0) ;
 
  // iniciar o mundo
  struct mundo_t *mundo = criamundo () ;
  if (!mundo)
    return;
 
  // executar o laço de simulação
  simulamundo (mundo) ;
 
  // destruir o mundo
  destroimundo (mundo) ;
 
  return (0) ;
}
