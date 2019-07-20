#ifndef __PILHA_H__
#define __PILHA_H__


typedef struct tElemento_char{
	char expressao;
	struct tElemento_char* prox;
} elemento_char;

typedef struct Node{
	elemento_char* topo;
} pilhaC;

typedef struct tElemento_double{
	double valor;
	struct tElemento_double* prox;
} elemento_double;

typedef struct Pilha{
	elemento_double* topo;
} pilhaD;

pilhaC* aloca_pilhaC();
elemento_char* aloca_elemento_char(char valor);
pilhaD* aloca_pilhaD();
elemento_double* aloca_elemento_double(double valor);
int esta_vazia(pilhaC* Node);
int esta_vaziadouble(pilhaD* Pilha);
void push(char valor, pilhaC* Node);
void pushdouble(double valor, pilhaD* Pilha);
void pop(pilhaC* Node);
void popdouble(pilhaD* Pilha);
char top(pilhaC* Node);
double topdouble(pilhaD* Pilha);
void libera_pilha(pilhaC* Node);
void libera_pilhadouble(pilhaD* Pilha);
void print(pilhaC* Node);
void printdouble(pilhaD* Pilha);

#endif
