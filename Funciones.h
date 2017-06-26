#include<stdio.h>

typedef struct Nodo{
	int h;
	char letra;
	int frec;
	struct Nodo *izq;
	struct Nodo *der;
}Nodo;

typedef struct ColaP{
	int max;
	Nodo *P[256];
}ColaP;

typedef struct Elemento{
	Nodo *nodo;
	struct Elemento *sig;
}Elemento;

typedef struct Cola{
	Elemento *tope;
	Elemento *base;
}Cola;

typedef struct Arbol{
	Nodo *raiz;
}Arbol;

void IniciarNodo(Nodo *n, int frec, char letra);
void IniciarCP(ColaP *C);
void ImprimeArray(ColaP *C);
void ImprimeHeap(ColaP *C);
void IniciarCola(Cola *q);
void Cambiar(ColaP *C, int i, int j);
void ArreglaHeap(ColaP *C, int i);
void CreaHeap(ColaP *C);
Nodo *ExtraeMinHeap(ColaP *C);
void AumentaHeap(ColaP *C, int i, Nodo *n);
void InsertaHeap(ColaP *C, Nodo *n);
void OrdenarHeap(ColaP *C);
void MezclarNodo(Nodo *aux,Nodo *aux1, Nodo *aux2);

void Encolar(Cola *q,Nodo *n);
Nodo* Desencolar(Cola *q);
int EsHoja(Nodo *n);
int Hojas(Nodo *root,int *nLeafs);
void PreOrden(FILE *f,Nodo *r);
Nodo *ConstruirArbol(FILE *f);
void IniciaElemento(Elemento *e,Nodo *n);
void ImprimeArbol(Nodo *r);
