#include <stdio.h>
#include <stdlib.h>
#include "infixposfix.h"
#include "pilha.h"

int main() {
	int op;
	printf("\n \t [Infixa] -> [Posfixa] ");
	printf("\nDeseja resolver algebricamente? (1), ou numericamente? (2)\n");
	scanf("%d", &op);
	if (op == 1) {
		printf("FORMATO ALGEBRICO.\n");
		char infixa[1000], posfixa[1000];
		printf("Digite a expressao infixa. ex: a+b-c*(d/e) \nObs: escreva sem espacos\n->");
		scanf(" %[^\n]s ", infixa);
		infixToPosfix(infixa,posfixa);
		printf("Posfixa: %s\n",posfixa);
	} else if (op == 2) {
		printf("\nFORMATO NUMERICO.\n");
		evaluatePosfix();
	}
	return 1;

}
