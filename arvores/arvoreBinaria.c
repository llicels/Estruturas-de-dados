#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define DIREITA 0
#define ESQUERDA 1

typedef struct NO_{
    int chave;
    struct NO_ *esq, *dir;
} NO;

typedef NO* ARVORE;

NO* criar_no(int chave){
    NO *novo = malloc(sizeof(NO));
    novo->chave = chave;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

void criarRaiz(ARVORE *arvore, int chave){
    *arvore = criar_no(chave);
}

NO* busca(ARVORE raiz, int chave){
    if (raiz==NULL) return NULL;

    if(raiz->chave == chave) return raiz;

    NO *esquerda = busca(raiz->esq, chave);
    if (esquerda != NULL) return esquerda;
    return busca(raiz->dir, chave);
}

bool inserir(ARVORE raiz, int chaveNova, int chavePai, int lado){
    NO *pai = busca(raiz, chavePai);
    if(pai == NULL) return false;

    NO *novo = criar_no(chaveNova);

    if(lado == ESQUERDA){
        novo->esq = pai->esq;
        pai->esq = novo;
    } 
    else if(lado == DIREITA){
        novo->dir = pai->dir;
        pai->dir = novo;
    } 
    else{
        free(novo);
        printf("\nLado inválido!!!");
        return false;
    }

    return true;
}

bool exibir_preordem(ARVORE raiz){
    if (raiz == NULL) return false;
    printf("%d", raiz->chave);
    printf("(");
    exibir_preordem(raiz->esq);
    printf("|");
    exibir_preordem(raiz->dir);
    printf(")");
}

void freesub(ARVORE raiz){
    if (raiz == NULL) return;
    freesub(raiz->esq);
    freesub(raiz->dir);
    free(raiz);
}

bool excluir(ARVORE *raiz, int chave){
     if (*raiz==NULL) return false;

     if((*raiz)->chave == chave){
         freesub(*raiz);
         *raiz = NULL;
         return true;
    } 

     bool certo = excluir(&(*raiz)->esq, chave);
     if (certo) return certo;
     return excluir(&(*raiz)->dir, chave);
}

int main(){
    ARVORE raiz;
    criarRaiz(&raiz, 1);

    bool certo = inserir(raiz, 2, 1, 1);
    if(!certo) printf("\nERRO");

    certo = inserir(raiz, 3, 1, 0);
    if(!certo) printf("\nERRO");

    certo = inserir(raiz, 8, 2, 0);
    if(!certo) printf("\nERRO");

    certo = inserir(raiz, 9, 8, 0);
    if(!certo) printf("\nERRO");

    certo = inserir(raiz, 5, 2, 0);
    if(!certo) printf("\nERRO\n");

    certo = inserir(raiz, 5, 90, 0);
    if(!certo) printf("\nERRO");

    exibir_preordem(raiz);

    excluir(&raiz, 9);
    printf("\n");
    exibir_preordem(raiz);

    return 0;

    
}