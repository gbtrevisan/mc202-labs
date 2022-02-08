#include "hospital.h"
#include <stdio.h>
#include <stdlib.h>

#define HOSPITAL_ABRE 8 * 60
#define TEMPO_CONSULTA 10

#define CLINICO_GERAL 10
#define RADIOLOGISTA 2
#define ENFERMEIRO 5
#define OTORRINOLARINGOLOGISTA 3
#define PNEUMOLOGISTA 4
#define DERMATOLOGISTA 7
#define NEUROLOGISTA 2
#define ONCOLOGISTA 1
#define PSIQUIATRA 4

int main() 
{
    char aux;
    int tempo = HOSPITAL_ABRE;
    p_atendimento atendimentos[9];
    atendimentos[0] = cria_atendimento(CLINICO_GERAL);
    atendimentos[1] = cria_atendimento(RADIOLOGISTA);
    atendimentos[2] = cria_atendimento(ENFERMEIRO);
    atendimentos[3] = cria_atendimento(OTORRINOLARINGOLOGISTA);
    atendimentos[4] = cria_atendimento(PNEUMOLOGISTA);
    atendimentos[5] = cria_atendimento(DERMATOLOGISTA);
    atendimentos[6] = cria_atendimento(NEUROLOGISTA);
    atendimentos[7] = cria_atendimento(ONCOLOGISTA);
    atendimentos[8] = cria_atendimento(PSIQUIATRA);
    p_paciente paciente;
    p_deque pacientes = cria_deque();

    while (scanf("%c", &aux) != EOF) {
        paciente = recebe_paciente();
        pacientes = insere_fim(pacientes, paciente);
    }

    while (paciente_na_fila(pacientes)) {
        p_no proximo;
        for (p_no l_pacientes = primeiro_paciente(pacientes); l_pacientes != NULL; l_pacientes = proximo) {
            paciente = pega_paciente(l_pacientes);
            p_consultas consultas = consultas_do_paciente(paciente);
            int consulta = consulta_atual(consultas);
            proximo = proximo_paciente(l_pacientes);
            if (!consulta) {
                paciente = adiciona_tempo(paciente, tempo);
                imprime_paciente(paciente);
                pacientes = libera_paciente(pacientes, l_pacientes);
            } else if (!ocupado(paciente))
                atendimentos[consulta - 1] = insere_na_fila(atendimentos[consulta - 1], paciente);
        }
        for (int i = 0; i < 9; i++)
            atende_pacientes(atendimentos[i]);
        tempo += TEMPO_CONSULTA;
    }

    for (int i = 0; i < 9; i++)
        destroi_atendimento(atendimentos[i]);
    destroi_deque(pacientes);
    
    return 0;
}
