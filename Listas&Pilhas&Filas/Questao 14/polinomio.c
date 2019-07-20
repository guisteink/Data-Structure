#include "polinomio.h"

node *createnode(int coef, int pot) {
	node *novo = (node*) calloc(1, sizeof(node));
	if (!novo)
		return 0;
	else {
		novo->coef = coef;
		novo->pot = pot;
		novo->prox = 0;
		return novo;
	}
}

void print(node *a) {
	if (!a) {
		return;
	} else {
		if (!a->coef && !a->pot)
			a = a->prox;
		printf("\n");
		while (a) {
			printf("\t+\t");
			printf("%dx^%d", a->coef, a->pot);
			a = a->prox;

		}
		return;
	}
}

//remove o nó b da encadeaçao com começo a.
void removeD(node *a, node *b) {
	if (!a && !b) {
		if (a->prox == b) {
			a->prox = b->prox;
			free(b);
			return;
		} else {
			node *ant = a;
			node *aux = a->prox;
			while (aux->prox) {
				if (aux == b) {
					ant->prox = aux->prox;
					free(aux);
				} else {
					ant = ant->prox;
					aux = aux->prox;
				}
			}
			return;
		}
	} else
		return;
}

//funcionando
//insere a lista a, na lista c
node *insere(node *a, node *c) {
	node *auxc = c;
	node *auxa = a;
	while (auxc->prox != 0) {
//printf("\xd");
		auxc = auxc->prox;
	} //c na ultima pos
	while (auxa) {

		auxc->prox = auxa;
//printf("\n%d", auxc->coef);
		auxc = auxc->prox;
		auxa = auxa->prox;
	}
	return c;
}

node *soma(node *c) {
	if (!c)
		return 0;
	else {
		node *aux = c;
		node *aux2 = aux->prox;
		while (aux->prox) {
			if (!aux->prox)
				aux2 = aux;
			else
				aux2 = aux->prox;
			while (aux2->prox) {
				//printf("xd");
				if (aux->pot == aux2->pot) {
					//printf("igual");
					aux2->coef += aux->coef;
					removeD(c, aux);
					aux = aux->prox;
					aux2 = aux2->prox;
				} else {
					aux2 = aux2->prox;
				}
				//printf("");
			}
			aux = aux->prox;
		}
		return c;
	}
}

node *subtrai(node *c) {
	if (!c)
		return 0;
	else {
		node *aux = c;
		node *aux2 = aux->prox;
		while (aux->prox) {
			if (!aux->prox)
				aux2 = aux;
			else
				aux2 = aux->prox;
			while (aux2->prox) {
				//printf("xd");
				if (aux->pot == aux2->pot) {
					//printf("igual");
					aux2->coef -= aux->coef;
					node *ant = aux;
					removeD(c, ant);
					aux = aux->prox;
					aux2 = aux2->prox;
				} else {
					aux2 = aux2->prox;
				}
				//printf("");
			}
			aux = aux->prox;
		}
		return c;
	}
}

////////////////////////////////
node *addpol(node *a, node *b, node *c) {
	if (!a)
		return b;
	if (!b)
		return a;
	else {
		c = insere(a, c);
		c = insere(b, c);
		c = soma(c);
		return c;
	}
}

node *subpol(node *a, node *b, node *c) {
	if (!a)
		return b;
	if (!b)
		return a;
	else {
		c = insere(a, c);
		c = insere(b, c);
		c = subtrai(c);
		return c;
	}
}

//multiplica cada elemento de a por b, e joga em c
node *multipol(node *a, node *b, node *c) {
	if (!a) {
		printf("asdd");
		return 0;
	}
	if (!b) {
		printf("asdd");
		return 0;
	} else {
		node *auxa = a;
		node *auxb = b;
		node *auxc = c;
		while (auxa->prox) {
			auxb = b;
			//printf("\n%d",auxa->coef);
			while (auxb->prox) {
				printf("\n%d", auxa->coef);
				auxc->coef = auxa->coef * auxb->coef;
				auxc->pot = auxa->pot + auxb->pot;
				auxc = auxc->prox;
				auxb = auxb->prox;
			}
			auxa = auxa->prox;
			//printf("pulou para para %dx^%d", auxa->coef, auxa->pot);
		}
		return c;
	}
}


node *divpol(node *a, node *b, node *c) {
	if (!a) {
		printf("asdd");
		return 0;
	}
	if (!b) {
		printf("asdd");
		return 0;
	} else {
		node *auxa = a;
		node *auxb = b;
		node *auxc = c;
		while (auxa->prox) {
			auxb = b;
			//printf("\n%d",auxa->coef);
			while (auxb->prox) {
				printf("\n%d", auxa->coef);
				auxc->coef = auxa->coef / auxb->coef;
				auxc->pot = auxa->pot - auxb->pot;
				auxc = auxc->prox;
				auxb = auxb->prox;
			}
			auxa = auxa->prox;
			//printf("pulou para para %dx^%d", auxa->coef, auxa->pot);
		}
		return c;
	}
}


