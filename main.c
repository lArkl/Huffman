#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "PQueue.h"

void CrearCola(char **str, int tam,ColaP *C){
	int i,j=0; //i es la letra en codigo ASCII
	int frec[128]={0};
	for(i=0;j<tam && str[j][i]!='\0';i++){
		printf("%c",str[j][i]);
		frec[(int)str[j][i]]++;
		if(i==1023){
			j++;
			i=-1;
		}
	}
	int max=0;
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

int Decimal(char *s){
	int len = strlen(s);
	int i,dec=0,base=1;
	for(i=len-1;i>-1;i--){
		int val = s[i]=='0'?0:1;
		dec += val*base;
		base*=2;
	}return dec;
}
/*
char *Hex(char *s){
	int i,len = strlen(s);
	int i,dec=0,base=1;
	for(i=len-1;i>-1;i--){
		int val = s[i]=='0'?0:1;
		dec += val*base;
		base*=2;
	}return dec;
}*/

char **MemoriaS(char **str,int cont){
	int i,tam = cont/1024+1;
	str = calloc(tam,sizeof(char *));
	for(i=0;i<tam;i++){
   	str[i] = calloc(1024,sizeof(char));
	}return str;
}

void LiberaS(char **str,int cont){
	int i,tam = cont/1024+1;
	free(str);
	for(i=0;i<tam;i++){
   	free(str[i]);
	};
}

void CodificacionH(FILE *f,char **str,int tam,ColaP *C){
   //Guardamos las letras
   int i,j=0;
   //char *letras[strlen(str)];
   //Armamos el arbol de huffman
   Nodo *r = Huffman(C);
   //impresion del arbol
   FILE *fp;
	fp = fopen("arbol.pre" , "w");
	if (fp==NULL) {
		perror("Error al abrir el archivo");
		return;
	}
	PreOrden(fp,r);
	fclose(fp);
   // cod sera donde guardaremos la conversion de cada letra
   char *cod[128];
   char arr[r->h+1];
   int top=0;
   for(i=0;i<128;i++){
   	cod[i] = calloc(r->h+1,sizeof(char));
   }
	puts("===================");
	printf("Tabla de conversion\n");
	ImprimeRutaH(r, arr, cod,top);
	printf("===================\n");
	printf("Codigo generado\n");
	for(i=0;j<tam && str[j][i]!='\0';i++){
		printf("%s",cod[str[j][i]]);
		fprintf(f, "%s",cod[str[j][i]]);		
		if(i==1023){
			i=-1;
			j++;
		}
		//fprintf(f, "%d",Decimal(cod[str[i]]));
	}printf("\n");
}

void DecodificacionH(char **str,int tam,ColaP *C){
   int i,j=0;
   //Armamos el arbol de huffman
   
   Nodo *raiz = C->P[0];
   Nodo *aux = raiz;
   FILE *f;/*FILE *f = fopen("arbol.pre", "r");
	if (f == NULL){
		printf("Error al abrir el archivo!\n");
		exit(1);
	}
	Nodo *raiz;
   raiz = ConstruirArbol(f, raiz);
	fclose(f);
	Nodo *aux = raiz;
	printf("%p\n",raiz->der);*/
	f = fopen("decod.txt", "w");
	if (f == NULL){
		printf("Error al abrir el archivo!\n");
		exit(1);
	}
	puts("===================");
	puts("Codigo leido");
	for(i=0;j<tam && str[j][i]!='\0';i++){
   	if(str[j][i]=='0')
   		aux = aux->izq;
   	else
   		aux = aux->der;
   	if(EsHoja(aux)){
   		printf("%c",aux->letra);
   		//printf("%c",'o');
   		fprintf(f, "%c",aux->letra);
			aux = raiz;
   	}
   	if(i==1023){
			j++;
			i=-1;
		}
   }fclose(f);
   printf("\n");
}

int Contador(char *nombre){
	FILE *fp;
	fp = fopen(nombre , "r");
	if (fp==NULL) {
		perror("Error al abrir el archivo");
		return -1;
	}
	int i,cont=0;
	char c;
	while ( (c = fgetc(fp)) != EOF) {
		cont++;
   }return cont;
   fclose(fp);
}


void Leer(char **str, char *nombre, int cont){
	FILE *fp;
	fp = fopen(nombre , "r");
	if (fp==NULL) {
		perror("Error al abrir el archivo");
		return;
	}
	int i;
	int tam = cont/1024 +1;
   for(i=0;i<tam;i++)
		fgets (str[i], 1024, fp);
	fclose(fp);
}

void main(){
	char **str;
	int cont = Contador("text.txt");
	str = MemoriaS(str,cont);
	Leer(str,"text.txt",cont);
	//calcular frecuencias
	FILE *f = fopen("text.bin", "w");
	if (f == NULL){
		printf("Error al abrir el archivo!\n");
		exit(1);
	}
	ColaP C;
	IniciarCP(&C);
	CrearCola(str,cont/1024+1,&C);
	CodificacionH(f,str,cont/1024+1,&C);
	fclose(f);
	Leer(str,"text.bin",cont);
	DecodificacionH(str,cont/1024+1,&C);
	LiberaS(str,cont);
}
