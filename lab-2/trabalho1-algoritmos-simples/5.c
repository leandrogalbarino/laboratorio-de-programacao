/*
Faça um programa que leia a quantidade de aulas ministradas em uma disciplina. Para esta disciplina
informada, considere 5 alunos. Para cada aluno, leia as duas notas obtidas pelo aluno na 
disciplina e o número de aulas assistidas. A seguir, calcule e mostre a média final deste aluno e 
verifique se ele foi aprovado (status = ‘A’) ou reprovado (status = ‘B’). Condição para ser 
aprovado: média >= 6 e mínimo de 75% de frequência. Organize o código em funções. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct aluno
{
    float nota1;
    float nota2;
    int aulasAssistidas;
    float media;
    char status;
};
typedef struct aluno Aluno;

struct disciplina
{
    Aluno vet[5];
    int aulasMinistradas;
};
typedef struct disciplina Disciplina;

void media(Aluno *aluno){
    aluno->media = (aluno->nota1 + aluno->nota2) / 2;
}

void condicao(Aluno *aluno, int aulasMinistradas){
    if(aluno->media >= 6){
        if((float)aluno->aulasAssistidas / aulasMinistradas >= 0.75){
            aluno->status = 'A';
        }
        else{
            aluno->status = 'B';
        }
    }
    else{
        aluno->status = 'B';
    }
}
void le_notas(Disciplina *disciplina, int i){
    printf("%d Aluno\n", i+1);
    printf("Digite a primeira nota: ");
    scanf("%f", &disciplina->vet[i].nota1);
    printf("Digite a segunda nota: ");
    scanf("%f", &disciplina->vet[i].nota2);
    printf("Numero de aulas assistidas: ");
    scanf("%d", &disciplina->vet[i].aulasAssistidas);
}
void exibirInformacoesAlunos(Disciplina *disciplina) {
    printf("\n");
    for (int i = 0; i < 5; i++) {
        printf("Informacoes do %d aluno:\n", i + 1);
        printf("Media: %.2f\n", disciplina->vet[i].media);
        printf("Status: %c\n", disciplina->vet[i].status);
    }
}

void alunos(Disciplina *disciplina){
    int i;
    printf("Quantidade de aulas ministradas: ");
    scanf("%d", &disciplina->aulasMinistradas);
    for(i=0;i<5;i++){
        le_notas(disciplina, i);
        media(&disciplina->vet[i]);
        condicao(&disciplina->vet[i], disciplina->aulasMinistradas);
    }
    exibirInformacoesAlunos(disciplina);
}

int main(){
    Disciplina disciplina;
    alunos(&disciplina);
    return 0;
}