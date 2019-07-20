/*
 * main.c
 *
 *  Created on: 11 de jun de 2019
 *      Author: Guilherme Stein Kuhn
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define MAXSIZEHT 11 //MAXIMO DE POSIÇOES NA HASHTABLE
#define MAXSIZEW 23 //MAXIMO DE LETRAS NA STRING

/**
 * Estruturas da hash table
 */
typedef struct tnode {
	char *info;
	struct tnode *prox;
} Node;

typedef struct {
	int size;
	struct tnode *first;
} Hash;

/* Funções da hash table

 /*
 * Função pra inicializar uma hash table;; com todas posições dela em null
 * Caso o tamanho desejado seja maior que o permitido, ele chama novamente com o maior possivel
 */
void initializeHT(Hash hashtable[], int sizeht) {
	if (sizeht > MAXSIZEHT)
		return initializeHT(hashtable, MAXSIZEHT);
	for (int i = 0; i < sizeht; i++) {
		hashtable[i].first = 0;
	}
	hashtable->size = sizeht;
	return;
}

//converte o tempo em milisegundos
double getTempo(clock_t ini, clock_t fim) {
	clock_t Ticks[2];
	double Tempo = -((Ticks[1] - Ticks[0]) * 1000.00000 / CLOCKS_PER_SEC);
	return Tempo;
}

/**
 * Função pra criar um node de informação(char).
 */
Node *createNodeHT(char *inf) {
	Node *ptr;
	if ((ptr = (Node *) malloc(sizeof(Node)))) {
		ptr->info = (char *) malloc(sizeof(char) * (strlen(inf) + 1));
		strcpy(ptr->info, inf);
		ptr->prox = NULL;
		return ptr;
	}
	return NULL;
}

/**
 * Função que calcula o hash de uma informacao
 * A funcao soma os valores ASC de cada letra numa string, e divide pelo valor do tamanho da hashtable.
 * fmod retorna o resto da divisao, que sera o indice do vetor hash onde a string sera adicionada
 */
int functionHT(char *inf, int sizeht) {
	int sum = 0;
	for (int i = 0; i < strlen(inf); i++)
		sum += inf[i];
	return fmod(sum, sizeht);
}

/* funcao: void printHT(Node *hashtable[])
 *  acao:        funcao que imprime o conteudo de uma tabela hash
 *  entrada:     tabela hash
 *  saida:       void
 *  suposicoes:  nenhuma
 */
void printHT(Hash hashtable[], int sizeht) {
	int i;
	for (i = 0; i < sizeht; i++) {
		printf("\nIndice: %d -> ", i);
		//getchar();
		Node *ptr = hashtable[i].first;
		while (ptr) {
			printf("\t%s", ptr->info);
			ptr = ptr->prox;
		}
		printf("\n\n");
		//getchar();
	}

}

/* FUNCAO A SER MODIFICADA PRA INSERIR ORDENADAMENTE DE ACORDO COM O STRCMP, QUE COMPARA LEXICOGRAFICAMENTE DUAS PALAVRAS
 * retorno 0, diz que as strings sao iguais;
 * retorno <0, diz que a primeira string é menor;
 * retorno >0, diz que a primeira string é maior.
 */
void insertHT(Hash hashtable[], int sizeht, char *word) {
	//apontamentos necessarios pra fazer o insert
	int pos = functionHT(word, sizeht);
	Node *ptr = createNodeHT(word), *ptraux, *pptraux;
	pptraux = hashtable[pos].first;

	//caso nao exista nenhum elemento no subconjunto
	if (!pptraux) {
		ptr->prox = hashtable[pos].first;
		hashtable[pos].first = ptr;
		hashtable[pos].size = 1;
	}

	//existem pelo menos 1 elemento
	else {
		//aponta o ptraux pro segundo elemento
		ptraux = pptraux->prox;
		//percorre ate achar uma palavra menor que a ser inserida, e enquanto ptraux exista
		while (ptraux && (strcmp(ptraux->info, ptr->info)) < 0) {
			pptraux = ptraux;
			ptraux = ptraux->prox;
		}
		//aponta o anterior e o sucessor, e coloca o ptr entre eles.
		pptraux->prox = ptr;
		ptr->prox = ptraux;
		hashtable[pos].size++;
	}
	return;
}

Node *searchbinaryinlist(Node *first, char *chave, int ini, int fim) {
	Node *ptr = first;
	int i, meio = (ini + fim) / 2;

	if (!first || !chave)
		return 0;

	for (i = 1; i < meio; i++)
		ptr = ptr->prox;
	if (strcmp(ptr->info, chave) == 0)
		return ptr;
	else if (strcmp(ptr->info, chave) > 0)
		return searchbinaryinlist(first, chave, ini, meio - 1);
	else if (strcmp(ptr->info, chave) < 0)
		return searchbinaryinlist(first, chave, meio + 1, fim);

}

/**
 * FUNCAO QUE BUSCA BINARIAMENTE
 */
void searchHT(Hash hashtable[], int sizeht, char *word) {
	clock_t Ticks[2];
	int pos = functionHT(word, sizeht);
	if (!hashtable[pos].first)
		return;

	Node *ptr = hashtable[pos].first;
	int sizesub = hashtable[pos].size;
	Ticks[0] = clock(); //tempo de entrada

	Node *ptraux = searchbinaryinlist(ptr, word, 1, sizesub); //faz a busca binaria
	Ticks[1] = clock();
	double Tempo = getTempo(Ticks[0], Ticks[1]);

	if (ptraux) {
		printf("\nPalavra contida na lista!");
		printf("\nTempo gasto: %g ms.", Tempo);
		return;
	} else { //caso nao tenha encontrado
		printf("\nPalavra NAO contida na lista!");
		printf("\nTempo gasto: %g ms.", Tempo);
		return;
	}

}

/* FUNCAO QUE DELETA UTILIZANDO A BUSCA BINARIA
 */
void deleteHT(Hash hashtable[], int sizeht, char *word) {
	int pos = functionHT(word, sizeht), sizesub = hashtable[pos].size;
	Node *ptr = hashtable[pos].first, *pptr = searchbinaryinlist(ptr, word, 0,
			sizesub), *pptraux = ptr->prox;

	if (!hashtable || !ptr || !word || !pptr)
		return;

	if (sizesub == 1) {
		hashtable[pos].size = 0;
		hashtable[pos].first = 0;
		free(pptr->info);
		free(pptr);
		return;
	}

	if (sizesub == 2) {
		hashtable[pos].size--;
		if (pptr == ptr) {
			hashtable[pos].first = pptraux;
			free(pptr->info);
			free(pptr);
			return;
		}
		if (pptr == pptraux) {
			ptr->prox = 0;
			free(pptr->info);
			free(pptr);
			return;

		}
	}

	else {
		if (pptr == ptr) {
			hashtable[pos].size--;
			hashtable[pos].first = pptraux;
			ptr = ptr->prox;
			free(pptr->info);
			free(pptr);
			return;
		}

		if (pptr == pptraux) {
			hashtable[pos].size--;
			ptr->prox = pptraux->prox;
			free(pptr->info);
			free(pptr);
			return;

		}

		while (pptraux->prox != pptr) {
			printf("\nteste1.5");
			pptraux = pptraux->prox;
		}
		pptraux->prox = pptr->prox;
		hashtable[pos].size--;
		free(pptr->info);
		free(pptr);
		return;
	}
}

/**
 * leitura de arquivo
 */
int loadDic(Hash hashtable[]) {
	FILE *fp = fopen("palavras2.txt", "a+");
	if (!fp) {
		printf("\nERRO AO ABRIR O ARQUIVO!\n");
		system("pause");
		return -1;
	}

	int pos, x = 0;
	char aux[MAXSIZEW];
	while (!feof(fp)) {
		fgets(aux, MAXSIZEW, fp);
		strtok(aux, "\n");
		pos = functionHT(aux, MAXSIZEHT);
		insertHT(hashtable, MAXSIZEHT, aux);
		x++;
	}
	return 1;
}

/**
 * PROGRAMA PRINCIPAL
 */
int main(int argc, char **argv) {

	Hash hashtable[MAXSIZEHT];
	char word[MAXSIZEW], worddelete[MAXSIZEW];
	int pos, posd;

	initializeHT(hashtable, MAXSIZEHT);
	loadDic(hashtable);

	printHT(hashtable, MAXSIZEHT);
	printf("\n\n");

	printf("\nDigite a palavra a ser buscada: ");
	fflush(stdin);
	gets(word);
	pos = functionHT(word, MAXSIZEHT);
	printf("\nPalavra: %s Indice: %d", word, pos);
	searchHT(hashtable, MAXSIZEHT, word);
	printf("\nDigite a palavra a ser deletada: ");
	fflush(stdin);
	gets(worddelete);
	posd = functionHT(worddelete, MAXSIZEHT);
	printf("\nPalavra: %s Indice: %d", worddelete, posd);
	deleteHT(hashtable, MAXSIZEHT, worddelete);

	printf("\n\n");
	printHT(hashtable, MAXSIZEHT);

	return 1;
}

