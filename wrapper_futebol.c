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

void insere_jogo(table *t, char *chave, jogo *jogo) { 
    insere_tabela(t, chave, (void *)jogo, sizeof(struct jogo));
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