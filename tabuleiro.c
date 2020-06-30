#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

void quadro_pecas(char **pecas, char **tabuleiro, char *disponivel, int inicial) {

  static int linha;
  static int linha_superior;
  static int coluna;
  static int coluna_esquerda;
  int i, j;

  if(inicial == 0) {
    linha = 1;
    linha_superior = 0;
    coluna = 2;
    coluna_esquerda = 0;
    printf("   0\n");
    printf("0 ");    
    printf("|_|");    
    printf(" 0\n");
    printf("   0\n");    
    tabuleiro = NULL;
    tabuleiro = (char **) realloc(tabuleiro, sizeof(char *) * linha);
    if(tabuleiro == NULL) {
      vermelho();
      printf("Não foi possivel adicinar linhas no tabuleiro\n");
      padrao();
      exit(1);
    }
    for(int i = 0; i < coluna; i++) {
      tabuleiro[i] = (char *) realloc(tabuleiro, sizeof(char) * coluna);
      if(tabuleiro[i] == NULL) {
        vermelho();
        printf("Não foi possivel adicinar colunas no tabuleiro\n");
        padrao();
        exit(1);
      }
    }
  } 

  printf("Pecas disponiveis: ");
  imprimir_disponivel(disponivel);

  char jogada[4];
  int existe = 0;

  printf("Escolha a peca desejada: ");
  do {                      // Verifica se a peça existe
    fgets(jogada, 4, stdin);  
    jogada[strlen(jogada) - 1] = '\0';   // Retira o caractere \n
    for(i = 0; i < 12; i += 2) {
      if((jogada[0] == disponivel[i]) && (jogada[1] == disponivel[i+1])) {
        existe = 1;
      }      
    }
    if(!existe) {
      printf("Peca invalida, escolha novamente: ");        
    }
  } while(!existe);
    
  int pos1, pos2;
  printf("Escolha a posição que deseja jogar: ");
  scanf("%d %d", &pos1, &pos2);

  tabuleiro[pos1][pos2] = jogada[0];
  tabuleiro[pos1][pos2 + 1] = jogada[1];

  int flag = 0;  
  // Verificação na linha superior
  for(i = 0; i < coluna; i++) {
    if(tabuleiro[0][i] != ' ') {    // Se a linha mais superior não estiver vazia
      linha_superior += - 1;
      flag = 1;
      break;
    }
  }

  if(flag) {
    linha += 1;     // Aumenta a quantidade de linhas 
    tabuleiro = (char **) realloc(tabuleiro, sizeof(char *) * linha);
    if(tabuleiro == NULL) {
      vermelho();
      printf("Não foi possivel adicinar linhas no tabuleiro\n");
      padrao();
      exit(1);
    }
    tabuleiro[linha-1] = (char *) realloc(tabuleiro, sizeof(char ) * coluna);
    if(tabuleiro[linha-1] == NULL) {
      vermelho();
      printf("Não foi possivel adicinar colunas no tabuleiro\n");
      padrao();
      exit(1);
    }
    
    // Inicializa as posições alocadas
    for(i = 0; i < coluna; i++) {
      tabuleiro[linha - 1][i] = ' ';
    }
    
    // Coloca as peças uma posição abaixo na matriz tabuleiro 
    int copia = linha - 2;
    for(i = 0; i < (linha - 2); i++) {
      for(j = 0; j < coluna; j += 2) {
        if(tabuleiro[copia][j] != ' ') {
          tabuleiro[copia + 1][j] = tabuleiro[copia][j];
          tabuleiro[copia + 1][j + 1] = tabuleiro[copia][j + 1];
          tabuleiro[copia][j] = ' ';
          tabuleiro[copia][j + 1] = ' ';
        }
      }
      copia += -1;
    }
  }

  return;
}