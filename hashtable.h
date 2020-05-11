#ifndef HASHTABLE
#define HASHTABLE
#include <stdbool.h>

/* estruturas relativas a hashtable com encadeamento externo (listas ligadas) */
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

/* funcao que cria um elemento a partir duma dada chave, valor e tamanho*/
node *cria_elemento(char *chave, void *valor, int size);

/* funcao que apaga um elemento, libertando a memoria associada */
void apaga_elemento(node *elemento);

/* funcao que cria hashtable com um dado size*/
table *cria_tabela(int tamanho);

/* Implementacao do algoritmo de Dan Bernstein, "djb2"*/
int hash(table *t, char *chave);

/* funcao que insere/atualiza valor numa tabela */
void insere_tabela(table *t, char *chave, void *valor, unsigned int size);

/* funcao que retorna ponteiro para o valor ou NULL se nao existir */
void *procura_tabela(table *t, char *chave);

/* remove da tabela o elemento referido por chave (tambem liberta a memoria alocada)*/
void remove_tabela(table *t, char *chave);

/* executa a funcao sobre todos os elementos da tabela enquanto essa funcao retorna true */
void iterar_tabela(table *t, bool (* funcao)(char *chave, void *valor, void *contexto), void *contexto);

/* apaga todos os elementos da tabela, libertando a memoria alocada na heap */
void destroi_tabela(table *t);

#endif