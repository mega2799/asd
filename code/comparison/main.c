#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#define LINE_LENGTH 120

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition (int *arr, int low, int high)
{
    int pivot = arr[high]; // pivot
    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int *arr, int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}






void insertion_sort(int *arr,int n)
{
    int key,i;

    for(int j=1; j<n; j++)
    {
        key=arr[j];
        i=j-1;
        while (i>=0 && arr[i]>key)
        {
            arr[i+1]=arr[i];
            i=i-1;
        }
        arr[i+1]=key;
    }
}

void merge(int *A,int p,int q,int r)
{
    int i=p,j=q+1,k=0;
    int *B=malloc(sizeof(int) * (r - p + 1));
    while (i<=q && j<=r)
    {
        if(A[i]<A[j])
        {
            B[k]=A[k];
            i++;
        }
        else
        {
            B[k]=A[j];
            j++;
            k++;
        }
    }
    while(i<=q)
    {
        B[k]=A[i];
        i=i+1;
        k=k+1;
    }
    while(j<=r)
    {
        B[k]=A[j];
        j++;
        k++;
    }
    for(int a=0; a<k; a++) A[a+p]=B[a];
}

void merge_sort(int *arr,int p, int r)
{
    int q;
    if(p<r)
    {
        q=(p+r)/2;
        merge_sort(arr,p,q);
        merge_sort(arr,q+1,r);
        merge(arr,p,q,r);
    }
}

int main (int argc, char* argv[])
{
    char line[LINE_LENGTH];
    int n, *arr;
    printf("Lettura del file %s\n",argv[1]);
//apertura del file il cui nome è passato in linea di comando
    FILE* fin = fopen(argv[1],"r");
    if(fin == NULL ) goto endo;
//conteggio delle righe presenti nel file
    n = 0;
    while ( fgets(line, LINE_LENGTH, fin)!= NULL ) n++;
//allocazione delle memoria (con valori azzerati)
    arr = (int*) calloc(n, sizeof(int));
//riposiziona il cursore a inizio file e legge i valori
    rewind(fin);
    n = 0;
    while (fgets(line,LINE_LENGTH,fin)!= NULL )
    {
        //legge la chiave (parte che precede il separatore)
        //buf = strtok(line, separator);
        //legge il valore (parte che segue il separatore) e lo salva
        //arr[n]=atoi( strtok(NULL, separator) );
        arr[n]=atoi(line);
       printf("%d ->%d\n",(n+1),arr[n]);
        n++;
    }
    fclose(fin);
    printf("\n");

    clock_t start,end;

    start= clock();
    //insertion_sort(arr,n);
    //merge_sort(arr,0,n);
    quickSort(arr,0,n);
    //selection

    printf("Dopo ordinamento\n");
   // for(int i=0; i<n; i++)
   // {
      //  printf("%d->%d \n",(i+1),arr[i]);
   // }

    free(arr);
    end=clock();
    printf("il tempo di esecuzione: %f sec\n",(double)(end-start)/CLOCKS_PER_SEC);
endo:
    printf("FINITO\n");
    return 0;
}

