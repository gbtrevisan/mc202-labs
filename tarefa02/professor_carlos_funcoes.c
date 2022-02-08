#include "professor_carlos.h"

/* Recebe 2 nomes e retorna 1 se são diferentes ou 0 se são iguais */
int nome_diferente(char nome1[], char nome2[]) {
    for (int i = 0; (nome1[i] != '\0' && nome2[i] != '\0'); i++)
        if (nome1[i] != nome2[i])
            return 1;
    return 0;
}

/* Recebe 2 alunos e retorna o aluno com menor nome em ordem lexicográfica */
Aluno ordem_lexicografica(Aluno aluno1, Aluno aluno2) {
    int tamanho1_nome = 0, tamanho2_nome = 0, i;
    if (nome_diferente(aluno1.nome, aluno2.nome)) {
        for (int i = 0; (aluno1.nome[i] != '\0' && aluno2.nome[i] != '\0'); i++) {
            if (aluno1.nome[i] < aluno2.nome[i]) 
                return aluno1;
            else if (aluno1.nome[i] > aluno2.nome[i])
                return aluno2;
        }
        for (i = 0; aluno1.nome[i] != '\0'; i++);
        tamanho1_nome = i;
        for (i = 0; aluno2.nome[i] != '\0'; i++);
        tamanho2_nome = i;
        if (tamanho2_nome < tamanho1_nome) /* Caso tenha chegado ao fim de algum nome */
            return aluno2;                 /* o menor deles em tamanho é o de menor */
        return aluno1;                     /* em ordem lexicografica */
    } else {
        for (int i = 0; (aluno1.sobrenome[i] != '\0' && aluno2.sobrenome[i] != '\0'); i++) {
            if (aluno1.sobrenome[i] < aluno2.sobrenome[i]) 
                return aluno1;
            else if (aluno1.sobrenome[i] > aluno2.sobrenome[i])
                return aluno2;
        }
        for (i = 0; aluno1.sobrenome[i] != '\0'; i++);
        tamanho1_nome = i;
        for (i = 0; aluno2.sobrenome[i] != '\0'; i++);
        tamanho2_nome = i;
        if (tamanho2_nome < tamanho1_nome) /* Caso tenha chegado ao fim de algum sobrenome */
            return aluno2;                 /* o menor deles em tamanho é o de menor */
        return aluno1;                     /* em ordem lexicografica */
    }
}

/* Dado um padrão e o um nome verifica se o padrão ocorre naquele nome */
int eh_substring(char padrao[], int tamanho, char nome[]) {
    int apareceu = 0;
    for (int i = 0; nome[i] != '\0'; i++) {
        if (nome[i] == padrao[apareceu])
            apareceu += 1;
        else
            apareceu = 0;
        if (apareceu == tamanho)
            return 1;
    }
    return 0;
}

/* Dado 2 alunos retorna o mais novo */
Aluno aluno_mais_novo(Aluno aluno1, Aluno aluno2) {
    if ((aluno1.nascimento.ano == aluno2.nascimento.ano)
    && (aluno1.nascimento.mes == aluno2.nascimento.mes)
    && (aluno1.nascimento.dia == aluno2.nascimento.dia))
        return ordem_lexicografica(aluno1, aluno2);

    if (aluno2.nascimento.ano > aluno1.nascimento.ano)
        return aluno2;
    else if ((aluno2.nascimento.ano == aluno1.nascimento.ano)
    && (aluno2.nascimento.mes > aluno1.nascimento.mes))
        return aluno2;
    else if ((aluno2.nascimento.ano == aluno1.nascimento.ano)
    && (aluno2.nascimento.mes == aluno1.nascimento.mes)
    && (aluno2.nascimento.dia > aluno1.nascimento.dia))
        return aluno2;
    return aluno1;
}

/* Dado 2 alunos retorna o mais velho */
/* OBS: Daria para ter usado a função aluno_mais_novo */
/* mas a função ficaria mais lenta então decidi fazer */
/* duas diferentes */
Aluno aluno_mais_velho(Aluno aluno1, Aluno aluno2) {
    if ((aluno1.nascimento.ano == aluno2.nascimento.ano)
    && (aluno1.nascimento.mes == aluno2.nascimento.mes)
    && (aluno1.nascimento.dia == aluno2.nascimento.dia))
        return ordem_lexicografica(aluno1, aluno2);

    if (aluno2.nascimento.ano < aluno1.nascimento.ano)
        return aluno2;
    else if ((aluno2.nascimento.ano == aluno1.nascimento.ano)
    && (aluno2.nascimento.mes < aluno1.nascimento.mes))
        return aluno2;
    else if ((aluno2.nascimento.ano == aluno1.nascimento.ano)
    && (aluno2.nascimento.mes == aluno1.nascimento.mes)
    && (aluno2.nascimento.dia < aluno1.nascimento.dia))
        return aluno2;
    return aluno1;
}

Aluno procura_novo_na_turma(Turma t[], int qtd_turmas, int j) {
    Aluno mais_novo = t[j].alunos[0];
    for (int i = 1; i < t[j].qtd; i++)
        mais_novo = aluno_mais_novo(mais_novo, t[j].alunos[i]);
    return mais_novo;
}

Aluno procura_novo_todas_turmas(Turma t[], int qtd_turmas) {
    Aluno mais_novo = t[0].alunos[0];
    for (int i = 0; i < qtd_turmas; i++)
        mais_novo = aluno_mais_novo(mais_novo, procura_novo_na_turma(t, qtd_turmas, i));
    return mais_novo;
}

Aluno procura_velho_na_turma(Turma t[], int qtd_turmas, int j) {
    Aluno mais_velho = t[j].alunos[0];
    for (int i = 1; i < t[j].qtd; i++)
        mais_velho = aluno_mais_velho(mais_velho, t[j].alunos[i]);
    return mais_velho;
}

Aluno procura_velho_todas_turmas(Turma t[], int qtd_turmas) {
    Aluno mais_velho = t[0].alunos[0];
    for (int i = 0; i < qtd_turmas; i++)
        mais_velho = aluno_mais_velho(mais_velho, procura_velho_na_turma(t, qtd_turmas, i));
    return mais_velho;
}

int conta_substrings(Turma t[], int qtd_turmas, char *padrao) {
    int n = 0, tamanho_p, k;
    for (k = 0; padrao[k] != '\0'; k++);
    tamanho_p = k;

    for (int i = 0; i < qtd_turmas; i++)
        for (int j = 0; j < t[i].qtd; j++)
            n += eh_substring(padrao, tamanho_p, t[i].alunos[j].nome);
    return n;
}

int add_aluno(Turma t[], Aluno A, int j) {
    t[j].alunos[t[j].qtd] = A;
    t[j].qtd += 1;
    return t[j].qtd;
}

int remove_aluno(Turma t[], int j) {
    t[j].qtd -= 1;
    return t[j].qtd;
}
