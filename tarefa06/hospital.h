typedef struct _consulta {
    int num;
    struct _consulta *prox_consulta;
} Consulta;

typedef Consulta *p_consulta;

typedef struct l_consultas {
    p_consulta ini, fim;
} L_consultas;

typedef L_consultas *p_consultas;

typedef struct _paciente {
    char *nome;
    int prioridade, tempo, ocupado;
    p_consultas consultas;
} Paciente;

typedef Paciente *p_paciente;

typedef struct _no {
    p_paciente paciente;
    struct _no *ant, *prox;
} No;

typedef No *p_no;

typedef struct _deque {
    p_no ini, fim;
} Deque;

typedef Deque *p_deque;

typedef struct _atendimento {
    int qtd_livre;
    int qtd_ocupada;
    p_deque fila_atendimento;
} Atendimento;

typedef Atendimento *p_atendimento;

void destroi_lista(p_consulta l);

p_consultas cria_consultas();
p_consultas insere_consulta(p_consultas l, int num);
int consulta_atual(p_consultas l);
int remove_consulta(p_consultas l);
p_consulta tem_consulta(p_consultas l);
void destroi_consultas(p_consultas l);

p_paciente recebe_paciente();
p_paciente define_nome(p_paciente p, char *nome_paciente);
p_paciente define_prioridade(p_paciente p, int prioridade);
p_paciente define_consultas(p_paciente p, p_consultas l);
p_paciente adiciona_tempo(p_paciente p, int tempo);
p_paciente altera_estado(p_paciente p, int num);
int prioridade(p_paciente p);
p_consultas consultas_do_paciente(p_paciente p);
int ocupado(p_paciente p);
void imprime_paciente(p_paciente p);
void destroi_paciente(p_paciente p);

p_no proximo_paciente(p_no p_atual);
p_paciente pega_paciente(p_no p_atual);
void destroi_pacientes(p_no no_paciente);

p_deque cria_deque();
p_deque insere_ini(p_deque d, p_paciente p);
p_deque insere_fim(p_deque d, p_paciente p);
p_paciente remove_ini(p_deque d);
p_paciente remove_fim(p_deque d);
p_no primeiro_paciente(p_deque d);
p_deque libera_paciente(p_deque d, p_no liberar);
int paciente_na_fila(p_deque d);
void destroi_deque(p_deque d);

p_atendimento cria_atendimento(int qtd_medicos);
p_atendimento insere_na_fila(p_atendimento a, p_paciente p);
p_paciente remove_da_fila(p_atendimento a);
int medico_disponivel(p_atendimento a);
p_atendimento atribui_medicos(p_atendimento a, int atribuicao);
p_atendimento atende_pacientes(p_atendimento a);
void destroi_atendimento(p_atendimento a);
