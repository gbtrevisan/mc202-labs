#include "numerosGigantes.h"
#include <stdio.h>
#include <stdlib.h>

/* Cria um número gigante com 0 digitos */
lista cria_lista() {
    return NULL;
}

/* Libera um digito de um número gigante */
void destroi_lista(lista l) {
    if (l != NULL) {
        destroi_lista(l->prox);
        free(l);
    }
}

/* Insere um digito em um número gigante */
lista armazena_num(lista l, int x) {
    lista novo;
    novo = malloc(sizeof(elemento));
    if (novo == NULL) {
        printf("Memoria insuficiente");
        exit(1);
    }
    novo->dado = x;
    novo->prox = l;
    return novo;
}

/* Retira os digitos zeros a esquerda de um número gigante */
lista zero_esquerda(lista l) {
    if (l->prox == NULL && l->dado == 0) {
        free(l);
        return NULL;
    } else if (l->prox == NULL)
        return l;
    l->prox = zero_esquerda(l->prox);
    if (l->prox == NULL && l->dado == 0) {
        free(l);
        return NULL;
    }
    return l;
}

/* Retorna o maior número dentre 2 números gigantes */
lista maximo(lista n1, lista n2) {
    lista i = n1, j = n2, maior;
    while (i != NULL && j!= NULL) {
        if (i->dado > j->dado)
            maior = n1;
        else if (j->dado > i->dado)
            maior = n2;
        i = i->prox;
        j = j->prox;
    }
    if (i == NULL && j != NULL)
        return n2;
    else if (j == NULL && i != NULL)
        return n1;
    return maior;
}

/* Função recursiva que soma 2 números gigantes */
lista soma_rec(lista n1, lista n2, int resto) {
    lista novo = cria_lista();
    novo = malloc(sizeof(elemento));
    if (novo == NULL) {
        printf("Memoria insuficiente");
        exit(1);
    }
    if (n1 == NULL && n2 == NULL) {
        if (resto != 0) {
            novo->dado = resto;
            novo->prox = NULL;
            return novo;
        }
        free(novo);
        return NULL;
    } else if (n1 == NULL) {
        novo->dado = (n2->dado + resto) % 10;
        resto = (n2->dado + resto) / 10;
        novo->prox = soma_rec(n1, n2->prox, resto);
    } else if (n2 == NULL) {
        novo->dado = (n1->dado + resto) % 10;
        resto = (n1->dado + resto) / 10;
        novo->prox = soma_rec(n1->prox, n2, resto);
    } else { 
        novo->dado = (n2->dado + n1->dado + resto) % 10;
        resto = (n2->dado + n1->dado + resto) / 10;
        novo->prox = soma_rec(n1->prox, n2->prox, resto);
    }
    return novo;
}

/* Função recursiva que subtrai 2 números gigantes */
lista subtracao_rec(lista n1, lista n2, int resto) {
    lista novo = cria_lista();
    novo = malloc(sizeof(elemento));
    if (novo == NULL) {
        printf("Memoria insuficiente");
        exit(1);
    }
    if (n1 == NULL && n2 == NULL) {
        free(novo);
        return NULL;
    } else if (n2 == NULL) {
        if (n1->dado - resto >= 0) {
            novo->dado = n1->dado - resto;
            resto = 0;
        } else {
            novo->dado = n1->dado + 10 - resto;
            resto = 1;
        }
        novo->prox = subtracao_rec(n1->prox, n2, resto);
    } else {
        if (n1->dado - resto - n2->dado >= 0) {
            novo->dado = (n1->dado - resto) - n2->dado;
            resto = 0;
        } else {
            novo->dado = (n1->dado - resto) + 10 - n2->dado;
            resto = 1;
        }
        novo->prox = subtracao_rec(n1->prox, n2->prox, resto);
    }
    return novo;
}

/* Função recursiva que multiplica um digito por um número gigante e retorna seu valor */
lista multiplicacao_rec(lista n1, lista n2, int resto) {
    int produto;
    lista novo = cria_lista();
    novo = malloc(sizeof(elemento));
    if (novo == NULL) {
        printf("Memoria insuficiente");
        exit(1);
    }
    if (n1 == NULL && n2 == NULL) {
        free(novo);
        return NULL;
    }
    else if (n2 == NULL) {
        if (resto) {
        novo->dado = resto;
        novo->prox = NULL;
        return novo;
        }
        free(novo);
        return NULL;
    }
    produto = (n1->dado * n2->dado + resto);
    novo->dado = produto % 10;
    resto = produto / 10;
    novo->prox = multiplicacao_rec(n1, n2->prox, resto);
    return novo;
}

/* Retorna a multiplicação de 2 números gigantes */
lista multiplicacao(lista n1, lista n2) {
    lista resultado = cria_lista(), prox = n1, produto, aux;
    int i = 0;
    while (prox != NULL) {
        produto = multiplicacao_rec(prox, n2, 0);
        for (int j = 0; j < i; j++)
            produto = armazena_num(produto, 0);
        aux = resultado;
        resultado = soma(resultado, produto);
        destroi_lista(produto);
        destroi_lista(aux);
        prox = prox->prox;
        i++;
    }
    return resultado;
}

/* Soma dois números gigantes */
lista soma(lista n1, lista n2) {
    return soma_rec(n1, n2, 0);
}

/* Subtrai dois números gigantes */
lista subtracao(lista n1, lista n2) {
    lista maior = maximo(n1, n2);
    if (maior == n1)
        return subtracao_rec(n1, n2, 0);
    return subtracao_rec(n2, n1, 0);
}

/* Decide qual operação deve ser feita e retorna o resultado */
lista realiza_operacao(lista n1, lista n2, char operador) {
    if (operador == '+')
        return soma(n1, n2);
    else if (operador == '-')
        return zero_esquerda(subtracao(n1, n2));
    else if (operador == '*')
        return zero_esquerda(multiplicacao(n1, n2));
    return NULL;
}
