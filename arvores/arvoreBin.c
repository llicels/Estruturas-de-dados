//esse codigo ta bem bugado O.O
#include <stdlib.h>
#include <stdio.h>

typedef struct{
    char chave;
} REGISTRO;

typedef struct no_{
    REGISTRO reg;
    struct NO_ *esq;
    struct NO_ *dir;
} NO;

typedef NO ARVORE;

void minha_funcao(REGISTRO *reg){
    printf("%c ", reg->chave);
}

void pre_ordem(ARVORE *arvore, void (*func)(REGISTRO*)){
    if(arvore == NULL) return;
    func(&arvore->reg);
    pre_ordem(arvore->esq, func);
    pre_ordem(arvore->dir, func);
}

int main()
{
    ARVORE a;
    NO *no;

    a.reg.chave = 'A';

    no = malloc(sizeof(NO));
    no->reg.chave = 'B';
    no->esq = NULL;
    no->dir = NULL;
    a.esq = no;

    no = malloc(sizeof(NO));
    no->reg.chave = 'C';
    no->esq = NULL;
    no->dir = NULL;
    a.dir = no;

    pre_ordem(&a, &minha_funcao);
    return 0;
}
