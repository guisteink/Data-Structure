/*
 * main.c
 *
 *  Created on: 22 de jun de 2019
 *      Author: guilh
 *      Exercicio 8
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	int chave;
} info;

typedef struct tnode {
	info *info;
	struct tnode *prox;
} node;

typedef struct {
	int size;
	struct tnode *last, *first, *window;
} lista;

info* createinfo(int x) {
	info *data = (info*) calloc(1, sizeof(info));
	if (!data)
		return 0;
	data->chave = x;
	return data;
}

node *createnode(info *x) {
	node *novo = (node*) calloc(1, sizeof(node));
	if (!novo || !x) {
		return 0;
	}
	novo->info = createinfo(x->chave); //calloc ja aponta os ponteiros para null, logo nao precisa se reapontar prox e ant;
	return novo;
}
lista *createlistavazia() {
	lista *l = (lista*) calloc(1, sizeof(lista));
	if (!l)
		return 0;
	return l;
}

lista *createlista(info *info) {
	node *n = createnode(info);

	lista *l = (lista*) calloc(1, sizeof(lista));
	if (!l || !n)
		return 0;
	l->first = l->last = n;
	l->size = 1;
	return l;
}

void printlista(lista *l) {
	printf("\nLISTA:\t");
	if (!l)
		return;
	node *ptr = l->first;
	while (ptr) {
		printf("%d\t", ptr->info->chave);
		ptr = ptr->prox;
	}
	return;
}

//tad list (a)
lista *inserefim(lista *l, info *info) {
	if (!l) {
		l = createlista(info);
		return l;
	}
	node *elem = createnode(info);
	if (l->size == 1 && elem) {
		l->last->prox = elem;
		l->last = elem;
		l->size++;
		return l;
	}
	if (l && elem) {
		node *ptr = l->last;
		ptr->prox = elem;
		l->last = elem;
		l->size++;
		return l;
	} else
		return 0;
}

lista *insereini(lista *l, info *info) {
	if (!l || l->size <= 0) {
		l = createlista(info);
		return l;
	}
	node *elem = createnode(info);
	if (l->size == 1 && elem) {
		elem->prox = l->first;
		l->first = elem;
		l->last = elem;
		l->size++;
		return l;
	}
	if (l && elem) {
		node *ptr = l->first;
		elem->prox = ptr;
		l->first = elem;
		l->size++;
		return l;
	} else
		return 0;
}

lista *deletefim(lista *l) {
	if (!l || l->size <= 0)
		return l;
	if (l->size == 1) {
		node *ptr = l->first = l->last;
		l->first = l->last = 0;
		free(ptr->info);
		free(ptr);
		l->size--;
		return l;
	}
	node *ptr = l->first;
	node *ptr2 = ptr->prox;
	while (ptr2->prox) {
		ptr = ptr2;
		ptr2 = ptr2->prox;
	}
	free(ptr2->info);
	free(ptr2);
	ptr->prox = 0;
	l->last = ptr;
	l->size--;
	return l;
}

lista *deleteini(lista *l) {
	if (!l || l->size <= 0)
		return l;
	if (l->size == 1) {
		node *ptr = l->first;
		l->last = 0;
		l->first = 0;
		l->size--;
		free(ptr->info);
		free(ptr);
		return l;
	}
	node *ptr = l->first;
	l->first = ptr->prox;
	l->size--;
	free(ptr->info);
	free(ptr);
	return l;
}

lista *deleteinfo(lista *l, info *info) {
	node *ptr, *pptr, *temp;

	if (!l)
		return 0;
	ptr = l->first;
	while (ptr->info->chave != info->chave) {

		if (!ptr->prox) {
			return 0;
		} else {
			pptr = ptr;
			ptr = ptr->prox;
		}
	}

	if (ptr == l->first) {
		l->first = ptr->prox;
	} else {
		pptr->prox = ptr->prox;
	}
	temp = ptr;
	free(ptr->info);
	free(ptr);
	l->size--;
	return l;
}

//posList (b)
void poslist(lista *l, int pos) {
	if (!l || pos <= 0)
		return;
	node *ptr = l->first;
	int i = 1;
	while (ptr->prox && i < pos) {
		ptr = ptr->prox;
		i++;
	}
	if (i == pos) {
		l->window = ptr;
		printf("\nposicionou");
		return;
	} else if (pos > l->size || !ptr) {
		printf("\nnao posicionou!");
		return;
	}
}

//(c) retorna o elemento de informacao da window
info *infolist(lista *l) {
	if (!l)
		return 0;
	else
		return l->window->info;
}

//(d) ordena lista (duplamente encadeada)
void ordenaDlist(lista *l) {

	int i, j, k;
	info *tempInfo;
	node *current, *next;

	k = l->size;
	if (!l)
		return;

	for (i = 0; i < (l->size - 1); i++, k--) {
		current = l->first;
		next = l->first->prox;
		for (j = 1; j < k; j++) {
			if (current->info->chave > next->info->chave) {
				tempInfo = current->info;
				current->info = next->info;
				next->info = tempInfo;
			}
			current = current->prox;
			next = next->prox;
		}
	}
}

int main(int argc, char **argv) {
	info *d1 = createinfo(4);
	info *d2 = createinfo(10);
	info *d3 = createinfo(22);

	lista *l = createlista(d1);

	l = inserefim(l, d2);

	l = insereini(l, d3);

	ordenaDlist(l);

	printlista(l);

	poslist(l, 2);

	info *window = infolist(l);
	printf("\nwindow: %d", window->chave);

	return 1;
}

