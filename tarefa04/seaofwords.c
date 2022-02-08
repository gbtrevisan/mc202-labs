#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **recebe_texto(int n, int m);
char **recebe_palavras(int q);
void nova_posicao(int lin, int col, int *nlin, int *ncol, int k);
int apareceR(char **texto, char *palavra, int **aux, int lin, int col, int tamanho, int qtd_letras, int n, int m);
void aparece(char **texto, char *palavra, int **aux, int n, int m);
void procura(char **texto, char *palavra, int n, int m);

int main() {
    int n, m, q;
    scanf("%d %d %d", &n, &m, &q);
    char **texto = recebe_texto(n, m);
    char **palavras = recebe_palavras(q);
    for (int i = 0; i < q; i++) {
        procura(texto, palavras[i], n, m);
        free(palavras[i]);
    }
    free(palavras);
    for (int i = 0; i < n; i++)
        free(texto[i]);
    free(texto);
    return 0;
}

/* Aloca uma matriz n x m de caracteres e devolve o ponteiro para ela */
char **recebe_texto(int n, int m) {
    char **texto = malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++) {
        texto[i] = malloc(m * sizeof(char));
        for (int j = 0; j < m; j++)
            scanf(" %c", texto[i] + j);
    }
    return texto;
}

/* Aloca uma matriz de strings de no maximo 25 caracteres
   e retorna seu ponteiro */
char **recebe_palavras(int q) {
    char **palavras = malloc(q * sizeof(char *));
    for (int i = 0; i < q; i++) {
        palavras[i] = malloc(20 * sizeof(char));
        scanf(" %s", palavras[i]);
    }
    return palavras;
}

/* Dado um inteiro k, altera por referencia a nova linha e coluna */
void nova_posicao(int lin, int col, int *nlin, int *ncol, int k) {
    static int movimentos[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    *nlin = lin + movimentos[k][0];
    *ncol = col + movimentos[k][1];
}

/* Funcao que procura uma palavra em um texto */
void procura(char **texto, char *palavra, int n, int m) {
    /* Para verificar se a posição já foi usada no texto */
    int **aux = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        aux[i] = calloc(m, sizeof(int));

    aparece(texto, palavra, aux, n, m);

    for (int i = 0; i < n; i++)
        free(aux[i]);
    free(aux);
}

/* Casca do recursão
   Recebe uma matriz de caracteres e uma string e vê se essa string aparece
   no texto através da funcao recursiva apareceR */
void aparece(char **texto, char *palavra, int **aux, int n, int m) {
    int tamanho = strlen(palavra);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) 
            if (palavra[0] == texto[i][j] && apareceR(texto, palavra, aux, i, j, tamanho, 0, n, m)) {
                printf("sim\n");
                return;
            }
    printf("nao\n");
}

/* Funcao recursiva backtracking que verifica se uma palavra está em um texto */
int apareceR(char **texto, char *palavra, int **aux, int lin, int col, int tamanho, int qtd_letras, int n, int m) {
    int nlin, ncol;
    if (qtd_letras == tamanho)
        return 1;
    if (lin < 0 || lin >= n || col < 0 || col >= m)
        return 0;
    if ((palavra[qtd_letras] == texto[lin][col]) && !aux[lin][col]) {
        aux[lin][col] = 1;
        for (int i = 0; i < 4; i++) {
            nova_posicao(lin, col, &nlin, &ncol, i);
            if (apareceR(texto, palavra, aux, nlin, ncol, tamanho, qtd_letras + 1, n, m))
                return 1;
        }
    }
    aux[lin][col] = 0;
    return 0;
}
