#include "listaLegal.h"
#include <stdio.h>
#include <stdlib.h>

p_no criaArvoreRN() {
    return NULL;
}

int noVermelho(p_no raiz) {
    if (raiz == NULL)
        return 0;
    return raiz->cor == VERMELHO;
}

int noPreto(p_no raiz) {
    return !noVermelho(raiz);
}

p_no rotacionaEsquerda(p_no raiz) {
    p_no x = raiz->dir;
    raiz->dir = x->esq;
    x->esq = raiz;
    x->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return x;
}

p_no rotacionaDireita(p_no raiz) {
    p_no x = raiz->esq;
    raiz->esq = x->dir;
    x->dir = raiz;
    x->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return x;
}

void sobeVermelho(p_no raiz) {
    raiz->esq->cor = PRETO;
    raiz->dir->cor = PRETO;
    raiz->cor = VERMELHO;
}

p_no insereOrdenadoRec(p_no raiz, long long int num) {
    if (raiz == NULL) {
        p_no novoNo = malloc(sizeof(No));
        novoNo->cor = VERMELHO;
        novoNo->esq = novoNo->dir = NULL;
        novoNo->num = num;
        novoNo->qtd = 1;
        return novoNo;
    }

    if (num < raiz->num)
        raiz->esq = insereOrdenadoRec(raiz->esq, num);
    else if (num > raiz->num)
        raiz->dir = insereOrdenadoRec(raiz->dir, num);
    
    if (raiz->num == num)
        raiz->qtd++;
    else {
        if (noPreto(raiz->esq) && noVermelho(raiz->dir))
            raiz = rotacionaEsquerda(raiz);
        if (noVermelho(raiz->esq) && noVermelho(raiz->esq->esq))
            raiz = rotacionaDireita(raiz);
        if (noVermelho(raiz->esq) && noVermelho(raiz->dir))
            sobeVermelho(raiz);
    }

    return raiz;
}

p_no insereOrdenado(p_no raiz, long long int num) {
    p_no arvore;
    arvore = insereOrdenadoRec(raiz, num);
    arvore->cor = PRETO;
    return arvore;
}

long long int qtdVezesAparece(p_no raiz, long long int num) {
    if (raiz == NULL)
        return 0;
    
    else if (num < raiz->num)
        return qtdVezesAparece(raiz->esq, num);
    else if (num > raiz->num)
        return qtdVezesAparece(raiz->dir, num);
    
    return raiz->qtd;
}

void qtdParaLegal(p_no raiz, long long int *qtd) {
    if (raiz != NULL) {
        qtdParaLegal(raiz->esq, qtd);
        if (raiz->qtd < raiz->num)
            *qtd += raiz->qtd;
        else if (raiz->qtd > raiz->num)
            *qtd += (raiz->qtd - raiz->num);
        qtdParaLegal(raiz->dir, qtd);
    }
}

void imprimeInOrdem(p_no raiz) {
    if (raiz != NULL) {
        imprimeInOrdem(raiz->esq);
        printf("%lli %lli\n", raiz->num, raiz->qtd);
        imprimeInOrdem(raiz->dir);
    }
}

void liberaArvoreRN(p_no raiz) {
    if (raiz != NULL) {
        liberaArvoreRN(raiz->esq);
        liberaArvoreRN(raiz->dir);
        free(raiz);
    }
}

int verificaArvoreRubroNegra(p_no raiz) {
    if (raiz == NULL)
        return 1;

    if (raiz->cor == VERMELHO) {
        if (raiz->esq && raiz->esq->cor == VERMELHO)
            return 0;
        if (raiz->dir && raiz->dir->cor == VERMELHO)
            return 0;
    }

    return (verificaArvoreRubroNegra(raiz->esq) 
            && verificaArvoreRubroNegra(raiz->dir));
}
