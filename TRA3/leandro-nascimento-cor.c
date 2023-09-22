#include <stdlib.h>
#include <stdio.h>
#include <time.h>
void cornormal(int a,int b);

void corfundo(int r, int g, int b)
{
    printf("\e[48;2;%d;%d;%dm", r, g, b);
}
void corletra(int r, int g, int b)
{
    printf("\e[38;2;%d;%d;%dm", r, g, b);
}
void posicao(int linha, int coluna){
    printf("\e[%d;%dH", linha, coluna);
}
void quadrado(int linha, int coluna, int r, int g, int b){
    int i=0, j=0, t=0;
    posicao(linha, coluna);
    for(j=linha; j <= linha+5; j++){
      for(i=coluna; i <= linha+coluna+10; i++){
/// todos os caracteres são da mesma cor, não precisa selecionar a cor a cada vez
      printf("\e[48;2;%d;%d;%dm", r, g, b);
      putchar(' ');
      posicao(j,i);
      }
    }
    for(t=linha; t <= linha+coluna; t++){
      posicao(t, 1);
      printf("\e[m");
      putchar(' ');
    }
}
void limpa(void)
{
    printf("\033[2J\033[3J");
}
void complementaquadrado(int linha, int coluna){
    for(int j = linha-1; j<linha+3; j++){
      for(int i = coluna-5; i < coluna+linha+6; i++){
      posicao(j, i);
      putchar(' ');
      } 
    }
}
void corn(void)
{
    printf("\e[m");
}
void barrared(int linha, int red){
/// as 3 são muito parecidas, poderia ser uma função só.
    int j=0;
    for(int i=0; i < 255; i+=10){
      posicao(linha,26+j);
      corfundo(i,0,0);
      putchar(' ');
     j++;
    }
    posicao(linha,26+(red%255)/10);
    corfundo(255,255,255);
    putchar(' ');
    posicao(linha,26-4);
    corn();
    corletra(255,215,0);    
    if(red <= 9 && red >= 0){
      printf("%d  ", red);
    }
    if(red <= 99 && red > 9){
      printf("%d ", red);
    }
    if(red > 99 ){
      printf("%d", red);
    }
}
void barragreen(int linha, int green){
    int j=0;
    for(int i=0; i < 255; i+=10){
      posicao(linha+1,26+j);
      corfundo(0,i,0);
      putchar(' ');
      j++;
    }
    posicao(linha+1,26+(green%255)/10);
    corfundo(255,255,255);
    putchar(' ');
    posicao(linha+1,26-4);
    corn();
    corletra(255,215,0);    
    if(green <= 9 && green >= 0){
    printf("%d  ", green);
    }
    if(green <= 99 && green > 9){
      printf("%d ", green);
    }
    if(green > 99 ){
      printf("%d", green);

    }
}
void barrablue(int linha, int blue){
    int j=0;
    for(int i=0; i < 255; i+=10){
     posicao(linha+2,26+j);       
      corfundo(0,0,i);
     putchar(' ');
      j++;
    }
    posicao(linha+2,26+(blue%255)/10);
    corfundo(255,255,255);
    putchar(' ');
    posicao(linha+2,26-4);
    corn();
    corletra(255,215,0);
    if(blue <= 9 && blue >= 0){
      printf("%d  ", blue);
    }
    if(blue <= 99 && blue > 9){
      printf("%d ", blue);
    }
    if(blue > 99 ){
      printf("%d", blue);

    }  
}
void pontuacao(int tentativa,int maquina[],int player[], int pontuacao[], int coordenadas[][3]){
/// a pontuação pedida não é assim
    int i=0, j=0, h=0;
    coordenadas[tentativa][0] = player[0];
    coordenadas[tentativa][1] = player[1];
    coordenadas[tentativa][2] = player[2];
    i = player[0] - maquina[0];
    j = player[1] - maquina[1];
    h = player[2] - maquina[2];
    if(i < 0){
      i = i*(-1);
    }
    if(j < 0){
      j = j*(-1);
    }
    if(h < 0){
      h = h*(-1);
    }
    pontuacao[tentativa] = (100 - ((i+j+h)/7.65));

}
void ordempartida(int pontuacao[], int coordenadas[][3]){
    int auxiliar, coord,coord1,coord2;
    int i, j;
    for(i=0; i < 3; i++){
      for(j=i+1; j < 4; j++){
         if(pontuacao[j] > pontuacao[i]){
          auxiliar = pontuacao[i];
          coord = coordenadas[i][0];
          coord1 = coordenadas[i][1];
          coord2 = coordenadas[i][2];
          pontuacao[i] = pontuacao[j];
          pontuacao[j] = auxiliar;
          coordenadas[i][0] = coord;
          coordenadas[i][1] = coord1;
          coordenadas[i][2] = coord2;

          coordenadas[i][0] = coordenadas[j][0];
          coordenadas[i][1] = coordenadas[j][1];
          coordenadas[i][2] = coordenadas[j][2];  

          coordenadas[j][0] = coord;
          coordenadas[j][1] = coord1;
          coordenadas[j][2] = coord2;                  
         }
      }
    }
}
void ordem(int ranking[]){
    int auxiliar;
    int i, j;
    for(i=0; i < 3; i++){
      for(j=i+1; j < 4; j++){
         if(ranking[j] > ranking[i]){
          auxiliar = ranking[i];
          ranking[i] = ranking[j];
          ranking[j] = auxiliar;
         }
      }
    }
}       
int main(){
/// muita repetição, muito código. deve dar para modularizar um tanto...
    limpa();
    srand(time(0));
    int red, blue, green;
    int tentativas, rodada = 0;
    int ranking[6] = {0,0,0,0,0,0};
    char jogar, fechar, lixo;
    int linha=3, coluna=8;     
    do{
/// indentação!
    int final[5] = {0,0,0,0,0};
    int maquina[3], player[3], coordenadas[5][3] = {};      
        maquina[0]= rand()%255;
        maquina[1]= rand()%255;
        maquina[2] = rand()%255;
        posicao(linha-1, coluna);
        corletra(255,215,0);
        printf("ACERTAR A COR:");
        quadrado(linha, coluna, maquina[0], maquina[1], maquina[2]);
        for(tentativas=0; tentativas < 4; tentativas++){
        posicao(linha-2, coluna+5);
        corletra(230,230,230);
        printf("USANDO CODIGOS RGB ATE 255!");             
        complementaquadrado(linha+5,coluna);
        posicao(linha+5,5);
        corletra(200,0,0);
        printf("RED:");
        posicao(linha+5,9);
        printf("   ");
        posicao(linha+5,9);
        scanf("%d", &red);
        scanf("%c", &lixo);        
        while(red > 255 || red < 0|| lixo != '\n'){
          complementaquadrado(linha+6,5);
          posicao(linha+5,5);        
          printf("RED:");          
          scanf("%d", &red);
          scanf("%c", &lixo); 
          posicao(linha+5,5);        
          }
        posicao(linha+7,5);
        corletra(0,200,0);    
        posicao(linha+6,11);
        printf("   ");
        posicao(linha+6,5);
        printf("GREEN:");
        posicao(linha+6,11);         
        scanf("%d", &green);
        scanf("%c", &lixo);
        while(green > 255 || green < 0|| lixo != '\n'){
          complementaquadrado(linha+7,5);
          posicao(linha+5,5);     
          corletra(200,0,0);

          printf("RED:%d   ", red);            
          posicao(linha+6,5);    
          corletra(0,200,0);                  
          printf("GREEN:");         
          scanf("%d", &green);
          scanf("%c", &lixo);             
          posicao(linha+5,5);        
          }    
        posicao(linha+7,5);
        corletra(0,0,200);          
        printf("BLUE:");
        posicao(linha+7,10);           
        scanf("%d", &blue);
        scanf("%c", &lixo);          
        while(blue > 255 || blue < 0|| lixo != '\n'){
          complementaquadrado(linha+8,5);
          posicao(linha+5,5);     
          corletra(200,0,0);             
          printf("RED:%d   ", red);            
          posicao(linha+6,5);    
          corletra(0,200,0);                  
          printf("GREEN:%d   ", green);
          posicao(linha+7,5);
          corletra(0,0,200); 
          printf("BLUE:");
          scanf("%d", &blue);
          scanf("%c", &lixo);                
          posicao(linha+5,5);        
          }      
        player[0] = red;
        player[1] = green;
        player[2] = blue;
        posicao(linha-1, coluna+25);
        corletra(255,215,0);
        printf("SUA COR ANTERIOR:");
        quadrado(linha, coluna+25, red, green, blue);
        complementaquadrado(linha+5,coluna+30);
        barrared(linha+5, red);
        barragreen(linha+5, green);
        barrablue(linha+5, blue);
        pontuacao(tentativas, maquina, player, final, coordenadas);
        ordempartida(final, coordenadas);
        if(final[0] == 100){
          coordenadas[tentativas+1][0] = 0;
          coordenadas[tentativas+1][1] = 0;
          coordenadas[tentativas+1][2] = 0;
          coordenadas[tentativas+1][0] = 0;
          coordenadas[tentativas+1][1] = 0;
          coordenadas[tentativas+1][2] = 0;          
          posicao(linha+8,8);
          corletra(255,215,0);
          printf("VOCE ACERTOU A COR!! MEUS PARABÉNS");
          
          break;
          }
        }
      posicao(linha,60);
      corletra(255,255,250);
      corfundo(128,0, 128);
      printf("PONTUACAO DA PARTIDA");
      posicao(linha+1,60);
      corletra(255,255,250);
      corn();
      printf("PONTUACAO 1:%d,%d,%d PONTUCAO:%d/100",coordenadas[0][0],coordenadas[0][1],coordenadas[0][2], final[0]);
      posicao(linha+2,60);
      printf("PONTUACAO 2:%d,%d,%d PONTUCAO:%d/100",coordenadas[1][0],coordenadas[1][1],coordenadas[1][2], final[1]);
      posicao(linha+3,60);
      printf("PONTUACAO 3:%d,%d,%d PONTUCAO:%d/100",coordenadas[2][0],coordenadas[2][1],coordenadas[2][2], final[2]);
      posicao(linha+4,60); 
      printf("A COR A ACERTAR ERA: %d|%d|%d \n", maquina[0],maquina[1],maquina[2]);
      posicao(linha+5,60);  
      corletra(255,255,250);
      printf("SUA MAIOR PONTUACAO FOI %d/100", final[0]);
      corfundo(128,0, 128);      
      posicao(linha+6,60);      
      corn();
      posicao(linha+9,8);
      corfundo(24,24,24);
      printf("JOGAR NOVAMENTE Y/N\n");
      corn();
      posicao(linha+10,8);
      scanf("%c", &jogar);
      if(jogar == '\n'){
        scanf("%c", &jogar);
        }
      corn();
      limpa();
      posicao(2,5);
      ranking[rodada] = final[0];
      rodada++;
    }  while (jogar == 'y' || jogar == 'Y');
    ordem(ranking);
    limpa();
    posicao(2,5);
    printf("RANKING:"); 
    posicao(linha,5);
    corfundo(255,215,0);   
    printf("TOP 1:%d",ranking[0]);
    corn();
    posicao(linha+1,5);
    printf("TOP 2:%d",ranking[1]);
    posicao(linha+2,5);
    printf("TOP 3:%d",ranking[2]);
    posicao(linha+5,5);
    printf("PRECISONE ENTER PARA FECHAR\n");
    scanf("%c", &fechar);
    if(fechar == '\n'){
        posicao(linha+6,5);       
        getchar();
      }
    posicao(1,1);
    limpa();
}
