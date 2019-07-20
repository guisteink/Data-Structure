/**
 * Guilherme Stein Kuhn - Estrutura de Dados - 2017101997
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define MAX 5

typedef struct {
	int chave;
} info;

typedef struct tnode {
	info *info;
	struct tnode *prox, *ant;
} node;

//*************************************** STACK *****************************
typedef struct {
	node *top;
	int size;
} stack;

//*************************************** QUEUE *****************************
typedef struct {
	stack *stk1, *stk2;
} queue;

//********************************************************************************
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

//(1)
//****************************************************************************
//--------------------------- FUNCOES STACK ----------------------------------
//****************************************************************************
stack *createstack(info *info) {
	node *elem = createnode(info);
	stack *stk = (stack*) calloc(1, sizeof(stack));
	if (stk && elem) {
		stk->size = 1;
		stk->top = elem;
		return stk;
	} else
		return 0;
}

stack *push(stack *stk, info *info) {
	if (stk->size > MAX)
		return 0;
	node *elem = createnode(info);
	if ((stk && stk->size > 0) && elem) {
		node *ptr = stk->top;
		ptr->prox = elem;
		elem->ant = ptr;
		stk->top = elem;
		stk->size++;
		return stk;
	} else
		return 0;
}

stack *pop(stack *stk) {
	if (!stk || stk->size <= 0)
		return 0;
	node *ptr = stk->top;
	ptr->ant->prox = 0; //2 ou mais elementos
	stk->top = ptr->ant;
	stk->size--;
	free(ptr->info);
	free(ptr);
	return stk;
}

int stacksize(stack *stk) {
	return stk->size;
}

node *stacktop(stack *stk) {
	return stk->top;
}

void printstack(stack *stk) {
	printf("pilha:");
	if (!stk || stk->size <= 0)
		return;
	if (stk->size == 1) {
		printf("\n[%d]", stk->top->info->chave);
		return;
	}
	node *ptr = stk->top;
	while (ptr) {
		printf("\n[%d]", ptr->info->chave);
		ptr = ptr->ant;
	}
	return;
}

//********************* FUNÇOES QUEUE ADAPTADAS *********************************
queue *createqueue() {
	//fila alocada com 2 vetores de pilha com 5 espaços alocados em branco
	queue *q = (queue*) calloc(1, sizeof(queue));
	q->stk1 = (stack*) calloc(MAX, sizeof(stack));
	q->stk2 = (stack*) calloc(MAX, sizeof(stack));
	q->stk1->top = q->stk2->top = q->stk1->size = q->stk2->size = 0;
	if (!q || q->stk1 || q->stk2)
		return 0;
	return q;
}

// ****************** FUNÇÕES INSERTQUEUE E REMOVEQUEUE ************************
//acabei definindo que as pilhas em cada fila, tem uma size definida pela constante MAX, pra entender melhor a questao
queue *insertqueue(queue *q, info *info) {
	if (!info)
		return q;
	if (!q) {
		q = createqueue();
		q->stk1 = push(q->stk1, info);
		return q;
	} else {
		if (q->stk1->size >= 0 && q->stk1->size <= MAX) {
			q->stk1 = push(q->stk1, info);
			return q;
		}
		if (q->stk2->size >= 0 && q->stk2->size <= MAX) {
			q->stk2 = push(q->stk2, info);
			return q;
		} else
			return q;
	}
}

queue *removequeue(queue *q) {
	if (!q)
		return 0;
	else {
		if (q->stk1->size >= 0 && q->stk1->size <= MAX) {
			q->stk1 = pop(q->stk1);
			return q;
		}
		if (q->stk2->size >= 0 && q->stk2->size <= MAX) {
			q->stk2 = pop(q->stk2);
			return q;
		}
		else return q;
	}
}

/**
 * CONCLUSAO:
 * AS FUNCOES INSERTQUEUE E REMOVEQUEUE ACABAM LEVANDO A COMPLEXIDADE DA PILHA * QTD DE PILHAS QUE EXISTEM NA FILA
 */


int main(int argc, char **argv) {

}

