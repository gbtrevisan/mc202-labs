typedef struct _elemento {
    int dado;
    struct _elemento *prox;
} elemento;

typedef elemento * lista;

lista cria_lista();
void destroi_lista(lista l);
lista armazena_num(lista l, int x);
lista maximo(lista n1, lista n2);
lista realiza_operacao(lista n1, lista n2, char operador);
lista soma(lista n1, lista n2);
lista subtracao(lista n1, lista n2);
lista multiplicacao(lista n1, lista n2);
