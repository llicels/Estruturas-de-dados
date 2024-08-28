#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

typedef struct 
{
    int chave;
}REGISTRO;

typedef struct aux
{
    REGISTRO reg;

    //um ponteiro para a própria estrutura
    struct aux *prox, *ant;

    //o tipo ELEMENTO é equivalente a aux, porém ELEMENTO não pode ser usado dentro da
    //struct pq ele ainda está sendo definido
}ELEMENTO;

typedef struct
{
    
    ELEMENTO *inicio;
    
}LISTA;

void inicilialiarLista(LISTA *lista){
    lista->inicio = NULL;
}

void reiniciarLista(LISTA *lista){
    ELEMENTO *ptr = lista->inicio;
    while(ptr != NULL){
        ELEMENTO *prox = ptr->prox;
        free(ptr);
        ptr = prox;

    }
    lista->inicio = NULL;
}

int tamanhoLista(LISTA *lista){
    int tamanho = 0;
    ELEMENTO *ptr = lista->inicio;
    while (ptr != NULL){
        tamanho++;
        ptr = ptr->prox;
    }
    return tamanho;
}

void exibirLista(LISTA *lista){
    ELEMENTO *fim = lista->inicio;
    while (fim != NULL)
    {
        printf("%d ", fim->reg.chave);
        fim = fim->prox;
    }
    
}

typedef ELEMENTO* PONT;

void buscaAux(LISTA *lista, int chave, PONT*anterior, bool *achou){
    *anterior = NULL;
    *achou = false;
    ELEMENTO *atual = lista->inicio;


    while (atual != NULL && atual->reg.chave < chave){
        *anterior = atual;
        atual = atual->prox;
    }

    if (atual != NULL && atual->reg.chave == chave){
        *achou = true;
    }

}

bool excluirElemento(LISTA *lista, int chave){
    ELEMENTO *anterior;
    bool achou;
    buscaAux(lista, chave, &anterior, &achou);


    if(!achou){
        return false;
    }


    if (anterior == NULL){
        ELEMENTO *aDarFree = lista->inicio;
        lista->inicio = lista->inicio->prox;
        lista->inicio->ant = NULL;
        free(aDarFree);
    } else{
        ELEMENTO *aDarFree = anterior->prox;
        anterior->prox = anterior->prox->prox;
        anterior->ant = anterior;
        free(aDarFree);
    }

    return true;
}

bool inserirLista(LISTA *lista, REGISTRO novoReg){
    ELEMENTO *anterior;
    bool achou;

    ELEMENTO *novo = malloc(sizeof(ELEMENTO));

    if (novo == NULL){
        return false;
    }
    novo->reg = novoReg;

    buscaAux(lista, novoReg.chave, &anterior, &achou);


    if (achou){
        free(novo);
        return false;
    }

    if (anterior == NULL){
        novo->ant = NULL;
        novo->prox = lista->inicio;
        lista->inicio = novo;
    } else{
        novo->ant = anterior;
        novo->prox = anterior->prox;
        anterior->prox = novo;
        if(novo->prox != NULL){
            novo->prox->ant = novo;
        }
    }

    return true;
}

ELEMENTO *listaBusca(LISTA *lista, int chave){
    ELEMENTO *elAtual = lista->inicio;
    while(elAtual != NULL){
        if (elAtual->reg.chave == chave){
            return elAtual;
        }
        elAtual = elAtual->prox;
    }
    return NULL;
}

ELEMENTO *listaBuscaOrdenada(LISTA *lista, int chave){
    ELEMENTO *elAtual = lista->inicio;
    while(elAtual != NULL && elAtual->reg.chave < chave){
        elAtual = elAtual->prox;
        }
    if (elAtual != NULL && elAtual->reg.chave == chave){
        return elAtual;
    }
    return NULL;
}

int main(){
    LISTA lista;

    inicilialiarLista(&lista);

    int tam = tamanhoLista(&lista);
    printf("\nO tamanho da lista e %d\n", tam);


    for (int i = 0; i < 6; i++){
        REGISTRO r = {.chave = rand()%100};
        printf("\tInserindo elemento com chave = %d\n", r.chave);
        inserirLista(&lista, r);
    }

    exibirLista(&lista);

    tam = tamanhoLista(&lista);
    printf("\nO tamanho da lista e %d\n", tam);

    excluirElemento(&lista, 0);

    tam = tamanhoLista(&lista);
    printf("\nApós exclusão, o tamanho da lista e %d\n", tam);

    exibirLista(&lista);

    reiniciarLista(&lista);


    return 0;
}

