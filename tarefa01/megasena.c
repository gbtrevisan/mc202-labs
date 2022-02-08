#include <stdio.h>
#define MAX 1000

void deslinearizar(int M[2], int posicao);
void premios(int M[MAX], int faixa_1, int faixa_2, int faixa_3, double n, int m);
int megasena(int M[6][10], int posicoes[6]);
void le_jogadores(int m, int M[MAX][6][10]);

int main() {
    int m, pos[6], acertos, faixa_1 = 0, 
    faixa_2 = 0, faixa_3 = 0, M[MAX][6][10], R[MAX];
    double n;
    scanf("%d %lf", &m, &n);
    le_jogadores(m, M);
    scanf("%d %d %d %d %d %d", &pos[0], &pos[1], &pos[2], &pos[3], &pos[4], &pos[5]);

    for (int i = 0; i < m; i++) {
        acertos = megasena(M[i], pos);
        if (acertos == 6) {
            faixa_1 += 1;
            R[i] = 1;
        } else if (acertos == 5) {
            faixa_2 += 1;
            R[i] = 2;
        } else if (acertos == 4) {
            faixa_3 += 1;
            R[i] = 3;
        }
    }

    premios(R, faixa_1, faixa_2, faixa_3, n, m);
    return 0;
}

/* Recebe uma posição e devolve o par [linha, coluna] */
void deslinearizar(int M[2], int posicao) {
    int linha, coluna;
    linha = (posicao - 1) / 6;
    coluna = (posicao - 1) - (linha * 10);
    M[0] = linha;
    M[1] = coluna;
}

/* Calcula o dinheiro recebido por cada participante */
void premios(int M[MAX], int faixa_1, int faixa_2, int faixa_3, double n, int m) {
    for (int i = 0; i < m; i++) {
        if (M[i] == 1)
            printf("%.2f\n", ((0.62 * n) / faixa_1));
        else if (M[i] == 2)
            printf("%.2f\n", ((0.19 * n) / faixa_2));
        else if (M[i] == 3)
            printf("%.2f\n", ((0.19 * n) / faixa_3));
        else
            printf("0.00\n");
    }
}

/* Recebe uma cartela, posições premiadas e devolve os acertos */
int megasena(int M[6][10], int posicoes[6]) {
    int P[2], acertos = 0;
    for (int i = 0; i < 6; i++) {
        deslinearizar(P, posicoes[i]);
        if (M[P[0]][P[1]] == 1)
            acertos += 1;
    }
    return acertos;
}
 /* Guarda todas as cartelas participantes da megasena */
void le_jogadores(int m, int M[MAX][6][10]) {
    for (int i = 0; i < m; i++)
        for (int j = 0; j < 6; j++)
            scanf("%d %d %d %d %d %d %d %d %d %d", 
            &M[i][j][0], &M[i][j][1], &M[i][j][2], 
            &M[i][j][3], &M[i][j][4], &M[i][j][5],
            &M[i][j][6], &M[i][j][7], &M[i][j][8], 
            &M[i][j][9]);
}
