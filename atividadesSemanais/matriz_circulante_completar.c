#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>


typedef struct {
	int* elementos;
	int n;
} MATRIZ_CIRCULANTE;

void inicializar_matriz(MATRIZ_CIRCULANTE *m, int ordem) {
	m->n = ordem;
	m->elementos = malloc (ordem * sizeof(int));
}

int calc_pos(int l, int c, int n) {
	int pos;
	if (c >= l) pos = c-l;
	else pos = c+n-l;
  
  	return pos;
}

bool acessar_matriz(MATRIZ_CIRCULANTE *m, int l, int c, int *v) {
	if (l <= 0 || l > m->n || c <= 0 || c > m->n) {
		return false;
	}
	
	*v = m->elementos[calc_pos(l,c,m->n)];
	
	return true;
}

bool atribuir_matriz(MATRIZ_CIRCULANTE *m, int l, int c, int v) {
	if (l != 1 || c <= 0 || c > m->n) {
		return false;
	}
	
	m->elementos[c-1] = v;
	
	return true;
}

void exibir_matriz(MATRIZ_CIRCULANTE *m) {
	int v;
	for (int i = 1; i <= m->n; i++) {
		for (int j = 1; j <= m->n; j++) {
			acessar_matriz(m, i, j, &v);
			printf("%4d ", v);	
		}
		printf("\n");
	}
}

int main () {

	MATRIZ_CIRCULANTE m;
	inicializar_matriz(&m, 4);
	
	int i = 1;
        for (int j = 1; j <= m.n; j++) {
                int valor = rand()%100;
                printf("Atribuindo valor %d na posição (%d, %d)\n", valor, i, j);
                bool deucerto = atribuir_matriz(&m, i, j, valor);
                if (!deucerto)
                        printf("Nao foi possivel atribuir em (%d, %d)\n", i ,j);
        }
	printf("\n");
	
	exibir_matriz(&m);
	printf("\n");
	// atribuir_matriz(&m, 1, 1, 1234);
	// exibir_matriz(&m);
	
	return 0;

}
