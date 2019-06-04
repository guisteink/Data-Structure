#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//SO UTILIZEI USAR TUDO DENTRO DE UMA MAIN TESTE PQ ESTAVA COM MTO CONFLITOS DE TIPOS, *TYPEDEF DAS ESTRUTURAS

//---------------------------------ESTRUTURAS---------------------------------

//--------------------------------- INFORMACAO ------------------------------

typedef struct {
	int chave;
} info;

//---------------------------- ARVORE BINARIA DE BUSCA ----------------------
typedef struct bt {
	struct bt *esq, *dir;
	info *info;
} bst;

//------------------------------- FUNCOES -----------------------------------------

info* createinfo(int x) {
	info *data = (info*) calloc(1, sizeof(info));
	if (!data)
		return 0;
	data->chave = x;
	return data;
}

bst *createbst(info *info) {
	if (!info)
		return 0;
	bst *novo = (bst*) calloc(1, sizeof(bst));
	if (!novo)
		return 0;
	novo->info = info;
	return novo;
}

void printbst(bst *bst) {
	if (!bst)
		return;
	printbst(bst->esq);
	printf("\t%d", bst->info->chave);
	printbst(bst->dir);
	return;
}

//1) busca em uma bst
bst *buscabst(bst *root, info *info) {
	if (root->info->chave == info->chave) {
		return root;
	}
	if (root->info->chave > info->chave)
		return buscabst(root->esq, info);
	else
		return buscabst(root->dir, info);
}

//2)insert na bst
bst *insertbst(bst *root, info *info) {
	bst *novo = createbst(info);
	if (!root) {
		root = novo;
		return novo;
	}
	if (root->info->chave > info->chave)
		root->esq = insertbst(root->esq, info);
	if (root->info->chave < info->chave)
		root->dir = insertbst(root->dir, info);
	else
		return 0; //NAO PERMITE QUE INSIRA ELEMENTOS IGUAIS, POIS UMA ARVORE EM SUA METODOLOGIA NAO PERMITE ISSO
}

//3)retorna o maior elemento dentro de uma arvore
bst *maiorbst(bst *root) {
	if (!root)
		return 0;
	bst *temp = root;
	while (temp->dir)
		temp = temp->dir;
	return temp;
}

//4)retorna o menor elemento dentro de uma arvore
bst *menorbst(bst *root) {
	if (!root)
		return 0;
	bst *temp = root;
	while (temp->esq)
		temp = temp->esq;
	return temp;
}

int isinbt(bst *root, info *i) {
	if (root->info == i)
		return 1;
	else {
		if (isinbt(root->esq, i) || isinbt(root->dir, i))
			return 1;
		else
			return 0;
	}
}

//5)deleta um node da lista
bst *deletebst(bst *bst, info *info) {
	if (!bst)
		return bst;
	if (info->chave < bst->info->chave)
		bst->esq = delete2(bst->esq, info);
	else if (info->chave > bst->info->chave)
		bst->dir = delete2(bst->dir, info);
	else {
		struct bt *temp;
		if (!bst->esq) {
			temp = bst->dir;
			free(bst->info);
			free(bst);
			return temp;
		} else if (!bst->dir) {
			temp = bst->esq;
			free(bst->info);
			free(bst);
			return temp;
		}
		temp = menorbst(bst->dir);
		bst->info = temp->info;
		bst->dir = delete2(bst->dir, temp->info);
	}
	return bst;

}

//********************************************************************************************
//-------------------------------- PROGRAMA PRINCIPAL ----------------------------------------
//********************************************************************************************
int main() {

//------------------------------------------INFORMACOES-------------------------------------------
	info *d1 = createinfo(1);
	info *d2 = createinfo(2);
	info *d3 = createinfo(3);
	info *d4 = createinfo(4);
	info *d5 = createinfo(5);

//-----------------------------------------NODES DE ARVORE-----------------------------------------
	bst *tree = createbst(d1);
	tree = insertbst(tree, d2);
	tree = insertbst(tree, d3);
	tree = insertbst(tree, d4);
	tree = insertbst(tree, d5);
	tree = delete2(tree, d3);

	printf("\n************************\narvore binaria de busca: ");
	printbst(tree);

	printf("\nmaior: %d", maiorbst(tree)->info->chave);
	printf("\nmenor: %d", menorbst(tree)->info->chave);

	return 0;
}
