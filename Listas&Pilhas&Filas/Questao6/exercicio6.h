#ifndef __EXERCICIO6_H__
#define __EXERCICIO6_H__


typedef struct no{
    int ch;
    struct no *prox, *ant;
}No;

typedef struct{
    No *inicio, *fim;
}Lista;



Lista *criaLista();
No *criaNo(int x);
void insereInicio(Lista *lst, int x);
void insereFim(Lista *lst, int x);
int buscaChave(Lista *lst, int x);
No *removeElemento(Lista *lst, int x);
void inserePos(Lista *lst,No *ch, int pos);
void printLista(Lista *lst);
void trocaPosicao(Lista *lst1,int c1,Lista *lst2,int c2);
#endif // __EXERCICIO6_H__
