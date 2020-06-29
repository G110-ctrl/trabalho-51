#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuario.h"
#include "cores.h"

void quadro_pecas(char **pecas, char **tabuleiro, char *disponivel) {

  static int linha;
  static int coluna;
    
  printf("   0\n");
  printf("0 ");    
  printf("|_|");    
  printf(" 0\n");
  printf("   0\n");    

  printf("Pecas disponiveis: ");
  imprimir_disponivel(disponivel);

  char jogada[4];
  int existe = 0;

  printf("Escolha a peca desejada: ");
  do {                      // Verifica se a peça existe
    fgets(jogada, 4, stdin);  
    jogada[strlen(jogada) - 1] = '\0';   // Retira o caractere \n
    for(int i = 0; i < 12; i += 2) {
      if((jogada[0] == disponivel[i]) && (jogada[1] == disponivel[i+1])) {
        existe = 1;
      }      
    }
    if(!existe) {
      printf("Peca invalida, escolha novamente: ");        
    }
  } while(!existe);
  
  return;
}