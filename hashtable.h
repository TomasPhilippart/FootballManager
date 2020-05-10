#ifndef HASHTABLE
#define HASHTABLE

#include <stdbool.h>

typedef struct node {
    char *chave;
    void *valor;
    struct node *next;
} node;

typedef struct table {
    node **lista;
    int tamanho;   
} table;

/* equivalente a strdup, duplica uma string */
char *dupstring(const char *src);

node *cria_elemento(char *chave, void *valor, int size);

void apaga_elemento(node *elemento);

/* funcao que cria hash table com um dado size*/
table *cria_tabela(int tamanho);

/* Implementacao do algoritmo de Dan Bernstein, "djb2"*/
int hash(table *t, char *chave);

/* funcao que insere/atualiza valor numa tabela */
void insere_tabela(table *t, char *chave, void *valor, unsigned int size);

/* funcao que retorna ponteiro para o valor ou NULL se nao existir */
void *procura_tabela(table *t, char *chave);

void remove_tabela(table *t, char *chave);

/* executa a funcao sobre todos os elementos da tabela enquanto essa funcao retorna true */
void iterar_tabela(table *t, bool (* funcao)(char *chave, void *valor, void *contexto), void *contexto);

void destroi_tabela(table *t);

#endif