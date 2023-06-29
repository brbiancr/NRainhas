#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"

int main(){
    int i, result1, result2;
    int *fitnessTorneio;
    int **individuosTorneio, **pai, **tabuleiro, **proximaPopulacao;
    FILE *arquivo;

    arquivo = fopen("dadosNRainhas.txt", "a+");
    if(arquivo == NULL){
        printf("ERRO AO ABRIR ARQUIVO PARA SALVAR DADOS!\n");
        return 0;
    } else{
        fprintf(arquivo, "Tamanho da populacao: %d\n", TAMANHOPOPULACAO);
        fprintf(arquivo, "Tamanho do tabuleiro: %d\n", TAMANHOTABULEIRO);
        fprintf(arquivo, "Quantidade de individuos por torneio: %d\n", QUANTIDADEINDIVIDUOSPORTORNEIO);
        fprintf(arquivo, "Taxa de elitismo: %.2f\n", TAXAELITISMO);
        fprintf(arquivo, "Taxa de mutacao: %.2f\n", TAXAMUTACAO);
        fprintf(arquivo, "Quantidade de rodadas: %d\n", RODADAS);
        fclose(arquivo);
    }


    // Alocando memoria
    populacaoAtual = (int**) malloc(sizeof(int*) * TAMANHOPOPULACAO);
    proximaPopulacao = (int**) malloc(sizeof(int*) * TAMANHOPOPULACAO);
    fitnessDaPopulacao = (int*) malloc(sizeof(int) * TAMANHOPOPULACAO);
    individuosTorneio = (int**) malloc(sizeof(int*) * QUANTIDADEINDIVIDUOSPORTORNEIO);
    pai = (int**) malloc(sizeof(int*) * 2);
    fitnessTorneio = (int*) malloc(sizeof(int) * QUANTIDADEINDIVIDUOSPORTORNEIO);
    tabuleiro = (int**) malloc(sizeof(int*) * TAMANHOTABULEIRO);

    for (i=0; i<TAMANHOPOPULACAO; i++){
        populacaoAtual[i] = (int*) malloc(sizeof(int) * TAMANHOTABULEIRO);
        proximaPopulacao[i] = (int*) malloc(sizeof(int) * TAMANHOTABULEIRO);
    }

    for (i=0; i<QUANTIDADEINDIVIDUOSPORTORNEIO; i++)
        individuosTorneio[i] = (int*) malloc(sizeof(int*) * TAMANHOTABULEIRO);

    for (i=0; i<2; i++)
        pai[i] = (int*) malloc(sizeof(int) * TAMANHOTABULEIRO);

    for (i=0; i<TAMANHOTABULEIRO; i++)
        tabuleiro[i] = malloc(sizeof(int) * TAMANHOTABULEIRO);

    // Verificando alocacao de memoria
    if (populacaoAtual == NULL || proximaPopulacao == NULL || fitnessDaPopulacao == NULL || individuosTorneio == NULL || pai == NULL || fitnessTorneio == NULL || tabuleiro == NULL){
        printf ("Falha ao alocar memoria!\n");
        return 0;
    }

    srand(time(NULL));
    inicializaPopulacao();
    for (i=0; i<RODADAS; i++){
        evoluiPopulacao(i, individuosTorneio, pai, fitnessTorneio, tabuleiro, proximaPopulacao);
    }

    printf("- Populacao Final -\n");
    mostraPopulacao();

    // Liberando memoria alocada
    free (*populacaoAtual);
    free (populacaoAtual);
    free (*proximaPopulacao);
    free (proximaPopulacao);
    free (fitnessDaPopulacao);
    free (*individuosTorneio);
    free (individuosTorneio);
    free (*pai);
    free (pai);
    free (fitnessTorneio);
    free (*tabuleiro);
    free (tabuleiro);

    return 0;
}
