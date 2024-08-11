#include <stdio.h>
#define MAX 10

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

int tamanho_lista(LISTA *lista) {
	return lista->tamanho;
}


// como lista é um ponteiro, utiliza-se lista->tamanho para acessar o
// tamanho da lista
int inserir_lista_fim (LISTA *lista, ELEMENTO el) {
	if (lista->tamanho == MAX) {
		return -1;
	}
	lista->elementos[lista->tamanho] = el;
	lista->tamanho++;
	return 0;
}

int inserir_lista_pos (LISTA *lista, ELEMENTO el, int pos) {
	if (lista->tamanho == MAX || pos > lista->tamanho || pos < 0) {
		return -1;
	}

    // elementos[i] é o ultimo elemento do array, recebe o penúltimo elemento
    // até a posição desejada estar livre
	int i = lista->tamanho;
	while (i > pos) {
		lista->elementos[i] = lista->elementos[i - 1];
		i--;
	}
	lista->elementos[pos] = el;
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

int buscar_lista (LISTA *lista, int chave) {
	for(int i = 0; i < lista->tamanho; i++) {
		if (lista->elementos[i].chave == chave) {
			return i;
		}
	} 
	return -1;
}

int excluir_el_lista(LISTA *lista, int chave) {
	int pos = buscar_lista(lista, chave);
	if (pos < 0) return -1;
	
	for (int i = pos; i < lista->tamanho -1 ; i++) {
		lista->elementos[i] = lista->elementos[i+1];
	}
	lista->tamanho--;
	return 0;
}

void reiniciar_lista(LISTA *lista) {
	lista->tamanho = 0;
}

int main() {
	LISTA minha_lista;
	
    //criando um elemento:
	//ELEMENTO e1 = {.chave = 99};
	//e1.chave = 99;

	for (int i = 0; i < 5; i++) {
		ELEMENTO e = {.chave = i*i};
		inserir_lista_fim(&minha_lista, e);
	}

	exibir_lista(&minha_lista);

    //↪OPERAÇÕES:
	// ELEMENTO e2;
	// e2.chave = 100;
	// inserir_lista_pos(&minha_lista, e2, 0); 
	// exibir_lista(&minha_lista);
	// e2.chave = -1;
	// inserir_lista_pos(&minha_lista, e2, minha_lista.tamanho);
	// exibir_lista(&minha_lista);
	
	// e2.chave = 1234;
	// inserir_lista_pos(&minha_lista, e2, minha_lista.tamanho/2);
	// exibir_lista(&minha_lista);
	
	// e2.chave = -2;
	// inserir_lista_pos(&minha_lista, e2, minha_lista.tamanho+1);
	// exibir_lista(&minha_lista);
	
	// int ret;
	// int chave;
	// chave = 100;
	// ret = buscar_lista(&minha_lista, chave);
	// if (ret >= 0)
	// 	printf("chave %d encontrada na posicao %d\n", chave , ret);
	// else
	// 	printf("chave %d nao encontrada \n", chave);
		
	
	// chave = -1;
	// ret = buscar_lista(&minha_lista, chave);
	// if (ret >= 0)
	// 	printf("chave %d encontrada na posicao %d\n", chave , ret);
	// else
	// 	printf("chave %d nao encontrada \n", chave);
		
	
	// chave = 1234;
	// ret = buscar_lista(&minha_lista, chave);
	// if (ret >= 0)
	// 	printf("chave %d encontrada na posicao %d\n", chave , ret);
	// else
	// 	printf("chave %d nao encontrada \n", chave);
		
	
	// chave = 333;
	// ret = buscar_lista(&minha_lista, chave);
	// if (ret >= 0)
	// 	printf("chave %d encontrada na posicao %d\n", chave , ret);
	// else
	// 	printf("chave %d nao encontrada \n", chave);
		
	// excluir_el_lista(&minha_lista, -1);
	// exibir_lista(&minha_lista);
	
	// excluir_el_lista(&minha_lista, 100);
	// exibir_lista(&minha_lista);
	
	// excluir_el_lista(&minha_lista, 1234);
	// exibir_lista(&minha_lista);
	
	
	// excluir_el_lista(&minha_lista, 1333234);
	// exibir_lista(&minha_lista);
	
	printf("Deseja reiniciar a lista?\n Y-sim, N-nao\n");
	char reinicia;
	scanf("%c", &reinicia);
	if(reinicia=='Y' || reinicia=='y'){
		reiniciar_lista(&minha_lista);
		exibir_lista(&minha_lista);
	}
	else{
		return 0;
	}
	// reiniciar_lista(&minha_lista);
	// exibir_lista(&minha_lista);
	
	return 0;
}
