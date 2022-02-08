enum Cores {VERMELHO, PRETO};

typedef struct ArvoreRubroNegra {
    long long int num, qtd;
    enum Cores cor;
    struct ArvoreRubroNegra *esq, *dir;
} No;

typedef No *p_no;

p_no criaArvoreRN();
int noVermelho(p_no raiz);
int noPreto(p_no raiz);
p_no rotacionaEsquerda(p_no raiz);
p_no rotacionaDireita(p_no raiz);
void sobeVermelho(p_no raiz);
p_no insereOrdenado(p_no raiz, long long int num);
long long int qtdVezesAparece(p_no raiz, long long int num);
void qtdParaLegal(p_no raiz, long long int *qtd);
void imprimeInOrdem(p_no raiz);
void liberaArvoreRN(p_no raiz);
int verificaArvoreRubroNegra(p_no raiz);
