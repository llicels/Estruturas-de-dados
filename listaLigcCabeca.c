//uma lista ligada com "pivo"
//"circular"
//a busca começa a partir do 1 elemento valido (não é a cabeça)
//insere o elemento novo na ordem e o novo elemento aponta para onde seu elemento antecessor apontava
//lista->cabeca funciona como o "NULL"


#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<malloc.h>
typedef struct 
{
    int chave;
}REGISTRO;

typedef struct aux
{
    REGISTRO reg;

    //um ponteiro para a própria estrutura
    struct aux *prox;

    //o tipo ELEMENTO é equivalente a aux, porém ELEMENTO não pode ser usado dentro da
    //struct pq ele ainda está sendo definido
}ELEMENTO;

typedef struct
{
    
    ELEMENTO *cabeca;
    
}LISTA;

void inicializarLista(LISTA *lista){
    lista->cabeca = malloc(sizeof(ELEMENTO));
    lista->cabeca->prox = lista->cabeca;
}

void reiniciarLista(LISTA *lista){
    ELEMENTO *ptr = lista->cabeca->prox;
    while(ptr != lista->cabeca){
        ELEMENTO *prox = ptr->prox;
        free(ptr);
        ptr = prox;

    }
    lista->cabeca->prox = lista->cabeca;
}

int tamanho(LISTA *lista){
    int tam = 0;
    ELEMENTO *atual = lista->cabeca;

    while(atual->prox != lista->cabeca){
        tam++;
        atual = atual->prox;
    }
    return tam;
}


void buscaAux(LISTA *lista, int chave, ELEMENTO**anterior, bool *achou){
    *anterior = lista->cabeca;
    *achou = false;
    ELEMENTO *atual = lista->cabeca->prox;

    lista->cabeca->reg.chave = chave;


    while (atual != lista->cabeca && atual->reg.chave < chave){
        *anterior = atual;
        atual = atual->prox;
    }

    if (atual != lista->cabeca && atual->reg.chave == chave){
        *achou = true;
    }

}

bool inserir(LISTA *lista, REGISTRO reg){
    ELEMENTO *ant;
    bool achou;

    buscaAux(lista, reg.chave, &ant, &achou);

    if (achou){
        return false;
    }
    ELEMENTO *novo = malloc(sizeof(ELEMENTO));
    if (novo == NULL){
        return false;
    }

    novo->reg = reg;
    novo->prox = ant->prox;
    ant->prox = novo;

    return true; 

}

bool excluir(LISTA *lista, int chave){
    ELEMENTO *anterior;
    bool achou;
    buscaAux(lista, chave, &anterior, &achou);
    if (!achou){
        return false;
    }
    ELEMENTO *aExcluir = anterior->prox;

    anterior->prox = aExcluir->prox;
     free(aExcluir);

     return true;
}

REGISTRO *listaBusca(LISTA *lista, int chave){
    lista->cabeca->reg.chave = chave;
    ELEMENTO *elAtual = lista->cabeca->prox;
    while(elAtual->reg.chave < chave){
        elAtual = elAtual->prox;
        }
    ELEMENTO *candidato = elAtual->prox;
    if(candidato == lista->cabeca){
        return NULL;
    }
    return &candidato->reg;
}

void exibir(LISTA *lista){
    ELEMENTO *atual = lista->cabeca->prox;
    printf("Tamanho: %d, Elementos: ", tamanho(lista));


    while (atual != lista->cabeca)
    {
        printf("%d \n", atual);
        atual = atual->prox;
    }
     
}


int main(){
    LISTA lista;

    inicializarLista(&lista);

    for (int i = 0; i < 6; i++){
        REGISTRO r = {.chave = rand()%100};
        printf("\tInserindo elemento com chave = %d\n", r.chave);
        inserir(&lista, r);
    }

    int tam = tamanho(&lista);
    printf("\nO tamanho da lista e %d\n", tam);



    return 0;
}


/*valgrind*/