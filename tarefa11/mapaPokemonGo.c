#include "mapaPokemonGo.h"
#include "minHeap.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_LUGIA_INICIAL 10

/* Cria um mapa com n pontos de parada */
p_mapa criaMapa(int n) {
    p_mapa mapa = malloc(sizeof(MapaPokemonGo));
    verificaFalhaAlloc(mapa);
    mapa->grafo = NULL;
    mapa->posicoes = malloc(n * sizeof(Posicao));
    verificaFalhaAlloc(mapa->posicoes);
    mapa->verticesLugia = malloc(MAX_LUGIA_INICIAL * sizeof(int));
    verificaFalhaAlloc(mapa->verticesLugia);
    mapa->qtd = 0;
    mapa->qtdLugia = 0;
    mapa->tamanhoLugia = MAX_LUGIA_INICIAL;
    mapa->tamanho = n;
    return mapa;
}

/* Libera um mapa e retorna NULL */
p_mapa liberaMapa(p_mapa mapa) {
    mapa->grafo = liberaGrafo(mapa->grafo);
    free(mapa->posicoes);
    free(mapa->verticesLugia);
    free(mapa);
    return NULL;
}

/* Insere um jogador no mapa de acordo com sua posição */
void insereJogador(p_mapa mapa, double xy[2]) {
    mapa->posicoes[0].xy[0] = xy[0];
    mapa->posicoes[0].xy[1] = xy[1];
    mapa->posicoes[0].lugia = 0;
    if (mapa->qtd == 0) {
        mapa->qtd++;
    }
}

/* Insere uma PokeStop no mapa de acordo com sua posição */
void inserePokeStop(p_mapa mapa, double xy[2]) {
    verificaTamanhoMapa(mapa);
    mapa->posicoes[mapa->qtd].xy[0] = xy[0];
    mapa->posicoes[mapa->qtd].xy[1] = xy[1];
    mapa->posicoes[mapa->qtd].lugia = 0;
    mapa->qtd++;
}

/* Insere uma Lugia no mapa de acordo com sua posição */
void insereLugia(p_mapa mapa, double xy[2]) {
    verificaTamanhoMapa(mapa);
    mapa->posicoes[mapa->qtd].xy[0] = xy[0];
    mapa->posicoes[mapa->qtd].xy[1] = xy[1];
    mapa->posicoes[mapa->qtd].lugia = 1;
    if (mapa->tamanhoLugia == mapa->qtdLugia) {
        mapa->verticesLugia = realloc(mapa->verticesLugia, 2 * mapa->tamanhoLugia * sizeof(int));
        verificaFalhaAlloc(mapa->verticesLugia);
        mapa->tamanhoLugia = 2 * mapa->tamanhoLugia;
    }
    mapa->verticesLugia[mapa->qtdLugia] = mapa->qtd;
    mapa->qtd++;
    mapa->qtdLugia++;
}

/* Verifica se precis aumentar o tamanho do mapa, i.e, o vetor de posicoes */
void verificaTamanhoMapa(p_mapa mapa) {
    if (mapa->qtd == mapa->tamanho) {
        mapa->posicoes = realloc(mapa->posicoes, 2 * mapa->tamanho * sizeof(Posicao));
        verificaFalhaAlloc(mapa->posicoes);
        mapa->tamanho = 2 * mapa->tamanho;
    }
}

/* Modela o mapa utilizando um grafo */
void modelaMapa(p_mapa mapa) {
    mapa->grafo = criaGrafo(mapa->qtd);
    for (int i = 0; i < mapa->qtd; i++)
        for (int j = 0; j < mapa->qtd; j++) 
            if (i != j)
                insereAresta(mapa->grafo, i, j);
}

/* Calcula a distancia euclidiana */
double distEuclidiana(double p1[2], double p2[2]) {
    return sqrt(((p1[0] - p2[0]) * (p1[0] - p2[0]))  + 
            ((p1[1] - p2[1]) * (p1[1] - p2[1])));
}

/* Tendo um mapa, modela um grafo e a partir dele retorna uma arvore
   onde as arestas que compoem os caminhos da raiz v até os vertices
   (paradas: PokeStop, Lugia, Jogador) são minimas */ 
int * encontraArvoreArestasMinimas(p_mapa mapa, int v) {
    int s;
    double distancia;
    NoHeap arestaMin;
    int *pai = calloc(mapa->qtd, sizeof(int));
    verificaFalhaAlloc(pai);
    p_heap minHeap = criaHeapMin(mapa->qtd);

    modelaMapa(mapa);

    for (int i = 0; i < mapa->qtd; i++) {
        insereHeap(minHeap, distEuclidiana(mapa->posicoes[0].xy, mapa->posicoes[i].xy), i);
    }

    while (!vazio(minHeap)) {
        arestaMin = removeMin(minHeap);
        s = arestaMin.v;
        for (p_no t = mapa->grafo->adj[s]; t != NULL; t = t->prox) {
            distancia = distEuclidiana(mapa->posicoes[t->v].xy, mapa->posicoes[s].xy);
            if (prioridade(minHeap, t->v) > distancia) {
                alteraPrioridade(minHeap, distancia, t->v);
                pai[t->v] = s;
            }
        }
    }

    minHeap = liberaHeapMin(minHeap);
    
    return pai;
}

void printaArvore(int *pai, int v) {
    if (v != 0)
        printaArvore(pai, pai[v]);
    printf("%d\n", v);
}
