#include "numerosGigantes.h"
#include <stdio.h>
#include <stdlib.h>

/* Lê um número gigante do terminal e armazena */
lista le_numero(lista l) {
    char numero;
    do {
    scanf("%c", &numero);
    if (numero == ' ' || numero == '\n')
        return l;
    l = armazena_num(l, numero - '0');
    } while (1);
}

/* Imprime uma número gigante de forma recursiva */
void imprime_lista_rec(lista l) {
    if (l != NULL) {
        imprime_lista_rec(l->prox);
        printf("%d", l->dado);
    }
}

/* Imprime um número gigante */
void imprime_lista(lista l) {
    if (l == NULL) {
        printf("0\n");
        return;
    }
    imprime_lista_rec(l);
    printf("\n");
}

int main() {
    int n;
    char operacao;
    scanf("%d ", &n);
    for (int i = 0; i < n; i++) {
        lista n1 = cria_lista(), n2 = cria_lista();
        lista resultado = cria_lista();
        scanf("%c ", &operacao);
        n1 = le_numero(n1);
        n2 = le_numero(n2);
        resultado = realiza_operacao(n1, n2, operacao);
        imprime_lista(resultado);
        destroi_lista(n1);
        destroi_lista(n2);
        destroi_lista(resultado);
    }
    return 0;
}
