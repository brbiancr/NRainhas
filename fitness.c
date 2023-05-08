#include "main.h"

/*
    ---------
    fitness()
    ---------
    Avalia a aptid�o de cada individuo da popula��o.
*/
void fitness(){
    int i, j, k, l, m;
    int fitnessRainha, colisao;
    int auxiliar1, auxiliar2;

    for (i=0; i<TAMANHOPOPULACAO; i++){
        fitnessDaPopulacao[i]= 0 ;

        posicionaRainhas(i);

        //mostraTabuleiro();

        for (j=0; j<TAMANHOTABULEIRO; j++){
            for (k=0; k<TAMANHOTABULEIRO; k++){
                colisao = 0;
                if (tabuleiro[j][k]==1){
                    for (l=0; l<TAMANHOTABULEIRO; l++){
                        for (m=0; m<TAMANHOTABULEIRO; m++){
                            // Verifica se h� colisao na linha
                            if (((j==l) && (m!=k)) && (tabuleiro[l][m]==1))
                                colisao++;

                            // Verifica se a rainha esta na diagonal principal, caso esteja, verifica se h� colis�o na diagonal principal
                            if (((j==k) && (l==m)) && (k!=m) && (tabuleiro[l][m]==1))
                                colisao++;

                            // Verifica se a rainha esta na diagonal secund�ria, caso esteja, verifica se h� colis�o na diagonal secund�ria
                            if (((j+k)==(TAMANHOTABULEIRO-1)) && ((l+m)==(TAMANHOTABULEIRO-1)) && (j!=l) && (tabuleiro[l][m]==1))
                                colisao++;

                            // Verifica colis�o na paralela a diagonal secund�ria
                            if (((l+m)==(j+k)) && ((j!=l) && (k!=m)) && (j!=k) && ((l+m)!=(TAMANHOTABULEIRO-1)) && (tabuleiro[l][m]==1))
                                colisao++;
                        }
                    }

                    // Verifica colisao na paralela a diagonal principal
                    if (j!=k || (j+k != TAMANHOTABULEIRO-1)){
                    // Verificando abaixo da rainha
                        auxiliar1 = j+1;
                        auxiliar2 = k+1;
                        while (auxiliar1 < TAMANHOTABULEIRO && auxiliar2 < TAMANHOTABULEIRO){
                            if (tabuleiro[auxiliar1][auxiliar2] == 1)
                                colisao++;
                            auxiliar1++;
                            auxiliar2++;

                        }
                        // Verificando acima da rainha
                        auxiliar1 = j-1;
                        auxiliar2 = k-1;
                        while (auxiliar1 >= 0 && auxiliar2 >= 0){
                            if (tabuleiro[auxiliar1][auxiliar2] == 1)
                                colisao++;
                            auxiliar1--;
                            auxiliar2--;
                        }
                    }

                    (colisao > 0) ? (fitnessRainha = 0) : (fitnessRainha = 1);

                    //printf ("Fitness da rainha: %d\n", fitnessRainha);

                    fitnessDaPopulacao[i] += fitnessRainha;
                }
            }

        }
    }
}

/*
    ------------------
    posicionaRainhas()
    ------------------
    Posiciona as rainhas no tabuleiro
    0 indica posi��o vazia
    1 indica Rainhas
*/
void posicionaRainhas(int individuo){
    int i, j;
    int linhaDaRainha;

    for (i=0; i<TAMANHOTABULEIRO; i++){
        for (j=0; j<TAMANHOTABULEIRO; j++){
            linhaDaRainha = populacaoAtual[individuo][j];
            if (i == (linhaDaRainha-1))
                tabuleiro[i][j] = 1;
            else
                tabuleiro[i][j] = 0;
        }
    }
}
