#include "tela.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
typedef struct {
    float pontos;
    char nome[10];
    float tempo_de_partida;
    bool terminou;
    int corplayer[3];
    int cormaquina[3];
}estado;

typedef struct{
    char rank1[10];
    char rank2[10];
    char rank3[10];
}nomes;

void cormaquina(cor *maquina){
    maquina->vermelho = (rand()%252);
    maquina->azul = (rand()%252);
    maquina->verde = (rand()%252);
}
void pintaquadrado(cor *pintar){

/// era para usar as funções de tela.h
    printf("\e[48;2;%d;%d;%dm", pintar->vermelho, pintar->verde, pintar->azul);
    putchar(' ');
}
void quadrado_player(cor *player, posicao *posicaoplayer){
/// deveria especializar mais a função.
/// a função se chama "quadrado_player", mas além de desenhar o quadrado do
///   jogador, ela também altera um dos componentes da cor do jogador.
    if(posicaoplayer->linha == 8){
        player->vermelho = ((posicaoplayer->coluna - 5) * 7);
    }    
    if(posicaoplayer->linha == 9){
        player->verde = ((posicaoplayer->coluna - 5 ) * 7);
    }    
    if(posicaoplayer->linha == 10){
        player->azul = ((posicaoplayer->coluna - 5) * 7);
    }    
    for(int i=0; i <= 10; i++){
        for(int j=0; j < 4; j++){
            posicao pos_player = {3+j,25+i};
            tela_posiciona(pos_player);
            pintaquadrado(player);
        }
    }
    tela_cor_normal();
    putchar(' ');
}
/// se a função acima fizesse só o desenho de um quadrado, estas duas
///   funções poderiam ser unificadas, simplificando essa parte do programa
void quadrado_maquina(cor maquina){
    for(int i=0; i <= 10; i++){
        for(int j=0; j < 4; j++){
            posicao pos_maq = {3+j,5+i};
            tela_posiciona(pos_maq);
            pintaquadrado(&maquina);       
        }
    }
    tela_cor_normal();
}
int calcula_distancia(int player, int maquina){
    int distancia;
    distancia = player - maquina;
    if(distancia < 0){
        distancia*=(-1);
    }
    return distancia;
}
int calcula_pontos(int cor_player, int cor_maquina){
    int pontos;
    int pior_chute = 0;
    int percentual;
    int distancia;
        if(calcula_distancia(cor_player, cor_maquina) > 128){
/// porque calcular a distancia de novo?
/// esse cálculo tá errado. que valor vai dar se cor_player for 200 e cor_maquina
///   for 10? que valor deveria dar?
            distancia = calcula_distancia(cor_player, cor_maquina);
            pior_chute = calcula_distancia(pior_chute,cor_maquina);
            percentual = 100*distancia/pior_chute;
            pontos = 100 - percentual;
        }
        else{
            pior_chute = 255;
            distancia = calcula_distancia(cor_player, cor_maquina);
            pior_chute = calcula_distancia(pior_chute,cor_maquina);
            percentual = 100 * distancia/pior_chute;
            pontos = 100 - percentual;
        }
        if(pontos < 0){
            pontos = 0;
        }
    return pontos; 
}
float pontuacao(cor player, cor maquina, estado *estado_da_partida){
    float pontos = 0;
    float vermelho, verde, azul;
    vermelho = calcula_pontos(player.vermelho, maquina.vermelho);
    verde = calcula_pontos(player.verde, maquina.verde);
    azul = calcula_pontos(player.azul, maquina.azul);
    pontos = (vermelho + verde + azul) / 3;
    pontos = pontos + (pontos * ((5/100)* (15 - estado_da_partida->tempo_de_partida) )) ;
    return pontos;
}
void pontos_placar(int cor_player, int posicao_linha){
    tela_cor_normal();
    posicao pontos = {posicao_linha,2};
    tela_posiciona(pontos);
    printf("%d", cor_player);
/// dá pra resolver esse problema imprimindo com %3d, que imprime o número com 3 caracteres
    if(cor_player > 9 && cor_player < 100){
        putchar(' ');
    }
    if(cor_player< 10){
        printf("  ");
    }
}
void barravermelha(cor *corplayer, posicao posicaoplayer){
    int j=0;
    for(int i=0; i < 255; i+=7){
        posicao barra={8,5+j};
        tela_posiciona(barra);
/// deveria usar a função de tela.h
        printf("\e[48;2;%d;%d;%dm", i, 0, 0);
        putchar(' ');
        j++;
        }
    tela_posiciona(posicaoplayer);    
    printf("\e[48;2;%d;%d;%dm", 255, 255, 255);
    putchar(' '); 
    pontos_placar(corplayer->vermelho, 8);  
}
void barraverde(cor *corplayer, posicao posicaoplayer){
    int j=0;
    for(int i=0; i < 255; i+=7){
        posicao barra={8+1,5+j};
        tela_posiciona(barra);
        printf("\e[48;2;%d;%d;%dm", 0, i, 0);
        putchar(' ');
        j++;
    }
    tela_posiciona(posicaoplayer);
    printf("\e[48;2;%d;%d;%dm", 255, 255, 255);
    putchar(' ');
    pontos_placar(corplayer->verde, 9);
}
void barraazul(cor *corplayer, posicao posicaoplayer){
    int j=0;
    for(int i=0; i < 255; i+=7){
        posicao barra={8+2,5+j};
        tela_posiciona(barra);
        printf("\e[48;2;%d;%d;%dm", 0, 0, i);
        putchar(' ');
        j++;
    }
    tela_posiciona(posicaoplayer);    
    printf("\e[48;2;%d;%d;%dm", 255, 255, 255);
    putchar(' ');
    pontos_placar(corplayer->azul, 10);
}

void controlabarras(cor *player, posicao *posicaoplayer, estado *estado_da_partida){
    barravermelha(player,*posicaoplayer);
    barraverde(player,*posicaoplayer);
    barraazul(player,*posicaoplayer);
/// os componentes da cor deveriam ser independentes entre si
/// te complicou porque tá misturando posição com cor, e espalhando essa
/// mistura pelo resto do programa.
/// a posição deveria ser calculada a partir da cor, e não o contrário, aí não
/// teria essa confusão
    int tecla = tela_le_char();  
    switch (tecla) {
        case c_up:
            if (posicaoplayer->linha > 8) posicaoplayer->linha--;
            break;
        case c_down:
            if (posicaoplayer->linha < 10) posicaoplayer->linha++;
            break;
        case c_left:
            if (posicaoplayer->coluna > 5) posicaoplayer->coluna--;
            break;
        case c_right:
            if (posicaoplayer->coluna < 41) posicaoplayer->coluna++;
            break;
        case c_enter:
            estado_da_partida->terminou = true;
            break;
    }
}
void rodada(double inicio, double *tempo , cor maquina, posicao *posicaoplayer, cor *player, estado *estado_da_partida){
    quadrado_player(player,posicaoplayer);    
    controlabarras(player, posicaoplayer, estado_da_partida);
    *tempo = tela_relogio() - inicio;

}
void guiar_usuario(){
    posicao mensagem = {1,12};
    cor cor_da_mensagem = {255, 255, 255};
    tela_cor_letra(cor_da_mensagem);
    tela_posiciona(mensagem);    
    printf("USANDO CORES RGB");
    cor_da_mensagem.vermelho = 239;
    cor_da_mensagem.verde= 184; 
    cor_da_mensagem.azul = 16;
    mensagem.linha = 2;
    mensagem.coluna = 4;
    tela_posiciona(mensagem);
    tela_cor_letra(cor_da_mensagem);
    printf("ACERTE A COR");
    mensagem.linha = 2;
    mensagem.coluna = 27;
    tela_posiciona(mensagem);
    printf("SUA COR");
}
void nome_do_jogador(estado *estado_da_partida){
    posicao fim_de_jogo = {1,5};
    tela_posiciona(fim_de_jogo);
    printf("DIGITE SEU NOME:");
    scanf("%s", estado_da_partida->nome);    
}
void armazena_cores(cor maquina, cor player, estado *estado_da_partida){
    estado_da_partida->cormaquina[0] = maquina.vermelho;
    estado_da_partida->cormaquina[1] = maquina.verde;
    estado_da_partida->cormaquina[2] = maquina.azul;
    estado_da_partida->corplayer[0] = player.vermelho;
    estado_da_partida->corplayer[1] = player.verde;
    estado_da_partida->corplayer[2] = player.azul;
}
void partida(estado *estado_da_partida){
    tela_cria();    
    tela_limpa();  
    tela_mostra_cursor(false);
    estado_da_partida->terminou = false;
    double inicio = tela_relogio();
    double tempo=0;
    float pontos = 0;
    guiar_usuario();
    cor maquina;
    cormaquina(&maquina);
    quadrado_maquina(maquina);
    cor player = {127,127,127};    
    posicao posicaoplayer = {7+2, 5+ (player.verde%255)/7};
    do {
/// indentação!
    rodada(inicio, &tempo, maquina, &posicaoplayer, &player, estado_da_partida);
  } while ((tempo < 15 && pontos < 100) && estado_da_partida->terminou == false);
    pontos = pontuacao(player, maquina, estado_da_partida);
    armazena_cores(maquina, player, estado_da_partida);     
    estado_da_partida->terminou = true;
    estado_da_partida->tempo_de_partida = tempo;
    estado_da_partida->pontos = pontos;    
    tela_cor_normal();     
    tela_destroi();
/// não deve usar as funções de tela depois de tela_destroi.
    tela_limpa();    
}
void leitura_nomes(nomes *nome_rankers){
    char aux[10];
    FILE *nomes;
    char nome[] = "nome";    
    nomes = fopen(nome, "r");
    if (nomes == NULL) {
        return;
    }
    for(int i=0; i < 3; i++){
        if (fscanf(nomes, "%s\n", aux) != 1) {
            break;
        }
        switch (i){
            case 0: strcpy(nome_rankers->rank1,aux);
                break;
            case 1:strcpy(nome_rankers->rank2,aux);
                break;
            case 2:strcpy(nome_rankers->rank3,aux);
                break;
        }
    }
    fclose(nomes); 
}
void leitura_records(float rankers[],nomes *nome_rankers){
    float val;
    FILE *arq;
    char nome[] = "records";    
    arq = fopen(nome, "r");
    if (arq == NULL) {     
        return;
    }
    for(int i=0; i < 3; i++){
        if (fscanf(arq, "%f\n", &val) != 1) {
/// não pode escrever em um arquivo aberto para leitura. o que está tentando fazer
///   aqui?
            fprintf(arq, "%f\n", 0.0);
        }
        rankers[i] = val; 
    }
    fclose(arq);
    leitura_nomes(nome_rankers);
}

void ordenarank(float rankers[], nomes *nome_rankers){
    int aux;
    char auxnome[10];
    if(rankers[2] > rankers[1]){       
        aux = rankers[1];
        rankers[1] = rankers[2];
        rankers[2] = aux;
        strcpy(auxnome, nome_rankers->rank2);
        strcpy(nome_rankers->rank2, nome_rankers->rank3);
        strcpy(nome_rankers->rank3, auxnome);         
    }
    if(rankers[1] > rankers[0]){       
        aux = rankers[0];
        rankers[0] = rankers[1];
        rankers[1] = aux;
        strcpy(auxnome, nome_rankers->rank1);
        strcpy(nome_rankers->rank1, nome_rankers->rank2);
        strcpy(nome_rankers->rank2, auxnome);             
    }  
}
void atualiza_nomes(nomes *nome_rankers){
    FILE *nomes;
    char nome[] = "nome";
    nomes = fopen(nome, "w");
    if (nomes == NULL) {
        return;
    }
    fprintf(nomes, "%s\n", nome_rankers->rank1);
    fprintf(nomes, "%s\n", nome_rankers->rank2);
    fprintf(nomes, "%s\n", nome_rankers->rank3);
    fclose(nomes); 
}

void atualizar_records(float rankers[], nomes *nome_rankers){
    FILE *arq;
    char nome[] = "records";    
    arq = fopen(nome, "w");
    if (arq == NULL) {
        return;
    }
    for(int i=0; i < 3; i++){
        fprintf(arq, "%f\n", rankers[i]);
    }
    fclose(arq);
/// porque usar 2 arquivos para manter os recordes?
    atualiza_nomes(nome_rankers);
}

void records(estado *estado_da_partida, float rankers[], nomes *nome_rankers){
    ordenarank(rankers, nome_rankers);
    if(estado_da_partida->pontos > rankers[2]){
        rankers[2] = estado_da_partida->pontos;
        strcpy(nome_rankers->rank3,estado_da_partida->nome);
    }
    ordenarank(rankers, nome_rankers);
    atualizar_records(rankers, nome_rankers);
}
int jogar_novamente(estado *estado_da_partida){
    int jogarnovamente;
    posicao fim_de_jogo = {10,5};
    tela_posiciona(fim_de_jogo);
    printf("JOGAR NOVAMENTE: 'Y' OR 'N'\n");
    fim_de_jogo.linha = 11;
    tela_posiciona(fim_de_jogo);
    jogarnovamente = tela_le_char();
    if(jogarnovamente == 'y' || jogarnovamente == 'Y'){
        tela_le_char();
        estado_da_partida->terminou = false;
        return true;
    }
    else{
        return false;
    }
}
void parabens(estado *estado_da_partida, float rankers[]){
    if(estado_da_partida->pontos > rankers[2]){
    posicao parabens_jogador = {8,5};
    tela_posiciona(parabens_jogador);
    cor tela = {239, 184, 16};
    tela_cor_letra(tela);       
    printf("PARABENS VOCÊ ENTROU NO RANK DE RECORDES");
    tela_cor_normal();
    }    
}
void placar_da_partida(estado *estado_da_partida, float rankers[]){
    nome_do_jogador(estado_da_partida);
    tela_limpa();    
    posicao fim_de_jogo = {3, 5};    
    tela_posiciona(fim_de_jogo);
    tela_posiciona(fim_de_jogo);
    cor tela = {239, 184, 16};
    tela_cor_letra(tela);   
    printf("PONTUACAO DA PARTIDA");
    tela_cor_normal();
    fim_de_jogo.linha = 4; 
    tela_posiciona(fim_de_jogo);
    printf("PONTUACAO:%.2f", estado_da_partida->pontos);
    fim_de_jogo.linha = 5;
    tela_posiciona(fim_de_jogo);
    printf("COR DO JOGADOR:%d/%d/%d", estado_da_partida->corplayer[0],estado_da_partida->corplayer[1],estado_da_partida->corplayer[2]);
    fim_de_jogo.linha = 6;
    tela_posiciona(fim_de_jogo);
    printf("COR DA MAQUINA:%d/%d/%d", estado_da_partida->cormaquina[0],estado_da_partida->cormaquina[1],estado_da_partida->cormaquina[2]);
    tela_posiciona(fim_de_jogo);
    fim_de_jogo.linha = 7;
    tela_posiciona(fim_de_jogo);
    printf("NOME:%s", estado_da_partida->nome);
    parabens(estado_da_partida, rankers);
}
void fechar(){
    posicao fechar_jogo = {12,5};
    tela_posiciona(fechar_jogo); 
    printf("PRESSIONE ENTER PARA FECHAR\n");
/// e se não for enter?
    int close = tela_le_char();
    if(close == c_enter){
/// usar as funções de tela.h
/// porque ler um char e ignorar?
        getchar();
    }
    getchar();
    fechar_jogo.coluna = 1;
    fechar_jogo.linha = 1;
    tela_posiciona(fechar_jogo);
    tela_limpa();      
}
void tela_fim(estado estado_da_partida, float rankers[], nomes *nome_rankers){
    tela_limpa();    
    posicao fim_de_jogo = {3, 9};
    tela_posiciona(fim_de_jogo);
    cor tela = {239, 184, 16};
    tela_cor_letra(tela);
    printf("RANKERS");
    tela_cor_normal();
    fim_de_jogo.coluna = 5;
    fim_de_jogo.linha = 4;
    tela_posiciona(fim_de_jogo); 
    printf("1.%.2f - %s ", rankers[0], nome_rankers->rank1);
    fim_de_jogo.linha = 5;
    tela_posiciona(fim_de_jogo);
    printf("2.%.2f - %s", rankers[1], nome_rankers->rank2);
    fim_de_jogo.linha = 6;
    tela_posiciona(fim_de_jogo);
    printf("3.%.2f - %s", rankers[2], nome_rankers->rank3);
    fechar();
}
int main(){
    srand(time(0));
    estado estado_da_partida;
    nomes nome_rankers;
    float rankers[3];
    leitura_records(rankers, &nome_rankers);
    do{
/// indentação
    partida(&estado_da_partida);
    placar_da_partida(&estado_da_partida, rankers);           
    jogar_novamente(&estado_da_partida);
    records(&estado_da_partida, rankers, &nome_rankers);
    } while (estado_da_partida.terminou == false);
    tela_fim(estado_da_partida, rankers, &nome_rankers);    
}
