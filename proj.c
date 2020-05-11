#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"
#include "wrapper_futebol.h"

#define MAX_STR 1024
#define M_EQUIPAS 701 /* ver isto*/ 
#define M_JOGOS 701 /* ver isto */

int main() {

    /* hashtables */
    table *equipas = cria_tabela(M_EQUIPAS);
    table *jogos = cria_tabela(M_JOGOS);

    /* array de ponteiros para jogos, de forma a manter conta da ordem da sua entrada */
    jogo **lista_jogos_por_entrada = (jogo **) malloc(M_JOGOS * sizeof(jogo*));
    int num_jogos = 0;

    int ch, numero_linha = 0;
    /* buffers temporarios usado para ler input de strings */
    char buffer_temp1[MAX_STR], buffer_temp2[MAX_STR], buffer_temp3[MAX_STR];

    while (1) {

        numero_linha++;
        switch(ch = getchar()) {
            
            /* REVIEW: Adiciona jogo */
            case 'a': {

                char *nome_jogo, *nome_eq1, *nome_eq2;
                int score_eq1, score_eq2;
                jogo novo_jogo;


                /* le input */
                scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", buffer_temp1, buffer_temp2, buffer_temp3, &score_eq1, &score_eq2);
                nome_jogo = dupstring(buffer_temp1);
                nome_eq1 = dupstring(buffer_temp2);
                nome_eq2 = dupstring(buffer_temp3);
            
                /* verifica se o jogo ja existe */
                if (procura_jogo(jogos, nome_jogo) != NULL) {
                    printf("%d Jogo existente.\n", numero_linha);
                
                /* verifica se as equipas existem */
                } else if (procura_equipa(equipas, nome_eq1) == NULL || procura_equipa(equipas, nome_eq2) == NULL) {
                    printf("%d Equipa inexistente.\n", numero_linha);

                } else {
                    /* cria novo jogo e insere */
                    novo_jogo = cria_jogo(nome_jogo, nome_eq1, nome_eq2, score_eq1, score_eq2);
                    insere_jogo(jogos, equipas, novo_jogo.nome, &novo_jogo);

                    /* REVIEW: adicionar jogo a lista de jogos por ordem */
                    if (num_jogos > M_JOGOS / 2) {
                        /* quando a lista esta a metade, re-alocar memoria para o dobro */
                        lista_jogos_por_entrada = (jogo **) realloc(lista_jogos_por_entrada,  M_JOGOS * 2 * sizeof(jogo *));
                    } 
                    lista_jogos_por_entrada[num_jogos] = &novo_jogo;
                    num_jogos++;
                }

                /* apaga todos os inputs temporarios */
                free(nome_jogo);
                free(nome_eq1);
                free(nome_eq2);
                break;
            }
                
            /* Adiciona equipa */
            case 'A': {

                char *nome;
                equipa nova_equipa;

                /* le input */
                scanf(" %[^:\n]", buffer_temp1);
                nome = dupstring(buffer_temp1);

                /* verifica se a equipa ja existe */
                if (procura_equipa(equipas, nome) != NULL) {
                    printf("%d Equipa existente.\n", numero_linha);

                } else {
                    /* cria nova equipa e insere */
                    nova_equipa = cria_equipa(nome, 0);
                    insere_equipa(equipas, nova_equipa.nome, &nova_equipa);
                }

                /* apaga todos os inputs temporarios */
                free(nome);
                break;
            }
                
            /* FIXME: Lista todos os jogos pela ordem de entrada */
            case 'l': {
                
                jogo *jogo;
                int i = 0;

                /* FIXME: imprime n vezes o ultimo jogo criado...*/
                for (jogo = lista_jogos_por_entrada[i]; i < num_jogos; i++) {
                    if (jogo != NULL) {
                        printf("%d %s %s %s %d %d\n", numero_linha, jogo->nome, jogo->nome_equipa1, jogo->nome_equipa2, jogo->score_eq1, jogo->score_eq2);
                    }
                }

                break;
            }

            /* Procura um jogo */
            case 'p': {
                char *nome;
                jogo *jogo;

                /* le input */
                scanf(" %[^:\n]", buffer_temp1);
                nome = dupstring(buffer_temp1);

                /* verifica se o jogo existe */
                if ((jogo = procura_jogo(jogos, nome)) == NULL) {
                    printf("%d Jogo inexistente.\n", numero_linha);

                } else {
                    printf("%d %s %s %s %d %d\n", numero_linha, nome, jogo->nome_equipa1, jogo->nome_equipa2, jogo->score_eq1, jogo->score_eq2);
                }

                /* apaga todos os inputs temporarios */
                free(nome);
                break;
            }
            
            /* Procura uma equipa */
            case 'P': {

                char *nome;
                equipa *equipa;

                /* le input */
                scanf(" %[^:\n]", buffer_temp1);
                nome = dupstring(buffer_temp1);

                /* verifica se a equipa existe */
                if ((equipa = procura_equipa(equipas, nome)) == NULL) {
                    printf("%d Equipa inexistente.\n", numero_linha);

                } else {
                    printf("%d %s %d\n", numero_linha, nome, equipa->jogos_ganhos);
                }

                /* apaga todos os inputs temporarios */
                free(nome);
                break;

            }
            
            /* Apaga um jogo */
            case 'r': {
                char *nome;
                jogo *jogo;


                /* le input */
                scanf(" %[^:\n]", buffer_temp1);
                nome = dupstring(buffer_temp1);

                /* verifica se o jogo existe */
                if ((jogo = procura_jogo(jogos, nome)) == NULL) {
                    printf("%d Jogo inexistente.\n", numero_linha);

                } else {
                    remove_jogo(jogos, nome);
                }

                /* apaga todos os inputs temporarios */
                free(nome);
                break;
            }
                
            /* Altera a pontuação de um jogo */
            case 's': {

                char *nome;
                int score1, score2;
                jogo *jogo;

                /* le input */
                scanf(" %[^:\n]:%d:%d", buffer_temp1, &score1, &score2);
                nome = dupstring(buffer_temp1);

                /* verifica se o jogo existe */
                if ((jogo = procura_jogo(jogos, nome)) == NULL) {
                    printf("%d Jogo inexistente.\n", numero_linha);

                } else {
                    muda_pontuacao(jogos, equipas, jogo, score1, score2);
                }


                /* apaga todos os inputs temporarios */
                free(nome);
                break;
            }

            
            /* TODO: Encontra as equipas que venceram mais jogos */
            case 'g':
                break;

            /* Termina o programa */
            case 'x':
                destroi_tabela(equipas);
                destroi_tabela(jogos);
                return 0;

        }
    }
}

