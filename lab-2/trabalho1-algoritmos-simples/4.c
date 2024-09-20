//EXÉRCICIO NUMERO 4, Faça um programa que leia os dados de 50 usuários. Depois, calcule e imprima: a) A quantidade total de livros lidos pelos entrevistados menores de 10 anos. b) A quantidade de mulheres que leu 5 livros ou mais.
#include <stdio.h>
#include <stdlib.h>
struct usuario{
  char sexo;
  int idade;
  int quantidade;
};
typedef struct usuario Usuario;

void leVetor (int tamanho, Usuario* vet){
  for(int i=0; i < tamanho; i++){
    printf("DIGITE SEU SEXO, F:feminino || M:masculino:");
    scanf(" %c", &vet[i].sexo);
    printf("DIGITE SUA IDADE:");
    scanf("%d", &vet[i].idade);
    printf("DIGITE A QUANTIDADE DE LIVROS QUE VOCÊ LEU NO ANO DE 2022:");
    scanf("%d", &vet[i].quantidade);
    printf("\n");
  }
}

int Calcula_Quantidade_Livros(int tamanho, Usuario* vet){
  int livros_menores_dez = 0;
  int i;
  for(i=0; i < tamanho; i++){
    if(vet[i].idade < 10){
      livros_menores_dez+= vet[i].quantidade;
    }
  }
  return livros_menores_dez;
} 

int calcula_Quantidade_Mulheres(int tamanho, Usuario* vet){
  int quantidade_mulheres = 0;
  int i;
  for(i=0; i < tamanho; i++){
    if((vet[i].sexo == 'F' || vet[i].sexo == 'f') && vet[i].quantidade >= 5){
      quantidade_mulheres++;
    }
  }
  return quantidade_mulheres;
}

void imprime_na_tela(int mulheres, int criancas){
  printf("MULHERES QUE LERAM 5 OU MAIS LIVROS:%d\n", mulheres);
  printf("QUANTIDADE DE LIVROS LIDOS POR CRIANCAS MENORES DE 10 ANOS:%d\n", criancas); 
}

int main(){
  Usuario dados_pessoais[50];
  int mulheres;
  int criancas;
  leVetor(50, dados_pessoais);
  mulheres = calcula_Quantidade_Mulheres(50, dados_pessoais);
  criancas = Calcula_Quantidade_Livros(50, dados_pessoais);
  imprime_na_tela(mulheres, criancas);
}