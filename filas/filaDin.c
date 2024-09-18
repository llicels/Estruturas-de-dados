/*sem cabeça*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
ponteiros para o inicio e para o fim
o elemento possui --chave-- e um --ponteiro para o prox--
no fim da fila o prox indica um ponteiro nulo

inserção:
- aloca na memoria a chave que quero inserir e o dele prox vai conter um ponteiro nulo
- o elemento que era ultimo passa a ter o prox apontando para o novo elemento
- o fim agora aponta para o novo elemento

remoção:
- o inicio passa a ser o prox do elemento que foi removido
- chave do elemento que foi removido é retornada
- free (elemento removido)
*/

//dados
typedef struct reg
{
    int chave;
}REGISTRO;

//gerencia a fila
typedef struct el
{
    REGISTRO reg;
    struct el*prox; 
}ELEMENTO;

typedef struct
{
    ELEMENTO *inicio;
    ELEMENTO *fim;
}FILA;

void inicializarFila(FILA *f){
    f->inicio = NULL;
    f->fim = NULL;
}

int tamanhoFila(FILA *f){
    ELEMENTO *atual = f->inicio;
    int tamanho=0;
    while(atual != NULL){
        tamanho++;
        atual = atual->prox;
    }
    return tamanho;
}

void exibir(FILA *f){
    ELEMENTO *atual = f->inicio;
    printf("\nFila (%d) comeco: ", tamanhoFila(f));
    while(atual != NULL){
        printf("%d ", atual->reg.chave);
        atual = atual->prox;
    }
    printf(" [fim]\n");
}

bool enfileirar(FILA *f, REGISTRO reg){
    ELEMENTO *novo = malloc(sizeof(ELEMENTO));
    if (novo == NULL) return false;

    novo->reg = reg;
    novo->prox = NULL;

    if(f->fim == NULL){
        f->inicio = novo;
    }
    else{
        f->fim->prox = novo;
    }
    f->fim = novo;

    return true;    
}

bool desenfileirar(FILA *f, REGISTRO *reg){
    if(f->inicio == NULL) return false;
    *reg = f->inicio->reg;
    ELEMENTO *antigo = f->inicio;
    f->inicio = f->inicio->prox;

    free(antigo);

    if(f->inicio == NULL) f->fim=NULL;


    return true;
}

void reinicialiazr(FILA *f){
    ELEMENTO *atual = f->inicio;
    while(atual){
        ELEMENTO *apagar = atual;
        atual = atual->prox;
        free(apagar);
    }
    f->inicio = NULL;
    f->fim = NULL;
}

int main(){
    FILA aFila;
    inicializarFila(&aFila);

    //inserindo:
    for (int i = 0; i < 8; i++)
    {
        REGISTRO reg;
        reg.chave = (rand()%100);
        bool funciona= enfileirar(&aFila, reg);
        if (funciona){
            printf("\nRegistro com chave %d enfileirado \n", reg.chave);
        } else{
            printf("\nFila estava cheia, nao foi possivel inserir!\n");
        }
        exibir(&aFila);
    }


    //desenfileirando:
    for (int i = 0; i < 8; i++)
    {
        REGISTRO reg;
        bool funciona = desenfileirar(&aFila, &reg);
        exibir(&aFila);

        if (funciona){
            printf("\nElemento desenfileirado %d!\n", reg.chave);
        } else{
            printf("\nFila estava fazia, nada a remover!\n");
        }
    }

    reinicialiazr(&aFila);
    return 0;
}