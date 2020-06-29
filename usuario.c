#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cores.h"

void preenche(char **pecas) {
  
  unsigned int letra = 65;      // Caracteres letras 
  unsigned int numero = 49;     // Caracteres numero (apartir de 1) 
  int i, j;
  int k = 0;
  
  for(i = 0; i < 6; i++) {
    for(j = 0; j < 36; j += 2) {
      pecas[i][j] = letra;
      pecas[i][j+1] = numero;
      k++;
      if(k == 3) {
        numero++;
        k = 0;
      }
    }
    numero = 49;
    letra++;
  }
  return;
}
 
void imprimir_disponivel(char *disponivel) {

  for(int i = 0; i < 12; i += 2) {
    switch(disponivel[i+1]) {
      case '1': 
        verde();
        printf("%c%c ", disponivel[i], disponivel[i+1]);
        padrao();
        break;
      case '2': 
        vermelho();
        printf("%c%c ", disponivel[i], disponivel[i+1]);
        padrao();
        break;
      case '3': 
        amarelo();
        printf("%c%c ", disponivel[i], disponivel[i+1]);
        padrao();
        break;
      case '4': 
        azul();
        printf("%c%c ", disponivel[i], disponivel[i+1]);
        padrao();
        break; 
      case '5': 
        roxo();
        printf("%c%c ", disponivel[i], disponivel[i+1]);
        padrao();
        break; 
      case '6': 
        marinho();
        printf("%c%c ", disponivel[i], disponivel[i+1]);
        padrao();
        break;      
    } 
  }
  return;
}

void pecas_disponiveis(char **pecas, char *disponivel) {
  
  int linha;
  int coluna;

  srand(time(NULL));
  coluna = rand() % 36;

  for(int i = 0; i < 12; i += 2) {    
    while(coluna % 2 != 0) {
      coluna = rand() % 36;      
      //printf("\n%d\n", coluna);
    }

    linha = rand() % 6;

    if(pecas[linha][coluna] != ' ') {
      disponivel[i] = pecas[linha][coluna];
      disponivel[i+1] = pecas[linha][coluna+1];
    }
    coluna = rand() % 36;
  }
  return;
}

void quadro_pecas(char **pecas, char **tabuleiro, char *disponivel) {

  printf("Peças disponiveis: ");
  imprimir_disponivel(disponivel);
  
  return;
}

void usuario(void) {

// Inserir usuarios 

  int num_jog;
  char **jogadores;
  char **tabuleiro;
  char **pecas;
  char *disponivel;

  printf("Quantidade de jogadores: ");
  scanf("%d", &num_jog);

  jogadores = (char **) malloc(sizeof(char *) * num_jog);
  if(jogadores == NULL) {
    vermelho();
    printf("Não foi possével alocar memoria!");
    padrao();
    exit(1);
  }
  for(int i = 0; i < num_jog; i++) {
    jogadores[i] = (char *) malloc(sizeof(char) * 100);
    if(jogadores[i] == NULL) {
      vermelho();
      printf("Não foi possével alocar memoria!");
      padrao();
      exit(1);      
    }
  }
  pecas = (char **) malloc(sizeof(char *) * 6);
  if(pecas == NULL) {
    vermelho();
    printf("Não foi possével alocar memoria!");
    padrao();
    exit(1);
  }
  for(int i = 0; i < 6; i++) {
    pecas[i] = (char *) malloc(sizeof(char) * 36);
    if(pecas[i] == NULL) {
      vermelho();
      printf("Não foi possével alocar memoria!");
      padrao();
      exit(1);
    }
  }

  printf("Digite o nome dos jogadores\n");

  int num_letra;
  for(int i = 0; i < num_jog; i++) {
    printf("jogador #%d: ", i + 1);
    setbuf(stdin, NULL);
    fgets(jogadores[i], 100, stdin);
    num_letra = strlen(jogadores[i]);
    jogadores[i][strlen(jogadores[i]) - 1] = '\0';
    jogadores[i] = (char *) realloc(jogadores[i] ,sizeof(char) * (num_letra + 1)); // Conta o '\0'
    if(jogadores[i] == NULL) {
      vermelho();
      printf("Não foi possével alocar memoria!");
      padrao();
      exit(1);
    }
  }

  disponivel = (char *) malloc(sizeof(char) * 12);
  if(disponivel == NULL) {
    vermelho();
    printf("Não foi possével alocar memoria!");
    padrao();
    exit(1);
  }

  preenche(pecas);  // preenche a matriz com a peças do jogo
  for(int i = 0; i < 6; i++) {
    for(int j = 0; j < 36; j += 2) {
      printf("%c%c ", pecas[i][j], pecas[i][j+1]);
    }
    printf("\n");
  }

  pecas_disponiveis(pecas, disponivel);
  quadro_pecas(pecas, tabuleiro, disponivel);

  //printf("\n");
  //for(int i = 0; i < 12; i += 2)
    //printf("%c%c ", disponivel[i], disponivel[i+1]);
  
  free(disponivel);
  for(int i = 0; i < num_jog; i++) {
    free(jogadores[i]);
  }
  free(jogadores);

  return;  
}