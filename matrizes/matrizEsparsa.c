#include <stdio.h>
#include <stdlib.h>

#define VALOR_PADRAO 0

typedef struct COL_{
    int valor;
    int n_col;
    struct COL_*prox;
} COLUNA;

typedef struct{
    int n_linhas;
    int n_colunas;
    COLUNA **linhas;
} MATRIZ_ESPARSA;

void iniciaMat(MATRIZ_ESPARSA *m, int lin, int col){
    m->n_linhas = lin;
    m->n_colunas = col;
    m->linhas = malloc (lin* sizeof(COLUNA*));
    for (int i = 0; i < lin; i++){
        m->linhas[i] = NULL;
    }
}

//a linha é uma lista de colunas
//começa do 1 (o input do usuario)
int acessar(MATRIZ_ESPARSA *m, int lin, int col){
    if (lin < 1 || lin > m->n_linhas) return -1;
    if (col < 1 || lin > m->n_colunas) return -1;

    COLUNA *coluna_atual = m->linhas[lin - 1];

    while (coluna_atual != NULL && coluna_atual->n_col < col){
        coluna_atual = coluna_atual->prox;
    }

    
    if (coluna_atual != NULL && coluna_atual->n_col == col){
        return coluna_atual->valor;
    } return VALOR_PADRAO;
}

int atribuir(MATRIZ_ESPARSA *m, int lin, int col, int valor){
    if (lin < 1 || lin > m->n_linhas) return -1;
    if (col < 1 || lin > m->n_colunas) return -1;

    COLUNA* anterior = NULL;
    COLUNA *coluna_atual = m->linhas[lin-1];

    while (coluna_atual != NULL && coluna_atual->n_col < col){
        anterior = coluna_atual;
        coluna_atual = coluna_atual->prox;
    }

    //se a coluna nao existe
    if(coluna_atual==NULL || coluna_atual->n_col != col){
        if(valor != VALOR_PADRAO){
            COLUNA *nova_coluna = malloc(sizeof(COLUNA));
            nova_coluna->n_col = col;
            nova_coluna->valor = valor;

            //primeira inserção ou inserção na primeira coluna
            if(anterior == NULL){
                m->linhas[lin-1] = nova_coluna;
            }else anterior->prox = nova_coluna;

            nova_coluna->prox = coluna_atual;
        }
    } else{
        //se a coluna já existe
        if (valor != VALOR_PADRAO){
            coluna_atual->valor = valor;
        } else{
            // se deseja atribuir o valor padrao
            if(anterior==NULL){
                m->linhas[lin-1] = m->linhas[lin-1]->prox;
            } else anterior->prox = coluna_atual->prox;
            free(coluna_atual);
        }
    }

    return 0;
}

void exibir(MATRIZ_ESPARSA *m){
    for (int i=1; i<=m->n_linhas; i++){
        for (int j = 1; j <= m->n_colunas; j++){
            printf("%2d ", acessar(m, i, j));
        }
        printf("\n");
    }
}

int main(){
    MATRIZ_ESPARSA *m = malloc(sizeof(MATRIZ_ESPARSA));
    iniciaMat(m, 4, 5);

    for (int i=1; i<=m->n_linhas; i++){
        for (int j = 1; j <= m->n_colunas; j++){
            atribuir(m, i, j, i*10+j);
        }}
    
    atribuir(m,1,1,VALOR_PADRAO);
    atribuir(m, 2, 2, VALOR_PADRAO);
    atribuir(m,3,3,-1);
    atribuir(m,4,5,99);

    exibir(m);


}