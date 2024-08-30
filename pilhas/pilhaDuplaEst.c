#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 50

typedef struct {
    int chave;
} REGISTRO;

typedef struct {
    REGISTRO elementos[MAX];
    int topo1, topo2;
} PILHA;

void iniciarPilha(PILHA *p){
    //indica que o topo está em uma posicao invalida
    p->topo1 = -1;
    p->topo2 = MAX;
}

int tamanhoPilha(PILHA *p, int Npilha){
    if (Npilha == 1) return (p->topo1 + 1);
    if (Npilha == 2) return (MAX - p->topo2);
    return -1;
}

bool push(PILHA *p, REGISTRO reg, int Npilha){
    if (p->topo2 - p->topo1 == 1){
        return false;
    }

    if (Npilha != 1 && Npilha != 2) return false;

    if (Npilha == 1){
        p->topo1++;
        p->elementos[p->topo1] = reg;
    }
    if (Npilha == 2){
        p->topo2--;
        p->elementos[p->topo2] = reg;
    }
    

    return true;
}

bool pop(PILHA *p, REGISTRO *reg, int Npilha){

    if (Npilha != 1 && Npilha != 2) return false;

    if(Npilha == 1){
    if (p->topo1 == -1){
        return false;
    }

    *reg = p->elementos[p->topo1];
    p->topo1--;
    }

    if (Npilha == 2){
        if (p->topo2 == MAX){
        return false;
    }

    *reg = p->elementos[p->topo2];
    p->topo2++;
    }

    return true;
}


void reinicia(PILHA *p){
    iniciarPilha(p);
}

bool exibir(PILHA *p, int Npilha){

    if (Npilha == 1){
        printf("Pilha com tamanho: %d; Topo: ", tamanhoPilha(p, 1));
        for (int i = p->topo1; i>=0; i--){
            printf("\n%d", p->elementos[i].chave);
        }
        printf("\nbase\n");
    }
    if (Npilha == 2){
        printf("Pilha com tamanho: %d; Topo: ", tamanhoPilha(p, 2));
        for (int i = p->topo2; i < MAX; i++){
            printf("\n%d", p->elementos[i].chave);
        }
        printf("\nbase\n");
    } else {
        return false;
    }

}

int main(){
    PILHA minhaPilha;
    REGISTRO reg;

    iniciarPilha(&minhaPilha);
    exibir(&minhaPilha, 1);

    reg.chave = 13;
    push(&minhaPilha, reg, 1);
    exibir(&minhaPilha, 1);

    reg.chave = 89;
    push(&minhaPilha, reg, 1);
    exibir(&minhaPilha, 1);

    reg.chave = 7;
    push(&minhaPilha, reg, 1);
    exibir(&minhaPilha, 1);

    reg.chave = 22;
    push(&minhaPilha, reg, 1);
    exibir(&minhaPilha, 1);

    reg.chave = 44;
    push(&minhaPilha, reg, 2);
    exibir(&minhaPilha, 2);

    reg.chave = 1989;
    push(&minhaPilha, reg, 2);
    exibir(&minhaPilha, 2);

    reg.chave = 1979;
    push(&minhaPilha, reg, 2);
    exibir(&minhaPilha, 2);


    pop(&minhaPilha, &reg, 1);
    printf("Registro removido: %d \n", reg.chave);
    //aqui é melhor pegar o valor de retorno
    exibir(&minhaPilha, 1);

    pop(&minhaPilha, &reg, 2);
    printf("Registro removido: %d \n", reg.chave);
    exibir(&minhaPilha, 2);


    return 0;
}