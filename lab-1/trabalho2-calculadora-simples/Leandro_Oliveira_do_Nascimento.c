#include <stdio.h>

float calculadora(char caracter, float numero, float numero2)
{
/// acho que este tá sobrando
  float numerox;
  float numero_return;
  numero_return = 0;  
  if(caracter == '/' || caracter == '*' || caracter == '+' ||       caracter == '-')
  {
    if(caracter == '/'){
    numero_return = numero / numero2;
    }
    if(caracter == '*'){
    numero_return = numero * numero2;
    }  
    if(caracter == '+'){
    numero_return = numero + numero2;
    } 
    if(caracter == '-'){
    numero_return = numero - numero2;
    }
  }
    else{
    printf("erro, o resultado é ");
    return numero;
  }
  return numero_return;
}  

int main(void) {
  float numero;
  float numero2;
  char caracter;
  printf("digite a conta\n");
  numero = 1;
  scanf("%f", &numero);
  while(caracter !=  '\n')
  {
     caracter = getchar();
     if ( caracter == '\n')
     {
       break;
     }
     scanf("%f", &numero2);
     numero = calculadora(caracter, numero , numero2);
  }
  printf("%0.2f", numero);

}

  
