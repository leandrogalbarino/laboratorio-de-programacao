#ifndef MAT_H
#define MAT_H

#include <stdio.h>

struct matriz
{
    char **matriz;
    int linhas;
    int colunas;
};

typedef struct matriz matriz;

char *mat_aloca_matriz_por_vetor(int m, int n);

void mat_dimencoes(matriz *mat);

void mat_desaloca(char **mat, int m);

char **mat_aloca(int m, int n);

void mat_preenche(matriz *mat);

void mat_imprime(matriz *mat);

void mat_inicializa(matriz *mat);

void mat_inverte(matriz *mat);

void mat_troca_linhas_por_colunas(matriz *mat);

void mat_troca_linhas(matriz *informacoes_jogo);
#endif