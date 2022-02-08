#include "professor_carlos.h"
#include <stdio.h>
#define MAX 50

void le_alunos(Turma turmas[MAX], int n);
void executa_operacoes(int k, Turma turmas[MAX], int n_turmas);

int main() {
    int n, k;
    Turma turmas[MAX];
    scanf("%d %d ", &n, &k);
    le_alunos(turmas, n);
    executa_operacoes(k, turmas, n);
    return 0;
}

/* Dado um vetor e um número n armazena os dados de n turmas */
void le_alunos(Turma turmas[MAX], int n) {
    int m;
    for (int i = 0; i < n; i++) {
        scanf("%d ", &m);
        turmas[i].qtd = m;
        for (int j = 0; j < m; j++)
            scanf("%s %s %d %d %d ", turmas[i].alunos[j].nome, 
            turmas[i].alunos[j].sobrenome, 
            &turmas[i].alunos[j].nascimento.dia, 
            &turmas[i].alunos[j].nascimento.mes, 
            &turmas[i].alunos[j].nascimento.ano);
    }
}

/* Dado a quantidade de operacoes k e um vetor com n_turmas, realiza as operacoes */
/* escolhidas sobre elas */
void executa_operacoes(int k, Turma turmas[MAX], int n_turmas) {
    char padrao[5];
    int j, X;
    Aluno aluno1;
    for (int i = 0; i < k; i++) {
        scanf("%d ", &X);
        if (X == 1) {
            scanf("%d ", &j);
            printf("%s\n", procura_novo_na_turma(turmas, n_turmas, j).nome);
        } else if (X == 2) {
            scanf("%d ", &j);
            printf("%s\n", procura_velho_na_turma(turmas, n_turmas, j).sobrenome);
        } else if (X == 3)
            printf("%s\n", procura_velho_todas_turmas(turmas, n_turmas).nome);
        else if (X == 4)
            printf("%s\n", procura_novo_todas_turmas(turmas, n_turmas).sobrenome);
        else if (X == 5) {
            scanf("%s ", padrao);
            printf("%d\n", conta_substrings(turmas, n_turmas, padrao));
        } else if (X == 6) {
            scanf("%d %s %s %d %d %d ", &j, aluno1.nome, aluno1.sobrenome,
            &aluno1.nascimento.dia, &aluno1.nascimento.mes, &aluno1.nascimento.ano);
            printf("%d\n", add_aluno(turmas, aluno1, j));
        } else {
            scanf("%d ", &j);
            printf("%d\n", remove_aluno(turmas, j));
        }
    }
}