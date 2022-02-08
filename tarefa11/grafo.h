typedef struct No 
{
    int v;
    struct No *prox;
} No;

typedef No * p_no;

typedef struct Grafo 
{
    int tamanho;
    p_no *adj;
} Grafo;

typedef Grafo * p_grafo;

void verificaFalhaAlloc(void *p);
p_no criaLista();
p_no liberaLista(p_no lista);
p_no insereLista(p_no lista, int v);
int buscaLista(p_no lista, int v);
p_no removeLista(p_no lista, int v);
p_grafo criaGrafo(int n);
p_grafo liberaGrafo(p_grafo grafo);
void insereAresta(p_grafo grafo, int u, int w);
void removeAresta(p_grafo grafo, int u, int w);
int verificaAresta(p_grafo grafo, int u, int w);
