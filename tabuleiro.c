#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

void quadro_pecas(char **pecas, char **tabuleiro, char *disponivel, char **jogadores, int num_jog) {

  static int linha;
  static int linha_superior;
  static int coluna;
  static int coluna_esquerda;
  static int quant;
  int i, j;     // Contadores 

  linha = 1;
  linha_superior = 0;
  coluna = 2;
  coluna_esquerda = 0;
  quant = 12;
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
  tabuleiro[0] = NULL;
  tabuleiro[0] = (char *) realloc(tabuleiro[0], sizeof(char) * coluna);
  if(tabuleiro[0] == NULL) {
    vermelho();
    printf("Não foi possivel adicinar colunas no tabuleiro\n");
    padrao();
    exit(1);
  }

  char jogada[4];
  int pos1, pos2;
  int existe = 0;
  int ref_linha = 0, ref_coluna = 0;

  while(1) {
 
  printf("Pecas disponiveis: ");
  for(i = 0; i < quant; i += 2) {
    printf("%c%c ", disponivel[i], disponivel[i + 1]);    
  }
  printf("\n");
  existe = 0;
  printf("Escolha a peça desejada: ");
  do {        // Verifica se a peça existe
    setbuf(stdin, NULL);
    fgets(jogada, 4, stdin);  
    jogada[strlen(jogada) - 1] = '\0';   // Retira o caractere \n
    for(i = 0; i < quant; i += 2) {
      if((jogada[0] == disponivel[i]) && (jogada[1] == disponivel[i + 1])) {
        existe = 1;
      }      
    }
    if(!existe) {
      printf("Peca invalida, escolha novamente: ");        
    }
  } while(!existe);
  
  printf("Linha que deseja jogar: ");
  scanf("%d", &pos1);
  printf("Coluna que deseja jogar: ");
  scanf("%d", &pos2);

  // Relaciona as posições impressas com as posições da matrzi tabuleiro

  i = ref_linha + pos1;
  j = ref_coluna + pos2;
  j = 2 * j; 

  tabuleiro[i][j] = jogada[0];
  tabuleiro[i][j + 1] = jogada[1];

  // Apagar do vetor disponivel a peça jogada
  int k = 0;
  for(i = 0; i < quant; i += 2) {
    if(disponivel[i] != jogada[0] || disponivel[i + 1] != jogada[1]) {
      disponivel[k] = disponivel[i];
      disponivel[k + 1] = disponivel[i + 1];
      k += 2;      
    } 
  }
  // Reinicializa o valor das ultimas posições do vetor disponivel
  quant += -2;
  disponivel[quant] = ' ';
  disponivel[quant + 1]  = ' ';

  int flag = 0;  
  // Verificação na linha superior
  for(i = 0; i < coluna; i++) { 
    if(tabuleiro[0][i] != ' ') { // Se a linha mais superior não estiver vazia
      //linha_superior += - 1;
      coluna_esquerda += -1;
      ref_linha++;
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
    tabuleiro[linha - 1] = NULL;
    tabuleiro[linha - 1] = (char *) realloc(tabuleiro[linha - 1], sizeof(char ) * coluna);
    if(tabuleiro[linha - 1] == NULL) {
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
    for(i = 0; i < (linha - 1); i++) {
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

  // Adiciona linha mais inferior da matriz tabuleiro
  flag = 0;
  for(i = 0; i < coluna; i++) {
    if(tabuleiro[linha - 1][i] != ' ') {  // verifica se a ultima linha da matriz tem peças 
      linha += 1;
      flag = 1;
      break;
    }
  }

  if(flag) {
    tabuleiro = (char **) realloc(tabuleiro, sizeof(char *) * linha);   // adicinar uma linha
    if(tabuleiro == NULL) {
      vermelho();
      printf("Não foi possivel adicinar linhas no tabuleiro\n");
      padrao();
      exit(1);
    }
    tabuleiro[linha - 1] = (char *) realloc(tabuleiro[linha - 1], sizeof(char ) * coluna);  // Aloca as colunas na nova linha alocada 
    if(tabuleiro[linha - 1] == NULL) {
      vermelho();
      printf("Não foi possivel adicinar colunas no tabuleiro\n");
      padrao();
      exit(1);
    }
    // Inicializa a nova linha alocada
    for(i = 0; i < coluna; i++) {
      tabuleiro[linha - 1][i] = ' ';  
    }
  }

  // Verifica a coluna mais a esquerda 
  flag = 0;
  for(i = 0; i < linha; i++) {
    if(tabuleiro[i][0] != ' ') {    // Se a coluna esquerda não estiver vazia
      //coluna_esquerda += - 1;
      linha_superior += - 1;
      ref_coluna += 1;
      flag = 1;
      break;
    }
  }
  // Adiciona colunas e reorganiza as peças na matriz
  if(flag) {
    coluna += 2;      // Adiciona 2 colunas para inserir uma peça a esquerda
    for(i = 0; i < linha; i++) {
      tabuleiro[i] = (char *) realloc(tabuleiro[i], sizeof(char ) * coluna);
      if(tabuleiro[i] == NULL) {
        vermelho();
        printf("Não foi possivel adicinar colunas no tabuleiro\n");
        padrao();
        exit(1);
      }
      // Inicializa as colunas alocadas
      tabuleiro[i][coluna - 2] = ' '; 
      tabuleiro[i][coluna - 1] = ' ';      
    }
    // Movimenta todas as peças para a direita do tabuleiro
    int copia = linha - 1;
    for(i = 0; i < (linha - 1); i++) {
      for(j = (coluna - 4); j >= 0; j += -2) {
        if(tabuleiro[copia][j] != ' ') {
          tabuleiro[copia][j + 2] = tabuleiro[copia][j];
          tabuleiro[copia][j + 3] = tabuleiro[copia][j + 1];
          tabuleiro[copia][j] = ' ';
          tabuleiro[copia][j + 1] = ' ';
        }
      }
      copia += -1;
    }
  }

  // Adiciona coluna a direita do tabuleiro
  flag = 0;
  for(i = 0; i < linha; i++) {
    if(tabuleiro[i][coluna - 1] != ' ') {
      coluna += 2;    // Adicina mais duas colunas (Armazena mais uma peça)
      flag = 1;
      break;
    }
  }
  if(flag) {
    for(i = 0; i < linha; i++) {
      tabuleiro[i] = (char *) realloc(tabuleiro[i], sizeof(char) * coluna);
      if(tabuleiro[i] == NULL) {
        vermelho();
        printf("Não foi possivel adicionar novas colunas no tabuleiro\n");
        padrao();
        exit(1);
      }
      // Inicializa as novas colunas alocadas 
      tabuleiro[i][coluna - 2] = ' ';
      tabuleiro[i][coluna - 1] = ' ';      
    }
  }

  // Imprimir tabuleiro
  int superior = linha_superior;
  int esquerda = coluna_esquerda;

  for(j = 0; j < coluna; j += 2) {
    printf("    %d", superior);
    superior++;
  }
  printf("\n");

  for(i = 0; i < linha; i++) {
    if(esquerda < 0) {
      printf("%d ", esquerda);
    }
    else {
      printf(" %d ", esquerda);
    }    
    for(j = 0; j < coluna; j += 2) {
      printf("|%c%c| ", tabuleiro[i][j], tabuleiro[i][j + 1]); 
    }
    printf("\n");
    esquerda++;
  }
  }
  return;
}