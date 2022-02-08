#include "dictHash.h"
#include <stdio.h>
#include <string.h>

void removeChar(char *string, int i);
void adicionaChar(char *string, char c, int i);
void trocaChar(char *string, char c, int i);
int corrige(p_dict dict, char string[MAX_KEY + 1]);


int main() 
{
    int qtdPalavrasDict, qtdPalavrasTexto, erros;
    char string[MAX_KEY + 1];
    p_dict dict = criaDicionario();

    scanf("%d %d", &qtdPalavrasDict, &qtdPalavrasTexto);

    for (int i = 0; i < qtdPalavrasDict; i++) {
        scanf("%s", string);
        dict = insereDicionario(dict, string);
    }

    for (int i = 0; i < qtdPalavrasTexto; i++) {
        scanf("%s", string);
        erros = corrige(dict, string);
        if (!erros) 
            printf("verde\n");
        else if (erros == 1) 
            printf("amarelo\n");
        else 
            printf("vermelho\n");
    }

    liberaDicionario(dict);

    return 0;
}

/* Remove o caracter da posicao i da string, diminuindo seu tamanho */
void removeChar(char *string, int i) {
    while(string[i] != '\0') {
        string[i] = string[i + 1];
        i++;
    }
}

/* Adiciona um caracter c na posicao i da string */
void adicionaChar(char *string, char c, int i) {
    int pos = i + 1;
    char aux1 = string[pos - 1], aux2;
    while (string[pos] != '\0') {
        aux2 = string[pos];
        string[pos] = aux1;
        aux1 = aux2;
        pos++;
    }
    string[pos] = aux1;
    string[pos + 1] = '\0';
    string[i] = c; 
}

/* Troca o caracter da posicao i na string com o caracter c */
void trocaChar(char *string, char c, int i) {
    string[i] = c;
}

/* Corrige uma palavra a partir de um dicionario e retorna a quantidade de erros
   0 - nenhum erro
   1 - apenas um erro
   2 - dois ou mais erros */
int corrige(p_dict dict, char string[MAX_KEY + 1]) {
    int i = 0, encontrou;
    char strCopia[MAX_KEY + 1], c;
    encontrou = procuraNoDict(dict, string);
    if (encontrou) return 0;
    else {
        while (string[i] != '\0') {
            strcpy(strCopia, string);
            removeChar(strCopia, i);
            encontrou = procuraNoDict(dict, strCopia);
            if (encontrou) return 1;
            for (c = 'a'; c < 'z' + 1; c++) {
                strcpy(strCopia, string);
                adicionaChar(strCopia, c, i);
                encontrou = procuraNoDict(dict, strCopia);
                if (encontrou) return 1;
                if (string[i + 1] == '\0') {
                    strcpy(strCopia, string);
                    adicionaChar(strCopia, c, i + 1);
                    encontrou = procuraNoDict(dict, strCopia);
                    if (encontrou) return 1;
                }
                strcpy(strCopia, string);
                trocaChar(strCopia, c, i);
                encontrou = procuraNoDict(dict, strCopia);
                if (encontrou) return 1;
            }
            i++;
        }
        return 2;
    }
}
