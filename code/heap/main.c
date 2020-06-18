#include<stdio.h>
#include "heap.h"



// gcc main.c heap.c -lm

int main(int argc,char** argv){
    char line[LINE_LENGHT];
    int n, *arr;
    printf("Lettura del file %s\n",argv[1]);
//apertura del file il cui nome è passato in linea di comando
    FILE* fin = fopen(argv[1],"r");
    if(fin == NULL ) goto endo;
//conteggio delle righe presenti nel file
    n = 0;
    while ( fgets(line, LINE_LENGHT, fin)!= NULL ) n++;
//allocazione delle memoria (con valori azzerati)
    arr = (int*) calloc(n, sizeof(int));
//riposiziona il cursore a inizio file e legge i valori
    rewind(fin);
    n = 0;
    while (fgets(line,LINE_LENGHT,fin)!= NULL )
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
    start=clock();
    
                                             printf("costruzione dell HEAP");
    for(int o=0;o<n;o++)
      printf("\n%d: %d",o+1,arr[o]);
    printf("\n");
                                             buildHeap(arr,n);
    printf("\n");
    for(int o=0;o<n;o++)
        printf("\n%d: %d",o+1,arr[o]);
    
    /*
    int max=extractMax(arr,n);
    printf("\n max: %d\n",max);
    for(int o=0;o<n-1;o++)
        printf("\n%d: %d",o+1,arr[o]);
    */
    
    addElement(arr,880);
     for(int o=0;o<n+1;o++)
         printf("\n%d: %d",o+1,arr[o]);

    
    printf("\nheap sort now....\n");
    printf("\n");

    printHeap(arr,n);

                                             heapsort(arr,n);
    for(int o=0;o<n;o++)
      printf("%d: %d\n",o+1,arr[o]);
    printf("\n");
    free(arr);
    end=clock();
    printf("\nil tempo di esecuzione: %f sec\n",(double)(end-start)/CLOCKS_PER_SEC);
endo:
    printf("FINITO\n");
	return 0;
}
