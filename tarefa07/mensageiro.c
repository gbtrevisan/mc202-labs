#include "arvoreBuscaBinaria.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MSG (5 + 1)

void recebe_mensagem(char *mensagem);
int gera_triade_rec(int n_autoridade, p_raiz *raiz, p_raiz *combinacao, int n);
p_raiz gera_triade(int n_autoridade, p_raiz *raiz);
void junta_tokens_rec(p_raiz raiz, p_raiz novo_token);
p_raiz junta_tokens(p_raiz raiz);

int main()
{
    int qtd_tokens, qtd_autoridades;
    long long int chave, n_da_autoridade;
    char mensagem[6];
    p_raiz token, tokens = criar_token(0, NULL, MAX_MSG), triade, novo_token;

    while (scanf("%d %d", &qtd_tokens, &qtd_autoridades) != EOF) {
        for (int i = 0; i < qtd_tokens; i++) {
            scanf(" %lli ", &chave);
            recebe_mensagem(mensagem);
            token = criar_token(chave, mensagem, MAX_MSG);
            tokens = insere_ord(tokens, token);
        }
        for (int i = 0; i < qtd_autoridades; i++) {
            scanf(" %lli", &n_da_autoridade);
            triade = gera_triade(n_da_autoridade, &tokens);
            novo_token = junta_tokens(triade);
            tokens = insere_ord(tokens, novo_token);
        }
        imprime_in(tokens);
        printf("\n");
        tokens = libera_abb(tokens);
    }

    return 0;
}

/* Recebe uma string do terminal entre "" e armazena */
void recebe_mensagem(char *mensagem) {
    int i = 0;
    char aux;
    scanf("%c", &aux);
    while (1) {
        scanf("%c", &aux);
        if (aux == '"') break;
        mensagem[i] = aux;
        i++;
    }
    mensagem[i] = '\0';
}

/* Gera uma triade de tokens por referencia tal que a soma de suas chaves é igual ao numero
   da autoridade dada, removendo por referencia os tokens da arvore principal que foram usados
   para gerar a triade */
int gera_triade_rec(int n_autoridade, p_raiz *raiz, p_raiz *combinacao, int n) {
    long long int prox_num, token_chave;
    p_raiz token, token_triade;
    if (*raiz == NULL)
        return 0;
    if (n_autoridade < 0 || (n_autoridade == 0 && n != 3))
        return 0;
    if (n == 3 && n_autoridade == 0) {
        return 1;
    } else if (n < 3) {
        token = procura_menor_soma(*raiz, n_autoridade);
        if (token == NULL)
            return 0;
        prox_num = token->chave - 1;
        token_chave = token->chave;
        while (!gera_triade_rec(n_autoridade - token->chave, raiz, combinacao, n + 1)) {
            token = procura_menor_soma(*raiz, prox_num);
            if (token == NULL)
                return 0;
            prox_num = token->chave - 1;
            token_chave = token->chave;
        }
        token = busca(*raiz, token_chave); // a arvore mudou e o ponteiro pode ter sido atualizado pela funcao remove_ord
        token_triade = criar_token(token_chave, token->mensagem, strlen(token->mensagem) + 1);
        *combinacao = insere_ord(*combinacao, token_triade);
        *raiz = remove_ord(*raiz, token_chave);
        return 1;
    }
    return 0;
}

/* Retorna uma arvore com 3 tokens tal que a soma de suas chaves é igual ao numero da autoridade 
   passada */
p_raiz gera_triade(int n_autoridade, p_raiz *raiz) {
    p_raiz triade = criar_token(0, NULL, 0);
    gera_triade_rec(n_autoridade, raiz, &triade, 0);
    return triade;
}

/* Junta uma ABB de tokens recursivamente em um único No token com as 
   chaves somadas e as mensagens concatenadas inordem */ 
void junta_tokens_rec(p_raiz raiz, p_raiz novo_token) {
    if (raiz != NULL) {
        junta_tokens_rec(raiz->esq, novo_token);
        novo_token->chave = novo_token->chave + raiz->chave;
        strcat(novo_token->mensagem, raiz->mensagem);
        junta_tokens_rec(raiz->dir, novo_token);
        free(raiz->mensagem);
        free(raiz);
    }
}

/* Junta uma ABB de tokens em um único No token com as 
   chaves somadas e as mensagens concatenadas inordem */ 
p_raiz junta_tokens(p_raiz raiz) {
    char *mensagem = ""; //token precisa começar com uma string vazia
    p_raiz novo_token = criar_token(0, mensagem, ((conta_caracteres(raiz)) + 1));
    junta_tokens_rec(raiz, novo_token);
    return novo_token;
}
