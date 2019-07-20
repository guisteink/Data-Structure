#ifndef __INFIXPOSFIX_H__
#define __INFIXPOSFIX_H__
#include "pilha.h"

int operando(char x);

int operador(char x);

int getPrioridade(char x);

double converte (char* infixa);

double solve(char* posfixa);

void infixToPosfix(char *infixa, char *posfixa); //infixtopostfix

int verificaInicio(char* infixa);

int inicializador(char op);

int finalizador(char op);

int definetipo(char op);

int quantidade(pilhaD* Pilha);

void evaluatePosfix();
//void evaluatePostFix(char *infixa, char *posfixa);

#endif
