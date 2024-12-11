#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"

//Ordenar as cidades cuja indetificação é E e F
int compare(const void *e, const void *f) {
    Cidade *cidadeE = (Cidade *)e;
    Cidade *cidadeF = (Cidade *)f;
    return cidadeE->Posicao - cidadeF->Posicao;
}
// Leitura dos dados da estrada do arquivo criado teste01
Estrada *getEstrada(const char *arquivodeTeste) { 
    FILE *file = fopen(arquivodeTeste, "r");
    if (file == NULL) {
        return NULL;
    }
	
    Estrada *estrada = (Estrada *)malloc(sizeof(Estrada));
    if (estrada == NULL) {
        fclose(file);
        return NULL;
    }
	// A leitura para o comprimento total da estrada
    if (fscanf(file, "%d", &estrada->T) != 1 || estrada->T < 3 || estrada->T > 1000000) {
        fclose(file);
        free(estrada);
        return NULL;
    }
	
    if (fscanf(file, "%d", &estrada->N) != 1 || estrada->N < 2 || estrada->N > 10000) {
        fclose(file);
        free(estrada);
        return NULL;
    }
	 // Alocando memória
    estrada->C = (Cidade *)malloc(estrada->N * sizeof(Cidade));
    if (estrada->C == NULL) {
        fclose(file);
        free(estrada);
        return NULL;
    }
	
    int c;
    while ((c = fgetc(file)) != EOF && c != '\n');
    // leitura das cidades e suas posições
	int i;
    for (i = 0; i < estrada->N; i++) {
        if (fscanf(file, "%d ", &estrada->C[i].Posicao) != 1) {
            fclose(file);
            free(estrada->C);
            free(estrada);
            return NULL;
        }

        char nomeCidade[256];
        if (fgets(nomeCidade, sizeof(nomeCidade), file) == NULL) {
            fclose(file);
            free(estrada->C);
            free(estrada);
            return NULL;
        }
		
        nomeCidade[strcspn(nomeCidade, "\n")] = '\0';
        strcpy(estrada->C[i].Nome, nomeCidade);
		// A verificação se a posição da cidade está dentro dos limites da estrada
        if (estrada->C[i].Posicao <= 0 || estrada->C[i].Posicao >= estrada->T) {
            fclose(file);
            free(estrada->C);
            free(estrada);
            return NULL;
        }
    }

    fclose(file);
    return estrada;
}
//A Função para calcular a menor vizinhança entre as cidades.
double calcularMenorVizinhanca(const char *arquivodeTeste) {
    Estrada *estrada = getEstrada(arquivodeTeste);
    int numeroCidades = estrada->N;
    double menorVizinhaca = estrada->T;
    

    qsort(estrada->C, estrada->N, sizeof(Cidade), compare);
    
    /*calculo do tamanho da menor vizinhança entre as cidades.*/
	int i;
    for (i = 0; i < numeroCidades; ++i) {
        double ladoEsquerdo, ladoDireito;

        if (i == 0) {
            ladoEsquerdo = 0;
            ladoDireito = (estrada->C[i].Posicao + estrada->C[i + 1].Posicao) / 2.0;
        } else if (i == numeroCidades - 1) {
            ladoEsquerdo = (estrada->C[i].Posicao + estrada->C[i - 1].Posicao) / 2.0;
            ladoDireito = estrada->T;
        } else {
            ladoEsquerdo = (estrada->C[i].Posicao + estrada->C[i - 1].Posicao) / 2.0;
            ladoDireito = (estrada->C[i].Posicao + estrada->C[i + 1].Posicao) / 2.0;
        }

        double tamanhoVizinhaca = ladoDireito - ladoEsquerdo;

        if (tamanhoVizinhaca < menorVizinhaca) {
            menorVizinhaca = tamanhoVizinhaca;
        }
    }
    free(estrada->C);
    free(estrada);

    return menorVizinhaca;
}
// Determinar a cidade com menor vizinhança
char *cidadeMenorVizinhanca(const char *arquivodeTeste) { 
    Estrada *estrada = getEstrada(arquivodeTeste);
    if (estrada == NULL) {
        return NULL;
    }

    int numeroCidades = estrada->N;
    int indexMenorVizinhanca = 0;
    double menorVizinhaca = estrada->T;

    qsort(estrada->C, estrada->N, sizeof(Cidade), compare);
    
	/*Calculo do tamanho da menor vizinhança, e determinacao da cidade 
	associada a esse menor tamanho*/
	int i;
    for (i = 0; i < numeroCidades; ++i) {
        double leftBound, rightBound;

        if (i == 0) {
            leftBound = 0;
            rightBound = (estrada->C[i].Posicao + estrada->C[i + 1].Posicao) / 2.0;
        } else if (i == numeroCidades - 1) {
            leftBound = (estrada->C[i].Posicao + estrada->C[i - 1].Posicao) / 2.0;
            rightBound = estrada->T;
        } else {
            leftBound = (estrada->C[i].Posicao + estrada->C[i - 1].Posicao) / 2.0;
            rightBound = (estrada->C[i].Posicao + estrada->C[i + 1].Posicao) / 2.0;
        }

        double tamanhoVizinhaca = rightBound - leftBound;

        if (tamanhoVizinhaca < menorVizinhaca) {
            menorVizinhaca = tamanhoVizinhaca;
            indexMenorVizinhanca = i;
        }
    }
	// alocacao da memoria 
    char *cidade = (char *) malloc(strlen(estrada->C[indexMenorVizinhanca].Nome) + 1);
    if (cidade == NULL) {
        free(estrada->C);
        free(estrada);
        return NULL;
    }
    
    strcpy(cidade, estrada->C[indexMenorVizinhanca].Nome);

    free(estrada->C);
    free(estrada);
    return cidade;
}

// Aqui esta o main.c que eu utilizei durante o projeto 
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"

int main() {
    const char *arquivodeTeste = "teste01.txt"; // Nome do arquivo de entrada

	// Calculando e exibindo a menor vizinhança entre as cidades
    double menorVizinhanca = calcularMenorVizinhanca(arquivodeTeste);
    if (menorVizinhanca < 0) {
        printf("---Erro!!! Nao foi possivel calcular a menor vizinhanca---.\n");
        return 1;
    }

    printf("---A menor vizinhanca encontrada foi: %.2f\n", menorVizinhanca);

	// Determinando e exibindo a cidade com menor vizinhança
    char *cidadeMenor = cidadeMenorVizinhanca(arquivodeTeste);
    if (cidadeMenor == NULL) {
        printf("---Erro!!! Nao foi possivel determinar a cidade com menor vizinhanca---.\n");
        return 1;
    }

    printf("---A cidade com a menor vizinhanca e: %s\n", cidadeMenor);
    free(cidadeMenor);

    return 0;
}
}*/