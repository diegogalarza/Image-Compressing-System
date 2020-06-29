#ifndef __STRUCTHUFFMAN_H
#define __STRUCTHUFFMAN_H

#include <stdio.h>
#include <stdlib.h>

struct tree
{
    int value;
    int freq;
    int direction;
    struct tree * padre;
    struct tree * left;
    struct tree * right;
};

struct nodoString
{
	char* binary;
	int valor;
	struct nodoString* next;
};
typedef struct nodoString* ListaString;

typedef struct tree* Tree;

struct nodoEstruc
{
	int value;
	struct nodoEstruc* next;
};

/*Nodo base de la estructura 
Con secondCola que es el struct que apunta a cada nodo*/
struct nodoEstrucbase
{
	struct tree* tree;
	struct nodoEstrucbase* next;
};

struct secondCola
{
	struct nodoEstrucbase* head; //Pointer to nodo
	//struct nodoEstrucbase* tail;  // Pointer to nodo
};

typedef struct nodoEstrucbase * NodoAux;
typedef struct secondCola * QueueAux;

struct newVals
{
	int rows;
	int cols;
	int maxVal;
	int* arrayCambio;
	int* arrayFirstNum;
	int** matrix;
	struct newVals* next;
};
typedef struct newVals* newValues;
/* Estructura principal de la informacion del PGM */
struct info{
	int rows;
	int cols;
	int maxVal;
	int ** matrix;
};

typedef struct info* PGMinfo;


#endif