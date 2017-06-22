#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "PQueue.h"

int Crear_Cola(char *str, Node *Cola){
	int i; //i es la letra en codigo ASCII
	int frec[256]={0};
	for(i=0;str[i]!='\0';i++){
		frec[(int)str[i]]++;
	}
	int max=0;
	for(i = 0; i < 256; i++){
		if (frec[i]){
			Cola[max].letra=i;
			Cola[max].frec=frec[i];
			max++;
		}
	}
	Heap_Sort(max,Cola);
	Imprime_Array(max,Cola);
	return max;
}

Node *Copiar_nodo(Node *aux, Node n){
	aux = calloc(1,sizeof(Node));
	aux->frec = n.frec;
	if(n.letra!=-1){
		//printf("%c\n",n.letra);	
		aux->letra = n.letra;
	}return aux;
}

void Huffman(int max, Node *Cola){
	Node n1,n2,n;
	int i,sum,cont=max;
	Node *aux1;
	Node *aux2;
	Node *aux;
	for(i=max-1; i>0 ; i--){
		n1 = Extrae_MinHeap(&cont,Cola);
		n2 = Extrae_MinHeap(&cont,Cola);
		n.frec = n1.frec + n2.frec;
		n.letra = -1;
		aux1 = Copiar_nodo(aux1,n1);
		printf("%c %d\n",aux1->letra,aux1->frec);
		aux2 = Copiar_nodo(aux2,n2);
		aux = Copiar_nodo(aux,n);
		aux->left = aux1;
		aux->right = aux2;
		//Imprime_Array(cont, Cola);
		Inserta_Heap(&cont, Cola, n);
		//Imprime_Array(cont, Cola);
	}
	int Leafs[max];
	int nLeaf = Hojas(aux,Leafs);
	printf("frec=%d\n",Leafs[1]);
	for(i=0;i<nLeaf;i++)
		printf("lele %d ",Leafs[i]);
	//printf("Arbolito\n");
	//Imprime_Arbol(aux);
	//Imprime_Heap(max,Cola);
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
	Node Cola[256];
	int max = Crear_Cola(str,Cola);
	Huffman(max,Cola);
}
