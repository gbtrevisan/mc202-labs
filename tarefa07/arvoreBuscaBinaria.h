typedef struct _Raiz{
    char *mensagem;
    long long int chave;
    struct _Raiz *esq, *dir;
} Raiz;

typedef Raiz *p_raiz;

void troca_com_sucessor(p_raiz raiz);
p_raiz criar_token(long long int chave, char *mensagem, int max_msg);
p_raiz insere_ord(p_raiz raiz, p_raiz token);
p_raiz remove_ord(p_raiz raiz, int chave);
p_raiz busca(p_raiz raiz, int chave);
p_raiz procura_menor_soma(p_raiz raiz, int soma);
int conta_caracteres(p_raiz raiz);
int soma_nos(p_raiz raiz);
void imprime_in(p_raiz raiz);
void destroi_arvore(p_raiz raiz);
p_raiz libera_abb(p_raiz raiz);
