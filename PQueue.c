#include "PQueue.h"
#include<stdlib.h>
#include<stdio.h>

void swap(Node *H, int i, int j){
	Node aux = H[i];
	H[i] = H[j];
	H[j] = aux;
}

void Imprime_Array(int max, Node *H){
	int i;
	for(i=0;i<max;i++)
		printf("%d\t",H[i].frec);
	printf("\n");
	for(i=0;i<max;i++)
		printf("%c\t",H[i].letra);
	printf("\n");
}

void Imprime_Heap(int max, Node *H){
	int i,cont=1;
	printf("===================\n");
	for(i=0;i<max;i++){
		if(i%2==1)
			printf("/%d\t",H[i].frec);
		else
			printf("%d\\ \t",H[i].frec);
		if(cont==i+1){
			cont=2*cont+1;
			printf("\n");
		}
	}printf("\n");
}


void Arregla_Heap(int max, Node *H, int i){
	int min=i;
	if(2*i+1<max && H[2*i+1].frec!=0 && H[2*i+1].frec<H[i].frec)
		min = 2*i+1;
	if(2*i+2<max && H[2*i+2].frec!=0 && H[2*i+2].frec<H[min].frec)
		min = 2*i+2;
	if(min!=i){
		swap(H,i,min);
		Arregla_Heap(max,H,min);
	}
}

void Crea_Heap(int max,Node *H){
	int i;
	for(i=max/2;i>=0;i--)
		Arregla_Heap(max,H,i);
}

Node Extrae_MinHeap(int *max, Node *H){
	Node min = H[0];
	H[0] = H[*max-1];
	*max = *max-1;
	Arregla_Heap(*max,H,0);
	return min;
}

void Aumenta_Heap(Node *H, int i, Node n){
	H[i]=n;
	while(i>0 && H[(i-1)/2].frec > H[i].frec){
		swap(H,i,(i-1)/2);
		i=(i-1)/2;
	}
}

void Inserta_Heap(int *max, Node *H, Node n){
	*max = *max+1;
	//H[*max-1].frec = 1000;
	Aumenta_Heap(H,*max-1,n);
}

void Heap_Sort(int max, Node *H){
	int i, cont=max;
	Node G[max];
	Crea_Heap(max,H);
	for(i=0;i<max;i++){
		G[i] = Extrae_MinHeap(&cont,H);
	}
	for(i=0;i<max;i++)
		H[i]=G[i];
}

void Inicia_Element(Element *e,Node *n){
	e->node = n;
	e->next = NULL;
}

void Apilar(Stack *s,Node *n){
	Element *e = calloc(1,sizeof(Element));
	Inicia_Element(e,n);
	if(s->top==NULL)
		s->top = e;
	else{
		e->next = s->top;
		s->top = e;
	}
}

Node* Desapilar(Stack *s){
	if(s->top!=NULL){
		Node* n=s->top->node;
		Element *aux=s->top;
		s->top=s->top->next;
		free(aux);
		return n;
	}else
		return NULL;
}

int Hojas(Node *root,int *nLeafs){
	Stack s;
	s.top = NULL;
	Apilar(&s,root);
	int number=0;
	while(s.top !=NULL){
		Node* n=Desapilar(&s);
		char child=0;
		if(n->left!=NULL){
			Apilar(&s,n->left);
			child=1;
		}	
		if(n->right!=NULL){
			Apilar(&s,n->right);
			child=1;
		}if(child==0){
			nLeafs[number]=n->frec;
			number++;		
		}
	}return number;
}

void Imprime_Arbol(Node *root){
	Stack s;
	s.top = NULL;
	Apilar(&s,root);
	while(s.top !=NULL){
		Node* n = Desapilar(&s);
		if(n->left!=NULL)
			Apilar(&s,n->left);
		if(n->right!=NULL)
			Apilar(&s,n->right);
		printf("%d ",n->frec);
	}
}

