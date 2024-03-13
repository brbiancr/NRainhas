#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "fitness.h"
#include "operadoresDeReproducao.h"
#include "ordenacao.h"
#include "populacao.h"
#include "print.h"
#include "selecao.h"

int main(){
    // Calcular o tempo de execucao do programa
    double time_spent = 0.0;
    clock_t begin = clock();

    int i;
    int *fitnessTorneio, fitnessDaPopulacao;
    int **individuosTorneio, **pai, **tabuleiro, **proximaPopulacao, **populacaoAtual;
    int encontrouSolucao = 0;
    FILE *arquivo;

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

    inicializaPopulacao(populacaoAtual);

    for (i = 0; encontrouSolucao == 0; i++){
        encontrouSolucao = evoluiPopulacao(i, individuosTorneio, pai, fitnessTorneio, tabuleiro, proximaPopulacao, encontrouSolucao, populacaoAtual, fitnessDaPopulacao);
        printf("Rodada %d\n", i+1);
    }

    // Calcular o tempo de execucao do programa
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    arquivo = fopen("dadosNRainhas.txt", "a+");
    if(arquivo == NULL){
        printf("ERRO AO ABRIR ARQUIVO PARA SALVAR DADOS!\n");
        fclose(arquivo);
        return 0;
    } else{
        fprintf(arquivo, "Tamanho da populacao\t%d\n", TAMANHOPOPULACAO);
        fprintf(arquivo, "Tamanho do tabuleiro\t %d\n", TAMANHOTABULEIRO);
        fprintf(arquivo, "Quantidade de individuos por torneio\t %d\n", QUANTIDADEINDIVIDUOSPORTORNEIO);
        fprintf(arquivo, "Taxa de elitismo\t %.2f\n", TAXAELITISMO);
        fprintf(arquivo, "Taxa de mutacao\t %.2f\n", TAXAMUTACAO);
        fprintf(arquivo, "Tipo de selecao\t");
        if(TIPODESELECAO == 1)
            fprintf(arquivo, "Selecao aleatoria\n");
        if(TIPODESELECAO == 2)
            fprintf(arquivo, "Selecao por roleta\n");
        if(TIPODESELECAO == 3)
            fprintf(arquivo, "Selecao por torneio\n");
        if(TIPODESELECAO == 4)
            fprintf(arquivo, "Selecao por torneio dos dissimilares\n");
        fprintf(arquivo, "Tipo de cruzamento\t ");
        if(TIPODECRUZAMENTO == 1)
            fprintf(arquivo, "Cruzamento de um ponto\n");
        if(TIPODECRUZAMENTO == 2)
            fprintf(arquivo, "Cruzamento de dois pontos\n");

        fprintf(arquivo, "Rodadas\t %d\n\n", i+1);
        fprintf(arquivo, "Tempo de execucao\t %f\n\n", time_spent);

        mostraPopulacao(populacaoAtual, fitnessDaPopulacao);

        fclose(arquivo);
    }

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
    free (arquivo);

    return 0;
}
