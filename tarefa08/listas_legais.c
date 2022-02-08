#include "listaLegal.h"
#include <stdio.h>
#include <assert.h>

int main() 
{
    int operacao, qtdNumLista, qtdOperacoes;
    long long int num;
    p_no listaLegal = criaArvoreRN();

    scanf("%d %d", &qtdNumLista, &qtdOperacoes);
    for (int i = 0; i < qtdNumLista; i++) {
        scanf("%lli", &num);
        listaLegal = insereOrdenado(listaLegal, num);
    }
    
    for (int i = 0; i < qtdOperacoes; i++) {
        scanf("%d", &operacao);
        if (operacao == 1) {
            scanf("%lli", &num);
            listaLegal = insereOrdenado(listaLegal, num);
        } else if (operacao == 2) {
            scanf("%lli", &num);
            printf("%lli\n", qtdVezesAparece(listaLegal, num));
        } else {
            num = 0;
            qtdParaLegal(listaLegal, &num);
            printf("%lli\n", num);
        }
    }

    liberaArvoreRN(listaLegal);

    return 0;
}