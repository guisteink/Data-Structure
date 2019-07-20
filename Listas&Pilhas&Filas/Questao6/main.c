#include<stdio.h>
#include<stdlib.h>
#include"exercicio6.c"

int main(){
     //Declaração de variáveis
    int i=0,x,c1,c2,pos1,pos2;
    Lista *lst1, *lst2;

    lst1=criaLista();
    lst2=criaLista();

    printf("\n----Lista 1----\n");
    insereFim(lst1,3);
    insereFim(lst1,4);
    insereFim(lst1,5);
    insereFim(lst1,6);
    printLista(lst1);

    printf("\n----Lista 2----\n");
    insereFim(lst2,1);
    insereFim(lst2,2);
    insereFim(lst2,3);
    insereFim(lst2,4);
    printLista(lst2);

    printf("\n----Listas modificadas----\n");
    trocaPosicao(lst1,4,lst2,1);

    return 0;
}


