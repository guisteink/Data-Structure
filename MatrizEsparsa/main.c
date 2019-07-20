/**
 * Guilherme Stein Kuhn - 20017101997 - Estrutura de Dados (2019/01).
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define maxline 3
#define maxcolunm 3

//Estruturas
struct node {
	int info;
	struct node *right, *down; //apontadores
	int line, column;   //pos. da linha e coluna
};

typedef struct {
	int i, j;     //qtd. de linhas e colunas da matriz
	struct node*origem, *EndLine, *EndColumn; //os apontadores right e down do elemento origem apontam para o elemento na posicao [0x0] da matriz
} matrix;

//no cabecado inicializado nas linhas
struct node *createHeadLine(matrix *A, int i) {
	struct node *novo = (struct node*) calloc(1, sizeof(struct node));
	if (novo) {
		novo->column = -1;
		novo->line = i;
		novo->info = 0;

		A->EndLine->down = novo;
		A->EndLine = novo;

		novo->down = NULL;
		novo->right = novo;

		return novo;
	} else {
		printf("\nProblema na alocacao de memoria.");
		return NULL;
	}
}

//no cabeca inicializado nas colunas
struct node *createHeadColumns(matrix *A, int j) {
	struct node *novo = (struct node*) calloc(1, sizeof(struct node));
	if (novo) {
		novo->column = j;
		novo->line = -1;
		novo->info = 0;

		A->EndColumn->right = novo;
		A->EndColumn = novo;

		novo->down = novo;
		novo->right = NULL;

		return novo;
	} else {
		printf("Problema na alocacao de memoria.");
		return NULL;
	}
}

//////////////////////////////////////////////////

struct node *createElem(int x, int y, int z) {
	struct node *novo = (struct node*) calloc(1, sizeof(struct node));
	if (novo) {
		novo->info = x;
		novo->line = y;
		novo->column = z;
		return novo;
	} else
		return NULL;
}

matrix *createMEsparsa(int m, int n) {
	matrix *novo = (matrix *) calloc(1, sizeof(matrix));
	if (novo || m >= 0 || n >= 0) {
		struct node *origem = (struct node*) calloc(1, sizeof(struct node));
		if (!origem)
			return 0;

		origem->column = -1;
		origem->line = -1;
		origem->info = 0;

		novo->EndLine = origem;
		novo->EndColumn = origem;
		novo->i = m;
		novo->j = n;

		//criando cabecas de linha, onde os valores de coluna em cada variam
		for (int i = 1; i <= m; i++) {
			struct node *head = createHeadLine(novo, i);
			//if(i = 1)origem->down=head;
		}
		for (int j = 1; j <= n; j++) {
			struct node *head = createHeadColumns(novo, j);
			//if(j = 1)origem->down=head;
		}


		return novo;
	} else
		return 0;
}

int getElem(matrix *A, int linha, int coluna) {
	struct node *aux;
	int i = 0;

	aux = A->origem->right;

	for (i = 0; i < coluna - 1; i++) { //chega na coluna desejada
		aux = aux->right;
	}

	do {
		aux = aux->down;
		if (aux->line == linha) {
			return aux->info;
		}
	} while (aux->column != 0);

	return 0; //elemento nao encontrado
}

/////////////////////////////
//(A) Funcao de imprimir a matriz lida

void imprimeMatrix(matrix *A) {
	if (!A || A->i < 0 || A->j < 0)
		return;

	int cont1, cont2;
	struct node *aux;

	aux = A->origem->down;

	for (cont1 = 1; cont1 <= A->i; cont1++) {
		for (cont2 = 1; cont2 = A->j; cont2++) {
			if (aux->right->line == cont1 && aux->right->column == cont2) {

				aux = aux->right;
				printf("    \t%0.1f", aux->info);
			} else {
				printf("    \tNULL");
			}
		}
		printf("\n");
		aux = aux->right->down;
	}
	return;
}

//(B) Funcao pra ler a matriz
int **read(FILE *arq, int **a) {
	if ((arq = fopen("matrixA.txt", "r")) == NULL) {
		printf("Failed to open file (matrixA.txt).");
		return 0;
	} else {
		for (int i = 0; i < maxline; i++) {
			for (int j = 0; j < maxcolunm; j++) {
				fscanf(arq, "%d%*c", &a[i][j]);
			}
		}
		printf("\n\nended read\n\n");
		return a;
	}
}

//(C) Funcao pra apagar a matriz e desalocar todos os campos
void apagaMatrix(matrix *A) {
	int cont1 = 1;
	int cont2 = 1;
	struct node *aux, *aux2;

	if (!A || !A->i || !A->j) {
		return;
	}

	aux = A->origem->down;
	aux = aux->right;

	//percorre a matriz desalocando as posicoes [cont1xcont2]
	for (cont1 = 1; cont1 <= A->i; cont1++) {
		for (cont2 = 1; cont2 <= A->j; cont2++) {
			if (aux->line == cont1 && aux->column == cont2) {
				aux2 = aux;
				aux = aux->right;
				free(aux2);
			}
		}
		aux = aux->down->right;
	}

	//desaloca as cabecas
	aux = A->origem->right;

	for (cont2 = 0; cont2 < A->j; cont2++) { //cabecas coluna
		aux2 = aux;
		aux = aux->right;
		free(aux2);
	}

	aux = A->origem->down;
	for (cont1 = 0; cont1 < A->i; cont1++) { //cabecas linha
		aux2 = aux;
		aux = aux->down;
		free(aux2);
	}

	aux = A->origem;
	free(aux);

	A->EndColumn = A->EndLine = A->origem = NULL;
	A->i = A->j = 0;
	A = NULL;

	return;
}

//////////////////////////////////////////////
//(F) Funcao que insere um elemento numa determinada posicao da matriz
void insere(matrix *A, int linha, int coluna, int x) {
	if (!A || A->i < 0 || A->j < 0 || !x)
		return;

	if (linha > A->i || coluna > A->j || !x || linha < 1 || coluna < 1)
		return;

	int cont = 0;
	struct node *aux;       //auxiliar
	struct node *auxColuna; //auxiliar para coluna
	struct node *auxLinha;  //auxiliar para linha

	//a variavel aux precisa ser alocada pq vai ser adicionada
	aux = createElem(x, linha, coluna);
	if (!aux) //problema na alocacao
		return;

	auxColuna = A->origem->down; //aponta pra 1º coluna de elementos
	auxLinha = A->origem->right; //aponta pra 1º linha de elementos

	for (cont; cont < linha - 1; cont++) //percorre pra baixo ate achar a linha certa
			{
		auxLinha = auxLinha->down;
	}
	cont = 0;
	while (cont < coluna && auxLinha->right->line != 0) {
		//elemento a esquerda
		if (auxLinha->right->column > aux->column) {
			aux->right = auxLinha->right;
			auxLinha->right = aux;
		}
		//elemento a direita
		else {
			auxLinha = auxLinha->right;
		}
		cont++;
	}

	//elemento ainda a direita
	if (auxLinha->right->line < 0) {
		aux->right = auxLinha->right;
		auxLinha->right = aux; //ultima elemento, se nao estiver reaponta ao auxiliar
	}

	//refaz o processo porem com colunas...
	for (cont = 0; cont < coluna - 1; cont++) {
		auxColuna = auxColuna->right;
	}

	cont = 0;
	while (cont < linha && auxColuna->down->column != 0) {
		if (auxColuna->down->line > aux->line) {
			aux->down = auxColuna->down;
			auxColuna->down = aux;
		} else {
			auxColuna = auxColuna->down;
		}
		cont++;
	}
	if (auxColuna->down->column < 0) {
		aux->down = auxColuna->down;
		auxColuna->down = aux;
	}

	return;
}

//(D)Funcao que soma duas matrizes
matrix *somaMatrix(matrix *A, matrix *B, matrix *C) {
	int cont1, cont2;
	int soma;
	struct node *auxA, *auxB;

	//matriz so podem ser somadas se forem do mesmo formato 5x5, 4x4
	if (A->i != B->i || A->j != B->j) {
		printf("Matrizes de formatos diferentes.");
		return NULL;
	}

	if (!A || !B || !A->i || !A->j) {
		return NULL;
	}

	C = createMEsparsa(A->i, B->j);

	auxA = A->origem->down;
	auxB = B->origem->down;

	for (cont1 = 1; cont1 <= A->i; cont1++) {
		for (cont2 = 1; cont2 <= A->j; cont2++) {
			if (cont2 == auxA->right->column && cont2 == auxB->right->column) {
				soma = auxA->right->info + auxB->right->info;
				if (soma) {
					insere(C, cont1, cont2, soma);
				}
				auxA = auxA->right;
				auxB = auxB->right;
			} else if (cont2 == auxA->right->column) {
				insere(C, cont1, cont2, auxA->right->info);
				auxA = auxA->right;
			} else if (cont2 == auxB->right->column) {
				insere(C, cont1, cont2, auxB->right->info);
				auxB = auxB->right;
			}
		}
		auxA = auxA->right->down;
		auxB = auxB->right->down;
	}

	return C;
}

//(E)Funcao que multiplica duas matrizes, e devolve o Produto em outra matriz
matrix *multiplicaMatrix(matrix *A, matrix *B, matrix *C) {
	int cont = 0, cont2 = 0, cont3 = 0;
	int total;

	if (A->j != B->i) { //so pode multiplicar se o numero de colunas de A eh igual ao numero de linhas de B
		printf(
				"Para multiplicar eh necessario que as colunas de A sejam iguais ao numero de linhas de B, ou o inverso.\n");
		return NULL;
	}

	if (!A || !B || !A->i || !A->j || !B->j) {
		return NULL;
	}

	C = createMEsparsa(A->i, B->j); //C eh formada pelo numero de linhas de A e de colunas de B

	for (cont = 1; cont <= A->i; cont++) {
		for (cont2 = 1; cont2 <= B->j; cont2++) {
			total = 0;
			for (cont3 = 1; cont3 <= A->j; cont3++) {
				total += getElem(A, cont, cont3) * getElem(B, cont3, cont2);
			}
			if (total) {
				insere(C, cont, cont2, total);
			}
		}
	}
	return C;
}

int **alocamatrix() {
	int **a = (int**) calloc(maxline, sizeof(int*));
	for (int i = 0; i < maxline; i++) {
		a[i] = (int*) calloc(maxcolunm, sizeof(int));
	}
	if(!a)return 0;
	else return a;

}

void printmatrix(int **a) {
	for (int i = 0; i < maxline; i++) {
		for (int j = 0; j < maxcolunm; j++) {
			printf("%d\t", a[i][j]);
		}
		printf("\n");
	}
}

//PRECISO DE UMA FUNCAO PRA PREENCHER A MATRIX ESPARSA ALOCANDO PARTINDO DA MATRIX LIDA
void preencheMatrix(matrix *A,int **a){
	printf("\nteste\n");
	if (!A || A->i < 0 || A->j < 0)
			return;

		int cont1, cont2;
		struct node *aux;
		printf("\nteste1\n");

		aux = A->origem->down;
		printf("\nteste2\n");

		for (cont1 = 1; cont1 <= A->i; cont1++) {
			for (cont2 = 1; cont2 = A->j; cont2++) {
				if (aux->right->line == cont1 && aux->right->column == cont2) {
					printf("\nteste3\n");
					insere(A,cont1,cont2,a[cont1][cont2]); //inseriu o elemento da posicao
					aux=aux->right;
				} else {
					aux=aux->right;
				}
			}
			printf("\n");
			aux = aux->right->down;
		}
		return;
}


int main() {

	FILE *entrada = fopen("matrixA.txt", "r");

	int **a=alocamatrix();
	matrix *Esparsa = createMEsparsa(maxline,maxcolunm);
	read(entrada, a);
	printmatrix(a);

	preencheMatrix(Esparsa,a);

	printf("\nteste");


	return 0;
}
