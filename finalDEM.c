#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "estructura.h"

#include "lectorPGM.c"
#include "dct.c"
#include "truncado.c"

#define PI 3.14159265359


int countListaString(ListaString list)
{
	ListaString temp = list;
	int cont = 0;
	while(temp != NULL)
	{
		cont++;
		temp = temp->next;
	}
	return cont;
}

NodoAux initializeNodoAux ()
{
	NodoAux newnodo = (NodoAux) malloc(sizeof(struct nodoEstrucbase));
	newnodo->tree = NULL;
	newnodo->next = NULL;
	return newnodo;
}

Tree initializeTree ()
{
	Tree newtree = (Tree) malloc(sizeof(struct tree));
	newtree->left = NULL;
	newtree->right = NULL;
	newtree->padre = NULL;
	return newtree;
}

int convertStringToBinary(char* bin)
{
	int binary = atoi(bin);
	return binary;
}

char* cutStrings(char* binario)
{
	int i = strlen(binario)-1;
	int cont = 0;
	char* newBin = malloc(200000 * sizeof(char));
	while (i >= 0)
	{
		char* w = &binario[i];
		if (strncmp(w, "0", 1) == 0)
			strcat(newBin, "0");
		else
			strcat(newBin, "1");
		i--;
	}
	return newBin;
}


int convertDecimalToBinary(long long n)
{
    int binaryNumber = 0, i = 0, still =0;
    while (n!=0)
    {
        still = n%2;
        n /= 2;
        binaryNumber += still*pow(10,i);
        i++;
    }
    return binaryNumber;
}


int convertBinaryToDecimal(long long n)
{
    int decimalNumber = 0, i = 0, still =0;
    while (n!=0)
    {
        still = n%10;
        n /= 10;
        decimalNumber += still*pow(2,i);
        i++;
    }
    return decimalNumber;
}

char* convertBinaryToString(int bin)
{
	char* binary = (char*) malloc(sizeof(char)*2000);
	binary = sprintf(binary, "%d", bin);
	return binary;
}

int valueOfElement(ListaString list, int matrixVal, int altura)
{
	ListaString temp = list;
	while(temp != NULL)
	{
		if(temp->valor == matrixVal)
		{
			char* newbin = cutStrings(temp->binary);
			int value = convertStringToBinary(newbin);
			value = convertBinaryToDecimal(value);
			return value;
		}
		temp = temp->next;
	}
	return 0;
}

void writeNEWPGM(const char *file, newValues pgminfo1, int** matrix, int rows, int cols)
{
    FILE *decompressedFile;
    decompressedFile = fclose(fopen(file, "w"));
    if(decompressedFile == NULL) 
	{
    	decompressedFile = fopen(file, "w+");
	}
 
    fprintf(decompressedFile, "P2");
    fprintf(decompressedFile, "\n");
    fprintf(decompressedFile, "# decompressed.ascii.pgm");
    fprintf(decompressedFile, "\n");
    fprintf(decompressedFile, "%d %d", pgminfo1->cols, pgminfo1->rows);
    fprintf(decompressedFile, "\n");
    fprintf(decompressedFile, "%d", pgminfo1->maxVal);
    fprintf(decompressedFile, "\n");
    for (int i = 0; i < pgminfo1->rows; i++)
    {
        for (int j = 0; j < pgminfo1->cols; j++) 
        	{
        		char valorInicial[200];
        		sprintf(valorInicial, "%d", pgminfo1->matrix[i][j]);
    			fputs(valorInicial, decompressedFile);
    			fprintf(decompressedFile, " ");
        	}
    }

    fprintf(decompressedFile, "\n");
    fclose(decompressedFile);
}


void writePGM(const char *file, ListaString list, PGMinfo pgminfo1, int* array, int sizeArray)
{
    FILE *compressedFile;
    compressedFile =  fclose(fopen(file, "w"));
    if(compressedFile == NULL) 
	{
    	compressedFile = fopen("compressedFile.txt", "w+");
	}
 
    fprintf(compressedFile, "%d %d ", pgminfo1->rows, pgminfo1->cols);
    fprintf(compressedFile, "\n");
    fprintf(compressedFile, "%d", pgminfo1->maxVal);
    fprintf(compressedFile, "\n");
    int numCases = countListaString(list);
    fprintf(compressedFile, "%d", numCases);
    fprintf(compressedFile, "\n");
    ListaString temp = list;
    while(temp != NULL)
    {
    	char numero[20000];
    	char valorInicial[20000];
    	int value = convertStringToBinary(temp->binary);
    	value = valueOfElement(temp, temp->valor, 200);
    	sprintf(numero, "%d", value);
    	fputs(numero, compressedFile);
    	fprintf(compressedFile, " ");
    	sprintf(valorInicial, "%d", temp->valor);
    	fputs(valorInicial, compressedFile);
    	fprintf(compressedFile, " ");
    	temp = temp->next;
    }
    fprintf(compressedFile, "\n");
    fprintf(compressedFile, "-");
    fprintf(compressedFile, "\n");
        for (int i = 0; i < sizeArray; ++i)
        {
        	char number[20000];
        	sprintf(number, "%d", array[i]);
 			fputs(number, compressedFile);
        	fprintf(compressedFile, " ");
        }
    fprintf(compressedFile, "-");
    fclose(compressedFile);
}



int ** matrixDecompressed(int* array, int size, int rows, int cols)
{
	int** matrix = createNewMatrix(rows, cols);
	int i = 0;
	while(i < size)
	{
		for (int w = 0; w < rows; w++)
			for(int j = 0; j< cols; j++)
			{
				matrix[w][j] = array[i];
				i++;
			}
	}
	return matrix;
}
int valueOfElementReverse(ListaString list, int matrixVal)
{
	ListaString temp = list;
	while(temp != NULL)
	{
		char* val = sprintf(val, "%d", matrixVal);
		if(temp->binary == val)
		{
			char* newbin = cutStrings(val);
			return 0;
		}
		temp = temp->next;
	}
	return 0;
}

int** returnFirstCodes(int** matrix, ListaString list, int rows, int cols)
{
	int cont = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			int newVal = matrix[i][j];
			newVal = valueOfElementReverse(list, matrix[i][j]);
			matrix[i][j] = newVal;
		}
	}
	return matrix;
}

/*-------------------------------------------------
---------------------------------------------------*/


int vacioArbol(Tree a)
{
	if (a == NULL)
		return 1;
	return 0;
}

/*-----------------------------------------------------
------------------------------------------------------*/

ListaString initializeString()
{
	ListaString newlist = (ListaString) malloc(sizeof(struct nodoString));
	newlist->binary = NULL;
	newlist = NULL;
	return newlist;
}

int* lastMatrix(int ** matrix, ListaString list, int rows, int cols, int altura)
{
	ListaString temp = list;
	int * array =(int*) calloc(rows*cols, sizeof(int));
	int cont = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			int newVal = valueOfElement(list, matrix[i][j], 2000);
			array[cont] = newVal;
			cont++;
		}
	}
	return array;
}

/*--------------------------------------------------
----------------------------------------------------
GUARDA UNA LISTA QUE TENGA TODOS LOS VALORES 
NECESARIOS PARA DESPUES SACAR LOS CODIGOS DE HUFFMAN
----------------------------------------------------
--------------------------------------------------*/
void agregarElemAux(NodoAux* nodo, Tree tree)
{
	NodoAux new = (NodoAux) malloc(sizeof(struct nodoEstrucbase)); 
	new->tree = tree;
	new->next = NULL;
	if(nodo == NULL)
	{
		*nodo = new;
	}
	else
	{
		new->next = *nodo;
		*nodo = new;
	}
}

NodoAux saveVals(QueueAux queue)
{
	NodoAux newNodo = (NodoAux) malloc(sizeof(struct nodoEstrucbase)); 
	newNodo = NULL;
	NodoAux* new = &newNodo;
	NodoAux temp = queue->head;
	while(temp != NULL)
	{
		agregarElemAux(new, temp->tree);
		temp= temp->next;

	}
	return newNodo;
}

/*----------------------------------
------------------------------------
CODIGO DE ARBOL DE HUFFMAN
------------------------------------
-----------------------------------*/
void agregarElem(QueueAux nodo, NodoAux new)
{
	if(nodo->head == NULL)
	{
		nodo->head = new;
	}
	else
	{
		NodoAux temp = nodo->head;
		new->next = temp;
		nodo->head = new;
	}
	
}

Tree extractMin(QueueAux nodo)
{ 
	NodoAux flag = nodo->head;
	NodoAux temp = nodo->head;
	int bandera = 0;
	Tree arbAux = temp->tree;
	if (temp->next == NULL)
	{
		arbAux = temp->tree;
		nodo->head = NULL;
		return arbAux;
	}
	if (temp->next->next == NULL)
	{
		if (arbAux->freq < temp->next->tree->freq)
		{
			arbAux = temp->tree;
			nodo->head = nodo->head->next;
		}
		else
		{
			arbAux = temp->next->tree;
			nodo->head->next = NULL;
		}
		return arbAux;
	}
	while(temp != NULL)
	{
		if(temp->next == NULL)
			break;
		if (arbAux->freq > temp->next->tree->freq)
		{
			arbAux = temp->next->tree;
			flag = temp;
			bandera = 1;
		}
		temp = temp->next;
	}
	if (bandera == 1)
	{
		if(flag->next->next == NULL)
		{
			flag->next = NULL;
		}
		else {
			flag->next = flag->next->next;
		}
	}
	else
	{
		nodo->head = nodo->head->next;
	}
	return arbAux;
}

Tree addTree(Tree arbol, Tree first, Tree second)
{
	arbol = initializeTree();
	arbol->left = first;
	arbol->direction = 0;
	arbol->right = second;
	arbol->direction = 1;
	arbol->value = 260;
	arbol->freq = first->freq + second->freq;
	return arbol;

}

int sizeOfTemp(QueueAux queue)
{
	NodoAux temp = queue->head;
	int cont = 0;
	while(temp != NULL)
	{
		cont++;
		temp = temp->next;
	}
	free(temp);
	return cont;
}

ListaString anxLista(ListaString lst, char* string, int elem){
  ListaString nuevo,tmp;
  
  nuevo = (ListaString) malloc(sizeof(struct nodoString));
  nuevo->binary = string;
  nuevo->valor = elem;
  nuevo->next = NULL;
  
  if(lst == NULL)
    lst = nuevo;
  else{
    tmp = lst;
    while(tmp->next != NULL)
      tmp = tmp->next;
    tmp->next = nuevo;
  }
  
  return lst;
}

Tree encontrarArbol(Tree* tree, int valor)
{
	Tree raiz = *tree;
	if(raiz == NULL)
		return NULL;
	if (raiz->value == valor)
	{
		return raiz;
	}
	else
	{
		Tree left = encontrarArbol(&raiz->left, valor);
		Tree right = encontrarArbol(&raiz->right, valor);
		if(left!= NULL || right != NULL)
		{
			if(right != NULL)
				return right;
			return left;
		}
		return NULL;
	}
}

char* constructBinaryHuffmanCode(Tree temp, long long int altura)
{
	char* string = (char*) malloc(altura* sizeof(char));
	Tree tree = temp;
	double treeVal = temp->value;
	while (tree->padre != NULL)
	{
		Tree temp = tree;
		tree = tree->padre;
		if (tree->left == temp)
		{
			strcat(string,"0");
		}
		else if (tree->right == temp)
		{
			strcat(string,"1");
		}
	}
	return string;
}

long long int alturaArbol(Tree huffman)
{
	if(vacioArbol(huffman))
		return 0;
	long long int alturaLeft = alturaArbol(huffman->left);
    long long int alturaRight = alturaArbol(huffman->right);
 
    if (alturaLeft > alturaRight) 
        return(alturaLeft+1);
   	else return(alturaRight+1);
}
ListaString HuffmanCodes(NodoAux nodo, Tree huffman)
{
	ListaString newlist = (ListaString) malloc(sizeof(struct nodoString));
	long long int altura = alturaArbol(huffman)+1;
	newlist = NULL;
	NodoAux temp = nodo;
	while (temp != NULL)
	{
		Tree arbol = encontrarArbol(&huffman, temp->tree->value);
		char* newchar = constructBinaryHuffmanCode(arbol, altura);
		newlist = anxLista(newlist, newchar,temp->tree->value);
		temp = temp->next;
	}
	return newlist;
}

Tree Huffman (QueueAux nodo)
{

	Tree newtree1= (Tree) malloc (sizeof(struct tree));
	QueueAux copyQueue = nodo;
	NodoAux tempAux = nodo->head;

	while (sizeOfTemp(copyQueue) > 1)
	{
		NodoAux nodoTemp = initializeNodoAux();
		Tree second = extractMin(copyQueue);
		Tree first = extractMin(copyQueue);
		Tree newtree = addTree(newtree, first, second);
		first->padre = newtree;
		second->padre = newtree;
		newtree->padre = NULL;
		nodoTemp->tree = newtree;
		nodoTemp->next = NULL;
		agregarElem(nodo, nodoTemp);
		newtree1 = nodo->head->tree;
		if (sizeOfTemp(copyQueue) == 1)
			break;
		}
	return newtree1;
}

/*FUNCIONES AUXILIARES PARA INICIALIZAR TODAS LAS ESTRUCTURAS*/
QueueAux initializeAux ()
{
	QueueAux newqueue = (QueueAux) malloc(sizeof(struct secondCola));
	newqueue->head = NULL;
	return newqueue;
}

/*-------------------------------------------------------------------------
---------------------------------------------------------------------------
PRINCIPAL FUNCION LA CUAL ES LLAMADA DESPUES DE ORDENARQUEUE, 
CADA VEZ QUE SE QUIERE AGREGAR UN VALOR A LA QUEUE SE LLAMA A ESTA FUNCION
/*-------------------------------------------------------------------------
-------------------------------------------------------------------------*/

void ordenarFreq(QueueAux cola, int valor)
{
	QueueAux newcola = initializeAux();
	NodoAux newnodo = (NodoAux) malloc(sizeof(struct nodoEstrucbase));
	Tree newtree = (Tree) malloc(sizeof(struct tree));
	newtree->value = valor;
	newtree->freq = 1;
	newnodo->tree = newtree;
	newnodo->next = NULL;
	newcola->head = newnodo;
	NodoAux tmp = cola->head;
	int flag = 0;
		if (cola->head == NULL)
		{
			cola->head = newnodo;
		}
		else
		{
			if (cola->head->tree->value == valor)
			{
				cola->head->tree->freq++;
				flag = 1;
			}
			else if (tmp->next != NULL)
			{
				tmp = cola->head;
				while(tmp->next != NULL)
				{
					tmp = tmp->next;
					if (tmp->tree->value == valor)
					{
						tmp->tree->freq = tmp->tree->freq+1;
						flag = 1;
						break;
					}
				}
			}
		if (flag == 0)
		{
			tmp->next = newnodo;
		}
	}
}

void ordenarQueue(QueueAux nodo, int** matrix, int rows, int cols)
{
	for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++) {
            ordenarFreq(nodo, matrix[i][j]);
    	}
	}
}


int main(int argc,char **argv)
{
	char* filename = argv[1];
	char* type = argv[2];
	char* quality = argv[3];
	int dQual = 1;
	if(strcmp(type, "-c")==0)
	{
		if(strcmp(quality, "min")==0)
		{
			dQual = 1;
		}
		else if(strcmp(quality, "max")==0)
		{
			dQual = 3;
		}
		else if(strcmp(quality, "normal")==0)
		{
			dQual = 2;
		}
		else{
			perror("Incorrect compression option.\n");
			exit(1);
		}

		PGMinfo p = (PGMinfo) malloc(sizeof(struct info));
		p = readPGM(filename, p);

		double** dctM = compressDCT(p->matrix, p->rows, p->cols, 8, p);

		int** dctMQuantif = quantify(dctM,p->rows, p->cols, dQual);

		newValues decompressedFile = (newValues) malloc(sizeof(struct newVals));
		QueueAux queue = initializeAux();
		NodoAux queue2 = (NodoAux) malloc(sizeof(struct nodoEstrucbase));
		ordenarQueue(queue, dctMQuantif, p->rows, p->cols);
		queue2 = saveVals(queue);
		Tree arb = malloc(sizeof(struct tree));
		arb = NULL;
		arb = Huffman(queue);
		ListaString new = (ListaString) malloc(sizeof(struct nodoString));
		new = HuffmanCodes(queue2 , arb);
		int* array = lastMatrix(dctMQuantif, new, p->rows, p->cols, 2000);
		int** newMatrix = matrixDecompressed(array, p->rows*p->cols, p->rows, p->cols);
		writePGM("compressedFile.txt", new, p, array, p->rows*p->cols);
		
	}

	else 
	{
		if(strcmp(quality, "min"))
		{
			dQual = 1;
		}
		else if(strcmp(quality, "max"))
		{
			dQual = 3;
		}
		else if(strcmp(quality, "normal"))
		{
			dQual = 2;
		}
		else{
			perror("Incorrect decompression option.\n");
			exit(1);
		}

		newValues decompressedFile = (newValues) malloc(sizeof(struct newVals));
		decompressedFile = readNEWPGM("compressedFile.txt", decompressedFile);
		decompressedFile->matrix = antiquantify(decompressedFile->matrix, dQual, decompressedFile->rows, decompressedFile->cols);
		decompressedFile->matrix = decompressIDCT(decompressedFile->matrix, decompressedFile->rows, decompressedFile->cols, 8, decompressedFile);
		writeNEWPGM(filename, decompressedFile, decompressedFile->matrix, decompressedFile->rows, decompressedFile->cols);
	}


	printf("\nProgram terminated!\n");
	return 0;
}