#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct 
{
    int chave;
} REGISTRO;

//_ELEMENTO == aux
typedef struct _ELEMENTO 
{
    struct _ELEMENTO* prox;
    REGISTRO reg;
} ELEMENTO;

typedef struct 
{
    ELEMENTO *topo;
} PILHA;

void inicializar(PILHA *p)
{
    p->topo = NULL;
}

//pode tambem passar a estrutura (sem *)
//seria (el = p.topo) pq não é um ponteiro para a estrutura
int tamanho (PILHA *p)
{
    ELEMENTO *el = p->topo;
    int t = 0;

    //enquanto el não é nulo
    while (el)
    {
        t++;
        el = el->prox;
    }
    return t;
}

void exibir (PILHA *p)
{
    printf("Pilha (%d) topo: ", tamanho(p));
    ELEMENTO *el = p->topo;

    //o mesmo que falar el != null
    while (el)
    {
        printf("%d ", el->reg.chave);
        el = el->prox;
    }
    printf(" base\n");
}

bool push(PILHA *p, REGISTRO reg)
{
    ELEMENTO *novoEl = malloc(sizeof(ELEMENTO));
    if (!novoEl) return false;

    novoEl->reg = reg;
    novoEl->prox = p->topo;
    p->topo = novoEl;

    return true;
}

bool pilhaVazia(PILHA *p)
{
    if (!p->topo) return true;
}

bool pop(PILHA *p, REGISTRO *reg)
{
    if (!reg) return false;
    if (pilhaVazia(p)) return false;

    ELEMENTO *apagar = p->topo;

    *reg = p->topo->reg;
    p->topo = p->topo->prox;
    free(apagar);
}

REGISTRO* peek(PILHA *p)
{
    if (!p->topo) return NULL;
    else return &p->topo->reg;
}

void reinicializar(PILHA *p)
{
    ELEMENTO *el = p->topo;
    while (el)
    {
        ELEMENTO *apagar = el;
        el = el->prox;
        free(apagar);
    }
    p->topo = NULL;
    
    printf("\n A pilha foi reiniciada");
}

int main(){
    PILHA *aPilha = malloc(sizeof(PILHA));
    if (!aPilha) return -1;

    inicializar(aPilha);

    for (int i = 0; i < 10; i++){
        int novaChave = rand()%100;
        REGISTRO reg = {.chave = novaChave};
        printf("\tpush %d\n", reg.chave);
        push(aPilha, reg);
        exibir(aPilha);
    }

    printf("O tamanho da pilha e %d \n", tamanho(aPilha));

    printf("\nTopo = %d\n", peek(aPilha)->chave);

    REGISTRO regTopo;
    pop(aPilha, &regTopo);

    reinicializar(aPilha);
    return 0;
}

