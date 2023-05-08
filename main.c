#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"

int main(){
    int i;
    int indice;

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
    indice = 0;
    fitness();
    ordenaPopulacao();
    indice = elitismo();
    do{
        //selecaoAleatoria();
        selecaoTorneio();
        //selecaoRoleta();
        indice = cruzamentoUmPonto(indice);
        //indice = cruzamentoDoisPontos(indice);
        mutacao(indice);
        //printf ("Indice: %d\n", indice);
    } while (indice < TAMANHOPOPULACAO);

    printf ("\n");
    atualizaPopulacao();
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
