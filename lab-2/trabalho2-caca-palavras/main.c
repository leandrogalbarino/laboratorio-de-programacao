#include "mat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define horiz_direta 0
#define horiz_reversa 1
#define vert_direta 2
#define vert_reversa 3
#define diag_direta 4
#define diag_sec 5
#define diag_reversa 6
#define diag_sec_reversa 7

struct coordenadas
{
    int linha[10];
    int coluna[10];
};
typedef struct coordenadas coordenadas;

struct procura
{
    char *string;
    coordenadas inicio;
    coordenadas fim;
    int direcao[10];
    int encontradas;
};
typedef struct procura Procura;

char *aloca_vetor(int linhas)
{
    char *vetor;
    vetor = (char *)malloc(linhas * sizeof(char));
    return vetor;
}

void libera_vetor(char *vetor) { free(vetor); }

void inverte_coordenadas(matriz *informacoes_jogo, Procura *busca, int i)
{
    int coluna = busca->inicio.coluna[i];
    int coluna_final = busca->fim.coluna[i];
    busca->inicio.coluna[i] = informacoes_jogo->colunas - coluna - 1;
    busca->fim.coluna[i] = informacoes_jogo->colunas - coluna_final - 1;
}

void troca_linhas_coordenadas(matriz *informacoes_jogo, Procura *busca, int i)
{
    int linhas = busca->inicio.linha[i];
    int linha_final = busca->fim.linha[i];

    busca->inicio.linha[i] = informacoes_jogo->linhas - linhas - 1;
    busca->fim.linha[i] = informacoes_jogo->linhas - linha_final - 1;
}

void troca_linhas_por_colunas_coordenadas(Procura *busca, int i)
{
    int aux;
    int aux2;
    aux = busca->inicio.linha[i];
    busca->inicio.linha[i] = busca->inicio.coluna[i];
    busca->inicio.coluna[i] = aux;

    aux2 = busca->fim.linha[i];
    busca->fim.linha[i] = busca->fim.coluna[i];
    busca->fim.coluna[i] = aux2;
}

char *direcao(int *direcao, int i)
{
    char *direcao_busca;
    switch (direcao[i])
    {
    case horiz_direta:
        direcao_busca = strdup("HORIZONTAL DIRETA");
        break;
    case horiz_reversa:
        direcao_busca = strdup("HORIZONTAL REVERSA");
        break;
    case vert_direta:
        direcao_busca = strdup("VERTICAL DIRETA");
        break;
    case vert_reversa:
        direcao_busca = strdup("VERTICAL REVERSA");
        break;
    case diag_direta:
        direcao_busca = strdup("DIAGONAL DIRETA");
        break;
    case diag_sec:
        direcao_busca = strdup("DIAGONAL SECUNDARIA");
        break;
    case diag_reversa:
        direcao_busca = strdup("DIAGONAL DIRETA REVERSA");
        break;
    case diag_sec_reversa:
        direcao_busca = strdup("DIAGONAL SECUNDARIA REVERSA");
        break;
    default:
        return NULL;
        break;
    }
    return direcao_busca;
}

void procurar_matriz(matriz *mat, Procura *busca)
{
    int i;
    char *achou;
    for (i = 0; i < mat->linhas; i++)
    {
        if (busca->encontradas == 9)
        {
            break;
        }
        achou = strstr(mat->matriz[i], busca->string);
        if (achou != NULL)
        {
            int indice = busca->encontradas;
            int coluna_inicial = achou - mat->matriz[i];
            int coluna_final = coluna_inicial + strlen(busca->string) - 1;

            if (coluna_inicial >= 0 && coluna_final < mat->colunas)
            {
                busca->inicio.linha[indice] = i;
                busca->inicio.coluna[indice] = coluna_inicial;
                busca->fim.linha[indice] = i;
                busca->fim.coluna[indice] = coluna_final;
                busca->encontradas++;
            }
        }
    }
}

void verifica_horiz_direta(matriz *informacoes_jogo, Procura *busca)
{
    int verif_encontro = busca->encontradas;
    procurar_matriz(informacoes_jogo, busca);
    if (verif_encontro != busca->encontradas && busca->encontradas < 10)
    {
        for (int i = verif_encontro; i < busca->encontradas; i++)
        {
            busca->direcao[i] = horiz_direta;
        }
    }
}

void verifica_horiz_reversa(matriz *informacoes_jogo, Procura *busca)
{
    int verif_encontro = busca->encontradas;
    mat_inverte(informacoes_jogo);
    procurar_matriz(informacoes_jogo, busca);

    if (verif_encontro != busca->encontradas && busca->encontradas < 10)
    {
        for (int i = verif_encontro; i < busca->encontradas; i++)
        {
            inverte_coordenadas(informacoes_jogo, busca, i);
            busca->direcao[i] = horiz_reversa;
        }
    }
    mat_inverte(informacoes_jogo);
}

void verifica_vert_direta(matriz *informacoes_jogo, Procura *busca)
{
    int verif_encontro = busca->encontradas;

    mat_troca_linhas_por_colunas(informacoes_jogo);
    procurar_matriz(informacoes_jogo, busca);
    if (verif_encontro != busca->encontradas && busca->encontradas < 10)
    {
        for (int i = verif_encontro; i < busca->encontradas; i++)
        {
            troca_linhas_por_colunas_coordenadas(busca, i);
            busca->direcao[i] = vert_direta;
        }
    }

    mat_troca_linhas_por_colunas(informacoes_jogo);
}

void verifica_vert_reversa(matriz *informacoes_jogo, Procura *busca)
{
    int verif_encontro = busca->encontradas;

    mat_troca_linhas_por_colunas(informacoes_jogo);
    mat_inverte(informacoes_jogo);
    procurar_matriz(informacoes_jogo, busca);
    if (verif_encontro != busca->encontradas && busca->encontradas < 10)
    {
        for (int i = verif_encontro; i < busca->encontradas; i++)
        {
            inverte_coordenadas(informacoes_jogo, busca, i);
            troca_linhas_por_colunas_coordenadas(busca, i);
            busca->direcao[i] = vert_reversa;
        }
    }

    mat_inverte(informacoes_jogo);
    mat_troca_linhas_por_colunas(informacoes_jogo);
}

void procurar_diag(matriz *informacoes_jogo, Procura *busca)
{
    for (int linha = 0; linha < informacoes_jogo->linhas; linha++)
    {
        for (int coluna = 0; coluna < informacoes_jogo->colunas; coluna++)
        {
            if (busca->encontradas == 9)
            {
                break;
            }
            int i = 0;
            int linha_atual = linha;
            int coluna_atual = coluna;
            while (i < strlen(busca->string) &&
                   linha_atual < informacoes_jogo->linhas &&
                   coluna_atual < informacoes_jogo->colunas &&
                   informacoes_jogo->matriz[linha_atual][coluna_atual] ==
                       busca->string[i])
            {
                i++;
                linha_atual++;
                coluna_atual++;
            }
            if (i == strlen(busca->string))
            {
                busca->inicio.linha[busca->encontradas] = linha;
                busca->inicio.coluna[busca->encontradas] = coluna;
                busca->fim.linha[busca->encontradas] = linha_atual - 1;
                busca->fim.coluna[busca->encontradas] = coluna_atual - 1;
                busca->encontradas++;
            }
        }
    }
}
void verifica_diag_direta(matriz *informacoes_jogo, Procura *busca)
{
    int verif_encontro = busca->encontradas;
    procurar_diag(informacoes_jogo, busca);
    if (verif_encontro != busca->encontradas && busca->encontradas < 10)
    {
        for (int i = verif_encontro; i < busca->encontradas; i++)
        {
            busca->direcao[i] = diag_direta;
        }
    }
}
void verifica_diag_sec(matriz *informacoes_jogo, Procura *busca)
{
    int verif_encontro = busca->encontradas;
    mat_inverte(informacoes_jogo);
    procurar_diag(informacoes_jogo, busca);
    if (verif_encontro != busca->encontradas && busca->encontradas < 10)
    {
        for (int i = verif_encontro; i < busca->encontradas; i++)
        {
            inverte_coordenadas(informacoes_jogo, busca, i);
            busca->direcao[i] = diag_sec;
        }
    }

    mat_inverte(informacoes_jogo);
}
void verifica_diag_reversa(matriz *informacoes_jogo, Procura *busca)
{
    int verif_encontro = busca->encontradas;
    mat_troca_linhas(informacoes_jogo);
    procurar_diag(informacoes_jogo, busca);
    if (verif_encontro != busca->encontradas && busca->encontradas < 10)
    {
        for (int i = verif_encontro; i < busca->encontradas; i++)
        {
            troca_linhas_coordenadas(informacoes_jogo, busca, i);
            busca->direcao[i] = diag_reversa;
        }
    }
    mat_troca_linhas(informacoes_jogo);
}

void verifica_diag_sec_reversa(matriz *informacoes_jogo, Procura *busca)
{
    int verif_encontro = busca->encontradas;
    mat_inverte(informacoes_jogo);
    mat_troca_linhas(informacoes_jogo);
    procurar_diag(informacoes_jogo, busca);
    if (verif_encontro != busca->encontradas && busca->encontradas < 10)
    {
        for (int i = verif_encontro; i < busca->encontradas; i++)
        {
            troca_linhas_coordenadas(informacoes_jogo, busca, i);
            inverte_coordenadas(informacoes_jogo, busca, i);
            busca->direcao[i] = diag_sec_reversa;
        }
    }
    mat_troca_linhas(informacoes_jogo);
    mat_inverte(informacoes_jogo);
}

void buscar_direcoes(matriz *informacoes_jogo, Procura *busca)
{
    busca->encontradas = 0;
    verifica_horiz_direta(informacoes_jogo, busca);
    verifica_horiz_reversa(informacoes_jogo, busca);
    verifica_vert_direta(informacoes_jogo, busca);
    verifica_vert_reversa(informacoes_jogo, busca);
    verifica_diag_direta(informacoes_jogo, busca);
    verifica_diag_sec(informacoes_jogo, busca);
    verifica_diag_reversa(informacoes_jogo, busca);
    verifica_diag_sec_reversa(informacoes_jogo, busca);
}
void mostra_posicoes_encontradas(matriz *informacoes_jogo, Procura *busca)
{
    if (busca->encontradas > 0)
    {
        printf("Foram encontradas a palavra %s\n", busca->string);
        for (int i = 0; i < busca->encontradas; i++)
        {
            printf("iniciando nas coordenadas: [%d,%d] e terminando nas coordenadas: "
                   "[%d,%d] ",
                   busca->inicio.linha[i] + 1, busca->inicio.coluna[i] + 1,
                   busca->fim.linha[i] + 1, busca->fim.coluna[i] + 1);
            printf("na direcao %s\n", direcao(busca->direcao, i));
        }
    }
}

void buscar_matriz(matriz *informacoes_jogo)
{
    Procura buscar = {0};
    buscar.string = aloca_vetor(informacoes_jogo->linhas + informacoes_jogo->colunas);
    printf("DIGITE SUA PALAVRA | DIGITE \"close\" PARA SAIR\n");
    do
    {
        scanf("%s", buscar.string);
        buscar_direcoes(informacoes_jogo, &buscar);
        mostra_posicoes_encontradas(informacoes_jogo, &buscar);
    } while (strcmp(buscar.string, "close") != 0);
    libera_vetor(buscar.string);
}

void caca_palavras(matriz *informacoes_jogo)
{
    mat_dimencoes(informacoes_jogo);
    mat_inicializa(informacoes_jogo);
    mat_preenche(informacoes_jogo);
    mat_imprime(informacoes_jogo);
    buscar_matriz(informacoes_jogo);
}
int main()
{
    matriz informacoes_jogo;
    caca_palavras(&informacoes_jogo);
}