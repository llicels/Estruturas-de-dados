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
    while (el != NULL)
    {
        printf("%d ", el->reg.chave);
        el = el->prox;
    }
    printf(" base\n");
}

bool push(PILHA *p, REGISTRO reg)
{
    ELEMENTO *novoEl = malloc(sizeof(ELEMENTO));
    if (novoEl == NULL) return false;

    novoEl->reg = reg;
    novoEl->prox = p->topo;
    p->topo = novoEl;

    return true;
}

bool pilhaVazia(PILHA *p)
{
    return p->topo == NULL;
}

bool pop(PILHA *p, REGISTRO *reg)
{
    if (reg == NULL) return false;
    if (pilhaVazia(p)) return false;

    ELEMENTO *apagar = p->topo;

    *reg = p->topo->reg;
    p->topo = p->topo->prox;
    free(apagar);

    return true;
}

REGISTRO* peek(PILHA *p)
{
    if (p->topo == NULL) return NULL;
    else return &(p->topo->reg);
}

 void reverter(PILHA *p)
 {

    //se quiser só exibir a pilha invertida e nao inverte-la de fato, é só exibir a pilhaAux1, não precisa da pilha Aux2
    PILHA *pilhaAux1= malloc(sizeof(PILHA));
    PILHA *pilhaAux2= malloc(sizeof(PILHA));

    inicializar(pilhaAux1);
    inicializar(pilhaAux2);

    REGISTRO reg;

    while(p->topo != NULL)
    {
        pop(p, &reg);
        push(pilhaAux1, reg);
    }

    while(pilhaAux1->topo != NULL)
    {
        pop(pilhaAux1, &reg);
        push(pilhaAux2, reg);
    }

    while(pilhaAux2->topo != NULL)
    {
        pop(pilhaAux2, &reg);
        push(p, reg);
    }

    printf("\nPilha revertida!\n");
    exibir(p);
    free(pilhaAux1);
    free(pilhaAux2);
}

void ordenar(PILHA *p){
    PILHA*pilhaAux1 = malloc(sizeof(PILHA));

    REGISTRO reg;
    inicializar(pilhaAux1);

    while(p->topo != NULL)
    {
        REGISTRO temp = p->topo->reg;
        pop(p, &reg);

        while (pilhaAux1->topo != NULL && pilhaAux1->topo->reg.chave < temp.chave)
        {
            pop(pilhaAux1, &reg);
            push(p, reg);
        }
        push(pilhaAux1, temp);
        
    }

    reverter(pilhaAux1);
    while(pilhaAux1->topo != NULL)
    {
        pop(pilhaAux1, &reg);
        push(p, reg);
    }
    printf("\nPilha ordenada!");
    exibir(p);

}

void reinicializar(PILHA *p)
{
    ELEMENTO *el = p->topo;
    while (el != NULL)
    {
        ELEMENTO *apagar = el;
        el = el->prox;
        free(apagar);
    }
    p->topo = NULL;
    
    printf("\nA pilha foi reiniciada");
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

    //reverter(aPilha);

    ordenar(aPilha);

    // printf("O tamanho da pilha e %d \n", tamanho(aPilha));

    // printf("\nTopo = %d\n", peek(aPilha)->chave);

    // REGISTRO regTopo;
    // pop(aPilha, &regTopo);
    // exibir(aPilha);
    // printf("\nTopo = %d\n", peek(aPilha)->chave);

    reinicializar(aPilha);
    return 0;
}

