#include <stdio.h>
#define MAX 5

/* lista com pivô
a ideia é reduzir para 1 comparação, leve melhora de desempenho

simula a insercao do elemento buscado na ultima pos da lista (indice == tamanho)
pq se nao a condicao "while" vai ser infinita

se (contador == tamanho) retorna -1 (chegou no elemento que foi inserido
artificialmente)

o vetor é declarado com [max+1] elementos para garantir que o truque 
funcione mesmo com a lista cheia */

typedef struct
    {
        int chave;
    } ELEMENTO;
    

typedef struct
    {
        ELEMENTO elementos[MAX+1];
        int tamanho;
    } LISTA;

void inicializar_lista(LISTA *lista) {
	lista->tamanho = 0;
}

int inserir_lista_fim (LISTA *lista, ELEMENTO el) {
	if (lista->tamanho == MAX) {
		return -1;
	}
	lista->elementos[lista->tamanho] = el;
	lista->tamanho++;
	return 0;
}

void exibir_lista(LISTA *lista) {
	printf("Conteudo da lista (%d): ", lista->tamanho);
	for (int i = 0; i < lista->tamanho; i++) {
		printf("%d ",  lista->elementos[i].chave);
	}
	printf("\n");
}

int buscaElementoComPivo(LISTA *lista, int chaveBuscada){

    //elemento pivo
    lista->elementos[lista->tamanho].chave = chaveBuscada;

    int i = 0;
    while (lista->elementos[i].chave != chaveBuscada){

        //na ultima iteracao i vai ser igual ao tamanho da lista, se
        //o elemento nao estiver na lista
        i++;
    }
    if (i== lista->tamanho){
        return -1;
    }

    return i;
}

int main (){
     LISTA minha_lista;

    inicializar_lista(&minha_lista);
     
     for (int i = 0; i < 5; i++) {
		ELEMENTO e = {.chave = i*i};
		inserir_lista_fim(&minha_lista, e);
	}

    exibir_lista(&minha_lista);

    int chaveEncontrada = buscaElementoComPivo(&minha_lista, 4);

    printf("Elemento encontrado na posicao: %d", chaveEncontrada);



    
    
    return 0;
}