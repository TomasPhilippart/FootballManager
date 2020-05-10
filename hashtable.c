#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*#include <assert.h> */
#include "hashtable.h"

/* equivalente a strdup, duplica uma string */
char *dupstring(const char *src) {
    char *dest = (char *) malloc(strlen(src) + 1);

    /* assert(src != NULL); */
    /* assert(dest != NULL); */
    strcpy(dest, src);

    return dest;
}

node *cria_elemento(char *chave, void *valor, int size) {
    /*assert(chave != NULL && valor != NULL);*/

    node *new_node = (node *) malloc(sizeof(node));

    /* verificar que foi alocada memoria */
    if (new_node == NULL) return NULL;

    new_node->chave = dupstring(chave);
    new_node->valor = malloc(size);
    memcpy(new_node->valor, valor, size); 

    return new_node;
}

/* destroi um elemento duma tabela e a memoria associada a ele */
void apaga_elemento(node *elemento) {
    free(elemento->valor);
    free(elemento->chave);
    free(elemento);
}

/* funcao que cria hash table com um dado size*/
table *cria_tabela(int tamanho) { 
    /* assert(tamanho > 0);*/

    int i;

    table *t = (table *) malloc(sizeof(table));
    /* assert(t != NULL); */

    t->tamanho = tamanho;
    t->lista = (node**) malloc(tamanho * sizeof(node*));  
    /* assert(t->lista != NULL); */

    /* inicializa a lista com ponteiros nulos (tb podia usar calloc()) */
    for (i = 0; i < tamanho; i++)
        t->lista[i] = NULL;

    return t;
}

/* Implementacao do algoritmo de Dan Bernstein, "djb2"*/
int hash(table *t, char *chave) {
    /* assert(t != NULL && chave != NULL); */

    int hash = 5381;
    int c;

    while ((c = *chave++)) {
        hash = (((hash << 5) + hash) + c) % t->tamanho; /* (hash*33 + c) % tamanho */
    }
    /* assert(hash < t->tamanho); */

    return hash;
}

/* funcao que insere/atualiza valor numa tabela */
void insere_tabela(table *t, char *chave, void *valor, unsigned int size) { 
    /* assert(t != NULL && chave != NULL && valor != NULL); */

    int pos = hash(t, chave);
    node *lista = t->lista[pos];
    node *new_node; /* alocar so se for necessario! */
    node *temp;

    for (temp = lista; temp != NULL; temp = temp->next) { 
        /* assert(temp->chave != NULL && temp->valor != NULL); */

        /* se encontrarmos a nossa chave, atualizar o valor */
        if (strcmp(temp->chave, chave) == 0) {
            memcpy(temp->valor, valor, size); /* porque valor e um ponteiro para void */
            return;
        }
    }

    /* alocar e inserir no fim */
    new_node = cria_elemento(chave, valor, size);
    new_node->next = lista;
    t->lista[pos] = new_node;
}

/* funcao que retorna ponteiro para o valor ou NULL se nao existir */
void *procura_tabela(table *t, char *chave) {
    /* assert(t != NULL && chave != NULL); */

    int pos = hash(t, chave);
    node *temp;

    for (temp = t->lista[pos]; temp != NULL; temp = temp->next) {
        /* assert(temp->chave  != NULL && temp->valor != NULL); */

        /* se encontrar, retornar pointeiro */
        if (strcmp(temp->chave, chave) == 0) {
            return temp->valor;
        }
    }
    return NULL;
}

/* funcao que remove valor numa tabela, pela chave */
void remove_tabela(table *t, char *chave) { 
    /* assert(t != NULL && chave != NULL); */

    int pos = hash(t, chave);
    node *temp = t->lista[pos];
    node *prev = NULL;

    while (temp != NULL) { 
        
        /* encontrado o elemento */
        if (strcmp(temp->chave, chave) == 0) {

            /* se for a head da lista*/
            if (prev == NULL) {
                t->lista[pos] = temp->next;
            } else {
                prev->next = temp->next;
            }
            apaga_elemento(temp);
            return;
        }

        prev = temp;
        temp = temp->next;
    }
}

/* implementar um "foreach" sobre a tabela de hash */
void iterar_tabela(table *t, bool (* funcao)(char *chave, void *valor, void *contexto), void *contexto) {
    /* assert(t != NULL && funcao != NULL); */

    int i;
    node *temp;

    for (i = 0; i < t->tamanho; i++) {
        
        for (temp = t->lista[i]; temp != NULL; temp = temp->next) {
            /* assert(temp->chave != NULL && temp->valor != NULL); */

            /* para quando a funcao retorna false */
            if (!funcao(temp->chave, temp->valor, contexto)) return;
        }
    }

}

/* funcao que apaga toda a memoria associada a tabela */
void destroi_tabela(table *t) {
    /* assert(t != NULL); */

    int i;
    node *temp, *next;

    for (i = 0; i < t->tamanho; i++) {
        temp = t->lista[i];

        /* apagar todos os elementos da lista */
        while (temp != NULL) {
            next = temp->next;
            apaga_elemento(temp);
            temp = next;
        }
    }

    /* apaga a estrutura em si */
    free(t->lista);
    free(t);
}