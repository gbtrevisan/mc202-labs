#define NOME_MAX 15
#define ALUGUEL_DIARIO 57
#define CONSUMO 10
#define CUSTO_GASOLINA 4.104
#define TAXA_DA_UBER 0.25
#define TAXA_CANCELAMENTO 7
#define PAGAMENTO_UBERX 1.40

#define PAI(i) ((i - 1) / 2)
#define F_ESQ(i) ((2 * i) + 1)
#define F_DIR(i) ((2 * i) + 2)

typedef struct {
    char nome[NOME_MAX + 1];
    double qtdEstrelas;
    int posAtual[2], posDestino[2];
} Passageiro;

typedef struct {
    int pos[2], emCorrida;
    int kmRodados, kmCliente, cancelDoDia;
    Passageiro *filaDoUber;
    int qtdPassageiros, tamanhoFila;
} UberHeap;

typedef UberHeap *p_uber;

int absoluto(int x);
void trocaPassageiros(Passageiro *p1, Passageiro *p2);
p_uber criaUberHeap(int tamanhoFila);
int passageiroPreferencial(p_uber uberHeap, int i, int j);
int distanciaManhattan(int p1[2], int p2[2]);
void desceNoHeap(p_uber uberHeap, int i);
void sobeNoHeap(p_uber uberHeap, int i);
void insereNaFila(p_uber uberHeap, Passageiro p);
void aceitaCorrida(p_uber uberHeap, char *nome, double qtdEstrelas, int posAtual[2], int posDestino[2]);
Passageiro removeDaFila(p_uber uberHeap);
void finalizaCorrida(p_uber uberHeap);
void cancelaCorrida(p_uber uberHeap, char *nome);
void finalizaExpediente(p_uber uberHeap);
void liberaUberHeap(p_uber uberHeap);
