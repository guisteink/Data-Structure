#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct tnode {
	int coef, pot;
	struct tnode *prox;
} node;

node *createnode(int coef, int pot);
void print(node *a);
node *addpol(node *a, node *b, node*c);
node *soma(node *c);
node* insere(node *a, node *c);
node *subpol(node *a, node *b, node *c);
node *subtrai(node *c);
void removeD(node *a,node *b);
node *multiplica(node *a, node *b, node *c);
node *multipol(node*a, node *b, node*c);
