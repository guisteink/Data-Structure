/*
 * main.c
 *
 *  Created on: 18 de jun de 2019
 *      Author: guilh
 *      Exercicio 5 & 13. Lista duplamente encadeada circular
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct tnode {
	int valor;
	struct tnode *ant, *prox;
} node;

typedef struct {
	int size;
	struct tnode *inicio, *fim;
} lista;

lista *crialista() {
	lista *l = (lista*) calloc(1, sizeof(lista));
	if (!l)
		return 0;
	return l;
}

node *crianode(int value) {
	node *n = (node*) calloc(1, sizeof(node));
	if (!n)
		return 0;
	n->valor = value;
	n->ant = n->prox = 0;
	return n;
}

int poslist(lista *l, int x) {
	int pos;
	node *ptr;
	if (!l)
		return 0;
	pos = 1;
	ptr = l->inicio;
	while (ptr) {
		if (ptr->valor == x)
			return pos;
		pos++;
		ptr = ptr->prox;
	}
	return 0;
}

int estanalista(lista *l, int x) {
	if (!poslist(l, x))
		return 0;
	else
		return 1;
}

//(f) impressao
void printlist(lista *l) {
	printf("\nLista: \n");
	if (!l)
		return;
	node *ptr = l->inicio;
	if (l->size == 1) {
		printf("%d\t", ptr->valor);
		return;
	}
	while (ptr != l->fim) {
		printf("%d\t", ptr->valor);
		ptr = ptr->prox;
	}
	if (ptr == l->fim)
		printf("%d\t", ptr->valor);

	return;
}

//(a) Insere first
lista *insereini(lista *l, int x) {
	node *novo = crianode(x);
	//printf("teste1.0");
	if (!l)
		l = crialista();
	if (l->size == 0) {
		//printf("teste1.2");
		l = crialista();
		//	printf("teste1.3");
		novo->prox = novo;
		novo->ant = novo;
		l->inicio = l->fim = novo;
		l->size++;
		return l;
	}
	node *ptr = l->inicio;
	if (l->size == 1) {
		novo->prox = novo->ant = ptr;
		ptr->ant = ptr->prox = novo;
		l->size++;
		l->inicio = novo;
		return l;
	}
	//printf("teste1.5");
	novo->ant = l->fim;
	novo->prox = ptr;
	ptr->ant = novo;
	l->fim->prox = novo;
	l->inicio = novo;
	return l;
}

//(b) Remove first
lista *removeini(lista *l) {
	if (!l)
		return 0;
	if (l->size == 1) {
		l->inicio = l->fim = 0;
		l->size = 0;
		free(l->inicio);
		free(l);
		return 0;
	}
	node *ptr = l->inicio;
	l->inicio = l->inicio->prox;
	l->inicio->ant = l->fim;
	l->fim->prox = l->inicio;
	l->size--;
	free(ptr);
	return l;
}

//(c) Insere last
lista *inserefim(lista *l, int x) {
	node *novo = crianode(x);
	if (!l || l->size == 0) {
		l = crialista();
		l->inicio = l->fim = novo;
		novo->ant = l->inicio;
		novo->prox = l->fim;
		return l;
	}
	node *ptr = l->fim;
	if (l->size == 1) {
		novo->prox = l->inicio;
		novo->ant = ptr;
		ptr->prox = novo;
		l->inicio->ant = novo;
		l->fim = novo;
		l->size++;
		return l;
	}
	novo->ant = ptr;
	novo->prox = l->inicio;
	l->inicio->ant = ptr;
	ptr->prox = novo;
	l->fim = novo;
	l->size++;
	return l;
}

//(d) remove uma chave informada
lista *removeinfo(lista *l, int chave) {
	if (!l)
		return 0;
	if (l->size == 1) {
		free(l->inicio);
		l->size = 0;
		return l;
	}
	node *ptr = l->inicio;
	while(ptr!=l->fim){
		if(ptr->valor == chave){
			ptr->ant->prox = ptr->prox;
			ptr->prox->ant = ptr->ant;
			l->size--;
			free(ptr);
			return l;
		}
		ptr=ptr->prox;
	}
}

int main() {
	lista *l = crialista();
	//printf("teste1");
	l = insereini(l, 5);
	l = insereini(l, 4);
	l = inserefim(l, 6);
	//l = removeini(l);
	l = removeinfo(l, 5);
	printlist(l);

	//printf("teste1");

}
