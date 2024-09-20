/*
Implemente uma função que calcule e mostre a área da superfície e o volume de uma esfera de raio r. 
O raio da esfera é informado pelo usuário. Esta função deve obedecer ao protótipo:
void calc_esfera (float r, float *area, float *volume)

A área da superfície e o volume são dados, respectivamente, por 4pr² e 4pr³/3.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void calc_esfera (float r, float *area, float *volume){
  float r2 = pow(r,2);
  float r3 = pow(r,3);
  *area = 4 * 3.1415 * r2;
  *volume = (4 * 3.1415 * r3) / 3;
  printf("A área da superficie é: %.2f\n", *area);
  printf("O volume é: %.2f", *volume);
}

int main(){
  float raio, volume, area;
  printf("Digite o raio da esfera: ");
  scanf("%f", &raio);
  calc_esfera(raio,&area,&volume);
  return 0;
}