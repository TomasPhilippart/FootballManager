#ifndef HASHTABLE
#define HASHTABLE
#include <stdbool.h>

/* declaracao das estruturas privadas */
typedef struct node node;

/* LISTA DE CHAVES: array dinamico que mantem conta da ordem pela qual
   um item foi introduzido na hashtable, guardando a sua chave  */
typedef struct chaves {
    char **lista_chaves;
    int tamanho;           /* capacidade alocada */
    int ultima_chave;
} chaves;

typedef struct table table;

char *dupstring(const char *src);

/* funcao que devolve um ponteiro para a estrutura chaves de uma tabela t */
chaves *devolve_chaves(table *t);

/* funcoes de destrucao (libertando memoria associada) */
void destroi_equipa(void *equipa_original);
void destroi_jogo(void *jogo_original);

/* funcao que cria hashtable com um dado size*/
table *cria_tabela(int tamanho);

/* funcao que insere/atualiza valor numa tabela */
bool insere_tabela(table *t, char *chave, void *valor, void *(* copiar)(void *valor));

/* funcao que retorna ponteiro para o valor ou NULL se nao existir */
void *procura_tabela(table *t, char *chave);

/* remove da tabela o elemento referido por chave (tambem liberta a memoria alocada)*/
bool remove_tabela(table *t, char *chave, void (* destroi)(void *valor));

/* executa a funcao sobre todos os elementos da tabela enquanto essa funcao retorna true */
void iterar_tabela(table *t, bool (* funcao)(char *chave, void *valor, void *contexto), void *contexto);

/* apaga todos os elementos da tabela, libertando a memoria alocada na heap */
void destroi_tabela(table *t, void (* destroi)(void *valor));

#endif