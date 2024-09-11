#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 7

typedef struct registro
{
    int chave;
} REGISTRO;

typedef struct filaEstatica
{
    REGISTRO A[MAX];
    int inicio;
    int tamanho;
} FILA;

typedef struct
{
    FILA semPrioridade;
    FILA comPrioridade;
} FILA_PRIORIDADE;


void inicializar(FILA *aFila){
    aFila->inicio = 0;
    aFila->tamanho = 0;
    printf("\nFila inicializada!");
}

void reinicializar(FILA *aFila){
    inicializar(aFila);
    printf("\nFila reinicializada!");
}

int tamanho(FILA *aFila){
    return aFila->tamanho;
}

void exibir(FILA *aFila){
    printf("\nFila (%d): [inicio]", tamanho(aFila));

    int posAtual = aFila->inicio;

    for (int i=0; i<tamanho(aFila); i++){
        printf("%d ", aFila->A[posAtual].chave);
        posAtual = (posAtual+1)%MAX;
    }
    printf ("[fim da fila] \n");
}

bool enfileirar(FILA *aFila, REGISTRO reg){
    if (aFila->tamanho == MAX) return false;

    int posInsercao = (aFila->inicio + aFila->tamanho) % MAX;

    aFila->A[posInsercao] = reg;
    aFila->tamanho++;
    return true;
}

bool desenfileirar(FILA *aFila, REGISTRO *reg){
    if (aFila->tamanho==0) return false;

    *reg = aFila->A[aFila->inicio];
    aFila->inicio = (aFila->inicio+1) % MAX;
    aFila->tamanho--;
    return true;
}

void inicializarP(FILA_PRIORIDADE *f){
    inicializar(&f->comPrioridade);
    inicializar(&f->semPrioridade);
}

bool enfileirarP(FILA_PRIORIDADE *f, REGISTRO reg, bool prio){
    if (prio) return enfileirar (&f->comPrioridade, reg);
    else return enfileirar (&f->semPrioridade, reg);
    return true;
}

bool desenfileirarP(FILA_PRIORIDADE *f, REGISTRO *reg){
    if (tamanho(&f->comPrioridade)>0) return desenfileirar(&f->comPrioridade, reg);
    else return desenfileirar(&f->semPrioridade, reg);

    return false;
}

void exibirP(FILA_PRIORIDADE *f){
    printf("\nCom prioridade:");
    exibir(&f->comPrioridade);
    printf("\nSem prioridade:");
    exibir(&f->semPrioridade);
}

int main(){
    FILA aFila;
    inicializar(&aFila);

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

    reinicializar(&aFila);
    FILA_PRIORIDADE fp;
    inicializarP(&fp);

    //inserindo:
    for (int i = 0; i < 8; i++)
    {
        REGISTRO reg;
        reg.chave = (rand()%100);
        bool funciona= enfileirarP(&fp, reg, false);
        if (funciona){
            printf("\nRegistro com chave %d enfileirado (sem prioridade)\n", reg.chave);
        } else{
            printf("\nFila estava cheia, nao foi possivel inserir!\n");
        }
        exibirP(&fp);
    }

    //inserindo:
    for (int i = 0; i < 8; i++)
    {
        REGISTRO reg;
        reg.chave = (rand()%100);
        bool funciona= enfileirarP(&fp, reg, true);
        if (funciona){
            printf("\nRegistro com chave %d enfileirado (com prioridade)\n", reg.chave);
        } else{
            printf("\nFila estava cheia, nao foi possivel inserir!\n");
        }
        exibirP(&fp);
    }

    //desenfileirando:
    for (int i = 0; i < 16; i++)
    {
        REGISTRO reg;
        bool funciona = desenfileirarP(&fp, &reg);
        exibirP(&fp);

        if (funciona){
            printf("\nElemento desenfileirado %d!\n", reg.chave);
        } else{
            printf("\nFila estava fazia, nada a remover!\n");
        }
    }
    
    
    return 0;
}
 