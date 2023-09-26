/*
Desenvolva um programa que efetue a leitura de três valores para os lados de um triângulo, 
considerando lados como: A, B e C. O programa deverá verificar se os lados fornecidos 
formam realmente um triângulo (cada lado é menor que a soma dos outros dois lados). 
Se for esta condição verdadeira, deverá ser indicado qual tipo de triângulo foi formado: 
isósceles (dois lados iguais e um diferente), escaleno (todos os lados diferentes) ou 
equilátero (todos os lados são iguais)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct triangulo
{
    int ladoA;
    int ladoB;
    int ladoC;
    char ehTriangulo;
    char tipo[20];
};
typedef struct triangulo Triangulo;

Triangulo verificaTriangulo (Triangulo t){
    if(t.ladoA < t.ladoB + t.ladoC && t.ladoB < t.ladoA + t.ladoC && t.ladoC < t.ladoA + t.ladoB){
        t.ehTriangulo = 'V';

        if((t.ladoA == t.ladoB && t.ladoA != t.ladoC) || (t.ladoA == t.ladoC && t.ladoA != t.ladoB) || (t.ladoB == t.ladoC && t.ladoB != t.ladoA)){
            strcpy(t.tipo, "Isosceles");
        }
        else if(t.ladoA != t.ladoB && t.ladoA != t.ladoC && t.ladoB != t.ladoC){
            strcpy(t.tipo, "Escaleano");
        }
        else if(t.ladoA == t.ladoB && t.ladoA == t.ladoC && t.ladoB == t.ladoC){
            strcpy(t.tipo, "Equilatero");
        }
    }
    else {
        t.ehTriangulo = 'F';
        strcpy(t.tipo, "Os lados não formam um triângulo.");
    }

    if(t.ehTriangulo == 'V'){
        printf("É um triângulo do tipo %s", t.tipo);
    }
    else{
        printf("%s", t.tipo);
    }
}

int main(){
    Triangulo t;

    printf("Digite o valor do lado A: ");
    scanf("%d", &t.ladoA);

    printf("Digite o valor do lado B: ");
    scanf("%d", &t.ladoB);

    printf("Digite o valor do lado C: ");
    scanf("%d", &t.ladoC);

    verificaTriangulo(t);

    return 0;
}