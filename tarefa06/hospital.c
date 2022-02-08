#include "hospital.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME 51

/* Checa se o ponteiro e NULL e termina o programa caso for */
void sem_memoria(void *p) {
    if (p == NULL) {
        printf("Sem memoria suficiente");
        exit(1);
    }
}

/* Destroi uma fila de consultas */
void destroi_lista(p_consulta l) {
    if (l != NULL) {
        destroi_lista(l->prox_consulta);
        free(l);
    }
}

/* Cria uma consulta e devolve um ponteiro para ela */
p_consultas cria_consultas() {
    p_consultas l = malloc(sizeof(L_consultas));
    sem_memoria(l);
    l->fim = NULL;
    l->ini = NULL;
    return l;
}

/* Insere uma consulta em uma fila de consultas */
p_consultas insere_consulta(p_consultas l, int num) {
    p_consulta c = malloc(sizeof(Consulta));
    sem_memoria(c);
    c->prox_consulta = NULL;
    c->num = num;
    if (l->fim != NULL)
        l->fim->prox_consulta = c;
    else
        l->ini = c;
    l->fim = c;
    return l;
}

/* Devolve a primeira consulta da fila ou 0 caso estiver vazia */
int consulta_atual(p_consultas l) {
    if (l->ini != NULL)
        return l->ini->num;
    return 0;
}
 
 /* Remove uma consulta do inicio da fila */
int remove_consulta(p_consultas l) {
    int num;
    p_consulta r = l->ini;
    if (r == NULL) {
        printf("Sem consulta marcada");
        exit(1);
    }
    num = r->num;
    l->ini = r->prox_consulta;
    if (l->ini == NULL)
        l->fim = NULL;
    free(r);
    return num;
}

/* Checa se tem consulta em uma fila de consultas */
p_consulta tem_consulta(p_consultas l) {
    return l->ini;
}

void destroi_consultas(p_consultas l) {
    destroi_lista(l->ini);
    free(l);
}

/* Cria um paciente e recebe seus dados, retornando um ponteiro para o paciente */
p_paciente recebe_paciente() {
    int i = 0;
    char c, aux[12];
    char *nome = malloc(MAX_NAME * sizeof(char));
    sem_memoria(nome);
    p_paciente p = malloc(sizeof(Paciente));
    sem_memoria(p);
    p_consultas consultas = cria_consultas();
    scanf("%c", &c);
    nome[0] = c;
    for (i = 1;; i++) {
        scanf("%c", &c);
        if (c == '"') {
            nome[i] = '\0';
            break;
        } 
        nome[i] = c;
    }
    p = define_nome(p, nome);
    scanf(" %c ", &c);
    if (c == 'p') {
        p = define_prioridade(p, 1);
        scanf("%s", aux);
    } else {
        p =  define_prioridade(p, 0);
        scanf("%s", aux);
    }
    scanf(" ");
    do {
        scanf("%c", &c);
        if (c != ' ' && c != '\n') {
            consultas = insere_consulta(consultas, c - '0');
        }
    } while (c != '\n');
    p = define_consultas(p, consultas);
    p->tempo = 0;
    p->ocupado = 0;
    return p;
}

/* Define o nome de um paciente */
p_paciente define_nome(p_paciente p, char *nome_paciente) {
    p->nome = nome_paciente;
    return p;
}

/* Define a prioridade de um paciente */
p_paciente define_prioridade(p_paciente p, int prioridade) {
    p->prioridade = prioridade;
    return p;
}

/* Define a fila de consultas de um paciente */
p_paciente define_consultas(p_paciente p, p_consultas l) {
    p->consultas = l;
    return p;
}
 /* Adiciona o tempo de consulta de um paciente */
p_paciente adiciona_tempo(p_paciente p, int tempo) {
    p->tempo += tempo;
    return p;
}

/* Altera o estado do paciente, 1 para ocupado e 0 para livre */
p_paciente altera_estado(p_paciente p, int num) {
    p->ocupado = num;
    return p;
}

/* Retorna as consultas de um paciente */
p_consultas consultas_do_paciente(p_paciente p) {
    return p->consultas;
}

/* Retorna se um paciente esta ocupado */
int ocupado(p_paciente p) {
    return p->ocupado;
}

/* Imprime um paciente */
void imprime_paciente(p_paciente p) {
    char *nome_paciente = p->nome;
    int horas = p->tempo / 60;
    int minutos = p->tempo % 60;
    if (horas / 10 == 0) {
        if (minutos == 0)
            printf("0%d:0%d %s\n", horas, minutos, nome_paciente);
        else
            printf("0%d:%d %s\n", horas, minutos, nome_paciente);
    } else {
        if (minutos == 0)
            printf("%d:0%d %s\n", horas, minutos, nome_paciente);
        else
            printf("%d:%d %s\n", horas, minutos, nome_paciente);
    }
}

/* Retorna a prioridade de um paciente */
int prioridade(p_paciente p) {
    return p->prioridade;
}

/* Destroi um paciente, liberando suas consultas e o proprio ponteiro paciente */
void destroi_paciente(p_paciente p) {
    if (p != NULL) {
        destroi_consultas(p->consultas);
        free(p->nome);
        free(p);
    }
}

/* De uma lista de pacientes, pega o próximo No */
p_no proximo_paciente(p_no p_atual) {
    if (p_atual != NULL)
        return p_atual->prox;
    return NULL;
}

/* De uma lista de pacientes, pega o paciente do No */
p_paciente pega_paciente(p_no p_atual) {
    return p_atual->paciente;
}

/* Destroi uma lista de pacientes */
void destroi_pacientes(p_no no_paciente) {
    if (no_paciente != NULL) {
        destroi_pacientes(no_paciente->prox);
        destroi_paciente(no_paciente->paciente);
        free(no_paciente);
    }
}

/* Libera um paciente em uma fila */
p_deque libera_paciente(p_deque d, p_no p) {
    p_no no_paciente = p;
    p_paciente paciente_liberado = p->paciente;
    if (no_paciente->ant != NULL)
        no_paciente->ant->prox = no_paciente->prox;
    else
        d->ini = no_paciente->prox;
    if (no_paciente->prox != NULL)
        no_paciente->prox->ant = no_paciente->ant;
    else
        d->fim = no_paciente->ant;
    destroi_paciente(paciente_liberado);
    free(no_paciente);
    return d;
}

/* Retorna 1 se existe paciente na fila e 0 senão */
int paciente_na_fila(p_deque d) {
    if (d->ini != NULL)
        return 1;
    return 0;
}

/* Cria um deque e retorna um ponteiro para o deque */
p_deque cria_deque() {
    p_deque deque = malloc(sizeof(Deque));
    deque->ini = NULL;
    deque->fim = NULL;
    return deque;
}

/* Insere no inicio de um deque */
p_deque insere_ini(p_deque d, p_paciente p) {
    p_no no = malloc(sizeof(No));
    no->paciente = p;
    no->ant = NULL;
    if (d->ini != NULL)
        d->ini->ant = no;
    else
        d->fim = no;
    no->prox = d->ini;
    d->ini = no;
    return d;
}

/* Insere no fim de um deque */
p_deque insere_fim(p_deque d, p_paciente p) {
    p_no no = malloc(sizeof(No));
    no->paciente = p;
    no->prox = NULL;
    if (d->fim != NULL)
        d->fim->prox = no;
    else
        d->ini = no;
    no->ant = d->fim;
    d->fim = no;
    return d;
}

/* Remove do inicio de um deque */
p_paciente remove_ini(p_deque d) {
    p_paciente p = d->ini->paciente;
    p_no r = d->ini;
    if (d->ini->prox != NULL)
        d->ini->prox->ant = NULL; // erro?
    else
        d->fim = NULL;
    d->ini = d->ini->prox;
    free(r);
    return p;
}

/* Pega o primeiro paciente de um deque */
p_no primeiro_paciente(p_deque d) {
    return d->ini;
}

/* Destroi um deque e sua lista de pacientes */
void destroi_deque(p_deque d) {
    destroi_pacientes(d->ini);;
    free(d);
}

/* Cria um atendimento e devolve um ponteiro para o atendimento */
p_atendimento cria_atendimento(int qtd_medicos) {
    p_atendimento atendimento = malloc(sizeof(Atendimento));
    atendimento->qtd_livre = qtd_medicos;
    atendimento->qtd_ocupada = 0;
    p_deque deque = cria_deque();
    atendimento->fila_atendimento = deque;
    return atendimento;
}

/* Insere um paciente na fila do atendimento de acordo com sua prioridade */
p_atendimento insere_na_fila(p_atendimento a, p_paciente p) {
    int prioridade_paciente = prioridade(p);
    if (primeiro_paciente(a->fila_atendimento) == NULL) {
        a->fila_atendimento = insere_ini(a->fila_atendimento, p);
    } else if (prioridade_paciente) {
        a->fila_atendimento = insere_ini(a->fila_atendimento, p);
    } else
        a->fila_atendimento = insere_fim(a->fila_atendimento, p);
     p = altera_estado(p, 1);
    return a;
}

/* Remove um paciente do inicio da fila de atendimento */
p_paciente remove_da_fila(p_atendimento a) {
    p_paciente paciente = remove_ini(a->fila_atendimento);
    return paciente;
}

/* Verifica se existem medicos disponíveis em uma fila de atendimento */
int medico_disponivel(p_atendimento a) {
    return a->qtd_livre;
}

/* Atribui medicos a um atendimento */
p_atendimento atribui_medicos(p_atendimento a, int atribuicao) {
    a->qtd_livre -= atribuicao;
    a->qtd_ocupada += atribuicao;
    return a;
}

/* Atende os pacientes na fila de um atendimento */
p_atendimento atende_pacientes(p_atendimento a) { // erro?
    p_paciente paciente;
    p_consultas consultas;
    while (a->qtd_livre != 0 && paciente_na_fila(a->fila_atendimento)) {
        paciente = remove_ini(a->fila_atendimento);
        paciente = altera_estado(paciente, 0);
        consultas = consultas_do_paciente(paciente);
        remove_consulta(consultas);
        a = atribui_medicos(a, 1);
    }
    a = atribui_medicos(a, -a->qtd_ocupada);
    return a;
}

/* Destroi um atendimento e libera seu deque */
void destroi_atendimento(p_atendimento a) {
    destroi_deque(a->fila_atendimento);
    free(a);
}
