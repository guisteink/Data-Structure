#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//SO UTILIZEI USAR TUDO DENTRO DE UMA MAIN TESTE PQ ESTAVA COM MTO CONFLITOS DE TIPOS, *TYPEDEF DAS ESTRUTURAS
//****************************************************************************
//---------------------------------ESTRUTURAS---------------------------------
//---------------------------- STACK ; QUEUE ; LISTA -------------------------
//****************************************************************************

//**************************************** NODE *****************************

typedef struct {
	int chave;
} info;

typedef struct node {
	info *info;
	struct node *prox, *ant;
} tnode;

//*************************************** STACK *****************************
typedef struct {
	tnode *top;
	int size;
} stack;

//*************************************** QUEUE *****************************
typedef struct {
	tnode *first, *last;
	int size;
} queue;

//*************************************** LISTA *****************************
typedef struct {
	tnode *first, *last;
	int size;
} lista;

//********************************************************************************
info* createinfo(int x) {
	info *data = (info*) calloc(1, sizeof(info));
	if (!data)
		return 0;
	data->chave = x;
	return data;
}

tnode *createnode(info *x) {
	tnode *novo = (tnode*) calloc(1, sizeof(tnode));
	if (!novo || !x) {
		return 0;
	}
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
	free(ptr->info);
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
		printf("\n[%d]", stk->top->info->chave);
		return;
	}
	tnode *ptr = stk->top;
	while (ptr) {
		printf("\n[%d]", ptr->info->chave);
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
	free(ptr->info);
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
		printf("[%d]\t", ptr->info->chave);
		ptr = ptr->prox;
	}
	return;
}

//****************************************************************************
//--------------------------- FUNCOES LISTA ----------------------------------
//****************************************************************************
lista *crialista(info *info) {
	lista *l = (lista*) calloc(1, sizeof(lista));
	tnode *elem = createnode(info);
	if (l && elem) {
		l->first = elem;
		l->last = elem;
		l->size = 1;
		return l;
	} else
		return 0;
}

lista *inserefim(lista *l, info *info) {
	if (!l) {
		l = crialista(info);
		return l;
	}
	tnode *elem = createnode(info);
	if (l && elem) {
		tnode *ptr = l->last;
		ptr->prox = elem;
		l->last = elem;
		l->size++;
		return l;
	} else
		return 0;
}

lista *insereini(lista *l, info *info) {
	if (!l) {
		l = crialista(info);
		return l;
	}
	tnode *elem = createnode(info);
	if (l && elem) {
		tnode *ptr = l->first;
		elem->prox = ptr;
		l->first = elem;
		return l;
	} else
		return 0;
}

lista *deletefim(lista *l) {
	if (!l)
		return 0;
	if (l->size == 1) {
		tnode *ptr = l->first = l->last;
		l->first = l->last = 0;
		free(ptr->info);
		free(ptr);
		l->size--;
		return l;
	}
	tnode *ptr = l->first;
	tnode *ptr2 = ptr->prox;
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
	free(ptr->info);
	free(ptr);
	return l;
}

void printlista(lista *l) {
	printf("\n\nlista:\t");
	if (!l)
		return;
	tnode *ptr = l->first;
	while (ptr) {
		printf("[%d]\t", ptr->info->chave);
		ptr = ptr->prox;
	}
}

//*****************************************************************************************
//----------------------------------- ARVORE BINARIA --------------------------------------
//*****************************************************************************************

//node do tipo binary tree
typedef struct bt {
	struct bt *esq, *dir;
	info *info;
} bintree;

//1)cria a arvore binaria
bintree *createbt(info *info) {
	bintree *root = (bintree*) calloc(1, sizeof(bintree)); //quando se gera uma arvore, se cria a raiz
	if (!root)
		return 0;
	root->info = info;
	return root;
}

//2) left bt
bintree *leftbt(bintree *bt) {
	if (!bt)
		return 0;
	return bt->esq;
}

//3)right bt
bintree *rightbt(bintree *bt) {
	if (!bt)
		return 0;
	return bt->dir;
}

//4) elemento de informacao
info *infobt(bintree *bt) {
	if (!bt)
		return 0;
	return bt->info;
}

//5) elemento nulo, ou nao
bool isemptybt(bintree *bt) {
	if (!bt)
		return true;
	else
		return false;
}

//******************************************************************
//6) verifica se um elemento de informacao esta presente em uma arvore
int isinbt(bintree *bt, info *i) {
	if (bt->info == i)
		return 1;
	else {
		if (isinbt(bt->esq, i))
			return 1;
		if (isinbt(bt->dir, i))
			return 1;
		else
			return 0;
	}
}

//7) libera toda a memoria malocada por uma arvore binaria
void destroybt(bintree *root) {
	if (!root)
		return;
	else {
		destroybt(root->esq);
		destroybt(root->dir);
		free(root->info);
		free(root);
		return;
	}
}

//8) calcula a altura de uma arvore binaria
int alturabt(bintree *root) {
	if (!root)
		return 0;
	else {
		int e, d;
		e = 1 + alturabt(root->esq);
		d = 1 + alturabt(root->dir);
		if (e > d)
			return e;
		else
			return d;
	}
}

//9) gera uma lista representando o percurso pre-order da arvore
lista *listapreorder(bintree *root, lista *l) {
	if (!root)
		return 0;
	else {
		l = inserefim(l, root->info);
		l = listapreorder(root->esq, l);
		l = listapreorder(root->dir, l);
	}
	return l;
}

//10) gera uma lista representando o percurso in-order da arvore
lista *listainorder(bintree *root, lista *l) {
	if (!root)
		return 0;
	else {
		l = listainorder(root->esq, l);
		l = inserefim(l, root->info);
		l = listainorder(root->dir, l);
	}
	return l;
}

//11) gera uma lista representando o percurso pos-order da arvore
lista *listaposorder(bintree *root, lista *l) {
	if (!root)
		return 0;
	else {
		l = listaposorder(root->esq, l);
		l = listaposorder(root->dir, l);
		l = inserefim(l, root->info);
		return l;
	}
}

//12) gera uma lista representando o percurso por niveis da arvore
lista *listatolevel(bintree *root, lista *l) {
	if (!(root || l))
		return 0;
	else {
		l = inserefim(l, root->info);
		l = inserefim(l, root->esq->info);
		l = inserefim(l, root->dir->info);
		l = listatolevel(root->esq, l);
		l = listatolevel(root->dir, l);
	}
	return l;
}

//13) RECONSTRUIR UMA BT, DADOS SEUS PERCURSOS INORDER E POSORDER
















//********************************************************************************************
//-------------------------------- PROGRAMA PRINCIPAL ----------------------------------------
int main() {

	//------------------------------------------INFORMACOES-------------------------------------------
	info *d1 = createinfo(1);
	info *d2 = createinfo(2);
	info *d3 = createinfo(3);
	info *d4 = createinfo(4);
	info *d5 = createinfo(5);

	//-------------------------------------------NODES---------------------------------------------------
	tnode *p1 = createnode(d1);
	tnode *p2 = createnode(d2);
	tnode *p3 = createnode(d3);
	tnode *p4 = createnode(d4);
	tnode *p5 = createnode(d5);

//----------------------------------------- TESTE DAS FUNCOES DE STACK -------------------------------------
	// testar separado, comentando os outros tad


	stack *stk = createstack(p1);
	stk = push(stk, p2);
	stk = push(stk, p3);
	stk = push(stk, p4);
	tnode *temp = p4;
	stk = pop(stk);
	stk = push(stk, p5);

	printstack(stk);

	p4 = temp;
//------------------------------------------ TESTE DA FUNCOES DE FILA -----------------------------------
	// testar separado, comentando os outros tad
	queue *q = createqueue(p1);
	q = insert(q, p2);
	q = insert(q, p3);
	q = insert(q, p4);
	q = insert(q, p5);
	tnode *temp2 = p5;
	q = delete(q);


	printqueue(q);

	p5 = temp2;

//------------------------------------------ TESTE DA FUNCOES DE LISTA -----------------------------------
	// testar separado, comentando os outros tad
	lista *l = crialista(d1);
	l = insereini(l, d2);
	l = inserefim(l, d3);
	l = inserefim(l, d4);
	l = insereini(l, d5);
	l = deletefim(l);
	l = deleteini(l);


	printlista(l);

	return 0;
}
