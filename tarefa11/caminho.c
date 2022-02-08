#include "mapaPokemonGo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NUM_VERT_INI 100
#define MAX_CHAR_POKEMON 8

double buscaMenorMaiorCaminhoLugia(p_mapa mapa, int *pai);

int main() 
{   
    int *pai;
    double xy[2];
    double maiorDistanciaMinima;
    char tipoParada[MAX_CHAR_POKEMON + 1];
    p_mapa mapa = criaMapa(NUM_VERT_INI);

    scanf("%lf %lf", &xy[0], &xy[1]);
    insereJogador(mapa, xy);

    while (scanf("%lf %lf %s", &xy[0], &xy[1], tipoParada) != EOF) 
    {
        if (!strcmp(tipoParada, "pokestop"))
            inserePokeStop(mapa, xy);
        else
            insereLugia(mapa, xy);
    }

    pai = encontraArvoreArestasMinimas(mapa, 0);
    maiorDistanciaMinima = buscaMenorMaiorCaminhoLugia(mapa, pai);

    printf("%.0lf\n", ceil(maiorDistanciaMinima));

    free(pai);
    liberaMapa(mapa);

    return 0;
}

/* Dado um mapa calcula a maior aresta minima dos percursos que o jogador faz
   até os Lugias através de uma arvore de arestas minimas pai*/
double buscaMenorMaiorCaminhoLugia(p_mapa mapa, int *pai) {
    int filho;
    double distancia, distMaior = 0, distMaiorMin;
    for (int i = 0; i < mapa->qtdLugia; i++) {
        filho = mapa->verticesLugia[i];
        distMaior = 0;
        while (filho != 0) {
            distancia = distEuclidiana(mapa->posicoes[filho].xy, mapa->posicoes[pai[filho]].xy);
            if (distancia > distMaior)
                distMaior = distancia;
            filho = pai[filho];
        }
        if (i == 0)
            distMaiorMin = distMaior;
        if (distMaiorMin > distMaior)
            distMaiorMin = distMaior;
    }
    return distMaiorMin;
}
