//EXERCÍCIO NÚMERO 2:
//Considere um vetor de 5 retângulos. Faça um programa que leia a base e a altura de cada retângulo e a seguir chame uma função que calcule e mostre na tela o perímetro e a área deste retângulo.
#include <stdlib.h>
#include <stdio.h>

struct retangulo{
  float base;
  float altura;
  float perimetro;
  float area;
};
typedef struct retangulo Retangulo;

void calculaPeriArea (Retangulo *ret){
  ret->area = ret->base * ret->altura;
  ret->perimetro = 2 * (ret->base  + ret->altura);
}     
void ler_base_e_altura(Retangulo ret[], int i){
    printf("RETÂNGULO %d\n", i+1);
    printf("Digite a medida da base do retângulo %d:\n", i+1);
    scanf("%f", &ret[i].base);
    printf("Digite a altura do retângulo %d:\n", i+1);
    scanf("%f", &ret[i].altura);   
}
void mostra_na_tela(Retangulo *ret, int i){
  printf("O perímetro do retangulo n°%d é de:%0.2f cm\n", i+1,ret->perimetro);
  printf("A area do retangulo n°%d é:%0.2f cm²\n\n", i+1,ret->area);    
}
int main(){
  Retangulo ret[5];
  for(int i = 0; i < 5; i++){
    ler_base_e_altura(ret, i);
    calculaPeriArea(&ret[i]);
    mostra_na_tela(&ret[i], i);
  }
}
