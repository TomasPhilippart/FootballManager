#include <stdio.h>
#include "wrapper_futebol.h"

/* funcoes "wrappers" para nao ter de ser preocupar com casting */

/* criacao */
equipa cria_equipa(char *nome, int jogos_ganhos) {
    equipa nova_equipa;
    nova_equipa.nome = nome;
    nova_equipa.jogos_ganhos = jogos_ganhos;

    return nova_equipa;
}

jogo cria_jogo(char *nome, char *nome_equipa1, char *nome_equipa2, int score_eq1, int score_eq2) {
    jogo novo_jogo;
    novo_jogo.nome = nome;
    novo_jogo.nome_equipa1 = nome_equipa1;
    novo_jogo.nome_equipa2 = nome_equipa2;
    novo_jogo.score_eq1 = score_eq1;
    novo_jogo.score_eq2 = score_eq2;

    return novo_jogo;
}

/* insercao*/
void insere_equipa(table *t, char *chave, equipa *equipa) { 
    insere_tabela(t, chave, (void *)equipa, sizeof(struct equipa));
}

void insere_jogo(table *t, table *t_equipas, char *chave, jogo *jogo) { 

    equipa *equipa1, *equipa2;
    insere_tabela(t, chave, (void *)jogo, sizeof(struct jogo));
    
    /* atualiza numero de jogos ganhos das equipas */
    equipa1 = procura_equipa(t_equipas, jogo->nome_equipa1);
    equipa2 = procura_equipa(t_equipas, jogo->nome_equipa2); 
    
    /* FIXME: ISTO ESTA A DAR ERRO: PORQUE JOGO->NOME_EQUIPA E LIXO, MESMO PROBLEMA DE HA POUCO */
    if ((equipa1 != NULL) && (equipa2 != NULL)) {
        /* calcula quem ganhou*/
        if (jogo->score_eq1 > jogo->score_eq2) {
            equipa1->jogos_ganhos++;
        } else if (jogo->score_eq2 > jogo->score_eq1) {
            equipa2->jogos_ganhos++;
        }

    } else {
        printf("Equipas nao encontradas.\n");
    }
}

/* remocao */
void remove_equipa(table *t, char *chave) { 
    remove_tabela(t, chave);
}

void remove_jogo(table *t, char *chave) { 
    remove_tabela(t, chave);
}

/* procura */
equipa *procura_equipa(table *t, char *chave) {
    return (equipa *) procura_tabela(t, chave);
}

jogo *procura_jogo(table *t, char *chave) {
    return (jogo *) procura_tabela(t, chave);
}

/* modifica */
void muda_pontuacao(table *t, table *t_equipas, jogo *jogo, int score1, int score2) {
    jogo->score_eq1 = score1;
    jogo->score_eq2 = score2;

    /* aproveitar o facto de que insere_jogo atualiza valores */
    insere_jogo(t, t_equipas, jogo->nome, jogo);
}