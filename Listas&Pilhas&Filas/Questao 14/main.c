#include "polinomio.h"

int main() {
	node *d = createnode(1, 2); //1x^2
	node *e = createnode(2, 3); //2x^3
	node *f = createnode(3, 4); //3x^4
	d->prox = e;
	e->prox = f;
	f->prox=0;

	node *g = createnode(1, 2);
	node *h = createnode(2, 4);
	g->prox = h;
	h->prox = 0;

	node *c =(node*)calloc(1,sizeof(node));
	c = multipol(d,g,c);
	print(c);



	return 0;
}
