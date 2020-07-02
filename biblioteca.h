void padrao(void);
void negrito(void);
void vermelho(void);
void verde(void);
void roxo(void);
void marinho(void);
void amarelo(void);
void azul(void);

void quadro_pecas(char **pecas, char **tabuleiro, char *disponivel, char **jogadores, int num_jog, int mode);

void jogada(char *disponivel);
int is_alpha(char *s);

void preenche(char **pecas);
void imprimir_disponivel(char *disponivel, int quant);
void pecas_disponiveis(char **pecas, char *disponivel);
void usuario(void);