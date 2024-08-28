#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 50

typedef struct {
    int chave;
} REGISTRO;

typedef struct {
    REGISTRO elementos[MAX];
    int topo;
} PILHA;

void iniciarPilha(PILHA *p){
    //indica que o topo está em uma posicao invalida
    p->topo = -1;
}

int tamanhoPilha(PILHA *p){
    return p->topo + 1;
}

bool push(PILHA *p, REGISTRO reg){
    if (p->topo == MAX-1){
        return false;
    }

    p->topo++;
    p->elementos[p->topo] = reg;

    return true;
}

bool pop(PILHA *p, REGISTRO *reg){
    if (p->topo == -1){
        return false;
    }

    *reg = p->elementos[p->topo];
    p->topo--;
    return true;
}

void reinicia(PILHA *p){
    p->topo = -1;
}

void exibir(PILHA *p){
    printf("Pilha com tamanho: %d; Topo: ", tamanhoPilha(p));
    for (int i = p->topo; i>=0; i--){
        printf("\n%d", p->elementos[i].chave);
    }
    printf("\nbase\n");

}

int main(){
    PILHA minhaPilha;
    REGISTRO reg;

    iniciarPilha(&minhaPilha);
    exibir(&minhaPilha);

    reg.chave = 13;
    push(&minhaPilha, reg);
    exibir(&minhaPilha);

    reg.chave = 89;
    push(&minhaPilha, reg);
    exibir(&minhaPilha);

    reg.chave = 7;
    push(&minhaPilha, reg);
    exibir(&minhaPilha);

    reg.chave = 22;
    push(&minhaPilha, reg);
    exibir(&minhaPilha);

    pop(&minhaPilha, &reg);
    printf("Registro removido: %d \n", reg.chave);
    exibir(&minhaPilha);


    return 0;
}