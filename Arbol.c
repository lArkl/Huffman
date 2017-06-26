#include "Estructuras.h"
#include<stdlib.h>

void IniciaElemento(Elemento *e,Nodo *n){
	e->nodo = n;
	e->sig = NULL;
}

void IniciarCola(Cola *q){
	q->tope = NULL;
	q->base = NULL;
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

int EsHoja(Nodo *n){
    return !(n->izq) && !(n->der) ;
}

int Hojas(Nodo *root,int *nLeafs){
	Cola q;
	IniciarCola(&q);
	Encolar(&q,root);
	int number=0;
	while(q.base !=NULL){
		Nodo* n = Desencolar(&q);
		if(n->izq!=NULL){
			Encolar(&q,n->izq);
		}	
		if(n->der!=NULL){
			Encolar(&q,n->der);
		}if(EsHoja(n)){
			nLeafs[number]=n->letra;
			number++;		
		}
	}return number;
}

void PreOrden(FILE *f,Nodo *r){
	if(r!=NULL){
		fprintf(f, "%c",r->letra);
		PreOrden(f,r->izq);
		PreOrden(f,r->der);
	}else
		fprintf(f, "#");
}

Nodo *ConstruirArbol(FILE *f){
	char c = fgetc(f);
	if(c=='#')
		return NULL;
	Nodo *r = calloc(1,sizeof(Nodo));
	IniciarNodo(r, 0, c);
	r->izq = ConstruirArbol(f);
	r->der = ConstruirArbol(f);
	return r;
}

void ImprimeArbol(Nodo *r){
	Cola q;
	IniciarCola(&q);
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

