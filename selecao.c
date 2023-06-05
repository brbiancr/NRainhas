#include "main.h"

/*
    ----------
    elitismo()
    ----------
    Copia para proximaPopulacao uma quantidade TAXAELITISMO dos individuos com maior fitness da populacaoAtual.
    Retorna do ultimo indiv�duo da popula��o
*/
void elitismo(int* indice, int **proximaPopulacao){
    int i, j;
    for (i=0; i<TAXAELITISMO*100; i++){
        for (j=0; j<TAMANHOTABULEIRO; j++)
            proximaPopulacao[i][j] = populacaoAtual[TAMANHOPOPULACAO-(i+1)][j];
    }

    *indice = i;
}

/*
    ------------------
    selecaoAleatoria()
    ------------------
    Seleciona de forma aleat�ria os dois individuos pais.
    O processo ocorre at� que ambos os pais sejam diferentes entre si.
*/
void selecaoAleatoria(int **pai){
    int i, j;
    int individuo;
    int cont = 0;

    for (i=0; i<2; i++){

        individuo = (rand()%TAMANHOPOPULACAO);
        printf ("Pai %d: individuo %d, ",i , individuo);
        for (j=0; j<TAMANHOTABULEIRO; j++){
            pai[i][j] = populacaoAtual[individuo][j];
            printf("%d ", pai[i][j]);
        }
        printf("\n");

        printf("\n");

        if (i>0){
            for (j=0; j<TAMANHOTABULEIRO; j++){
                if (pai[0][j] == pai[1][j])
                    cont++;
            }
        }

        if (cont == TAMANHOTABULEIRO){
            printf ("PAIS IGUAIS, SELECIONE PAIS DIFERENTES!\n\n");
            i--;
        }
    }
}

/*
    ---------------
    selecaoRoleta()
    ---------------
    Representa proporcionalmente os individuos na roleta de acordo com seu fitness.
    Gira a roleta e seleciona um pai.
    O precesso se repete at� que exista dois pais diferentes entre si.
*/
void selecaoRoleta(int **pai){
    int i, j;
    int k = 0;
    int somaFitness = 0;
    int numeroSorteado, fitnessAcumulado, cont;

    // Soma os fitness da popula��o
    for (i=0; i<TAMANHOPOPULACAO; i++)
        somaFitness += fitnessDaPopulacao[i];

    printf ("-> Soma dos fitness: %d\n\n", somaFitness);


    for(k=0; k<2; k++){
        cont = 0;
        // Roda a roleta (sorteia um numero aleatorio)
        numeroSorteado = rand()%somaFitness;
        printf("NUMERO SORTEADO: %d\n", numeroSorteado);

        // Seleciona um pai
        fitnessAcumulado = 0;
        for (i=0; (i<TAMANHOPOPULACAO) && (fitnessAcumulado <= numeroSorteado); i++){
            fitnessAcumulado += fitnessDaPopulacao[i];
            if (fitnessAcumulado > numeroSorteado){
                for (j=0; j<TAMANHOTABULEIRO; j++)
                    pai[k][j] = populacaoAtual[i][j];
            }
        }

        // Verifica se os pais s�o iguais
        if (k>0){
            for (i=0; i<TAMANHOTABULEIRO; i++){
                if (pai[0][i] == pai[1][i])
                    cont++;
            }
        }

        if (cont == TAMANHOTABULEIRO){
            printf ("PAIS IGUAIS, SELECIONE PAIS DIFERENTES!\n");
            k--;
        }
        // Mostra o pai sorteado
        else{
            printf ("Pai %d: ", k+1);
            for (i=0; i<TAMANHOTABULEIRO; i++)
                printf ("%d", pai[k][i]);
            printf ("\n");
        }
        printf ("\n");
    }
}

/*
    ----------------
    selecaoTorneio()
    ----------------
    S�o selecionados N individuos distintos entre si para participar do torneio.
    O individuo com maior aptid�o entre os selecionados � escolhido para ser um pai.
    O precesso se repete at� que exista dois pais diferentes entre si.
*/
void selecaoTorneio(int **individuosTorneio, int **pai, int *fitnessTorneio){
    int i, j, k;
    int individuo[QUANTIDADEINDIVIDUOSPORTORNEIO];
    int cont = 0;

    for (k=0; k<2; k++){
        // Seleciona individuos para o torneio
        for (i=0; i < QUANTIDADEINDIVIDUOSPORTORNEIO; i++){
            individuo[i] = rand()%TAMANHOPOPULACAO;

            // Verifica se existem individuos iguais no torneio
            for(j=0; j<i; j++){
                if(individuo[i] == individuo[j]){
                    individuo[i] = rand()%TAMANHOPOPULACAO;
                    j = -1;
                }
            }

            fitnessTorneio[i] = fitnessDaPopulacao[individuo[i]];
            for (j=0; j<TAMANHOTABULEIRO; j++)
                individuosTorneio[i][j] = populacaoAtual[individuo[i]][j];

        }

        // Ordenar os individuos do torneio
        ordenaTorneio(individuosTorneio, fitnessTorneio);

        // Seleciona o individuo com maior fitness para ser o pai
        printf("Pai %d selecionado: ", k);
        for (i=0; i<TAMANHOTABULEIRO; i++){
            pai[k][i] = individuosTorneio[QUANTIDADEINDIVIDUOSPORTORNEIO-1][i];
            printf("%d ", pai[k][i]);
        }
        printf("\n\n");
    }

    // Verifica se os pais sao iguais
    if (k>0){
        for (i=0; i<TAMANHOTABULEIRO; i++){
            if (pai[0][i] == pai[1][i])
                cont++;
        }
    }

    if (cont == TAMANHOTABULEIRO){
        printf ("PAIS IGUAIS, SELECIONE PAIS DIFERENTES!\n\n");
        printf ("Pai 1: ");
        for (i=0; i<TAMANHOTABULEIRO; i++){
            pai[1][i] = individuosTorneio[QUANTIDADEINDIVIDUOSPORTORNEIO-2][i];
            printf ("%d ", pai[1][i]);
        }
        printf ("\n");
    }
}
