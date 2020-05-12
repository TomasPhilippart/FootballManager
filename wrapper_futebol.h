#ifndef WRAPPER_FUTEBOL
#define WRAPPER_FUTEBOL

#include "hashtable.h"

/* ========================= ESTRUTURAS  ============================= */
/* EQUIPA: caracterizada por um nome e o numero de jogos ganhos */
typedef struct equipa {
    char *nome;
    int jogos_ganhos;
} equipa;

/* JOGO: caracterizada por um nome, duas equipas e uma pontuacao (score) */
typedef struct jogo {
    char *nome_equipa1, *nome_equipa2;
    int score_eq1, score_eq2;
    char *nome;  
} jogo;

/* ========================= CRIACAO  ============================= */
equipa cria_equipa(char *nome, int jogos_ganhos);
jogo cria_jogo(char *nome, char *nome_equipa1, char *nome_equipa2, int score_eq1, int score_eq2);

/* ========================= INSERCAO  ============================= */
bool insere_equipa(table *t, char *chave, equipa *equipa);
bool insere_jogo(table *t, table *t_equipas, char *chave, jogo *jogo);

/* ========================= REMOCAO  ============================= */
bool remove_equipa(table *t, char *chave);
bool remove_jogo(table *t_jogos, table *t_equipas, char *chave);

/* ========================= PROCURA  ============================= */
equipa *procura_equipa(table *t, char *chave);
jogo *procura_jogo(table *t, char *chave);

/* ========================= AUXILIARES  ============================= */
bool muda_pontuacao(table *t_equipas, jogo *jogo, int score1, int score2);

#endif