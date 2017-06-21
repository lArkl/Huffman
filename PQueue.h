typedef struct Node{
	char letra;
	int frec;
	struct Node *left;
	struct Node*right;
} Node;

typedef struct Element{
	Node *node;
	struct Element *next;
}Element;

int Hojas(Node *root,int *nLeafs);
void swap(Node *H, int i, int j);
void Imprime_Array(int max, Node *H);
void Arregla_Heap(int max, Node *H, int i);
void Imprime_Heap(int max, Node *H);
void Crea_Heap(int max,Node *H);

Node Extrae_MinHeap(int *max, Node *H);
void Inserta_Heap(int *max, Node *H, Node n);
void Heap_Sort(int max, Node *H);
