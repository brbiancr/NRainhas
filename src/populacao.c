#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "populacao.h"
#include "fitness.h"
#include "ordenacao.h"
#include "operadoresDeReproducao.h"
#include "selecao.h"

/*
    -------------------
    atualizaPopulacao()
    -------------------

*/
void atualizaPopulacao(int **proximaPopulacao, int **populacaoAtual){
    int i, j;

    for (i=0; i<TAMANHOPOPULACAO; i++){
        for (j=0; j<TAMANHOTABULEIRO; j++)
            populacaoAtual[i][j] = proximaPopulacao[i][j];
    }
}

/*
    -----------------
    evoluiPopulacao()
    -----------------
    Evolui a populacao ate que a quantidade de evolucoes sejam alcancadas ou ate que uma solucao otima seja encontrada
*/
int evoluiPopulacao(int rodada, int **individuosTorneio, int **pai, int *fitnessTorneio, int **tabuleiro, int **proximaPopulacao, int encontrouSolucao, int **populacaoAtual, int *fitnessDaPopulacao){
    int indiceInicio = 0;
    int *indice = &indiceInicio;

    encontrouSolucao = fitness(tabuleiro, fitnessDaPopulacao, encontrouSolucao, populacaoAtual);
    ordenaPopulacao(populacaoAtual, fitnessDaPopulacao);
    elitismo(indice, proximaPopulacao, populacaoAtual);
    do{
        switch (TIPODESELECAO){
            case 1: selecaoAleatoria(pai, populacaoAtual);
                    break;
            case 2: selecaoRoleta(pai, fitnessDaPopulacao, populacaoAtual);
                    break;
            case 3: selecaoTorneio(individuosTorneio, pai, fitnessTorneio, populacaoAtual, fitnessDaPopulacao);
                    break;
            case 4: selecaoTorneioDosDissimilares(individuosTorneio, pai, fitnessTorneio, populacaoAtual, fitnessDaPopulacao);
                    break;
        }

        switch (TIPODECRUZAMENTO){
            case 1: cruzamentoUmPonto(indice, pai, proximaPopulacao);
                    break;
            case 2: cruzamentoDoisPontos(indice, pai, proximaPopulacao);
                    break;
        }

        mutacao(indice, proximaPopulacao);

    } while (indiceInicio < TAMANHOPOPULACAO);

    atualizaPopulacao(proximaPopulacao, populacaoAtual);
    encontrouSolucao = fitness(tabuleiro, fitnessDaPopulacao, encontrouSolucao, populacaoAtual);
    ordenaPopulacao(populacaoAtual, fitnessDaPopulacao);

    return encontrouSolucao;
}

/*
    ---------------------
    inicializaPopulacao()
    ---------------------
    Inicializa de forma aleatoria a populacao inicial.
    A populacao inicial nao deve ter individuos iguais.
*/
void inicializaPopulacao(int **populacaoAtual){
    int i, j, k, l;
    int cont;

    for (i=0; i<TAMANHOPOPULACAO; i++){
        for (j=0; j<TAMANHOTABULEIRO; j++){
            populacaoAtual[i][j] = rand()%TAMANHOTABULEIRO;

            do{
                cont = 0;
                if (i>0){
                    for (k=0; k<i; k++){
                        for (l=0; l<TAMANHOTABULEIRO; l++){
                            if (populacaoAtual[i][j] == populacaoAtual[k][l])
                                cont++;
                        }
                    }

                }
                for (k=0; k<TAMANHOTABULEIRO; k++)
                    populacaoAtual[i][k] = rand()%TAMANHOTABULEIRO;
            } while(cont == TAMANHOTABULEIRO);
        }
    }
}
