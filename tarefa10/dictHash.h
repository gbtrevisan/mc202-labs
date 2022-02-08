#define TAM_MAX_HASH 211
#define MAX_KEY 25

typedef struct No {
    char chave[MAX_KEY + 1];
    struct No *prox;
} No;

typedef No *p_no;

typedef struct DictHash {
    p_no tabela[TAM_MAX_HASH];
} DictHash;

typedef DictHash *p_dict;

p_no criaLista();
p_no insereLista(p_no lista, char *chave);
void liberaLista(p_no lista);
int hash(char *chave);
p_dict criaDicionario();
p_dict insereDicionario(p_dict dict, char *chave);
p_no busca(p_dict dict, char *chave);
void liberaDicionario(p_dict dict);
int procuraNoDict(p_dict dict, char *chave);
int contaErros(char *chaveDict, char *palavra);
