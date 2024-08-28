//busca
/* pos = L->inicio
    while(pos != 0 && L->elementos[pos].reg.chave<chaveBuscada)
    {
        pos = L->elementos[pos].prox;
    }
    if(L->elementos[pos].reg.chave == chaveBuscada)
        {
            return pos;
        }
    else return -1;
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 50
#define INVALIDO -1

//estática 

typedef struct 
{
    int chave;
}REGISTRO;

typedef struct 
{
    REGISTRO reg;
    int prox;
}ELEMENTO;

typedef struct
{
    ELEMENTO elementos[MAX];
    int inicio;
    int disp;
}LISTA;

void inicializarLista(LISTA *lista){
    lista->inicio = INVALIDO;
    lista->disp = 0;

    for (int i = 0; i < MAX; i++){
        lista->elementos[i].prox = i+1;
    }
    lista->elementos[MAX - 1].prox = INVALIDO;
}

int tamanhoLista(LISTA *lista){
    int tamanho = 0;
    int posAtual = lista->inicio;
    while(posAtual != INVALIDO){
        tamanho ++;
        posAtual = lista->elementos[posAtual].prox;
    }
    return tamanho;
}

void exibirLista(LISTA *lista){
    printf("Conteudo da lista (%d): ", tamanhoLista(lista));
    for (int pos = lista->inicio; pos != INVALIDO; pos = lista->elementos[pos].prox){
        printf("%d ", lista->elementos[pos].reg.chave);
    }
    printf("\n");
}

bool inserirLista(LISTA *lista, REGISTRO reg){
    int anterior = INVALIDO;
    int pos = lista->inicio;

    if (lista->disp == INVALIDO){
        return false;
    }

    while (pos != INVALIDO && lista->elementos[pos].reg.chave < reg.chave){
        anterior = pos;
        pos = lista->elementos[pos].prox;
    }

    int disp = lista->disp;
    lista->disp = lista->elementos[disp].prox;

    if (anterior == INVALIDO){
        int antigoProx = lista->inicio;
        lista->elementos[disp].reg = reg;
        lista->elementos[disp].prox = antigoProx;
        lista->inicio = disp;
    } else{
        int antigoProx = lista->elementos[anterior].prox;
        lista->elementos[anterior].prox = disp;
        lista->elementos[disp].reg = reg;
        lista->elementos[disp].prox = antigoProx;
    }

    return true;
}

int busca(LISTA *lista, int chaveBuscada){
    int pos = lista->inicio;

    /*se a lista não estiver ordenada:
    while(pos != INVALIDO)
    {
        if(lista->elementos[pos].reg.chave == chaveBuscada)
        {
            return pos;
        }
        pos = lista->elementos[pos].prox;
    }
    return INVALIDO;
    */
    while(pos != INVALIDO && lista->elementos[pos].reg.chave<chaveBuscada)
    {
        pos = lista->elementos[pos].prox;
    }
    if(lista->elementos[pos].reg.chave == chaveBuscada)
        {
            return pos;
        }
    else return INVALIDO;
}


int excluirLista(LISTA *lista, int chave) {
	int anterior = INVALIDO;
	int pos = lista->inicio;
	
	if (lista->disp == INVALIDO) {
		return false;
	}
	
	while (pos != INVALIDO &&
		lista->elementos[pos].reg.chave < chave) {
		anterior = pos;
		pos = lista->elementos[pos].prox;
	}
	
	if (pos == INVALIDO || lista->elementos[pos].reg.chave != chave)
		return -1;
	
	if (anterior == INVALIDO) {
		lista->inicio =  lista->elementos[pos].prox;
	} else {
		lista->elementos[anterior].prox =  lista->elementos[pos].prox;
	}
	
	// retorna o disponivel para a lista de disponiveis
	lista->elementos[pos].prox = lista->disp;
	lista->disp = pos;
	
}

int reinicializar(LISTA *lista){
    for (int i = 0; i<MAX; i++){
        REGISTRO reg0 = {.chave = 0};
        lista->elementos[i].reg = reg0;
        lista->elementos[i].prox = i+1;
    }
    inicializarLista(lista);
    printf("Lista reinicializada");
}


int main(){
    LISTA lista;
    inicializarLista(&lista);

    for (int i = 0; i < 6; i++){
        REGISTRO r = {.chave = rand()%100};
        printf("Inserindo elemento com chave = %d\n\t", r.chave);
        inserirLista(&lista, r);
        //exibirLista(&lista);
    }

    REGISTRO r = {.chave = 32};
    inserirLista(&lista, r);
    exibirLista(&lista);

    int encontrada = busca(&lista, 34);
    printf("Elemento de chave 34 encontrado na posicao fisica: %d\n", encontrada);

    reinicializar(&lista);

    while (lista.inicio != INVALIDO) {
		excluirLista(&lista, lista.elementos[lista.inicio].reg.chave);
		exibirLista(&lista);
	}
}


