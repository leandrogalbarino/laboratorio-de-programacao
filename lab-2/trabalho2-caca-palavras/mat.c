#include <stdio.h>
#include <stdlib.h>
#include "mat.h"

char *mat_aloca_matriz_por_vetor(int linhas, int colunas)
{
    char *mat;
    mat = (char *)malloc(linhas * colunas * sizeof(char *));
    if (mat == NULL)
    {
        printf("ERRO AO ALOCAR A MATRIZ");
        exit(1);
    }
    return mat;
}

char **mat_aloca(int linhas, int colunas)
{
    char **mat;
    int i;
    mat = (char **)malloc(linhas * sizeof(char *));
    if (mat == NULL)
    {
        printf("ERRO AO ALOCAR A MATRIZ");
        exit(1);
    }
    for (i = 0; i < linhas; i++)
    {
        mat[i] = (char *)malloc(colunas * sizeof(char));
        if (mat[i] == NULL)
        {
            printf("ERRO AO ALOCAR!");
            exit(1);
        }
    }
    return mat;
}

void mat_desaloca(char **mat, int linhas)
{
    int i;
    for (i = 0; i < linhas; i++)
    {
        free(mat[i]);
    }
    free(mat);
}

void clear_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void mat_dimencoes(matriz *mat)
{
    printf("DIGITE O NUMERO DE LINHAS DA MATRIZ:");
    scanf("%d", &mat->linhas);
    printf("DIGITE O NUMERO DE COLUNAS DA MATRIZ:");
    scanf("%d", &mat->colunas);
    clear_buffer();
}

void mat_preenche(matriz *mat)
{
    int i, j;
    char letra;
    printf("DIGITE O SEU TEXTO DE CACA PALAVRAS:\n");
    for (i = 0; i < mat->linhas; i++)
    {
        for (j = 0; j < mat->colunas;)
        {
            letra = getchar();
            if ((mat->matriz[0][0] != '-') && (letra == '\n' || letra == EOF))
            {
                return;
            }
            if (letra != ' ' && letra != '\n')
            {
                mat->matriz[i][j] = letra;
                j++;
            }
        }
    }
}

void mat_imprime(matriz *mat)
{
    int i, j;
    for (i = 0; i <= mat->colunas; i++)
    {
        printf("%d|", i);
    }
    printf("\n");
    for (i = 0; i < mat->linhas; i++)
    {
        printf("%d|", i + 1);
        for (j = 0; j < mat->colunas; j++)
        {
            printf("%c|", mat->matriz[i][j]);
        }
        printf("\n");
    }
}

void mat_inicializa(matriz *mat)
{
    mat->matriz = mat_aloca(mat->linhas, mat->colunas);
    for (int i = 0; i < mat->linhas; i++)
    {
        for (int j = 0; j < mat->colunas; j++)
        {
            mat->matriz[i][j] = '-';
        }
    }
}

void mat_troca_linhas_por_colunas(matriz *mat)
{
    matriz aux;
    aux.matriz = mat_aloca(mat->colunas, mat->linhas);

    for (int i = 0; i < mat->linhas; i++)
    {
        for (int j = 0; j < mat->colunas; j++)
        {
            aux.matriz[j][i] = mat->matriz[i][j];
        }
    }
    mat_desaloca(mat->matriz, mat->linhas);
    mat->matriz = aux.matriz;
    int temp = mat->linhas;
    mat->linhas = mat->colunas;
    mat->colunas = temp;
}
void mat_inverte(matriz *mat)
{
    int i, j;
    matriz aux;
    aux.matriz = mat_aloca(mat->linhas, mat->colunas);
    for (i = 0; i < mat->linhas; i++)
    {
        for (j = 0; j < mat->colunas; j++)
        {
            aux.matriz[i][j] = mat->matriz[i][mat->colunas - 1 - j];
        }
    }

    mat_desaloca(mat->matriz, mat->linhas);
    mat->matriz = aux.matriz;
}

void mat_troca_linhas(matriz *informacoes_jogo)
{
    int i, j;
    char **aux;
    aux = mat_aloca(informacoes_jogo->linhas, informacoes_jogo->colunas);
    for (i = 0; i < informacoes_jogo->linhas; i++)
    {
        for (j = 0; j < informacoes_jogo->colunas; j++)
        {
            aux[i][j] = informacoes_jogo->matriz[informacoes_jogo->linhas - i - 1][j];
        }
    }
    mat_desaloca(informacoes_jogo->matriz, informacoes_jogo->linhas);
    informacoes_jogo->matriz = aux;
}