#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void le_dados(char ** termos, double ** historico, int n, int m);
void calcula(double ** historico, double ** dados, int n, int m);
void estatisticas(char ** termos, double ** dados, int n);
void resultados(char ** termos, double ** dados, int n);
void maximo_minimo(double * valores, int m, double * maximo, double * minimo);
double media(double * valores, int m);
double desvio_p(double * valores, int m, double media);
void printa_termos(char ** termos, int n_termos);

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    char ** termos = malloc(n * sizeof(char *));
    double ** historico = malloc(n * sizeof(double *));
    double ** dados = malloc(n * sizeof(double *));
    le_dados(termos, historico, n, m);
    calcula(historico, dados, n, m);
    estatisticas(termos, dados, n);
    resultados(termos, dados, n);

    for (int i = 0; i < n; i++) {
        free(termos[i]);
        free(historico[i]);
        free(dados[i]);
    }

    free(termos);
    free(historico);
    free(dados);
    return 0;
}

/* Calcula o maximo e minimo e altera por referencia */
void maximo_minimo(double * valores, int m, double * maximo, double * minimo) {
    *maximo = valores[0];
    *minimo = valores[0];
    for (int i = 0; i < m; i++) {
        if (*maximo < valores[i])
            *maximo = valores [i];
        if (*minimo > valores[i])
            *minimo = valores[i];
    }
}

/* Calcula media e retorna o valor*/
double media(double * valores, int m) {
    double soma = 0;
    for (int i = 0; i < m; i++)
        soma += valores[i];
    return (soma/m);
}

/* Calcula o devio padrao e retorna o valor */
double desvio_p(double * valores, int m, double media) {
    double soma = 0;
    for (int i = 0; i < m; i++)
        soma += (valores[i] - media) * (valores[i] - media);
    return sqrt(soma/m);
}

/* Armazena os termos e o historico de cada dia de forma dinamica */
void le_dados(char ** termos, double ** historico, int n, int m) {
    for (int i = 0; i < n; i++) {
        *(termos + i) = malloc(25 * sizeof(char));
        *(historico + i) = malloc(m * sizeof(double));
        scanf("%s ", *(termos + i));
        for (int j = 0; j < m; j++)
            scanf("%lf ", (historico[i] + j));
    }
}

/* Calula maximo, minimo, media e desvio padrao de todos os termos */
void calcula(double ** historico, double ** dados, int n, int m) {
    for (int i = 0; i < n; i++){
        *(dados + i) = malloc(4 * sizeof(double));
        maximo_minimo(historico[i], m, &dados[i][0], &dados[i][1]);
        dados[i][2] = media(historico[i], m);
        dados[i][3] = desvio_p(historico[i], m, dados[i][2]);
    }
}

/* Imprime os maximos, minimos, medias e desvio padrao de cada termo */
void estatisticas(char ** termos, double ** dados, int n) {
    for (int i = 0; i < n; i++)
        printf("%s %.02lf %.02lf %.02lf %.02lf\n",
         termos[i], dados[i][0], dados[i][1], dados[i][2], dados[i][3]);
    printf("\n");
}

/* Recebe um ponteiro de ponterios do tipo char e imprime as strings */
void printa_termos(char ** termos, int n_termos) {
    for (int i = 0; i < n_termos; i++) {
        if (i == n_termos - 1) {
            printf("%s\n", termos[i]);
            break;
        }
        printf("%s ", termos[i]);
    }
}

/* Imprime os resultados de acordo com cada categoria
   A funcao tem 2 for quase iguais
   O primeiro conta quantos termos cada categoria tem
   Depois um vetor dinamico de ponteiros char é criado com
   o tamanho de cada categoria (para não usar memoria de forma
   desnecessaria) */
void resultados(char ** termos, double ** dados, int n) {
    int bots = 0, ev_surp = 0, ev_norm = 0, ev_loc = 0, ev_irr = 0;
    int i1 = 0, i2 = 0, i3 = 0, i4 = 0, i5 = 0;
    for (int i = 0; i < n; i ++) { /* Para saber o tamanho de cada vetor */
        if (dados[i][2] >= 60 && dados[i][3] > 15) 
            bots += 1;
        else if (dados[i][2] >= 60 && dados[i][3] <= 15)
            ev_surp += 1;
        else if (dados[i][2] < 60 && dados[i][0] >= 80 && dados[i][1] > 20)
            ev_norm += 1;
        else if (dados[i][2] < 60 && dados[i][0] >= 80 && dados[i][1] <= 20)
            ev_loc += 1;
        else if (dados[i][2] < 60 && dados[i][0] < 80)
            ev_irr += 1;
    }
    /* Cria os vetores de forma dinamica com o tamanho necessario */
    char ** t_bots = malloc(bots * sizeof(char *));
    char ** t_surp = malloc(ev_surp * sizeof(char *));
    char ** t_norm = malloc(ev_norm * sizeof(char *));
    char ** t_loc = malloc(ev_loc * sizeof(char *));
    char ** t_irr = malloc(ev_irr * sizeof(char *));
    for (int i = 0; i < n; i ++) { /* Armazena o endereço de cada termo em seu vetor */
        if (dados[i][2] >= 60 && dados[i][3] > 15){
            t_bots[i1] = termos[i];
            i1 += 1;
        } else if (dados[i][2] >= 60 && dados[i][3] <= 15) {
            t_surp[i2] = termos[i];
            i2 += 1;
        } else if (dados[i][2] < 60 && dados[i][0] >= 80 && dados[i][1] > 20) {
            t_norm[i3] = termos[i];
            i3 += 1;
        } else if (dados[i][2] < 60 && dados[i][0] >= 80 && dados[i][1] <= 20) {
            t_loc[i4] = termos[i];
            i4 += 1;
        }else if (dados[i][2] < 60 && dados[i][0] < 80) {
            t_irr[i5] = termos[i];
            i5 += 1;
        }
    }
    /* Imprime os resultados */
    printf("RESULTADO:\n");
    printf("Bot (%d): ", bots);
    printa_termos(t_bots, bots);
    printf("Surpreendente (%d): ", ev_surp);
    printa_termos(t_surp, ev_surp);
    printf("Normal (%d): ", ev_norm);
    printa_termos(t_norm, ev_norm);
    printf("Local (%d): ", ev_loc);
    printa_termos(t_loc, ev_loc);
    printf("Irrelevante (%d): ", ev_irr);
    printa_termos(t_irr, ev_irr);

    free(t_bots);
    free(t_surp);
    free(t_norm);
    free(t_loc);
    free(t_irr);
}
