#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>

/* Verfica se houve alguma falha ao alocar memoria */
void verificaFalhaAlloc(void *p) {
    if (p == NULL) {
        printf("Falha ao tentar alocar memoria!");
        exit(1);
    }
}

/* Cria uma lista ligada */
p_no criaLista() {
    return NULL;
}

/* Destroi uma lista ligada */
void destroiLista(p_no lista) {
    if (lista != NULL) {
        destroiLista(lista->prox);
        free(lista);
    }
}

/* Libera uma lista ligada e retorna NULL */
p_no liberaLista(p_no lista) {
    destroiLista(lista);
    return NULL;
}

/* Insere em uma lista ligada */
p_no insereLista(p_no lista, int v) {
    p_no novo = malloc(sizeof(No));
    verificaFalhaAlloc(novo);
    novo->prox = lista;
    novo->v = v;
    return novo;
}

/* Busca em uma lista ligada */
int buscaLista(p_no lista, int v) {
    for (p_no t = lista; lista != NULL; t = t->prox)
        if (t->v == v)
            return 1;
    return 0;
}

/* Cria um grafo com n vertices*/
p_grafo criaGrafo(int n) {
    p_grafo grafo = malloc(sizeof(Grafo));
    verificaFalhaAlloc(grafo);
    grafo->adj = calloc(n, sizeof(p_no));
    verificaFalhaAlloc(grafo->adj);
    grafo->tamanho = n;
    return grafo;
}

/* Libera um grafo e retorna NULL */
p_grafo liberaGrafo(p_grafo grafo) {
    if (grafo == NULL)
        return grafo;
    for (int i = 0; i < grafo->tamanho ; i++)
        grafo->adj[i] = liberaLista(grafo->adj[i]);
    free(grafo->adj);
    free(grafo);
    return NULL;
}

/* Cria uma aresta entre o vertice u e o vertice w */
void insereAresta(p_grafo grafo, int u, int w) {
    grafo->adj[u] = insereLista(grafo->adj[u], w);
    grafo->adj[w] = insereLista(grafo->adj[w], u);
}

/* Verifica se ha aresta entre u e w */
int verificaAresta(p_grafo grafo, int u, int w) {
    return (buscaLista(grafo->adj[u], w));
}
