#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "Estructuras.h"

void CrearCola(char *nombre, ColaP *C){
	//Lectura del archivo
	char c;
	int frec[128]={0};
	FILE *fp;
	fp = fopen(nombre , "r");
	if (fp==NULL) {
		perror("Error al abrir el archivo");
		return;
	}
	puts("Texto a comprimir:");
	while ( (c = fgetc(fp)) != EOF) {
		printf("%c",c);
		frec[c]++;
   }
	fclose(fp);
	//Creacion de la Cola
	int i,max=0;
	for(i = 0; i < 128; i++){
		if (frec[i]){
			C->P[max] = (Nodo *)calloc(1,sizeof(Nodo));
			IniciarNodo(C->P[max], frec[i], i);
			max++;
		}
	}C->max = max;
	OrdenarHeap(C);
	//ImprimeArray(C);
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

int Decimal(char *s){
	int len = strlen(s);
	int i,dec=0,base=1;
	for(i=len-1;i>-1;i--){
		int val = s[i]=='0'?0:1;
		dec += val*base;
		base*=2;
	}return dec;
}

void Binario(char *str, int c){
	int i,val;
	for(i=6;i>=0;i--){
		str[i] = (c%2==1)?'1':'0';
		c/=2;
	}//return str;
}

void CodificacionH(char *nombre, ColaP *C){
	//Armamos el arbol de huffman
   Nodo *r = Huffman(C);
   //impresion del arbol
	FILE *f = fopen("arbol.pre" , "w");
	if (f==NULL) {
		perror("Error al abrir el archivo");
		return;
	}
	PreOrden(f,r);
	fclose(f);
	// cod sera donde guardaremos la conversion de cada letra
   char *cod[128];
   char c,arr[r->h+1];
   int i,top=0;
   for(i=0;i<128;i++){
   	cod[i] = calloc(r->h+1,sizeof(char));
   }
	puts("===================");
	printf("Tabla de conversion\n");
	ImprimeRutaH(r, arr, cod,top);
	printf("===================\n");
	printf("Codigo generado:\n");
	//Leemos el archivo original
	FILE *fp = fopen(nombre , "r");
	if (fp==NULL) {
		perror("Err al abrir el archivo");
		return;
	}
	f = fopen("text.bin" , "w");
	if (f==NULL) {
		perror("Error al abrir el archivo");
		return;
	}
	while ( (c = fgetc(fp)) != EOF) {
		printf("%s",cod[c]);
		fprintf(f,"%s",cod[c]);
   }printf("\n");
	fclose(fp);
	fclose(f);
	//Conversion a ascii
	fp = fopen("text.bin" , "r");
	char str[8];
	f = fopen("text.cod" , "w");
	//puts("===================");
	puts("Texto comprimido!");
	while ( fgets (str, 8, fp)!=NULL) {
		if(strlen(str)==7){
			fprintf(f,"%c",Decimal(str));
		}else{
			int n = strlen(str);
			for(i=6;i>=0;i--)
				str[i]=(n-7+i>=0)?str[n-7+i]:0;
		}
   }fprintf(f,"%c",-1);
   printf("\n");
   fclose(fp);
   fclose(f);
}

void DecodificacionH(ColaP *C){
   int i,j=0;
   //Armamos el arbol de huffman
   FILE *f = fopen("arbol.pre", "r");
	if (f == NULL){
		printf("Error al abrir el archivo!\n");
		exit(1);
	}
	Nodo *raiz;
	raiz = ConstruirArbol(f);
	fclose(f);
	Nodo *aux = raiz;
	//decodificamos
	FILE *fp = fopen("text.cod", "r");
	if (fp == NULL){
		printf("Error al abrir el archivo!\n");
		exit(1);
	}
	f = fopen("decod.txt", "w");
	if (f == NULL){
		printf("Error al abrir el archivo!\n");
		exit(1);
	}
	puts("===================");
	puts("Codigo leido");
	char c;
	char str[7];
	while ( (c = fgetc(fp)) != EOF) {
		Binario(str,c);
		//printf("%s",str);
		for(i=0;i<7;i++){
			if(str[i] =='0')
				aux = aux->izq;
			else
				aux = aux->der;
			if(EsHoja(aux)){
				printf("%c",aux->letra);
				fprintf(f, "%c",aux->letra);
				aux = raiz;
			}
		}
   }printf("\n");
	fclose(f);
	fclose(fp);
}

void main(int argc, char** argv){
	//Por defecto compactara el archivo text.txt
	if(argv[1] == NULL)
		argv[1]="text";
	char nombre[strlen(argv[1])+5];
	strcpy(nombre,argv[1]);
	strcat(nombre,".txt");
	
	ColaP C;
	IniciarCP(&C);
	//Calculamos frecuencia y llenamos la cola
	CrearCola(nombre,&C);
	CodificacionH(nombre,&C);
	
	DecodificacionH(&C);

}
