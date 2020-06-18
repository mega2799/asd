#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#define LINE_LENGHT 120

int *heap;
int heapSize;

void printHeap(int*,int);

int parent(int);
int leftChild(int);
int rightChild(int);

void buildHeap(int* ,int);
void heapsort(int*,int);
void heapify(int*,int,int);
int extractMax();
void addElement(int*,int);

#endif

