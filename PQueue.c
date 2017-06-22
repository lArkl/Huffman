#include "PQueue.h"
#include<stdlib.h>
#include<stdio.h>

void IniciarNodo(Nodo *n, int frec, char letra){
	n->h=0;
	n->frec = frec;
	n->letra=letra;
	n->izq=NULL;
	n->der=NULL;
}

void IniciarCP(ColaP *C){
	C->max=0;
	int i;
	for(i=0;i<256;i++)
		C->P[i] = NULL;
}


void Cambiar(ColaP *C, int i, int j){
	Nodo *aux = C->P[i];
	C->P[i] = C->P[j];
	C->P[j] = aux;
}

void ImprimeArray(ColaP *C){
	int i;
	for(i=0;i<C->max;i++)
		printf("%d\t",C->P[i]->frec);
	printf("\n");
	for(i=0;i<C->max;i++)
		printf("%c\t",C->P[i]->letra);
	printf("\n");
}

void ImprimeHeap(ColaP *C){
	int i,cont=1;
	printf("===================\n");
	for(i=0;i<C->max;i++){
		if(i%2==1)
			printf("/%d\t",C->P[i]->frec);
		else
			printf("%d\\ \t",C->P[i]->frec);
		if(cont==i+1){
			cont=2*cont+1;
			printf("\n");
		}
	}printf("\n");
}


void ArreglaHeap(ColaP *C, int i){
	int min=i;
	if(2*i+1<C->max && C->P[2*i+1]->frec!=0 && C->P[2*i+1]->frec<C->P[i]->frec)
		min = 2*i+1;
	if(2*i+2<C->max && C->P[2*i+2]->frec!=0 && C->P[2*i+2]->frec < C->P[min]->frec)
		min = 2*i+2;
	if(min!=i){
		Cambiar(C,i,min);
		ArreglaHeap(C,min);
	}
}

void CreaHeap(ColaP *C){
	int i;
	for(i=C->max/2;i>=0;i--)
		ArreglaHeap(C,i);
}

Nodo *ExtraeMinHeap(ColaP *C){
	Nodo *min = C->P[0];
	C->P[0] = C->P[C->max-1];
	C->max = C->max-1;
	ArreglaHeap(C,0);
	return min;
}

void AumentaHeap(ColaP *C, int i, Nodo *n){
	C->P[i] = n;
	while(i>0 && C->P[(i-1)/2]->frec > C->P[i]->frec){
		Cambiar(C,i,(i-1)/2);
		i=(i-1)/2;
	}
}

void InsertaHeap(ColaP *C, Nodo *n){
	C->max = C->max+1;
	//H[*max-1].frec = 1000;
	AumentaHeap(C,C->max-1,n);
}

void OrdenarHeap(ColaP *C){
	int i, max=C->max;
	Nodo *G[max];
	CreaHeap(C);
	for(i=0;i<max;i++){
		G[i] = ExtraeMinHeap(C);
	}
	for(i=0;i<max;i++){
		C->P[i]=G[i];
	}C->max=max;
}

void IniciaElemento(Elemento *e,Nodo *n){
	e->nodo = n;
	e->sig = NULL;
}

void Encolar(Cola *q,Nodo *n){
	Elemento *e = calloc(1,sizeof(Elemento));
	IniciaElemento(e,n);
	if(q->base==NULL){
		q->tope = e;
		q->base = e;
	}else{
		q->tope->sig = e;
		q->tope = e;
	}
}

Nodo* Desencolar(Cola *q){
	if(q->base!=NULL){
		Nodo* n = q->base->nodo;
		Elemento *aux = q->base;
		q->base = aux->sig;
		free(aux);
		return n;
	}else
		return NULL;
}

int Hojas(Nodo *root,int *nLeafs){
	Cola q;
	q.tope = NULL;
	q.base = NULL;
	Encolar(&q,root);
	int number=0;
	while(q.base !=NULL){
		Nodo* n = Desencolar(&q);
		char child=0;
		if(n->izq!=NULL){
			Encolar(&q,n->izq);
			child=1;
		}	
		if(n->der!=NULL){
			Encolar(&q,n->der);
			child=1;
		}if(child==0){
			nLeafs[number]=n->letra;
			number++;		
		}
	}return number;
}

void ImprimeArbol(Nodo *r){
	Cola q;
	q.tope = NULL;
	q.base = NULL;
	Encolar(&q,r);
	Nodo *n;
	while(q.base !=NULL && q.tope!=NULL){
		n = Desencolar(&q);
		if(n->izq!=NULL)
			Encolar(&q,n->izq);
		if(n->der!=NULL){
			Encolar(&q,n->der);
		}
		printf("%d %c\n",n->frec,n->letra);
	}
}

