#include "minHeap.h"
#include <stdio.h>
#include <stdlib.h>

void verificaAlocao(void *p) {
    if (p == NULL) {
        printf("Erro ao tentar alocar memoria ...");
        exit(1);
    }
}

/* Cria um heap binário de minimo */
p_heap criaHeapMin(int n) {
    p_heap heap = malloc(sizeof(MinHeap));
    verificaAlocao(heap);
    heap->v = malloc(n * sizeof(NoHeap));
    verificaAlocao(heap->v);
    for (int i = 0; i < n; i++)
        heap->v[i].dist = heap->v[i].v = 0;
    heap->tamanho = n;
    heap->n = 0;
    return heap;
}

/* libera um heap binario de minimo */
p_heap liberaHeapMin(p_heap heap) {
    free(heap->v);
    free(heap);
    return NULL;
}

/* Sobe um no do heap de acordo com sua chave dist*/
void sobeNoHeap(p_heap heap, int i) {
    NoHeap aux;
    if (heap->v[i].dist < heap->v[PAI(i)].dist) {
        aux = heap->v[PAI(i)];
        heap->v[PAI(i)] = heap->v[i];
        heap->v[i] = aux;
        sobeNoHeap(heap, PAI(i));
    }
}

/* Desce um no no heap de acordo com sua chave dist */
void desceNoHeap(p_heap heap, int i) {
    int menorFilho;
    NoHeap aux;
    if (F_ESQ(i) < heap->n) {
        menorFilho = F_ESQ(i);
        if (F_DIR(i) < heap->n && heap->v[F_DIR(i)].dist < heap->v[menorFilho].dist)
            menorFilho = F_DIR(i);
        if (heap->v[i].dist > heap->v[menorFilho].dist) {
            aux = heap->v[menorFilho];
            heap->v[menorFilho] = heap->v[i];
            heap->v[i] = aux;
            desceNoHeap(heap, menorFilho);
        }
    }
}

/* Insere no heap */
void insereHeap(p_heap heap, double d, int v) {
    heap->v[heap->n].dist = d;
    heap->v[heap->n].v = v;
    heap->n++;
    sobeNoHeap(heap, heap->n - 1);
}

/* Retorna a prioridade de um elemento v do heap */
double prioridade(p_heap heap, int v) {
    for (int i = 0; i < heap->n; i++)
        if (heap->v[i].v == v)
            return heap->v[i].dist;
    return -1;
}

/* Altera a prioridade de um elemento v do heap */
void alteraPrioridade(p_heap heap, double d, int v) {
    double prioridade;
    for (int i = 0; i < heap->n; i++)
        if (heap->v[i].v == v) {
            prioridade = heap->v[i].dist;
            heap->v[i].dist = d;
            if (prioridade < heap->v[i].dist)
                desceNoHeap(heap, i);
            else if (prioridade > heap->v[i].dist)
                sobeNoHeap(heap, i);
            break;
        }
}

/* Verifica se o heap esta vazio */
int vazio(p_heap heap) {
    return !heap->n;
}

/* Remove o minimo do heap */
NoHeap removeMin(p_heap heap) {
    NoHeap min = heap->v[0];
    heap->v[0] = heap->v[heap->n - 1];
    heap->n--;
    desceNoHeap(heap, 0);
    return min;
}
