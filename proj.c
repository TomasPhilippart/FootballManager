#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"
#include "wrapper_futebol.h"

#define MAX_STR 1024
#define M_EQUIPAS 701 /* ver isto*/ 
#define M_JOGOS 701 /* ver isto */

int main() {

    table *equipas = cria_tabela(M_EQUIPAS);
    table *jogos = cria_tabela(M_JOGOS);

    int ch, numero_linha = 0;
    char buffer_temp[MAX_STR];

    while (1) {
        
        switch(ch = getchar()) {

            /* Adiciona jogo */
            case 'a': {

                char *nome_jogo, *nome_eq1, *nome_eq2;
                int score_eq1, score_eq2;
                jogo novo_jogo;

                numero_linha++;

                /* le input */
                scanf(" %[^:\n]", buffer_temp);
                nome_jogo = dupstring(buffer_temp);

                scanf(":%[^:\n]", buffer_temp);
                nome_eq1 = dupstring(buffer_temp);

                scanf(":%[^:\n]", buffer_temp);
                nome_eq2 = dupstring(buffer_temp);

                scanf(":%d:%d", &score_eq1, &score_eq2);

                /* verifica se o jogo ja existe */
                if (procura_jogo(jogos, nome_jogo) != NULL) {
                    printf("%d Jogo existente.\n", numero_linha);
                
                /* verifica se as equipas existem */
                } else if (procura_equipa(equipas, nome_eq1) == NULL || procura_equipa(equipas, nome_eq2) == NULL) {
                    printf("%d Equipa inexistente.\n", numero_linha);

                } else {
                    /* cria novo jogo e insere */
                    novo_jogo = cria_jogo(nome_jogo, nome_eq1, nome_eq2, score_eq1, score_eq2);
                    insere_jogo(jogos, novo_jogo.nome, &novo_jogo);
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

                numero_linha++;

                /* le input */
                scanf(" %[^:\n]", buffer_temp);
                nome = dupstring(buffer_temp);

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
                
            /* Lista todos os jogos pela ordem de entrada */
            case 'l':
                break;
            
            /* Procura um jogo */
            case 'p':
                break;
            
            /* Procura uma equipa */
            case 'P':
                break;
            
            /* Apaga um jogo */
            case 'r':
                break;
            
            /* Altera a pontuação de um jogo */
            case 's':
                break;
            
            /* Encontra as equipas que venceram mais jogos */
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

