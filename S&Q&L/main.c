#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//****************************************************************************
//---------------------------------ESTRUTURAS---------------------------------
//---------------------------- STACK ; QUEUE ; LISTA -------------------------
//****************************************************************************

typedef struct node {
	int info;
	struct node *prox, *ant;
} tnode;

typedef struct {
	tnode *top;
	int size;
} stack;

typedef struct {
	tnode *first, *last;
	int size;
} queue;

typedef struct {
	tnode *first, *last;
	int size;
} lista;

tnode *createnode(int x) {
	tnode *novo = (tnode*) calloc(1, sizeof(tnode));
	if (!novo)
		return 0;
	novo->info = x; //calloc ja aponta os ponteiros para null, logo nao precisa se reapontar prox e ant;
	return novo;
}

//****************************************************************************
//--------------------------- FUNCOES STACK ----------------------------------
//****************************************************************************
stack *createstack(tnode *elem) {
	stack *stk = (stack*) calloc(1, sizeof(stack));
	if (!stk)
		return 0;
	stk->size = 1;
	stk->top = elem;
	return stk;
}

stack *push(stack *stk, tnode *elem) {
	if (!stk || stk->size <= 0) {
		stk = createstack(elem);
		return stk;
	}
	tnode *ptr = stk->top;
	ptr->prox = elem;
	elem->ant = ptr;
	stk->top = elem;
	stk->size++;
	return stk;
}

stack *pop(stack *stk) {
	if (!stk || stk->size <= 0)
		return 0;
	tnode *ptr = stk->top;
	ptr->ant->prox = 0;
	stk->top = ptr->ant;
	stk->size--;
	free(ptr);
	return stk;
}

int stacksize(stack *stk) {
	return stk->size;
}

tnode *stacktop(stack *stk) {
	return stk->top;
}

void printstack(stack *stk) {
	printf("pilha:");
	if (!stk || stk->size <= 0)
		return;
	if (stk->size == 1) {
		printf("\n[%d]", stk->top);
		return;
	}
	tnode *ptr = stk->top;
	while (ptr) {
		printf("\n[%d]", ptr->info);
		ptr = ptr->ant;
	}
	return;
}

//****************************************************************************
//--------------------------- FUNCOES QUEUE ----------------------------------
//****************************************************************************
queue *createqueue(tnode *elem) {
	queue *q = (queue*) calloc(1, sizeof(queue));
	if (!q)
		return 0;
	q->size = 1;
	q->first = elem;
	q->last = elem;
	return q;
}

queue *insert(queue *q, tnode *elem) {
	if (!q || q->size <= 0) {
		q = createqueue(elem);
		return q;
	}
	tnode *ptr = q->last;
	ptr->prox = elem;
	elem->ant = ptr;
	q->last = elem;
	q->size++;
	return q;
}

queue *delete(queue *q) {
	if (!q || q->size <= 0)
		return NULL;
	tnode *ptr = q->first;
	q->first = ptr->prox;
	free(ptr);
	return q;
}

int queuesize(queue *q) {
	return q->size;
}

tnode *queuefirst(queue *q) {
	return q->first;
}

tnode *queuelast(queue *q) {
	return q->last;
}

void printqueue(queue *q) {
	printf("\n\nfila:\t");
	if (!(q->size || q))
		return;
	tnode *ptr = q->first;
	while (ptr) {
		printf("[%d]\t", ptr->info);
		ptr = ptr->prox;
	}
	return;
}

//****************************************************************************
//--------------------------- FUNCOES LISTA ----------------------------------
//****************************************************************************
lista *crialista(tnode *elem) {
	lista *l = (lista*) calloc(1, sizeof(lista));
	if (!l)
		return 0;
	l->first = elem;
	l->last = elem;
	l->size = 1;
	return l;
}

lista *inserefim(lista *l, tnode *elem) {
	if (!l) {
		l = crialista(elem);
		return l;
	}
	tnode *ptr = l->last;
	ptr->prox = elem;
	l->last = elem;
	l->size++;
	return l;
}

lista *insereini(lista *l, tnode *elem) {
	if (!l) {
		l = crialista(elem);
		return l;
	}
	tnode *ptr = l->first;
	elem->prox = ptr;
	l->first = elem;
	return l;
}

lista *deletefim(lista *l) {
	if (!l)
		return 0;
	if (l->size == 1) {
		tnode *ptr = l->first = l->last;
		l->first = l->last = 0;
		free(ptr);
		l->size--;
		printf("lalalalal");
		return l;
	}
	tnode *ptr = l->first;
	tnode *ptr2 = ptr->prox;
	while (ptr2->prox) {
		ptr = ptr2;
		ptr2 = ptr2->prox;
	}
	free(ptr2);
	ptr->prox = 0;
	l->last = ptr;
	l->size--;
	return l;
}

lista *deleteini(lista *l) {
	if (!l)
		return 0;
	if (l->size == 1) {
		tnode *ptr = l->last = l->first;
		free(ptr);
		l->size = 0;
		return 0;
	}
	tnode *ptr = l->first;
	l->first = ptr->prox;
	l->size--;
	free(ptr);
	return l;
}

void printlista(lista *l) {
	printf("\n\nlista:\t");
	if (!l)
		return;
	tnode *ptr = l->first;
	while (ptr) {
		printf("[%d]\t", ptr->info);
		ptr = ptr->prox;
	}
}

//********************************************************************************************
//-------------------------------- PROGRAMA PRINCIPAL ----------------------------------------
int main() {
	//----------------------------------------- TESTE DAS FUNCOES DE STACK -------------------------------------
	tnode *p1 = createnode(1);
	tnode *p2 = createnode(2);
	tnode *p3 = createnode(3);
	tnode *p4 = createnode(4);
	tnode *p5 = createnode(5);

	stack *stk = createstack(p1);
	stk = push(stk, p2);
	stk = push(stk, p3);
	stk = push(stk, p4);
	stk = pop(stk);
	stk = push(stk, p5);

	printstack(stk);

	//------------------------------------------ TESTE DA FUNCOES DE FILA -----------------------------------
	tnode *f1 = createnode(1);
	tnode *f2 = createnode(2);
	tnode *f3 = createnode(3);
	tnode *f4 = createnode(4);
	tnode *f5 = createnode(5);

	queue *q = createqueue(f1);
	q = insert(q, f2);
	q = insert(q, f3);
	q = insert(q, f4);
	q = insert(q, f5);
	q = delete(q);

	printqueue(q);

	//------------------------------------------ TESTE DA FUNCOES DE LISTA -----------------------------------
	tnode *n1 = createnode(1);
	tnode *n2 = createnode(2);
	tnode *n3 = createnode(3);
	tnode *n4 = createnode(4);
	tnode *n5 = createnode(5);

	lista *l = crialista(n1);
	l = insereini(l, n2);
	l = inserefim(l, n3);
	l = inserefim(l, n4);
	l = insereini(l, n5);
	l = deletefim(l);
	l = deleteini(l);

	printlista(l);













	return 0;
}

