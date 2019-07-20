/**
 * Guilherme Stein Kuhn - Estrutura de Dados - 2017101997
 */
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
	novo->info = createinfo(x->chave); //calloc ja aponta os ponteiros para null, logo nao precisa se reapontar prox e ant;
	return novo;
}

//(1)
//****************************************************************************
//--------------------------- FUNCOES STACK ----------------------------------
//****************************************************************************
stack *createstack(info *info) {
	tnode *elem = createnode(info);
	stack *stk = (stack*) calloc(1, sizeof(stack));
	if (stk && elem) {
		stk->size = 1;
		stk->top = elem;
		return stk;
	} else
		return 0;
}

stack *push(stack *stk, info *info) {
	tnode *elem = createnode(info);
	if ((stk && stk->size > 0) && elem) {
		tnode *ptr = stk->top;
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
	tnode *ptr = stk->top;
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

//(2)
//****************************************************************************
//--------------------------- FUNCOES QUEUE ----------------------------------
//****************************************************************************
queue *createqueue(info *info) {
	queue *q = (queue*) calloc(1, sizeof(queue));
	tnode *n = createnode(info);
	if (!q || !info || !n)
		return q;
	q->first = q->last = n;
	q->size = 1;
	return q;
}

queue *insert(queue *q, info *info) {
	tnode *elem = createnode(info);
	if ((q && q->size >= 1) && elem) {
		tnode *ptr = q->last;
		ptr->prox = elem;
		elem->ant = ptr;
		q->last = elem;
		q->size++;
		return q;
	} else
		return 0;
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

//(3)
//****************************************************************************
//--------------------------- FUNCOES LISTA ----------------------------------
//****************************************************************************
lista *crialistavazia() {
	lista *l = (lista*) calloc(1, sizeof(lista));
	if (!l)
		return 0;
	/**
	 * calloc ja zera todos os apontamentos
	 */
	return l;
}

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

//busca ordenada deve ser feita em listas ordenadas
int buscaOrdenada(lista *l, info *info) {
	if (!l || !info)
		return 0;
	tnode *ptr = l->first;
	if (ptr->info->chave == info->chave)
		return 1;
	if (ptr->info->chave < info->chave)
		return 0;
	if (ptr->info->chave > info->chave) {
		while (ptr) {
			if (ptr->info->chave == info->chave)
				return 1;
			ptr = ptr->prox;
		}
	}
}

//busca desordenada
int buscaDesordenada(lista *l, info *info) {
	if (!l || !info)
		return 0;
	tnode *ptr = l->first;
	while (ptr) {
		if (ptr->info->chave == info->chave)
			return 1;
		ptr = ptr->prox;
	}
}

lista *inserefim(lista *l, info *info) {
	if (!l || l->size <= 0) {
		l = crialista(info);
		return l;
	}
	tnode *elem = createnode(info);
	if (l->size == 1 && elem) {
		l->last->prox = elem;
		l->last = elem;
		l->size++;
		return l;
	}
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
	if (!l || l->size <= 0) {
		l = crialista(info);
		return l;
	}
	tnode *elem = createnode(info);
	if (l->size == 1 && elem) {
		elem->prox = l->first;
		l->first = elem;
		l->last = elem;
		l->size++;
		return l;
	}
	if (l && elem) {
		tnode *ptr = l->first;
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
	if (!l || l->size <= 0)
		return l;
	if (l->size == 1) {
		tnode *ptr = l->first;
		l->last = 0;
		l->first = 0;
		l->size--;
		free(ptr->info);
		free(ptr);
		return l;
	}
	tnode *ptr = l->first;
	l->first = ptr->prox;
	l->size--;
	free(ptr->info);
	free(ptr);
	return l;
}

lista *deleteinfo(lista *l, info *info) {
	tnode *ptr, *pptr, *temp;

	if (!l)
		return 0;
	ptr = l->first;
	//navigate through list
	while (ptr->info->chave != info->chave) {

		//if it is last node
		if (!ptr->prox) {
			return 0;
		} else {
			//store reference to current link
			pptr = ptr;
			//move to next link
			ptr = ptr->prox;
		}
	}

	//found a match, update the link
	if (ptr == l->first) {
		//change first to point to next link
		l->first = ptr->prox;
	} else {
		//bypass the current link
		pptr->prox = ptr->prox;
	}
	temp = ptr;
	free(ptr->info);
	free(ptr);
	l->size--;
	return l;
}

//intercala
lista *intercala(lista *l1, lista *l2, lista *l3) {
	printf("\nLista intercalada!\n");
	if (!l1 && !l2)
		return 0;
	if (!l1)
		return l2;
	if (!l2)
		return l1;
	tnode *ptr1 = l1->first;
	tnode *ptr2 = l2->first;

	while (ptr1 && ptr2) {
		l3 = inserefim(l3, ptr1->info);
		l3 = inserefim(l3, ptr2->info);
		ptr1 = ptr1->prox;
		ptr2 = ptr2->prox;
	}
	if (!ptr2) {
		while (ptr1) {
			l3 = inserefim(l3, ptr1->info);
			ptr1 = ptr1->prox;
		}
	}
	if (!ptr1) {
		while (ptr2) {
			l3 = inserefim(l3, ptr2->info);
			ptr2 = ptr2->prox;
		}
	}
	info *a;
	return l3;
}

//ordena crescente
void sortList(lista *lst) {

	int i, j, k;
	info *tempInfo;
	tnode *current;
	tnode *next;

	k = lst->size;
	if (!lst && lst->size <= 0)
		return;

	for (i = 0; i < (lst->size - 1); i++, k--) {
		current = lst->first;
		next = lst->first->prox;
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

//ordena decrescente
void sortListdec(lista *lst) {

	int i, j, k;
	info *tempInfo;
	tnode *current;
	tnode *next;

	k = lst->size;
	if (!lst && lst->size <= 0)
		return;

	for (i = 0; i < (lst->size - 1); i++, k--) {
		current = lst->first;
		next = lst->first->prox;
		for (j = 1; j < k; j++) {
			if (current->info->chave < next->info->chave) {
				tempInfo = current->info;
				current->info = next->info;
				next->info = tempInfo;
			}
			current = current->prox;
			next = next->prox;
		}
	}
}

//remove duplicadas
lista *removedup(lista *l) {
	if (!l)
		return l;
	tnode *ptr = l->first, *pptr;
	while (ptr) {
		pptr = ptr->prox;
		while (pptr) {
			if (ptr->info->chave == pptr->info->chave) {
				l = deleteinfo(l, pptr->info);
			}
			pptr = pptr->prox;
		}
		ptr = ptr->prox;
	}
	return l;
}

void printlista(lista *l) {
	if (!l || l->size <= 0)
		return;
	tnode *ptr = l->first;
	while (ptr) {
		printf("[%d]\t", ptr->info->chave);
		ptr = ptr->prox;
	}
}

int main() {

	//Questao 4, realiza a leitura de 10 elementos
	//(a)
	lista *l1 = crialistavazia(), *l2 = crialistavazia();
	printf("\nLista 1!\n");
	int x, i, qtd = 3, a, b;
	for (i = 0; i < qtd; i++) {
		printf("\nElemento a ser inserido: ");
		scanf("%d", &x);
		info *temp = createinfo(x);
		l1 = inserefim(l1, temp);
	}
	printf("\nLista2!\n");
	for (i = 0; i < qtd; i++) {
		printf("\nElemento a ser inserido: ");
		scanf("%d", &x);
		info *temp = createinfo(x);
		l2 = inserefim(l2, temp);
	}

	//(b)
	printf("\n\nLista 1:\n");
	printlista(l1);
	printf("\n\nLista 2:\n");
	printlista(l2);

	//(c)
	for (i = 0; i < 2; i++) {
		printf("\n\nQue elemento da l1 que migrara pra l2? ");
		scanf("%d", &a);
		info *temp1 = createinfo(a);
		int aux1 = buscaDesordenada(l1, temp1);
		if (aux1) {
			l2 = inserefim(l2, temp1);
			l1 = deleteinfo(l1, temp1);
		}
	}

	printf("\n\nLista 1:\n");
	printlista(l1);
	printf("\n\nLista 2:\n");
	printlista(l2);

	//(d) Ordena decrescente
	sortListdec(l2);
	sortListdec(l1);
	printf("\n\nLista 1 ordenada decrescente:\n");
	printlista(l1);
	printf("\n\nLista 2 ordenada decrescente:\n");
	printlista(l2);

	//(e) intercalar
	lista *l3 = crialistavazia();
	l3 = intercala(l1, l2, l3);
	printlista(l3);

	return 1;
}
