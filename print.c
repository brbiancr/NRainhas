#include "main.h"

/*
    -----------------
    mostraPopulacao()
    -----------------
*/
void mostraPopulacao(){
    int i, j;
    for (i=0; i<TAMANHOPOPULACAO; i++){
        for (j=0; j<TAMANHOTABULEIRO; j++){
            printf("%d ", populacaoAtual[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/*
    -----------------
    mostraTabuleiro()
    -----------------
    Mostra na tela o tabuleiro com as rainhas posicionadas
    0 indica posicao vazia
    1 indica rainha
*/
void mostraTabuleiro(){
    int i, j;

    for (i=0; i<TAMANHOTABULEIRO; i++){
        for (j=0; j<TAMANHOTABULEIRO; j++)
            printf("%d ", tabuleiro[i][j]);
        printf("\n");
    }
}
