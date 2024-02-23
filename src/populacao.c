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
void atualizaPopulacao(int **proximaPopulacao){
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
int evoluiPopulacao(int rodada, int **individuosTorneio, int **pai, int *fitnessTorneio, int **tabuleiro, int **proximaPopulacao, int encontrouSolucao){
    int indiceInicio = 0;
    int *indice = &indiceInicio;

    encontrouSolucao = fitness(tabuleiro, fitnessDaPopulacao, encontrouSolucao);
    ordenaPopulacao();
    elitismo(indice, proximaPopulacao);
    do{
        switch (TIPODESELECAO){
            case 1: selecaoAleatoria(pai);
                    break;
            case 2: selecaoRoleta(pai);
                    break;
            case 3: selecaoTorneio(individuosTorneio, pai, fitnessTorneio);
                    break;
            case 4: selecaoTorneioDosDissimilares(individuosTorneio, pai, fitnessTorneio);
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

    atualizaPopulacao(proximaPopulacao);
    encontrouSolucao = fitness(tabuleiro, fitnessDaPopulacao, encontrouSolucao);
    ordenaPopulacao();

    return encontrouSolucao;
}

/*
    ---------------------
    inicializaPopulacao()
    ---------------------
    Inicializa de forma aleatoria a populacao inicial.
    A populacao inicial nao deve ter individuos iguais.
*/
void inicializaPopulacao(){
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
