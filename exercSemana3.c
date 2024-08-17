#include <stdio.h>
#include <stdlib.h>
#define MAX 50
#define ERRO -1
#define true 1
#define false 0

typedef int bool;

typedef int TIPOCHAVE;

typedef struct{
    TIPOCHAVE chave;
} REGISTRO;

typedef struct {
    REGISTRO A[MAX+1];
    int nroElem;
} LISTA;

void inicializarLista(LISTA* l){
    l->nroElem = 0;
}

void exibirLista(LISTA* l){
    int i;
    printf("Lista: \" ");
    for (i=0; i < l->nroElem; i++)
    printf("%i ", l->A[i].chave);
    printf("\"\n");
}

int ordenar(LISTA* l){

    //lista cheia
    if (l->nroElem == MAX){
        return -1;
    }

    //ultimo elemento da lista

    for (int j=0; j<l->nroElem; j++){
        int el = l->A[j].chave;
        int i = j-1;

        while(i>=0 && l->A[i].chave > el){
            l->A[i+1] = l->A[i];
            i--;
    }

    l->A[i+1].chave = el;
    }

    return 0;
}

int main(){
    LISTA l;

    inicializarLista(&l);
    l.nroElem = 4;
    l.A[0].chave = rand()%100;
    l.A[1].chave = rand()%100;
    l.A[2].chave = rand()%100;
    l.A[3].chave = rand()%100;
    exibirLista(&l);
    ordenar(&l);
    exibirLista(&l);
}