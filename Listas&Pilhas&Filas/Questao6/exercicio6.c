#include<stdio.h>
#include<stdlib.h>
#include"exercicio6.h"


Lista *criaLista(){
    Lista *lst;
    if(!(lst=(Lista *)malloc(sizeof(Lista)))) return NULL;
    lst->inicio=lst->fim=NULL;
    return lst;
}

No *criaNo(int x){
    No *ptr;
    if(!(ptr=(No *)malloc(sizeof(No)))) return NULL;
    ptr->prox=ptr->ant=NULL;
    ptr->ch=x;
    return ptr;
}

void insereInicio(Lista *lst, int x){
    No *ptr;
    if(!lst || !(ptr=criaNo(x))) return;
    ptr->ch=x;
    ptr->prox=lst->inicio;
    ptr->ant=NULL;
    if(lst->inicio==NULL) {lst->inicio=lst->fim=ptr; return;}
    lst->inicio->ant=ptr;
    lst->inicio=ptr;

}

void insereFim(Lista *lst, int x){
    No *ptr, *aux;
    if(!lst || !(ptr=criaNo(x))) return;
    ptr->ch=x;
    if(lst->inicio==NULL)
    {
    	lst->inicio=lst->fim=ptr;
    }
    else
	{
		aux=lst->fim;
		aux->prox=ptr;
		ptr->ant=aux;
		lst->fim=ptr;
	}
}

int buscaChave(Lista *lst, int x){
    No *ptr;
    int i;
    if(!lst || lst->inicio==NULL) return 0;
    for(i=1,ptr=lst->inicio;ptr->ch!=x && ptr->prox!=NULL ;ptr=ptr->prox,i++);
    if(ptr->prox==NULL) return 0;
    return i;
}

No *removeElemento(Lista *lst, int x)
{
	No *ptr;
	int i;

	if (!lst || lst->inicio==NULL){
		printf("\nImpossivel retirar elemento!\n");
		return NULL;
	}
	ptr=lst->inicio;
	for(i=1; i<x;i++, ptr=ptr->prox);
	if(ptr->ant!=NULL) ptr->ant->prox=ptr->prox;
	else lst->inicio=ptr->prox;
	if(ptr->prox!=NULL) ptr->prox->ant=ptr->ant;
	return ptr;
}


void inserePos(Lista *lst,No *ch, int pos){
    No *ptr;
    int i;
    if(!lst)return;
    for(i=1,ptr=lst->inicio;i<pos;i++,ptr=ptr->prox);
    if(i==1){
       /* ptr->ant=ch;
        ch->prox=ptr;
        lst->inicio=ch;*/
        insereInicio(lst,ch->ch);
    }
    else if (ptr->prox==NULL){
        /*lst->fim->prox=ch;
        ch->ant=lst->fim;
        lst->fim=ch;*/
        insereFim(lst,ch->ch);
    }
    else{
       ptr->ant->prox=ch;
       ch->ant=ptr->ant;
       ptr->ant=ch;
       ch->prox=ptr;
    }
}


//Imprimir lista
void printLista(Lista *lst) {

    No *ptr;

    if(lst->inicio==NULL) return;
    printf("\n[ ");
    ptr=lst->inicio;

    //inicia do primeiro elemento da Lista Dupla

    while(ptr != NULL)
    {
      printf("(%d) ",ptr->ch);
      ptr = ptr->prox;
    }
	printf(" ]");

}

void trocaPosicao(Lista *lst1,int c1,Lista *lst2,int c2){
    int pos1, pos2;
   pos1=buscaChave(lst1,c1);
    pos2=buscaChave(lst2,c2);


    inserePos(lst2,removeElemento(lst1,buscaChave(lst1,c1)),pos2);
    inserePos(lst1,removeElemento(lst2,buscaChave(lst2,c2)),pos1);



    printLista(lst1);
    printLista(lst2);
}




