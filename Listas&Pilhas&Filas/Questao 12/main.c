#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct tnode {
	int valor, lin, col;
	struct tnode *down, *right;
} node;

//node la e cb, sao os primeiros nodes da matriz
int produtoEscalarME(node *la, node *cb) {
	if (!la || !cb || (la->lin != cb->col))
		return 0; //produto escalar zero.
	node *ptrl = la->right; //aponta ptrl para o primeiro valor da linha, seja nulo ou nao;;
	node *ptrc = cb->down; //aponta ptrc para o primeiro valor da coluna, seja nulo ou nao;;;
	int i, produto;
	for (i = 0; i < la->lin; i++) { //vai percorrer até o fim da linha, consequentemente da coluna, ja que tem o mesmo tamanho
		produto = ptrl->valor * ptrc->valor;
		ptrl = ptrl->right;
		ptrc = ptrc->down;
	}
	return produto;
}

