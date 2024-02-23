// Defines
#define TAMANHOPOPULACAO 1000
#define TAMANHOTABULEIRO 16
#define QUANTIDADEINDIVIDUOSPORTORNEIO 5
#define TAXAELITISMO 0.2
#define TAXAMUTACAO 0.08
#define TIPODESELECAO 4 // 1- Aleatoria. 2- Roleta. 3- Torneio. 4- Torneio dos dissimilares
#define TIPODECRUZAMENTO 2 // 1- Cruzamento de um ponto. 2- Cruzamento de dois pontos

// Vari�veis globais
int **populacaoAtual;
int *fitnessDaPopulacao;
