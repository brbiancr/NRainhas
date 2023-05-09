#include "main.h"

/*
    -----------------
    ordenaPopulacao()
    -----------------
    Ordena os individuos da popula��o de acordo com seu fitness.
    A ordena��o � feita em ordem crescente.
*/
void ordenaPopulacao(){
    int i, j, k;
    int auxiliar;
    int auxiliarA[TAMANHOTABULEIRO];

    for (i=0; i<TAMANHOPOPULACAO; i++){
        auxiliar = fitnessDaPopulacao[i];
        for (k=0; k<TAMANHOTABULEIRO; k++)
            auxiliarA[k] = populacaoAtual[i][k];

        for (j=i; (j>0) && auxiliar<fitnessDaPopulacao[j-1]; j--){
            fitnessDaPopulacao[j] = fitnessDaPopulacao[j-1];
            for (k=0; k<TAMANHOTABULEIRO; k++)
                populacaoAtual[j][k] = populacaoAtual[j-1][k];
        }
        fitnessDaPopulacao[j] = auxiliar;
        for (k=0; k<TAMANHOTABULEIRO; k++)
            populacaoAtual[j][k] = auxiliarA[k];
    }

    printf ("***POPULACAO ORDENADA PELO FITNESS***: \n");
    mostraPopulacao();
    printf("\n");
}

/*
    ---------------
    ordenaTorneio()
    ---------------
    Ordena os individuos do torneio de acordo com seu fitness.
    A ordena��o � feita em ordem crescente.
*/
void ordenaTorneio(int **individuosTorneio, int *fitnessTorneio){
    int i, j, k;
    int auxiliar;
    int auxiliarA[TAMANHOTABULEIRO];

    for (i=0; i<QUANTIDADEINDIVIDUOSPORTORNEIO; i++){
        auxiliar = fitnessTorneio[i];
        for (k=0; k<TAMANHOTABULEIRO; k++)
            auxiliarA[k] = individuosTorneio[i][k];

        for (j=i; (j>0) && auxiliar<fitnessTorneio[j-1]; j--){
            fitnessTorneio[j] = fitnessTorneio[j-1];
            for (k=0; k<TAMANHOTABULEIRO; k++)
                individuosTorneio[j][k] = individuosTorneio[j-1][k];
        }
        fitnessTorneio[j] = auxiliar;
        for (k=0; k<TAMANHOTABULEIRO; k++)
            individuosTorneio[j][k] = auxiliarA[k];
    }

    printf ("Torneio ordenado pelo fitness: \n");
    for (i=0; i<QUANTIDADEINDIVIDUOSPORTORNEIO; i++){
        for (j=0; j<TAMANHOTABULEIRO; j++)
            printf ("%d ", individuosTorneio[i][j]);
        printf (" => ");
        printf("%d\n", fitnessTorneio[i]);
    }
    printf("\n");
}
