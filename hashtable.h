#ifndef HASHTABLE
#define HASHTABLE
#include <stdbool.h>

/* ========================= ESTRUTURAS  ============================= */
/* privadas */
typedef struct node node;
typedef struct table table;


char *dupstring(const char *src);

/* ========================= FUNCOES DA HASHTABLE  ============================= */
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

/* executa a funcao sobre todos os elementos da tabela na mesma ordem que foram inserido */
void iterar_ordenado(table *t, bool (* funcao)(char *chave, void *valor, void *contexto), void *contexto);

/* apaga todos os elementos da tabela, libertando a memoria alocada na heap */
void destroi_tabela(table *t, void (* destroi)(void *valor));

#endif