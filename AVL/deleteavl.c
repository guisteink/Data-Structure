#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
//FUNÇÃO DELETE PARA ÁRVORE BALANCEADA
AVL *deleteAVL(AVL *avl, Info *inf) {
	int growup = 0;
	return auxDeleteAVL(avl, inf, &growup);
}

//AUXILIAR PARA FUNÇÃO deleteAVL
AVL *auxDeleteAVL(AVL *avl, Info *inf, int *growup) {
	AVL *point;
	AVL *aux;
	int bal;

	if (!avl) {
		return avl;
	}

	else if (inf->value < avl->info->value) {
		avl->left = auxDeleteAVL(avl->left, inf, growup);

		if (*growup) {
			switch (avl->balance) {
			case +1:
				avl->balance = 0;
				break;
			case 0:
				avl->balance = -1;
				growup = 0;
				break;
			case -1:
				aux = avl->right;
				bal = aux->balance;
				if (bal <= 0)
					RR_RotationAVL(&avl);
				else
					RL_RotationAVL(&avl);
			}
		}
	} else if (inf->value > avl->info->value) {
		avl->right = auxDeleteAVL(avl->right, inf, growup);
		if (*growup) {
			switch (avl->balance) {
			case -1:
				avl->balance = 0;
				break;

			case 0:
				avl->balance = +1;
				*growup = 0;
				break;

			case +1:
				aux = avl->left;
				bal = aux->balance;
				if (bal >= 0)
					LL_RotationAVL(&avl);
				else
					LR_RotationAVL(&avl);
			}

		}
	} else {
		point = avl;

		if (point->right == NULL) {
			avl = point->left;
			*growup = 1;
		} else if (point->left == NULL) {
			avl = point->right;
			*growup = 1;
		} else {
			//nó com dois filhos
			//REMOVER IGUAL A BST
			struct avlno *aux = findLargestElementAVL(leftAVL(avl));
			avl->info->value = aux->info->value;
			//printf("\n%d",avl->info->value);
			Info *inf = aux->info;
			point = NULL;
			avl->left = auxDeleteAVL(leftAVL(avl), inf, growup);
		}
		free(point);
	}
	return avl;
}
