#include "main.h"

/*
    -------------------
    atualizaPopulacao()
    -------------------

*/
void atualizaPopulacao(){
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
void evoluiPopulacao(int rodada, int **individuosTorneio, int **pai, int *fitnessTorneio){
    int indiceInicio = 0;
    int *indice = &indiceInicio;

    printf("RODADA: %d\n", rodada+1);

    fitness();
    ordenaPopulacao();
    elitismo(indice);
    do{
        //selecaoAleatoria(pai);
        selecaoTorneio(individuosTorneio, pai, fitnessTorneio);
        //selecaoRoleta(pai);
        cruzamentoUmPonto(indice);
        //indiceInicio = cruzamentoDoisPontos(indice);
        mutacao(indice);
        //printf ("Indice: %d\n", indice);
    } while (indiceInicio < TAMANHOPOPULACAO);
    printf ("\n");
    atualizaPopulacao();
    printf("Populacao Atual: \n");
    mostraPopulacao();
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
    printf ("***POPULACAO INICIAL***\n");
    mostraPopulacao();
}
