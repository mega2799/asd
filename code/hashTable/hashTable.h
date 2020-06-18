#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "hash.h"

// questa struttura definisce il singolo nodo, cioè il singolo elemento della lista
typedef struct Node_
{
   struct Node_ *next;  // puntatore al nodo successivo
   uint8_t* data;       // valore contenuto nel nodo
} Node;

// definizione della tabella hash come array di array, di tipo Node
Node **hashTable;
// dimensione della tabella hash, numero di celle
uint32_t m;

uint32_t hashMapping(uint32_t h);
uint32_t hashFunction(const uint8_t* key);

void insertNode(const uint8_t* val);
void deleteNode(const uint8_t* val);
uint32_t findNode (const uint8_t* val);

void printTable(int n, int stats);

#endif // HASHTABLE_H_INCLUDED
