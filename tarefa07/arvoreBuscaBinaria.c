#include "arvoreBuscaBinaria.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Verifica se um ponteiro recem alocado é NULL, se sim termina o programa */
void sem_memoria(void *p) {
    if (p == NULL) {
        printf("Sem memoria suficiente");
        exit(1);
    }
}

/* Troca no de uma arvore binaria com seu sucessor */
void troca_com_sucessor(p_raiz raiz) {
    p_raiz min = raiz->dir;
    p_raiz pai_min = raiz;
    while (min->esq != NULL) {
        pai_min = min;
        min = min->esq;
    }
    if (pai_min->esq == min)
        pai_min->esq = min->dir;
    else
        pai_min->dir = min->dir;
    raiz->chave = min->chave;
    free(raiz->mensagem);
    raiz->mensagem = malloc((strlen(min->mensagem) + 1) * sizeof(char));
    strcpy(raiz->mensagem, min->mensagem);
    free(min->mensagem);
    free(min);
}

/* Cria um token de uma arvore binaria de busca de tokens */
p_raiz criar_token(long long int chave, char *mensagem, int max_msg) {
    p_raiz token;
    if (mensagem == NULL)
        token = NULL;
    else {
        token = malloc(sizeof(Raiz));
        sem_memoria(token);
        token->mensagem = malloc(max_msg * sizeof(char));
        strcpy(token->mensagem, mensagem);
        token->chave = chave;
        token->dir = NULL;
        token->esq = NULL;
    }
    return token;
}

/* Insere um token em uma abb de tokens */
p_raiz insere_ord(p_raiz raiz, p_raiz token) {
    if (raiz == NULL) {
        return token;
    }
    else if (token->chave < raiz->chave)
        raiz->esq = insere_ord(raiz->esq, token);
    else if (token->chave > raiz->chave)
        raiz->dir = insere_ord(raiz->dir, token);
    return raiz;
}

/* Remove um token de sua abb a partir de sua chave */
p_raiz remove_ord(p_raiz raiz, int chave) {
    p_raiz aux;
    if (raiz == NULL)
        return raiz;
    if (chave < raiz->chave)
        raiz->esq = remove_ord(raiz->esq, chave);
    else if (chave > raiz->chave)
        raiz->dir = remove_ord(raiz->dir, chave);
    else if (raiz->esq == NULL) {
        aux = raiz->dir;
        free(raiz->mensagem);
        free(raiz);
        return aux;
    } else if (raiz->dir == NULL) {
        aux = raiz->esq;
        free(raiz->mensagem);
        free(raiz);
        return aux; 
    } else
        troca_com_sucessor(raiz);
    return raiz;
}

/* Busca por um token em uma arvore a partir de sua chave */
p_raiz busca(p_raiz raiz, int chave) {
    if (raiz == NULL)
        return NULL;
    if (chave < raiz->chave)
        return busca(raiz->esq, chave);
    if (chave > raiz->chave)
        return busca(raiz->dir, chave);
    return raiz;
}

/* Procura em uma ABB o maior token que é menor que a soma recursivamente */
p_raiz procura_menor_soma_rec(p_raiz raiz, p_raiz menor_soma, int soma) {
    if (raiz == NULL)
        return menor_soma;
    if (raiz->esq != NULL && soma < raiz->chave)
        return procura_menor_soma_rec(raiz->esq, menor_soma, soma);
    else if (raiz->dir != NULL && soma > raiz->chave)
        return procura_menor_soma_rec(raiz->dir, raiz, soma);
    else if (raiz->esq == NULL && soma < raiz->chave)
        return menor_soma;
    return raiz;
}

/* Procura em uma ABB o maior token que é menor que a soma */
p_raiz procura_menor_soma(p_raiz raiz, int soma) {
    return procura_menor_soma_rec(raiz, NULL, soma);
}

/* Retorna a quantidade de caracteres de uma ABB de tokens */
int conta_caracteres(p_raiz raiz) {
    if (raiz == NULL)
        return 0;
    return strlen(raiz->mensagem) + conta_caracteres(raiz->esq) + conta_caracteres(raiz->dir);
}

/* Soma todas as chaves de uma ABB de tokens */
int soma_nos(p_raiz raiz) {
    if (raiz == NULL)
        return 0;
    return raiz->chave + soma_nos(raiz->esq) + soma_nos(raiz->dir);
}

/* Imprime todas as strings de uma ABB de tokens inordem */
void imprime_in(p_raiz raiz) {
    if (raiz != NULL) {
        imprime_in(raiz->esq);
        printf("%s", raiz->mensagem);
        imprime_in(raiz->dir);
    }
}

/* Libera uma ABB de tokens */
void destroi_arvore(p_raiz raiz) {
    if (raiz != NULL) {
        destroi_arvore(raiz->esq);
        destroi_arvore(raiz->dir);
        free(raiz->mensagem);
        free(raiz);
    }
}

/* Libera uma ABB de tokens e retorna NULL */
p_raiz libera_abb(p_raiz raiz) {
    destroi_arvore(raiz);
    return NULL;
}
