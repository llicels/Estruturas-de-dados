/*

INSERÇÃO EM LISTA ORDENADA

//verificar se a lista está cheia 

i = l->tamanho; (ultimo elemento da lista);

//começa no fim da lista
// ex: [2, 4, 6] inserir 5
// [2, 4, _, 6] [2, 4, 5, 6]
// elementos[i+1] = 6 e elementos[i] = 5

while(l-<elementos[i-1].chave > chaveInsercao && i>0){

    l->elementos[i] = l->elementos[i-1];
    i --;
}

l->elementos[i] = chaveInsercao;
l->tamanho++;



↪resolvendo e entendendo os bugs...

i == 3 é um elemento invalido, pois a ultima posicao válida é 2

então "while(l-<elementos[i-1].chave > chaveInsercao && i>0)" [i-1 = 3-1 = 2]
confere a **ultima posicao valida**

*/


/*
BUSCA BINARIA EM UM VETOR ORDENADO

inf = primeiro index
sup = ultimo index

meio = inf+sup /2

se sup < inf (ou inf > sup), elemento não encontrado


*/

#include <stdio.h>
#define MAX 5

typedef struct
    {
        int chave;
    } ELEMENTO;
    

typedef struct
    {
        ELEMENTO elementos[MAX];
        int tamanho;
    } LISTA;

void inicializar_lista(LISTA *lista) {
	lista->tamanho = 0;
}


void exibir_lista(LISTA *lista) {
	printf("Conteudo da lista (%d): ", lista->tamanho);
	for (int i = 0; i < lista->tamanho; i++) {
		printf("%d ",  lista->elementos[i].chave);
	}
	printf("\n");
}

int inserirListaOrd (LISTA *lista, ELEMENTO el){
    if (lista->tamanho >= MAX){
        return -1;
    }

    //(ultimo elemento da lista)
    int i = lista->tamanho;

    //começa no fim da lista
    // ex: [2, 4, 6] inserir 5
    // [2, 4, _, 6] [2, 4, 5, 6]
    // elementos[i] = 6 e elementos[i-1] = 5

    
    // i>0 tem que ir 1º para nao ter risco de ir para uma posicao invalida
    // [i-1] confere a ultima posica valida
    while(i > 0 && lista->elementos[i-1].chave  > el.chave){
        lista->elementos[i] = lista->elementos[i-1];
        i--;
    }

    lista->elementos[i] = el;
    lista->tamanho++;

    return 0;
}

int main (){
     LISTA minha_lista;

    inicializar_lista(&minha_lista);
     
     for (int i = 0; i < 5; i++) {
	 	ELEMENTO e = {.chave = i*i};
	 	inserirListaOrd(&minha_lista, e);
	 }

    exibir_lista(&minha_lista);

    
    return 0;
}