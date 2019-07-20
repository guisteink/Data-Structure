#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "infixposfix.h"
#include "pilha.h"

//pra identificar um operando na expressao algebrica
int operando(char x) {
	if ((x >= 48 && x <= 57) || (x >= 65 && x <= 90) || (x >= 97 && x <= 121)
			|| x == ' ' || x == '.' || x == ',')
		return 1;
	return 0;
}

//para identificar um operador na expressao algebrica
int operador(char x) {
	if (x == '+' || x == '-' || x == '*' || x == '/')
		return 1;
	return 0;
}

//para dar getPrioridade a certa operacao na expressao algebrica
int getPrioridade(char x) {
	if (x == '*' || x == '/')
		return 2; //maior prioridade
	else if (x == '+' || x == '-')
		return 1; //prioridade padrao
	return 0; //zero prioridade
}

//recebe uma expressao em char e converte pra double
double converte(char* infixa) {
	int i, j, q = 0;
	double result = 0;
	for (i = 0; i < strlen(infixa); i++) {
		if (infixa[i] == ',' || infixa[i] == '.') {
			q = i;
		}
	}
	if (q) {
		for (i = (q - 1), j = 0; j < q; i--, j++) {
			result += (infixa[j] - '0') * pow(10, i);
		}
		for (i = 0, j = (q + 1); j < strlen(infixa); i++, j++) {
			result += (infixa[j] - '0') / pow(10, i + 1);
		}
	} else {
		for (i = (strlen(infixa) - 1), j = 0; j < strlen(infixa); i--, j++) {
			result += (infixa[j] - '0') * pow(10, i);
		}
	}
	return result;
}

//recebe uma equação posfixa e resolve atraves do armazenamento em uma pilha
double solve(char* posfixa) {
	pilhaD* pilha = aloca_pilhaD(); //aloca a pilha aux de double
	char aux[1000]; //declara uma string auxiliar
	int i, j, k = 0; //contadores para percorrer a pilha, a string posfixa e a string auxiliar
	double total, aux1, aux2, resultado;

	for (i = 0; i < strlen(posfixa); i++) { //i percorre a posfixa
		if (operando(posfixa[i]) && posfixa[i] != ' ') { //verifica se a posicao i é um operando e nao é espaço
			for (j = i; posfixa[j] != ' '; j++) { //j recebe a posiçao i e verifica se nao é espaço
				aux[k] = posfixa[j]; //joga o operando pra dentro da string auxiliar
				k++; //percorre o contador da string auxiliar
			}
			aux[k] = '\0';
			i = j; //atualiza qndo terminar
			k = 0; //atualiza qndo terminar
			pushdouble(converte(aux), pilha); //empilha na pilha double, atraves da conversao
		} else if (operador(posfixa[i])) { //se na posiçao i existir um operador
			aux1 = topdouble(pilha); //o auxiliar1 recebe o topo da pilha
			popdouble(pilha); //logo apos, retira o topo da pilha
			aux2 = topdouble(pilha); //e o auxiliar2 recebe o segundo do topo
			popdouble(pilha); //e em seguida o retira, pra realizar as operacoes abaixo
			//e entao trata os casos de operadores com suas devidas prioridades e realiza as operaçoes
			if (posfixa[i] == '*') {
				total = aux1 * aux2;
			} else if (posfixa[i] == '/') {
				total = aux2 / aux1;
			} else if (posfixa[i] == '+') {
				total = aux1 + aux2;
			} else if (posfixa[i] == '-') {
				total = aux2 - aux1;
			}
			pushdouble(total, pilha);			//empilha
		}
	}
	resultado = topdouble(pilha);
	popdouble(pilha);
	libera_pilhadouble(pilha);
	return resultado;
}

//transformar de infixa para posfixa
void infixToPosfix(char *infixa, char *posfixa) {
	pilhaC* pilha = aloca_pilhaC();
	int i, j = 0;
	for (i = 0; i < strlen(infixa); i++) {
		if (operando(infixa[i])) { //se a posicao da infixa.i for um operando ele coloca na posfixa.j e atualiza j
			posfixa[j] = infixa[i];
			j++;
		} else if (operador(infixa[i])) { //se for um operador e de acordo com a prioridade ele desempilha, ou empilha o que esta no topo
			while (!esta_vazia(pilha)
					&& (getPrioridade(top(pilha)) >= getPrioridade(infixa[i]))) {
				posfixa[j] = top(pilha);
				pop(pilha);
				j++;
			}
			push(infixa[i], pilha);
		} else if (infixa[i] == '(') { //começo
			push(infixa[i], pilha);
		} else if (infixa[i] == ')') { //fim
			while (top(pilha) != '(') { //enquanto o topo nao é '(' ele empilha j no topo e atualiza j.
				posfixa[j] = top(pilha);
				pop(pilha);
				j++;
			}
			if (top(pilha) == '(') {
				pop(pilha);
			}
		}
	}
	while (!esta_vazia(pilha)) {
		posfixa[j] = top(pilha);
		pop(pilha);
		j++;
	}
	posfixa[j] = '\0';
	libera_pilha(pilha);
}

int verificaInicio(char* expressao) {
	pilhaC* pilha = aloca_pilhaC();
	int i, flag = 1;
	for (i = 0; i < strlen(expressao); i++) {
		switch (expressao[i]) {
		case '(':
			push(expressao[i], pilha);
			break;
		case '[':
			push(expressao[i], pilha);
			break;
		case '{':
			push(expressao[i], pilha);
			break;
		case ')':
			if (esta_vazia(pilha)) {
				printf("erro!\n");
				libera_pilha(pilha);
			} else {
				if (top(pilha) != '(') {
					flag = 0;
				}
				pop(pilha);
			}
			break;
		case ']':
			if (esta_vazia(pilha)) {
				printf("erro!\n");
				libera_pilha(pilha);
			} else {
				if (top(pilha) != '[') {
					flag = 0;
				}
				pop(pilha);
			}
			break;
		case '}':
			if (esta_vazia(pilha)) {
				printf("erro!\n");
				libera_pilha(pilha);
			} else {
				if (top(pilha) != '{') {
					flag = 0;
				}
				pop(pilha);
			}
			break;
		}
	}
	if (!esta_vazia(pilha) || flag == 0) {
		printf("erro.\n");
		libera_pilha(pilha);
		return 0;
	} else {
		libera_pilha(pilha);
		return 1;
	}
}

//verifica se o char é o começo da funçao algebrica
int inicializador(char op) {
	if (op == '(' || op == '[' || op == '{')
		return 1;
	return 0;
}

//verifica se o char é o fim da função algebrica
int finalizador(char op) {
	if (op == ')' || op == ']' || op == '}')
		return 1;
	return 0;
}

//recebe um caracter, e define seu tipo, operando( "ABCD" ) operador( "+-*/" ) inicializador( "(" ) finalizador ( ")" )
int definetipo(char op) {
	if (inicializador(op) || finalizador(op))
		return -1;
	else if (operando(op))
		return 0;
	else
		return 1;
}

//verifica o tamanho da pilha
int quantidade(pilhaD* Pilha) {
	int qtd = 0;
	elemento_double* e = Pilha->topo;
	while (e != NULL) {
		qtd++;
		e = e->prox;
	}
	return qtd;
}

void evaluatePosfix() {
	char infixa[1000], posfixa[1000];
	printf("Digite a expressao infixa. ex: 1+2-3*(4/5)\nObs: escreva sem espacos\n->");
	scanf(" %[^\n]s ", infixa);
	if (verificaInicio(infixa)){
		infixToPosfix(infixa, posfixa);
		printf("Posfixa = %s\n", posfixa);
	} else {
		strcat(infixa, " ");
		if (verificaInicio(infixa)) {
			infixToPosfix(infixa, posfixa);
			printf("Posfixa = %s\n", posfixa);
		}
	}
}
