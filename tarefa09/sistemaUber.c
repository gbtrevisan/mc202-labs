#include "sistemaUber.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Retorna o valor absoluto de um num */
int absoluto(int x) {
    if (x < 0)
        return -(x);
    return x;
}

/* Troca passageiros em um vetor de passageiros */
void trocaPassageiros(Passageiro *p1, Passageiro *p2) {
    Passageiro aux = *p1;
    *p1 = *p2;
    *p2 = aux;
}

/* Cria um uber Heap com um tamanho de fila inicial */
p_uber criaUberHeap(int tamanhoFila) {
    p_uber uberHeap = malloc(sizeof(UberHeap));
    uberHeap->filaDoUber = malloc(tamanhoFila * sizeof(Passageiro));
    uberHeap->tamanhoFila = tamanhoFila;
    uberHeap->pos[0] = uberHeap->pos[1] = 0;
    uberHeap->emCorrida = 0;
    uberHeap->kmRodados = 0;
    uberHeap->cancelDoDia = 0;
    uberHeap->kmCliente = 0;
    uberHeap->qtdPassageiros = 0;
    return uberHeap;
}

/* Recebendo duas posicoes em um uber Heap retorna qual o passageiro com maior prioridade */
int passageiroPreferencial(p_uber uberHeap, int i, int j) {
    int preferencial = -1;
    if (uberHeap->qtdPassageiros > i) {
        if (uberHeap->qtdPassageiros > j && 
                uberHeap->filaDoUber[j].qtdEstrelas > uberHeap->filaDoUber[i].qtdEstrelas)
            preferencial = j;
        else
            preferencial = i;
    }
    return preferencial;
}

/* Calcula a distancia Manhattan */
int distanciaManhattan(int p1[2], int p2[2]) {
    int x = p1[0] - p2[0];
    int y = p1[1] - p2[1];
    return absoluto(x) + absoluto(y);
}

/* Desce um passageiro na fila de acordo com sua prioridade */
void desceNoHeap(p_uber uberHeap, int i) {
    int preferencial = passageiroPreferencial(uberHeap, F_ESQ(i), F_DIR(i));
    if (preferencial > 0 && uberHeap->filaDoUber[i].qtdEstrelas < 
                uberHeap->filaDoUber[preferencial].qtdEstrelas) {
        trocaPassageiros(&uberHeap->filaDoUber[i], &uberHeap->filaDoUber[preferencial]);
        desceNoHeap(uberHeap, preferencial);
    }   
}

/* Sobe um passageiro na fila de acordo com sua prioridade */
void sobeNoHeap(p_uber uberHeap, int i) {
    if (uberHeap->filaDoUber[i].qtdEstrelas > uberHeap->filaDoUber[PAI(i)].qtdEstrelas) {
        if (PAI(i) == 0 && uberHeap->emCorrida) // se estiver em corrida não quero trocar
            return;
        trocaPassageiros(&uberHeap->filaDoUber[i], &uberHeap->filaDoUber[PAI(i)]);
        sobeNoHeap(uberHeap, PAI(i));
    }
}

/* Insere um passageiro em uma fila de prioridade do uber */
void insereNaFila(p_uber uberHeap, Passageiro p) {
    if (uberHeap->qtdPassageiros == uberHeap->tamanhoFila)
        uberHeap->filaDoUber = realloc(uberHeap->filaDoUber, uberHeap->tamanhoFila * 2);
    uberHeap->filaDoUber[uberHeap->qtdPassageiros] = p;
    uberHeap->qtdPassageiros++;
    sobeNoHeap(uberHeap, uberHeap->qtdPassageiros - 1);
}

/* Aceita uma corrida e insere o passageiro na fila */
void aceitaCorrida(p_uber uberHeap, char *nome, double qtdEstrelas, int posAtual[2], int posDestino[2]) {
    Passageiro p;
    strcpy(p.nome, nome);
    p.qtdEstrelas = qtdEstrelas;
    p.posAtual[0] = posAtual[0];
    p.posAtual[1] = posAtual[1];
    p.posDestino[0] = posDestino[0];
    p.posDestino[1] = posDestino[1];
    if (uberHeap->qtdPassageiros == 0)
        uberHeap->emCorrida = 1;
    insereNaFila(uberHeap, p);
    printf("Cliente %s foi adicionado(a)\n", p.nome);
}

/* Remove o passageiro de maior prioridade da fila */
Passageiro removeDaFila(p_uber uberHeap) {
    Passageiro p = uberHeap->filaDoUber[0];
    trocaPassageiros(&uberHeap->filaDoUber[uberHeap->qtdPassageiros - 1], 
            &uberHeap->filaDoUber[0]);
    uberHeap->qtdPassageiros--;
    desceNoHeap(uberHeap, 0);
    return p;
}

/* Finaliza a corrida atual do uber, i.e remove o passageiro de maior prioridade */
void finalizaCorrida(p_uber uberHeap) {
    Passageiro p = removeDaFila(uberHeap);
    int kmCliente = distanciaManhattan(p.posAtual, p.posDestino);
    uberHeap->kmRodados += distanciaManhattan(uberHeap->pos, p.posAtual);
    uberHeap->kmRodados += kmCliente;
    uberHeap->kmCliente += kmCliente;
    uberHeap->pos[0] = p.posDestino[0];
    uberHeap->pos[1] = p.posDestino[1];
    if (uberHeap->qtdPassageiros == 0)
        uberHeap->emCorrida = 0;
    else
        uberHeap->emCorrida = 1;
    printf("A corrida de %s foi finalizada\n", p.nome);
}

/* Cancela uma corrida a partir do nome do passageiro */
void cancelaCorrida(p_uber uberHeap, char *nome) {
    for (int i = 0; i < uberHeap->qtdPassageiros; i++) {
        if (!strcmp(nome, uberHeap->filaDoUber[i].nome)) {
            printf("%s cancelou a corrida\n", uberHeap->filaDoUber[i].nome);
            uberHeap->cancelDoDia++;
            trocaPassageiros(&uberHeap->filaDoUber[i], 
                    &uberHeap->filaDoUber[uberHeap->qtdPassageiros - 1]);
            uberHeap->qtdPassageiros--;
            if (uberHeap->qtdPassageiros == 0)
                uberHeap->emCorrida = 0;
            else
                uberHeap->emCorrida = 1;
            desceNoHeap(uberHeap, i);
            break;
        }
    }
}

/* Finaliza o expediente do motorista, printando seus dados do dia */
void finalizaExpediente(p_uber uberHeap) {
    int kmTotal = uberHeap->kmRodados;
    int dinheiroCancel = uberHeap->cancelDoDia * 7;
    double rendBruto = ((uberHeap->kmCliente * PAGAMENTO_UBERX) + dinheiroCancel);
    double despesas = (ALUGUEL_DIARIO + ((double)kmTotal / CONSUMO * CUSTO_GASOLINA));
    double rendLiquido = rendBruto * (1 - TAXA_DA_UBER) - despesas;
    printf("Jornada finalizada. Aqui esta o seu rendimento de hoje\n");
    printf("Km total: %d\nRendimento bruto: %.2lf\n", kmTotal, rendBruto);
    printf("Despesas: %.2lf\nRendimento liquido: %.2lf\n", despesas, rendLiquido);
}

/* Libera um UberHeap */
void liberaUberHeap(p_uber uberHeap) {
    free(uberHeap->filaDoUber);
    free(uberHeap);
}
