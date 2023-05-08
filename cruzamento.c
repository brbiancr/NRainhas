#include "main.h"

/*
    ----------------------
    cruzamentoDoisPontos()
    ----------------------

    S�o selecionados dois pontos de corte diferentes entre si de maneira aleat�ria nos individuos pais.
    Recombina os dois pais gerando um novo filho.
    Adiciona o filho na prozima gera��o.
    Retorna o indice do ultimo indiv�duo da popula��o.
*/
int cruzamentoDoisPontos(int indice){
    int i;
    int corte1, corte2;
    int filho[TAMANHOPOPULACAO];

    do{
        corte1 = rand() % TAMANHOTABULEIRO+1;
        corte2 = rand() % TAMANHOTABULEIRO+1;
    } while (corte1 == corte2 || (corte1 == TAMANHOTABULEIRO || corte2 == TAMANHOTABULEIRO) );

    printf ("Ponto de corte 1: %d\n", corte1);
    printf ("Ponto de corte 2: %d\n", corte2);

    if (corte1 > corte2){
        for (i=0; i<=corte2; i++)
            filho[i] = pai[0][i];

        for (i=corte2+1; i<=corte1; i++)
            filho[i] = pai[1][i];

        for (i=corte1+1; i<TAMANHOTABULEIRO; i++)
            filho[i] = pai[0][i];
    }
    else {
        for (i=0; i<corte1; i++)
            filho[i] = pai[0][i];

        for (i=corte1; i<corte2; i++)
            filho[i] = pai[1][i];

        for (i=corte2; i<TAMANHOTABULEIRO; i++)
            filho[i] = pai[0][i];
    }

    // Adiciona o filho na popula��o
    for (i=0; i<TAMANHOTABULEIRO; i++)
        proximaPopulacao[indice][i] = filho[i];

    // Mostra o filho gerado
    for (i=0; i<TAMANHOTABULEIRO; i++){
        printf ("%d ", proximaPopulacao[indice][i]);
    }
    printf ("\n");

    return indice+1;
}

/*
    -------------------
    cruzamentoUmPonto()
    -------------------

    Seleciona aleatoriamente um ponto de corte nos individuos pais.
    Recombina os dois pais gerando um novo filho.
    Adiciona o filho gerado na ger��o seguinte
    Retorna o indice do ultimo indiv�duo da popula��o.
*/
int cruzamentoUmPonto(int indice){
    int i;
    int corte;
    int filho[TAMANHOTABULEIRO];

    do{
        corte = rand()% TAMANHOTABULEIRO+1;
    } while (corte == TAMANHOTABULEIRO);

    printf ("Ponto de corte: %d\n", corte);

    for (i=0; i<corte; i++)
        filho[i] = pai[0][i];

    for (i=corte; i<TAMANHOTABULEIRO; i++)
        filho[i] = pai[1][i];

    // Adiciona o filho na populacao
    for (i=0; i<TAMANHOTABULEIRO; i++)
        proximaPopulacao[indice][i] = filho[i];
    // Mostra o filho gerado
    printf("Filho: ");
    for (i=0; i<TAMANHOTABULEIRO; i++)
        printf ("%d ", proximaPopulacao[indice][i]);
    printf ("\n\n");

    return indice+1;
}

/*
    ---------
    mutacao()
    ---------

    Define a partir da TAXAMUTACAO se haver� ou n�o muta��o.
    Caso a muta��o ocorra, define de modo aleat�rio quantos pontos ser�o mutados (1 ou 2)
                           Define de modo aleat�rio quais os pontos de muta��o.
                           Muta o individiduo filho
*/
void mutacao(int indice){
    int i, j;
    int quantidadeDePontos;
    int mutarIndividuo;

    mutarIndividuo = rand()%(int)(1.0/TAXAMUTACAO);     // Define se haver� ou n�o muta��o

    if (mutarIndividuo == 0){
        printf ("*** OCORRE MUTACAO! ***\n");
        quantidadeDePontos = rand()%TAMANHOPOPULACAO;
        printf ("Quantidade de pontos de mutacao: %d\n", quantidadeDePontos);
        int posicao[quantidadeDePontos];

        printf ("Individuo antes da mutacao: ");
        for (i=0; i<TAMANHOTABULEIRO; i++)
            printf ("%d ", proximaPopulacao[indice-1][i]);
        printf("\n");

        for (i=0; i<quantidadeDePontos; i++){
            posicao[i] = rand()%TAMANHOTABULEIRO+1;

            // Verificando se existem pontos de mutacao iguais
            for(j=0; j<i; j++){
                if(posicao[i] == posicao[j]){
                    posicao[i] = rand()%TAMANHOTABULEIRO+1;
                    j = -1;
                }
            }
        }

        for(i=0; i<quantidadeDePontos; i++){
            proximaPopulacao[indice-1][posicao[i]] = rand()%TAMANHOTABULEIRO;
        }

        printf("Individuo mutado: ");
        for (i=0; i<TAMANHOTABULEIRO; i++)
            printf("%d ", proximaPopulacao[indice-1][i]);
        printf ("\n");
    }
    else{
        printf ("*** NAO OCORRE MUTACAO! ***\n");
    }

}



