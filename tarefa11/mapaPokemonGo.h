#include "grafo.h"

typedef struct Posicao 
{
    double xy[2];
    int lugia;
} Posicao;

typedef struct MapaPokemonGo 
{
    p_grafo grafo;
    Posicao *posicoes;
    int tamanho, qtd;
    int *verticesLugia;
    int tamanhoLugia, qtdLugia;
} MapaPokemonGo;

typedef MapaPokemonGo * p_mapa;

p_mapa criaMapa(int n);
p_mapa liberaMapa(p_mapa mapa);
void insereJogador(p_mapa mapa, double xy[2]);
void inserePokeStop(p_mapa mapa, double xy[2]);
void insereLugia(p_mapa mapa, double xy[2]);
void verificaTamanhoMapa(p_mapa mapa);
void modelaMapa(p_mapa mapa);
double distEuclidiana(double p1[2], double p2[2]);
int * encontraArvoreArestasMinimas(p_mapa mapa, int v);
void printaArvore(int *pai, int v);
