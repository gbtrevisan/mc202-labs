#define PAI(i) (i - 1) / 2
#define F_ESQ(i) (2 * i + 1)
#define F_DIR(i) (2 * i + 2)

typedef struct NoHeap {
    int v;
    double dist;
} NoHeap;

typedef struct MinHeap {
    int tamanho, n;
    NoHeap *v;
} MinHeap;

typedef MinHeap * p_heap;

void verificaAlocao(void *p);
p_heap criaHeapMin(int n);
p_heap liberaHeapMin(p_heap heap);
void sobeNoHeap(p_heap heap, int i);
void desceNoHeap(p_heap heap, int i);
void insereHeap(p_heap heap, double d, int v);
double prioridade(p_heap heap, int v);
void alteraPrioridade(p_heap heap, double d, int v);
int vazio(p_heap heap);
NoHeap removeMin(p_heap heap);
