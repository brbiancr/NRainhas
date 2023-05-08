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
    ---------------------
    inicializaPopulacao()
    ---------------------
    Inicializa de forma aleat�ria a popula��o inicial.
    A popula��o inicial n�o deve ter individuos iguais.
*/

/*
    -----------------
    evoluiPopulacao()
    -----------------
    Evolui a populacao ate que a quantidade de evolucoes sejam alcancadas ou ate que uma solucao otima seja encontrada
*/
void evoluiPopulacao(){
    int i;
    int indice;

    printf("RODADA: %d\n", i+1);
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
    printf("Populacao Atual: \n");
    mostraPopulacao();
}

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
