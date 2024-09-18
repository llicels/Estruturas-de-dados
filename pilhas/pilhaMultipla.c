#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 20
#define NP 4

typedef struct 
{
    int chave;
}REGISTRO;

typedef struct 
{
    int topo[NP+1];
    int base[NP];
    REGISTRO regs[MAX];    
}PILHA;

void inicializar(PILHA *pm){
        for(int i=0; i<NP; i++){
            pm->base[i] = i*(MAX/NP);
            pm->topo[i] = pm->base[i]-1; //pq a pilha está vazia
        }

        pm->base[NP] = MAX;
}


//verifica se uma pilha individual está cheia
bool pilhaCheia(PILHA *pm, int k){
    if (k < 0 || k>= NP) return true;

    //true se a pilha estiver cheia, false se não não
    return(pm->topo[k] == pm->base[k+1] - 1);
}

bool pilhaVazia(PILHA *pm, int k){
    if(k<0 || k>=NP) return false;

    return(pm->topo[k] == pm->base[k] - 1);
}


void reinicializar(PILHA *pm){
    inicializar(pm);
}
int tamanho(PILHA *pm, int k){
    if(k<0 || k>=NP) return 0;

    //para quando a pilha tiver somente um elemento, base=topo, na pos 0, o tamanho será 0+1
    return pm->topo[k] - pm->base[k] +1;
}



void exibir(PILHA *pm){
    for(int i = 0; i < NP;i++){
        printf("Pilha k = %d tamanho=%d (base)", i, tamanho(pm, i));
        for(int j = pm->base[i]; j <= pm->topo[i]; j++){
            printf("%d ", pm->regs[j].chave);
        }
        printf("(topo)\n");
    }
}

bool deslocarDireita(PILHA *pm, int k){
    if(k<0 || k>=NP) return false;

    if(pilhaCheia(pm,k)) return false;

    for(int i = pm->topo[k]; i>=pm->base[k]; i--){
        pm->regs[i+1] = pm->regs[i];
    }

    pm->base[k]++;
    pm->topo[k]++;
    return true;
}

bool deslocarEsquerda(PILHA *pm, int k){
    //não pode deslocar a pilha 0
    if(k<1 || k>=NP) return false;

    //a pilha anterior precisa ter espaço
    if(pilhaCheia(pm,k-1)) return false;

    for(int i = pm->base[k]; i <= pm->topo[k]; i++){
        pm->regs[i-1] = pm->regs[i];
    }

    pm->topo[k]--;
    pm->base[k]--;
}




bool push(PILHA *pm, int k, REGISTRO reg){
    if(k<0 || k>=NP) return false;

    if(pilhaCheia(pm, k)){

        for (int i=k+1; i < NP; i++){
            deslocarDireita(pm, i);
        }

        if(pilhaCheia(pm, k)){

            for(int i = 1; i<=k; i++){
                deslocarEsquerda(pm, i);
            }

        } 
        if(pilhaCheia(pm, k)) return false;
    } 

    pm->topo[k] ++;
    pm->regs[pm->topo[k]] = reg;
}


bool pop(PILHA *pm, int k, REGISTRO* reg){
    if(k<0 || k>=NP) return false;

    if (pilhaVazia(pm, k)) return false;

    //pos que está no topo
    *reg = pm->regs[pm->topo[k]];
    pm->topo[k]--;
    return true;
}

int main(){
    PILHA pm;
    inicializar(&pm);

    for (int i = 0; i<7; i++){
        REGISTRO reg;
        reg.chave = rand()%100;
        printf("Inserindo %d \n", reg.chave);
        push(&pm, 2, reg);
        exibir(&pm);
    }
}




