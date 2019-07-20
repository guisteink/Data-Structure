#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define tammax 100

typedef struct tnode {
	int id, time;
	struct tnode *down;
} node;

typedef struct {
	int quantum;
	int qtdprocessos; //qtd. de estruturas no vetor da fila
	node *vec[tammax];
} escalonador;


//recebe um node para o 1º da fila e o libera
void remove(node *n){
	if(!n)return;
	else{
		node *ptr = n;
		n=n->down;
		free(ptr);
		return;
	}
}

//verifica, atualiza e remove
void solve(node *n, int i, escalonador *e) {
	if (!n)
		return;
	else {
		while (n) { //percorre enquanto n existir;
			n->time = n->time - (pow(2, i) * e->quantum); //atualiza o time de cada prioridade;
			if (n->time) { //se existe quer dizer que é maior que zero. logo satisfaz
				node *ptr = n;
				n = n->down;
				remove(ptr);
			} else
				n = n->down;
		}
		return;
	}
}

//a
//verifica se o time de cada node - o quantum do escalonador é <= zero.
//caso for, tira ele da fila, se nao, mantem e pula pro proximo
//começa verificando pelo maior indice de prioridade na fila, qnto maior o indice i, maior a prioridade
void roundScheduler(escalonador *e) {
	if (!e)
		return;
	else {
		int i = e->qtdprocessos - 1;
		while (i >= 0) {
			if (e->vec[i]->down) {
				solve(e->vec[i]->down, i, e);
			}
			i--;
		}
	}
}

