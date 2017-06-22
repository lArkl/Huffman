#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "PQueue.h"

void CrearCola(char *str, ColaP *C){
	int i; //i es la letra en codigo ASCII
	int frec[256]={0};
	for(i=0;str[i]!='\0';i++){
		frec[(int)str[i]]++;
	}
	int max=0;
	for(i = 0; i < 256; i++){
		if (frec[i]){
			C->P[max] = (Nodo *)calloc(1,sizeof(Nodo));
			IniciarNodo(C->P[max], frec[i], i);
			max++;
		}
	}C->max = max;
	OrdenarHeap(C);
	ImprimeArray(C);
}

void MezclarNodo(Nodo *aux,Nodo *aux1, Nodo *aux2){
	aux->frec = aux1->frec + aux2->frec;
	aux->izq = aux1;
	aux->der = aux2;
	aux->h = (aux1->h > aux2->h)?aux1->h+1:aux2->h+1;
}

Nodo *Huffman(ColaP *C){
	int i=0,max=C->max;
	Nodo *aux1, *aux2,*aux;		
	for(i = max-1; i>0 ; i--){
		aux1 = ExtraeMinHeap(C);
		aux2 = ExtraeMinHeap(C);
		aux = (Nodo *)calloc(1,sizeof(Nodo));
		IniciarNodo(aux,0,-1);
		MezclarNodo(aux,aux1,aux2);
		InsertaHeap(C, aux);
	}C->max=max;
	return ExtraeMinHeap(C);
}
/*
void RutaHuffman(int max, Nodo *r){
	Cola q;
	int i=0;
	char *s[max];
	q.tope = NULL;
	q.base = NULL;
	Encolar(&q,r);
	Nodo *n;
	while(q.base !=NULL && q.tope!=NULL){
		n = Desencolar(&q);
		int flag=0;
		if(n->izq!=NULL){
			Encolar(&q,n->izq);
			flag++;
			//s[i]=
		}if(n->der!=NULL){
			Encolar(&q,n->der);
			flag++;
		}if(flag==0){
			//s[i]=
			i++;
		}
	}
}*/

void ImprimeRutaH(Nodo* r, int arr[], int top){
	if (r->izq){
		arr[top] = 0;
  		ImprimeRutaH(r->izq, arr, top + 1);
	}
	if (r->der){
		arr[top] = 1;
		ImprimeRutaH(r->der, arr, top + 1);
	}

	// If this is a leaf node, then it contains one of the input
	// characters, print the character and its code from arr[]
	if (EsHoja(r)){
		printf("%c: ", r->letra);
		int i;
		for (i = 0; i < n; ++i)
			printf("%d", arr[i]);
		printf("\n");
	}
}

void main(){
	FILE *fp;
	char str[4096];
	fp = fopen("text.txt" , "r");
	if (fp==NULL) {
		perror("Error opening file");
		return;
	}
	if( fgets (str, 4096, fp)!=NULL ){
	  puts(str);
	}
	fclose(fp);
	//calcular frecuencias
	ColaP C;
	IniciarCP(&C);
	CrearCola(str,&C);
	Nodo *raiz = Huffman(&C);
	printf("%d",raiz->frec);
	ImprimeRutaH(Nodo* r, int arr[], int top);
}
