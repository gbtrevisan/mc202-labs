#include "sistemaUber.h"
#include <stdio.h>

#define TAM_INICIAL_FILA 25

int main() 
{
    int posAtual[2], posDestino[2];
    double qtdEstrelas;
    char nome[NOME_MAX + 1], acao;
    p_uber uberHeap = criaUberHeap(TAM_INICIAL_FILA);

    while(scanf("%c ", &acao) != EOF) 
    {
        if (acao == 'A') {
            scanf(" %s %lf", nome, &qtdEstrelas);
            scanf("%d %d", &posAtual[0], &posAtual[1]);
            scanf("%d %d", &posDestino[0], &posDestino[1]);
            aceitaCorrida(uberHeap, nome, qtdEstrelas, posAtual, posDestino);
        } else if (acao == 'F') {
            finalizaCorrida(uberHeap);
        } else if (acao == 'C') {
            scanf(" %s", nome);
            cancelaCorrida(uberHeap, nome);
        } else if (acao == 'T') {
            printf("\n");
            finalizaExpediente(uberHeap);
        }
    }

    liberaUberHeap(uberHeap);

    return 0;
}
