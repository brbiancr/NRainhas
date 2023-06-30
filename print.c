#include <stdio.h>
#include "main.h"


/*
    -----------------
    mostraPopulacao()
    -----------------

    Mostra cada individuo da populacao seguido do seu fitness.
    Mostra o individuo com maior fitness.
    Mostra a media de fitness da populacao.
    Salva todos esses dados em um arquivo "dadosNRainhas.txt"
*/
void mostraPopulacao(){
    int i, j;
    FILE *arquivo;

    arquivo = fopen("dadosNRainhas.xls", "a+");
    if(arquivo == NULL){
        printf("ERRO AO ABRIR ARQUIVO PARA SALVAR DADOS!\n");
        return 0;
    }

    fprintf(arquivo, "- Populacao Final -\t - Fitness -\n");

    float mediaFitness = 0;
    for (i=0; i<TAMANHOPOPULACAO; i++){
        for (j=0; j<TAMANHOTABULEIRO; j++){
            printf("%d ", populacaoAtual[i][j]);
            fprintf(arquivo, "%d ", populacaoAtual[i][j]);
        }
        printf("Fitness: %d\n", fitnessDaPopulacao[i]);
        fprintf(arquivo, "\t%d\n", fitnessDaPopulacao[i]);
        mediaFitness += fitnessDaPopulacao[i];
    }

    printf("Maior fitness: %d\n", fitnessDaPopulacao[TAMANHOPOPULACAO-1]);
    printf("Media fitness: %f\n", mediaFitness/TAMANHOPOPULACAO);
    fprintf(arquivo, "Maior fitness\t %d\n", fitnessDaPopulacao[TAMANHOPOPULACAO-1]);
    fprintf(arquivo, "Media fitness\t %f\n", mediaFitness/TAMANHOPOPULACAO);

    fclose(arquivo);
}

/*
    -----------------
    mostraTabuleiro()
    -----------------
    Mostra na tela o tabuleiro com as rainhas posicionadas
    0 indica posicao vazia
    1 indica rainha
*/
void mostraTabuleiro(int **tabuleiro){
    int i, j;

    for (i=0; i<TAMANHOTABULEIRO; i++){
        for (j=0; j<TAMANHOTABULEIRO; j++)
            printf("%d ", tabuleiro[i][j]);
        printf("\n");
    }
}
