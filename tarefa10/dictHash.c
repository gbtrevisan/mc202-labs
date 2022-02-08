#include "dictHash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Cria uma lista ligada */
p_no criaLista() {
    return NULL;
}

/* Insere uma chave em uma lista ligade de strings */
p_no insereLista(p_no lista, char *chave) {
    p_no novo = malloc(sizeof(No));
    strcpy(novo->chave, chave);
    novo->prox = lista;
    return novo;
}

/* Libera uma lista ligada */
void liberaLista(p_no lista) {
    if (lista != NULL) {
        liberaLista(lista->prox);
        free(lista);
    }
}

/* Calcula o codigo hash de uma string */
int hash(char *chave) {
    int x = 0, lenChave = strlen(chave) ;
    for (int i = 0; i < lenChave; i++)
        x = (256 * x + chave[i]) % TAM_MAX_HASH;
    return x;
}

/* Cria um dicionario e retorna seu ponteiro */
p_dict criaDicionario() {
    p_dict dict = malloc(sizeof(DictHash));
    for (int i = 0; i < TAM_MAX_HASH; i++) {
        dict->tabela[i] = criaLista();
    }
    return dict;
}

/* Insere uma palavra em um dicionario a partir de um codigo hash */
p_dict insereDicionario(p_dict dict, char *chave) {
    int pos = hash(chave);
    dict->tabela[pos] =  insereLista(dict->tabela[pos], chave);
    return dict;
}

/* Busca por um no a partir de uma chave */
p_no busca(p_dict dict, char *chave) {
    int pos = hash(chave);
    p_no no = dict->tabela[pos];
    while (no != NULL && strcmp(no->chave, chave))
        no = no->prox;
    return no;
}

/* Libera um dicionario */
void liberaDicionario(p_dict dict) {
    for (int i = 0; i < TAM_MAX_HASH; i++)
        liberaLista(dict->tabela[i]);
    free(dict);
}

/* Procura uma palavra no dicionario */
int procuraNoDict(p_dict dict, char *chave) {
    int pos = hash(chave);
    p_no no = dict->tabela[pos];
    while (no != NULL && strcmp(no->chave, chave))
        no = no->prox;
    if (no)
        return 1;
    return 0;
}

/* int contaErros(char *chaveDict, char *palavra) {
    int lenChave = strlen(chaveDict), lenPalavra = strlen(palavra);
    int erros, i;
    for (i = 0; i < lenChave && i < lenPalavra; i++) {
        if (chaveDict[i] != palavra[i])
            erros++;
    }
    if (i + 1 == lenChave)
        erros += lenPalavra - lenChave;
    else
        erros += lenChave - lenPalavra;
    return erros;
} */
