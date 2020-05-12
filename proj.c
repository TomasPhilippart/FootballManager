#include <stdio.h>
#include <stdlib.h>
#include "wrapper_futebol.h"

#define MAX_STR 1024
#define M_EQUIPAS 701 /* ver isto*/ 
#define M_JOGOS 701 /* ver isto */

/* ========================= PROTOTIPOS  ============================= */
/* declaracao de funcoes: optei por manter os nomes das funcoes
   iguais aos comandos que as invocam por questoes de nao interferencia
   com as outras funcoes.  */
void a(table *jogos, table *equipas, int numero_linha);
void A(table *equipas, int numero_linha);
void l();
void p(table *jogos, int numero_linha);
void P(table *equipas, int numero_linha);
void r(table *jogos, table *equipas, int numero_linha);
void s(table *jogos, table *equipas, int numero_linha);
void g();

/* ============================== MAIN ============================= */
int main() {

    /* criacao de hashtables para equipas e jogos */
    table *equipas = cria_tabela(M_EQUIPAS);
    table *jogos = cria_tabela(M_JOGOS);

    int ch, numero_linha = 0;

    while (1) {
        numero_linha++;

        switch(ch = getchar()) {
            
            /* Adiciona jogo */
            case 'a': 
                a(jogos, equipas, numero_linha);
                break;
             
            /* Adiciona equipa */
            case 'A':
                A(equipas, numero_linha);
                break;
            
                
            /* Lista todos os jogos pela ordem de entrada */
            case 'l':  
                l(jogos, numero_linha);
                break;

            /* Procura um jogo */
            case 'p': 
                p(jogos, numero_linha);
                break;
            
            /* Procura uma equipa */
            case 'P': 
                P(equipas, numero_linha);
                break;
            
            /* Apaga um jogo */
            case 'r': 
                r(jogos, equipas, numero_linha);
                break;
            
                
            /* Altera a pontuação de um jogo */
            case 's': 
                s(jogos, equipas, numero_linha);
                break;
            

            
            /* TODO: Encontra as equipas que venceram mais jogos */
            case 'g': {
                /*g();*/
                break;
            }

            /* Termina o programa */
            case 'x': 
                destroi_tabela(equipas, destroi_equipa);
                destroi_tabela(jogos, destroi_jogo);
                return 0;
            
        }
    }
}



void a(table *jogos, table *equipas, int numero_linha) {

    int score_eq1, score_eq2;

    /* strings na stack para ler input*/
    char nome[MAX_STR], nome_eq1[MAX_STR], nome_eq2[MAX_STR];
    jogo novo_jogo;

    /* le input */
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", nome, nome_eq1, nome_eq2, &score_eq1, &score_eq2);

    /* verifica se o jogo ja existe */
    if (procura_jogo(jogos, nome) != NULL) {
        printf("%d Jogo existente.\n", numero_linha);
    
    /* verifica se as equipas existem */
    } else if (procura_equipa(equipas, nome_eq1) == NULL || procura_equipa(equipas, nome_eq2) == NULL) {
        printf("%d Equipa inexistente.\n", numero_linha);

    } else {
        /* cria novo jogo e insere */
        novo_jogo = cria_jogo(nome, nome_eq1, nome_eq2, score_eq1, score_eq2);
        insere_jogo(jogos, equipas, novo_jogo.nome, &novo_jogo);
    }
}

void A(table *equipas, int numero_linha) {

    equipa nova_equipa;
    char nome[MAX_STR];

    /* le input */
    scanf(" %[^:\n]", nome);

    /* verifica se a equipa ja existe */
    if (procura_equipa(equipas, nome) != NULL) {
        printf("%d Equipa existente.\n", numero_linha);

    } else {
        /* cria nova equipa e insere */
        nova_equipa = cria_equipa(nome, 0);
        insere_equipa(equipas, nova_equipa.nome, &nova_equipa);
    }
}

void l(table *jogos, int numero_linha) {
    chaves *chaves = devolve_chaves(jogos);
    jogo *jogo;
    int i;

    /* para cada elemento de lista de chaves diferente de NULL, imprimir o jogo correspondente (se existir)*/
    for (i = 0; i < chaves->ultima_chave; i++) {
        if (chaves->lista_chaves[i] != NULL) {
            if ((jogo = procura_jogo(jogos, chaves->lista_chaves[i])) != NULL) {
                printf("%d %s %s %s %d %d\n", numero_linha, jogo->nome, jogo->nome_equipa1, jogo->nome_equipa2, jogo->score_eq1, jogo->score_eq2);
            }
        }
        
    }
    
}

void p(table *jogos, int numero_linha) {

    jogo *jogo;

    char nome[MAX_STR];
    /* le input */
    scanf(" %[^:\n]", nome);

    /* verifica se o jogo existe */
    if ((jogo = procura_jogo(jogos, nome)) == NULL) {
        printf("%d Jogo inexistente.\n", numero_linha);

    } else {
        printf("%d %s %s %s %d %d\n", numero_linha, jogo->nome, jogo->nome_equipa1, jogo->nome_equipa2, jogo->score_eq1, jogo->score_eq2);
    }
}

void P(table *equipas, int numero_linha) {

    equipa *equipa;
    char nome[MAX_STR];

    /* le input */
    scanf(" %[^:\n]", nome);

    /* verifica se a equipa existe */
    if ((equipa = procura_equipa(equipas, nome)) == NULL) {
        printf("%d Equipa inexistente.\n", numero_linha);

    } else {
        printf("%d %s %d\n", numero_linha, nome, equipa->jogos_ganhos);
    }
}

void r(table *jogos, table *equipas, int numero_linha) {

    char nome[MAX_STR];

    /* le input */
    scanf(" %[^:\n]", nome);

    /* verifica se o jogo existe */
    if (!remove_jogo(jogos, equipas, nome)) 
        printf("%d Jogo inexistente.\n", numero_linha);

}

void s(table *jogos, table *equipas, int numero_linha) {

    int score1, score2;
    char nome[MAX_STR];
    jogo *jogo;
    
    /* le input */
    scanf(" %[^:\n]:%d:%d", nome, &score1, &score2);

    /* verifica se o jogo existe */
    if ((jogo = procura_jogo(jogos, nome)) == NULL) {
        printf("%d Jogo inexistente.\n", numero_linha);
    } else {
        muda_pontuacao( equipas, jogo, score1, score2);
    }
}

/* TODO */
void g();