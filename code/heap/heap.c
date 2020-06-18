#include "heap.h"
#define _USE_MATH_DEFINES
#include<math.h>

int parent(int i){return (int)(i-1)/2;}
int leftChild(int i){return (2*i)+1;}
int rightChild(int i){return (2*i)+2;}


void swap(int *a,int *b){
    int t;
    t=*a;
    *a=*b;
    *b=*a;
}

void addElement(int a[],int el){
    int n=sizeof(a)/sizeof(int);
    a=(int*)realloc(a,n+1);
    a[++n]=el;
    buildHeap(a,n);

}


void buildHeap(int a[],int n){
	int i;
	for(i=n/2-1;i>=0;i--) heapify(a,n,i);
}

void heapify(int arr[], int n, int i) 
{ 
    int largest = i; // Initialize largest as root 
    int l = 2*i + 1; // left = 2*i + 1 
    int r = 2*i + 2; // right = 2*i + 2 
  
    // If left child is larger than root 
    if (l < n && arr[l] > arr[largest]) 
        largest = l; 
  
    // If right child is larger than largest so far 
    if (r < n && arr[r] > arr[largest]) 
        largest = r; 
  
    // If largest is not root 
    if (largest != i) 
    { 
       int t;
        t=arr[i];
        arr[i]=arr[largest];
        arr[largest]=t;
  
        // Recursively heapify the affected sub-tree 
        heapify(arr, n, largest); 
    } 
} 

void heapsort(int a[],int n){
    for(int i=n-1;i>0;i--){
        int t=a[0];
        a[0] = a[i];
        a[i]=t;
        heapify(a,i,0);
    }
}

int extractMax(int a[],int n){
    if(a==NULL) return -1;
    int max=a[0];
    a[0]=a[n-1];
    n--;
    heapify(a,n,0);
    return max;
}


void printHeap(int a[],int n){
    int h,step,line=1,j;
    h=(int)log2((double)n)+1;
    step=((int)pow(2,h-1))-1;
    printf("\n");
    for(j=0;j<step;j++) printf("\t");
    for(int i=0;i<n;i++){
        if(((int)log2(i+1)+1)>line){
            line++;
            step=((int)pow(2,h-line))-1;
            printf("\n\n");
            for(j=0;j<step;j++)printf("\t");
        }
        printf("%d",a[i]);
        for(j=0;j<(2*step)+2;j++) printf("\t");
    }
}
