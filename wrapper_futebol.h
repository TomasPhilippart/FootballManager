#ifndef WRAPPER_FUTEBOL
#define WRAPPER_FUTEBOL

#include "hashtable.h"

/* Estrutura Equipa */
typedef struct equipa {
    char *nome;
    int jogos_ganhos;
} equipa;

/* Estrutura Jogo, caracterizada por um nome, duas equipas e uma pontuacao (score) */
typedef struct jogo {
    char *nome_equipa1, *nome_equipa2;
    int score_eq1, score_eq2;
    char *nome;  
} jogo;


/* criacao */
equipa cria_equipa(char *nome, int jogos_ganhos);
jogo cria_jogo(char *nome, char *nome_equipa1, char *nome_equipa2, int score_eq1, int score_eq2);

/* insercao */
void insere_equipa(table *t, char *chave, equipa *equipa);
void insere_jogo(table *t, table *t_equipas, char *chave, jogo *jogo);

/* remocao */
void remove_equipa(table *t, char *chave);
void remove_jogo(table *t, char *chave);

/* funcoes de procura */
equipa *procura_equipa(table *t, char *chave);
jogo *procura_jogo(table *t, char *chave);

/* modificacao */
void muda_pontuacao(table *t, table *t_equipas, jogo *jogo, int score1, int score2);

#endif