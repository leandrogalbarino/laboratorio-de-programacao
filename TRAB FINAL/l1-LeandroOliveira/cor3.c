// não consegui corrigir todo o código, mas arrumei algumas coisas
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
    cor cor_do_quadrado = {pintar->vermelho, pintar->verde, pintar->azul};
    tela_cor_fundo(cor_do_quadrado);
    putchar(' ');
}

void desenha_quadrado(cor *quadrado, posicao posicao_do_desenho){
    for(int i=0; i <= 10; i++){
        for(int j=0; j < 4; j++){
            posicao pos_do_quadrado = {posicao_do_desenho.linha+j,posicao_do_desenho.coluna+i};
            tela_posiciona(pos_do_quadrado);
            pintaquadrado(quadrado);       
        }
    }
    tela_cor_normal();
    putchar(' ');
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
    printf("%3d", cor_player);
}
void barravermelha(cor *corplayer){
    int j=0;
    cor vermelho = {255, 0, 0};
    cor cor_selecionada = {255,255,255};
    for(int i=0; i < 255; i+=7){
        posicao barra={8,5+j};
        tela_posiciona(barra);
        tela_cor_fundo(vermelho);   
        putchar(' ');
        j++;
        }
    tela_posiciona((posicao) { 8, 5 + (corplayer->vermelho % 255) / 7 });
    tela_cor_fundo(cor_selecionada);   
    putchar(' '); 
    pontos_placar(corplayer->vermelho, 8);  
}
void barraverde(cor *corplayer){
    int j=0;
    cor verde = {0, 255, 0};
    cor cor_selecionada = {255,255,255};
    for(int i=0; i < 255; i+=7){
        posicao barra={8+1,5+j};
        tela_posiciona(barra);
        tela_cor_fundo(verde);   
        putchar(' ');
        j++;
    }
    tela_posiciona((posicao) { 8 + 1, 5 + (corplayer->verde % 255) / 7 });
    tela_cor_fundo(cor_selecionada);   
    putchar(' ');
    pontos_placar(corplayer->verde, 9);
}
void barraazul(cor *corplayer) {
    int j = 0;
    cor azul = {0, 0, 255};
    cor cor_selecionada = {255,255,255};    
    for (int i = 0; i < 255; i += 7) {
        posicao barra = { 8 + 2, 5 + j };
        tela_posiciona(barra);
        tela_cor_fundo(azul);
        putchar(' ');
        j++;
    }
    tela_posiciona((posicao) { 8 + 2, 5 + (corplayer->azul % 255) / 7 });
    tela_cor_fundo(cor_selecionada);
    putchar(' ');
    pontos_placar(corplayer->azul, 10);
}
void barra_selecionada(int *barra_seleciona, char direcao) {
    if (direcao == 'c') {
        if (*barra_seleciona > 8) {
            (*barra_seleciona)--;
        }
    } else if (direcao == 'd') {
        if (*barra_seleciona < 10) {
            (*barra_seleciona)++;
        }
    }
}
void borda_das_barras(int valor_da_barra, posicao *posicao_atual, cor *player){
    switch (valor_da_barra) {
        case 8:
            posicao_atual->linha = 8;
            posicao_atual->coluna = 5 + (player->vermelho % 255) / 7;
            break;
        case 9:
            posicao_atual->linha = 8 + 1;
            posicao_atual->coluna = 5 + (player->verde % 255) / 7;        
            break;
        case 10:
            posicao_atual->linha = 8 + 2;
            posicao_atual->coluna = 5 + (player->azul % 255) / 7;
            break;        
        default:
            break;
    }
}
void altera_barra(int valor_barra_selecionada, char direcao, cor *player) {
    posicao posicao_atual;
    borda_das_barras(valor_barra_selecionada, &posicao_atual, player);
    tela_posiciona(posicao_atual);
    if (direcao == 'e' && posicao_atual.coluna > 5) {
        if (valor_barra_selecionada == 8)
            (*player).vermelho -= 7;
        else if (valor_barra_selecionada == 9)
            (*player).verde -= 7;
        else if (valor_barra_selecionada == 10)
            (*player).azul -= 7;
    }
    else if (direcao == 'd' && posicao_atual.coluna < 41) {
        if (valor_barra_selecionada == 8)
            (*player).vermelho += 7;
        else if (valor_barra_selecionada == 9)
            (*player).verde += 7;
        else if (valor_barra_selecionada == 10)
            (*player).azul += 7;
    }
}
void controlabarras(cor *player, posicao *posicaoplayer, estado *estado_da_partida){
    barravermelha(player);
    barraverde(player);
    barraazul(player);
    int tecla = tela_le_char();  
    int valor_barra_selecionada = posicaoplayer->linha;
    switch (tecla) {
        case c_up:
            barra_selecionada(&valor_barra_selecionada, 'c');
            posicaoplayer->linha = valor_barra_selecionada;
            break;
        case c_down:
            barra_selecionada(&valor_barra_selecionada, 'd');
            posicaoplayer->linha = valor_barra_selecionada;
            break;
        case c_left:
            altera_barra(valor_barra_selecionada, 'e', player);
            break;
        case c_right:
            altera_barra(valor_barra_selecionada, 'd', player);
            break;
        case c_enter:
            estado_da_partida->terminou = true;
            break;
    }
}
void rodada(double inicio, double *tempo , cor maquina, posicao *posicaoplayer, cor *player, estado *estado_da_partida){
    posicao posicao_do_desenho = {3,25};
    desenha_quadrado(player, posicao_do_desenho);
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
    scanf("%7s", estado_da_partida->nome);    
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
    posicao posicao_do_desenho = {3,5};
    desenha_quadrado(&maquina,posicao_do_desenho);
    cor player = {127,127,127};    
    posicao posicaoplayer = {8, 5+ (player.verde%255)/7};
    do {
        rodada(inicio, &tempo, maquina, &posicaoplayer, &player, estado_da_partida);
  } while ((tempo < 15 && pontos < 100) && estado_da_partida->terminou == false);
    pontos = pontuacao(player, maquina, estado_da_partida);
    armazena_cores(maquina, player, estado_da_partida);     
    estado_da_partida->terminou = true;
    estado_da_partida->tempo_de_partida = tempo;
    estado_da_partida->pontos = pontos;    
    tela_cor_normal();
    tela_destroi();
    tela_limpa();  
}
void leitura_nomes(nomes *nome_rankers){
    FILE *nomes;
    char nome[] = "nome";
    char vetor_nulo[10]= {};
    char aux[10];
    int i;    
    nomes = fopen(nome, "r");
    if (nomes == NULL) {
        return;
    }
    char *nomes_players[] = {
        nome_rankers->rank1,
        nome_rankers->rank2,
        nome_rankers->rank3        
    };
    for (i = 0; i < 3; i++) {
        if (fscanf(nomes, "%s\n", aux) != 1) {
            strcpy(nomes_players[i], vetor_nulo);
        }
        else {
            strcpy(nomes_players[i], aux);
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
            rankers[i] = 0; 
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
    int close = tela_le_char();
    if(close == c_enter){
        close = tela_le_char();      
    }
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
        partida(&estado_da_partida);
        placar_da_partida(&estado_da_partida, rankers);           
        jogar_novamente(&estado_da_partida);
        records(&estado_da_partida, rankers, &nome_rankers);
    } while (estado_da_partida.terminou == false);
    tela_fim(estado_da_partida, rankers, &nome_rankers);    
}