#include "tela.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct{
    int pontos;
    char nome_do_jogador[10];
    bool venceu;
    bool jogar;
}estado ;
typedef struct{
    char nome_do_primeiro[10];
    char nome_do_segundo[10];
    char nome_do_terceiro[10];
    char nome_do_quarto[10];
    char nome_do_quinto[10];    
    int pontos_do_jogador[5];
} rank;
bool gera_nova_letra(char tabuleiro[][5]){
    int linha, coluna;
    while(true){
        linha = rand()%5;
        coluna = rand()%5;
        if(tabuleiro[linha][coluna] == '\0'){
            if(rand()%4 == 0){
                tabuleiro[linha][coluna] = 'B';                                                         
                return true;
            }
            else{               
                tabuleiro[linha][coluna] = 'A';
                return true;
            }
        }
    }
    return false;
}
int cor_retangulo_da_letra(char letra){
    switch (letra){
    case 'A':
            return tela_cria_cor(0.40,0.50,0.55);
        break;
    case 'B':
            return tela_cria_cor(0.54,0.40,0.50);
        break;
    case 'C':
            return tela_cria_cor(0.54, 0.44, 0.39);
        break;
    case 'D':
            return tela_cria_cor(0.39, 0.54, 0.44);
        break;
    case 'E':
            return tela_cria_cor(0.43, 0.78, 0.94);
        break;
    case 'F':
            return tela_cria_cor(0.91, 0.49, 0.74);
        break;               
    default:
        break;
    }
    return 0;    
}
void desenha_letras_no_tabuleiro(char tabuleiro [][5], int i, int j){
    int cor;    
    char vetor_de_controle[3] = {0};                 
    cor = cor_retangulo_da_letra(tabuleiro[i-1][j-1]);
    vetor_de_controle[0] = tabuleiro[i-1][j-1]; 
    tela_retangulo(j*100,i*100,(j+1)*100,(i+1)*100,5,8,cor);
    tela_texto(100*(j+1) - 50,100*(i+1) - 50,50,8,vetor_de_controle);
}
void desenha_partes_vazias_do_tabuleiro(int i, int j){
    tela_retangulo(j*100,i*100,(j+1)*100,(i+1)*100,5,8,tela_cria_cor(0.52, 0.83, 0.78));    
}
void desenha_interface(char tabuleiro[][5], char pontos[]){
    tela_retangulo(0,0,700,700,5,8,tela_cria_cor(0.01, 0.01,0.2));
    tela_texto(70,70, 20, 8, pontos);      
    for(int i=1;i <= 5; i++){
        for(int j=1; j <= 5;j++){
            if(tabuleiro[i-1][j-1] == '\0'){
                desenha_partes_vazias_do_tabuleiro(i,j);
            }
            else{
                desenha_letras_no_tabuleiro(tabuleiro, i,j);
            }
        }
    }
}
void rotacionar_tabuleiro(char tabuleiro[][5]) {
    char temp[5][5];
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            temp[j][4 - i] = tabuleiro[i][j];
        }
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            tabuleiro[i][j] = temp[i][j];
        }
    }
}
void direcao_do_movimento(char tabuleiro[][5],char direcao){
    if(direcao == 'd'){
        rotacionar_tabuleiro(tabuleiro);
        rotacionar_tabuleiro(tabuleiro);                       
    }
    if(direcao == 'e'){
        rotacionar_tabuleiro(tabuleiro);
        rotacionar_tabuleiro(tabuleiro);
        rotacionar_tabuleiro(tabuleiro);
        rotacionar_tabuleiro(tabuleiro);                
    }
    if(direcao == 'c'){
        rotacionar_tabuleiro(tabuleiro);
        rotacionar_tabuleiro(tabuleiro);
        rotacionar_tabuleiro(tabuleiro); 
    }
    if(direcao == 'b'){
        rotacionar_tabuleiro(tabuleiro);
    }
}
void faz_movimento(char tabuleiro[][5]){
    for(int l=0; l < 5; l++){
        for(int c=0;c < 5; c++){
            if(tabuleiro[l][c] == 0){
                for(int j=c; j < 5; j++){
                    if(tabuleiro[l][j] != 0){
                        tabuleiro[l][c] = tabuleiro[l][j];
                        tabuleiro[l][j] = 0;
                        break;
                    }
                }
            }
        }
    }
}
void copia_matriz(char tabuleiro[][5], char tabuleiro_de_verificacao[][5]){
    int i,j;
    for(i=0; i<5; i++){
        for(j=0; j<5; j++){
            tabuleiro_de_verificacao[i][j] = tabuleiro[i][j];
        }
    }
}
bool verifica_mudanca(char tabuleiro[][5], char tabuleiro_de_verificacao[][5]){
    int i,j;    
    for(i=0; i<5; i++){
        for(j=0; j<5; j++){
            if(tabuleiro_de_verificacao[i][j] != tabuleiro[i][j]){
                return true;
            }    
        }
    }
    return false;
}
bool espaco_na_matriz(char tabuleiro[][5]){
    for(int i=0; i < 5; i++){
        for(int j=0; j < 5; j++){
            if(tabuleiro[i][j] == '\0'){
                return true;
                break;
            }
        }
    }
    return false;
}
void junta_letras(char tabuleiro[][5]){
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 3; j++){
            if(tabuleiro[i][j] == tabuleiro[i][j+1] && tabuleiro[i][j] == tabuleiro[i][j+2] && tabuleiro[i][j] != 0){
                tabuleiro[i][j] = tabuleiro[i][j] + 1; // próxima letra da tabela ASCII
                tabuleiro[i][j+1] = 0;
                tabuleiro[i][j+2] = 0;
            }
        }
    }
}
//26 linhas
int pontos_letras_juntadas(char tabuleiro[][5]){
    int i,j;
    for(i=0; i < 5; i++){
        for(j=0; j < 3; j++){
            if((tabuleiro[i][j] == tabuleiro[i][j+1]) &&  (tabuleiro[i][j] == tabuleiro[i][j+2] && tabuleiro[i][j] != 0)){                                             
                tabuleiro[i][j] = tabuleiro[i][j] + 1; // próxima letra da tabela ASCII
                tabuleiro[i][j+1] = 0;
                tabuleiro[i][j+2] = 0;                
                switch (tabuleiro[i][j]){
                    case 'B':
                        return 30;
                    case 'C':
                        return 90;
                    case 'D':
                        return 270;
                    case 'E':
                        return 810;
                    case 'F':
                        return 2430;                                                                                                             
                    default:
                        break;
                }
            }
        }
    }
    return 0;
}
void pontuacao(char tabuleiro[][5], char tabuleiro_de_verificacao[][5], int *pontos){
    int i, j;
    char teste[5][5]={};
    copia_matriz(tabuleiro_de_verificacao, teste);
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (tabuleiro[i][j] != tabuleiro_de_verificacao[i][j]) {
                faz_movimento(teste);
                if ((teste[i][j] == teste[i][j + 1]) && (teste[i][j] == teste[i][j + 2])) {
                        *pontos+=pontos_letras_juntadas(teste);
                        i+=2;
                } else if (tabuleiro[i][j] != tabuleiro_de_verificacao[i][j] && tabuleiro[i][j] != 0) {
                    (*pontos)++;
                    }
                }
            }
        }
}
void calcula_pontos( char tabuleiro[][5], char tabuleiro_de_verificacao[][5], char direcao, int *pontos ){
    switch (direcao){
    case 'c':
        direcao_do_movimento(tabuleiro_de_verificacao, 'c');         
        pontuacao(tabuleiro,tabuleiro_de_verificacao,pontos);
        direcao_do_movimento(tabuleiro_de_verificacao, 'b');   
        break;
    case 'b':
        direcao_do_movimento(tabuleiro_de_verificacao, 'b');         
        pontuacao(tabuleiro,tabuleiro_de_verificacao,pontos);
        direcao_do_movimento(tabuleiro_de_verificacao, 'c');   
        break;
    case 'd':
        direcao_do_movimento(tabuleiro_de_verificacao, 'd');         
        pontuacao(tabuleiro,tabuleiro_de_verificacao,pontos);
        direcao_do_movimento(tabuleiro_de_verificacao, 'd'); 
        break;
    case 'e':
        pontuacao(tabuleiro,tabuleiro_de_verificacao,pontos);
        break;                                
    default:
        break;
    }    
}
void movimentacao(char tabuleiro[][5], char direcao ){
    switch (direcao){
    case 'c':
            direcao_do_movimento(tabuleiro,'c');
            faz_movimento(tabuleiro);
        break;
    case 'b':
            direcao_do_movimento(tabuleiro,'b');
            faz_movimento(tabuleiro);
        break;
    case 'e':
            faz_movimento(tabuleiro);
        break;
    case 'd':
            direcao_do_movimento(tabuleiro,'d');
            faz_movimento(tabuleiro);
        break;                        
    default:
        break;
    }
}
void movimenta_e_inverte(char tabuleiro[][5], char direcao){
    switch (direcao){
    case 'c':
            faz_movimento(tabuleiro);
            direcao_do_movimento(tabuleiro, 'b');    
        break;
    case 'b':
            faz_movimento(tabuleiro);
            direcao_do_movimento(tabuleiro, 'c');         
        break;
    case 'e':
            faz_movimento(tabuleiro);
        break;
    case 'd':
            faz_movimento(tabuleiro);
            direcao_do_movimento(tabuleiro, 'd');
        break;                    
    default:
        break;
    }
}
//28 linhas
void altera_tabuleiro(char tabuleiro[][5], int *tecla, char tabuleiro_de_verificacao[][5], int *pontos){
    *tecla = tela_tecla();
    char direcao;
    switch (*tecla){
        case c_up:
            direcao = 'c';
            break;
        case c_down: 
            direcao = 'b';
            break;
        case c_left: 
            direcao = 'e';
            break;
        case c_right: 
            direcao = 'd';        
            break;
        default: 
            *tecla = 0;
            return;
    }
    movimentacao(tabuleiro, direcao);
    junta_letras(tabuleiro);
    calcula_pontos(tabuleiro,tabuleiro_de_verificacao,direcao,pontos);
    movimenta_e_inverte(tabuleiro, direcao);
    if (!verifica_mudanca(tabuleiro, tabuleiro_de_verificacao) && espaco_na_matriz(tabuleiro)){
        altera_tabuleiro(tabuleiro,tecla, tabuleiro_de_verificacao, pontos);
    }    
}
bool venceu(char tabuleiro[][5]){
    int i,j;
    for(i=0; i < 5; i++){
        for(j=0; j < 5; j++){
            if(tabuleiro[i][j] == 'F'){
                       return true;    
            }
        }
    }
    return false;    
}
void desenha_interface_game_over(char tabuleiro[][5], char pontos_desenho[]){
    desenha_interface(tabuleiro, pontos_desenho);
    tela_retangulo(10,300,690,400,5,tela_cria_cor(0.91, 0.49, 0.74),tela_cria_cor(0.51, 0.56, 0.77));      
    tela_texto(350,350,100,8 ,"GAME OVER");
    tela_retangulo(470,407,690,427,1,0,tela_cria_cor(0.51, 0.56, 0.77));      
    tela_texto_esq(680,410,12,8,"PRECIONE ENTER PARA FECHAR");
    tela_atualiza();              
}
void desenha_interface_vitoria(char tabuleiro[][5], char pontos_desenho[]){
    desenha_interface(tabuleiro, pontos_desenho);            
    tela_retangulo(10,300,690,400,5,tela_cria_cor(0.75, 0.91, 0.97), tela_cria_cor(0.8, 0.63, 0.87));      
    tela_texto(350,350,90,8 ,"VOCÊ VENCEU");
    tela_retangulo(470,407,690,427,1,0,tela_cria_cor(0.8, 0.63, 0.87));      
    tela_texto_esq(680,410,12,8,"PRECIONE ENTER PARA FECHAR");            
    tela_atualiza();    
}
void desenha_fim_do_jogo(char tabuleiro[][5], char pontos_desenho[]){
    int tecla = 0;
    if(!venceu(tabuleiro)){  
        while(true){
            tecla = tela_tecla();
            desenha_interface_game_over(tabuleiro, pontos_desenho);
            if(tecla == c_enter){
                break;
            }   
        }
    }
    else{
        while(true){
            tecla = tela_tecla();
            desenha_interface_vitoria(tabuleiro, pontos_desenho);
            if(tecla == c_enter){
                break;
            }   
        }
    }
}
void verifica_fim_da_partida(estado *estado_da_partida, char tabuleiro[][5], int pontos) {
    char pontos_desenho[5] = {};
    sprintf(pontos_desenho, "%04d", pontos);  
    if (!espaco_na_matriz(tabuleiro) || venceu(tabuleiro)) {
        desenha_fim_do_jogo(tabuleiro, pontos_desenho);
        estado_da_partida->jogar = false;
    }
    else {
        gera_nova_letra(tabuleiro);        
    }
}
void executar_turno(estado *estado_da_partida, char tabuleiro[][5], int *tecla, int *pontos) {
    char pontos_desenho[5] = {};
    char tabuleiro_de_verificacao[5][5];
    copia_matriz(tabuleiro, tabuleiro_de_verificacao);
    altera_tabuleiro(tabuleiro, tecla, tabuleiro_de_verificacao, pontos);
    sprintf(pontos_desenho, "%04d", *pontos);
    desenha_interface(tabuleiro, pontos_desenho);
    estado_da_partida->pontos = *pontos;
    tela_atualiza();
}
void partida(estado *estado_da_partida, char tabuleiro[][5]) {
    int tecla;
    int pontos = estado_da_partida->pontos;
    while (true) {
        executar_turno(estado_da_partida, tabuleiro, &tecla, &pontos);
        if (tecla == c_up || tecla == c_down || tecla == c_left || tecla == c_right) {
            break;
        }
    }
    verifica_fim_da_partida(estado_da_partida, tabuleiro, pontos);
}
void desenha_nome_do_jogador(char nome[]){
    tela_retangulo(0,0,700,700,5,8,tela_cria_cor(0.01, 0.01,0.2));
    tela_texto(350,250,40,8,"DIGITE SEU NOME, JOGADOR");       
    tela_retangulo(100,300,600,400,5, tela_cria_cor(0.91, 0.49, 0.74), tela_cria_cor(0.51, 0.56, 0.77));
    tela_texto(350,350, 50,8 , nome);
    tela_retangulo(370,407,610,427,1,0,tela_cria_cor(0.51, 0.56, 0.77));      
    tela_texto_esq(600,410,12,8,"PRECIONE ENTER PARA CONFIRMAR");
}
//26 linhas
void nome_do_jogador(estado *estado_da_partida){
    int tecla = 0;
    int i = 0;
    char nome[10] = {};
    desenha_nome_do_jogador(nome);
    tela_atualiza();
    while(true){
        tecla = tela_tecla();
        if((tecla >= 'A' && tecla <= 'Z') || (tecla >= 'a' && tecla <= 'z')){
            nome[i] = tecla;    
            desenha_nome_do_jogador(nome);
            tela_atualiza();
            i++;
        }
        if(tecla == c_back && i > 0){
            i--;
            nome[i] = 0;
            desenha_nome_do_jogador(nome);
            tela_atualiza();            
        }
        if(tecla == c_enter || i > 8 || tecla == ' '){
            strcpy(estado_da_partida->nome_do_jogador,nome);            
            break;
        }
    }
}
void inicia_partida(char tabuleiro[][5], estado *estado_da_partida){
    char pontos[5] = {};
    estado_da_partida->jogar = true;
    estado_da_partida->pontos = 0;
    gera_nova_letra(tabuleiro);
    gera_nova_letra(tabuleiro);
    desenha_interface(tabuleiro, pontos);
    tela_atualiza();
}
void ler_pontos(FILE *arq, rank *rankers) {
    int val, i;
    for (i = 0; i < 5; i++) {
        if (fscanf(arq, "%d\n", &val) != 1) {
            rankers->pontos_do_jogador[i] = 0;
        }
        else {
            rankers->pontos_do_jogador[i] = val;
        }
    }
}
void ler_nomes(FILE *arq, rank *rankers) {
    char aux[10];
    char vetor_nulo[10] = {0};
    char *nomes[] = {
        rankers->nome_do_primeiro,
        rankers->nome_do_segundo,
        rankers->nome_do_terceiro,
        rankers->nome_do_quarto,
        rankers->nome_do_quinto
    };
    int i;
    for (i = 0; i < 5; i++) {
        if (fscanf(arq, "%s\n", aux) != 1) {
            strcpy(nomes[i], vetor_nulo);
        }
        else {
            strcpy(nomes[i], aux);
        }
    }
}
void leitura_records(rank *rankers) {
    FILE *arq;
    char nome[] = "records";
    arq = fopen(nome, "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    ler_pontos(arq, rankers);
    ler_nomes(arq, rankers);
    fclose(arq);
}
void escreve_nomes_no_arquivo(FILE *arq, rank *rankers){
        fprintf(arq, "%s\n", rankers->nome_do_primeiro);
        fprintf(arq, "%s\n", rankers->nome_do_segundo);
        fprintf(arq, "%s\n", rankers->nome_do_terceiro);
        fprintf(arq, "%s\n", rankers->nome_do_quarto);
        fprintf(arq, "%s\n", rankers->nome_do_quinto);   
}
void escreve_pontos_no_arquivo(FILE *arq, rank *rankers){
    int i;    
    for(i=0; i < 5; i++){
       fprintf(arq, "%d\n", rankers->pontos_do_jogador[i]);
    }
}
void atualizar_records(rank *rankers){
    FILE *arq;
    char nome[] = "records";    
    arq = fopen(nome, "w");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    escreve_pontos_no_arquivo(arq, rankers);
    escreve_nomes_no_arquivo(arq, rankers); 
    fclose(arq);
}
void ordena_nomes(rank *rankers, int posicao) {
    char auxnome[10];
    char *nomes[] = {
        rankers->nome_do_primeiro,
        rankers->nome_do_segundo,
        rankers->nome_do_terceiro,
        rankers->nome_do_quarto,
        rankers->nome_do_quinto
    };
    if (posicao >= 1 && posicao < 5) {
        strcpy(auxnome, nomes[posicao - 1]);
        strcpy(nomes[posicao - 1], nomes[posicao]);
        strcpy(nomes[posicao], auxnome);
    }
}
void ordenarank(rank *rankers){
    int aux;
    for(int i = 4; i > 0; i--)
    if(rankers->pontos_do_jogador[i] > rankers->pontos_do_jogador[i-1]){       
        aux = rankers->pontos_do_jogador[i-1];
        rankers->pontos_do_jogador[i-1] = rankers->pontos_do_jogador[i];
        rankers->pontos_do_jogador[i]  = aux;
        ordena_nomes(rankers, i);     
    }
}
void records(estado *estado_da_partida, rank *rankers){
    ordenarank(rankers);
    if(estado_da_partida->pontos > rankers->pontos_do_jogador[4]){
        rankers->pontos_do_jogador[4] = estado_da_partida->pontos;
        strcpy(rankers->nome_do_quinto,estado_da_partida->nome_do_jogador);
    }
    ordenarank(rankers);
    atualizar_records(rankers);
}
void desenha_colocacao_rankers(){
    tela_texto_esq(260,240,20,8, "1°-");
    tela_texto_esq(260,290,20,8, "2°-");
    tela_texto_esq(260,340,20,8, "3°-");
    tela_texto_esq(260,390,20,8, "4°-");
    tela_texto_esq(260,440,20,8, "5°-");  
}
void desenha_pontuacao_rankers(rank rankers){
    char pontos[5][8];
    for (int i = 0; i < 5; i++) {
        sprintf(pontos[i], "%04d", rankers.pontos_do_jogador[i]);
    }    
    tela_texto_dir(265,240,20,8, pontos[0]);
    tela_texto_dir(265,290,20,8, pontos[1]);
    tela_texto_dir(265,340,20,8, pontos[2]);
    tela_texto_dir(265,390,20,8, pontos[3]);
    tela_texto_dir(265,440,20,8, pontos[4]);
}
void desenha_nomes_rankers(rank rankers){
    tela_texto_dir(350,240,20,8, rankers.nome_do_primeiro);
    tela_texto_dir(350,290,20,8, rankers.nome_do_segundo);
    tela_texto_dir(350,340,20,8, rankers.nome_do_terceiro);
    tela_texto_dir(350,390,20,8, rankers.nome_do_quarto);
    tela_texto_dir(350,440,20,8, rankers.nome_do_quinto);
}
void interface_records(rank rankers){
    int tecla;
    while(true){
        tecla = tela_tecla();
        tela_retangulo(0,0,700,700,5,8,tela_cria_cor(0.01, 0.01,0.2));
        tela_texto(350,170,40,8,"RECORDS");       
        tela_retangulo(200,200,500,500,5, tela_cria_cor(0.91, 0.49, 0.74), tela_cria_cor(0.51, 0.56, 0.77));
        desenha_colocacao_rankers();      
        desenha_pontuacao_rankers(rankers);
        desenha_nomes_rankers(rankers);
        tela_retangulo(297,507,510,527,1,0,tela_cria_cor(0.51, 0.56, 0.77));      
        tela_texto_esq(500,510,12,8,"PRECIONE ENTER PARA FECHAR");
        tela_atualiza();                
        if(tecla == c_enter){
            break;
        }   
    }    
}
int main(){
    estado estado_da_partida;
    rank rankers;
    srand(time(0));
    tela_inicio(700, 700, "EFE");
    char tabuleiro[5][5] = {0};
    leitura_records(&rankers);
    inicia_partida(tabuleiro,&estado_da_partida);  
    do{         
    partida(&estado_da_partida, tabuleiro);
    }while(estado_da_partida.jogar == true);
    nome_do_jogador(&estado_da_partida);
    records(&estado_da_partida, &rankers);
    interface_records(rankers);
    tela_fim();
}