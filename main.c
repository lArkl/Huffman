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
	//ImprimeArray(C);
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
	return aux;
}

void ImprimeRutaH(Nodo* r, char *arr, char **cod,int top){
	if (r->izq){
		arr[top] = '0';
  		ImprimeRutaH(r->izq, arr,cod,top+1);
	}
	if (r->der){
		arr[top] = '1';
		ImprimeRutaH(r->der, arr,cod,top+1);
	}//Si es hoja almacenamos e imprimimos su valor binario
	if (EsHoja(r)){
		printf("%c: ", r->letra);
		int i;
		for (i = 0; i < top; ++i){
			printf("%c", arr[i]);
			cod[r->letra][i]= arr[i];
		}//puts(cod[r->letra]);
		printf("\n");
	}
}

void CodificacionH(FILE *f,char *str,ColaP *C){
   //Guardamos las letras
   int i;
   char letras[C->max];
   //Armamos el arbol de huffman
   Nodo *r = Huffman(C);
   // cod sera donde guardaremos la conversion de cada letra
   char *cod[256];
   char arr[r->h+1];
   int top=0;
   for(i=0;i<256;i++){
   	cod[i] = calloc(r->h+1,sizeof(char));
   }
	printf("===================\n");
	printf("Tabla de conversion\n");
	ImprimeRutaH(r, arr, cod,top);
	printf("===================\n");
	printf("Codigo generado\n");
	for(i=0;str[i]!='\0';i++){
		printf("%s",cod[str[i]]);
		fprintf(f, "%s",cod[str[i]]);
	}printf("\n");
}

void DecodificacionH(char *str,ColaP *C){
   //Guardamos las letras
   int i;
   //char letras[C->max];
   //Armamos el arbol de huffman
   Nodo *raiz = C->P[0];
   Nodo *aux = raiz;
   printf("\n");
   for(i=0;str[i]!='\0';i++){
   	if(str[i]=='0')
   		aux = aux->izq;
   	else
   		aux = aux->der;
   	if(EsHoja(aux)){
   		printf("%c",aux->letra);
   		aux = raiz;
   	}
   }printf("\n");
}

void main(){
	FILE *fp;
	char str[4096];
	fp = fopen("text.txt" , "r");
	if (fp==NULL) {
		perror("Error al abrir el archivo");
		return;
	}
	if( fgets (str, 4096, fp)!=NULL ){
	  puts(str);
	}
	fclose(fp);
	//calcular frecuencias
	FILE *f = fopen("text.cod", "w");
	if (f == NULL){
		printf("Error opening file!\n");
		exit(1);
	}
	ColaP C;
	IniciarCP(&C);
	CrearCola(str,&C);
	CodificacionH(f,str,&C);
	fclose(f);
	
	fp = fopen("text.cod" , "r");
	if (fp==NULL) {
		perror("Error al abrir el archivo");
		return;
	}
	//Lectura para decodificacion
	if( fgets (str, 4096, fp)!=NULL ){
		printf("===================\n");
		printf("Codigo leido\n");
		puts(str);
	}
	fclose(fp);
	DecodificacionH(str,&C);
}
