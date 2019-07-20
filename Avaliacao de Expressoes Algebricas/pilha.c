#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

pilhaC* aloca_pilhaC(){
	pilhaC* n = (pilhaC*) malloc(sizeof(pilhaC));
	n->topo = NULL;
	return n;
}

elemento_char* aloca_elemento_char(char valor){
	elemento_char* b = (elemento_char*) malloc(sizeof(elemento_char));
	b->expressao = valor;
	b->prox = NULL;
	return b;
}

pilhaD* aloca_pilhaD(){
	pilhaD* p = (pilhaD*) malloc(sizeof(pilhaD));
	p->topo = NULL;
	return p;
}

elemento_double* aloca_elemento_double(double valor){
	elemento_double* e = (elemento_double*) malloc(sizeof(elemento_double));
	e->valor = valor;
	e->prox = NULL;
	return e;
}

int esta_vazia(pilhaC* Node){
	return (Node->topo == NULL);
}

int esta_vaziadouble(pilhaD* Pilha){
	return (Pilha->topo == NULL);
}

void push(char valor, pilhaC* Node){
	elemento_char* b = aloca_elemento_char(valor);
	b->prox = Node->topo;
	Node->topo = b;
}

void pushdouble(double valor, pilhaD* Pilha){
	elemento_double* e = aloca_elemento_double(valor);
	e->prox = Pilha->topo;
	Pilha->topo = e;
}

void pop(pilhaC* Node){
	if(esta_vazia(Node)){
		printf("\n");
	}
	else{
		elemento_char* temp;
		temp = Node->topo;
		Node->topo = Node->topo->prox;
		free(temp);
	}
}

void popdouble(pilhaD* Pilha){
	if(esta_vaziadouble(Pilha)){
		printf("erro pop double\n");
	}
	else{
		elemento_double* temp;
		temp = Pilha->topo;
		Pilha->topo = Pilha->topo->prox;
		free(temp);
	}
}

char top(pilhaC* Node){
	return Node->topo->expressao;
}

double topdouble(pilhaD* Pilha){
	return Pilha->topo->valor;
}

void libera_pilha(pilhaC* Node){
	elemento_char* b;
	b = Node->topo;
	while(b != NULL){
		Node->topo = b->prox;
		free(b);
		b = Node->topo;
	}
	free(Node);
}

void libera_pilhadouble(pilhaD* Pilha){
	elemento_double* e;
	e = Pilha->topo;
	while(e != NULL){
		Pilha->topo = e->prox;
		free(e);
		e = Pilha->topo;
	}
	free(Pilha);
}

void print(pilhaC* Node){
	elemento_char* b = Node->topo;
	while(b != NULL){
		printf("%d\n", b->expressao);
		b = b->prox;
	}
}

void printdouble(pilhaD* Pilha){
	elemento_double* e = Pilha->topo;
	int i=1;
	if(Pilha->topo == NULL){
		printf("Pilha Vazia!\n\n");
	}
	else{
		while(e != NULL){
			printf("%d. %.2lf\n", i, e->valor);
			e = e->prox;
			i++;
		}
		printf("\n");
	}
}
