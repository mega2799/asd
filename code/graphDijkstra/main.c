#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define LINE_LENGTH 120
#define KEY_LENGTH 4


int main (int argc, char* argv[])
{
   char line[LINE_LENGTH];
   uint8_t *buf;
   int **matrix;
   const char *separator = ",";
   int n;
   clock_t start, end;


   int w,start_node, end_node, i , j , max_node_label;



   printf("\nLettura del file %s\n\n",argv[1]);

   FILE* fin = fopen(argv[1] ,"r");
   if(fin == NULL ) goto end;

   //conteggio il numero di nodi
   n = 0;
   while ( fgets((char*)line, LINE_LENGTH, fin)!= NULL ) {
      buf = strtok(line,separator);
      start_node = atoi(buf);
      if (start_node > max_node_label ) max_node_label = start_node;
      
      while(1){
      buf = strtok(NULL,separator);
      if( buf== NULL ) break;
      end_node = atoi(buf);
      if (end_node > max_node_label) max_node_label = end_node;
      buf = strtok(NULL,separator);
      w = atoi(buf);
      }
   }
   n = max_node_label;
   rewind(fin);
   for(i = 0; i< n ; i ++) matrix[i] = calloc(n, sizeof(int));
   while ( fgets((char*)line, LINE_LENGTH, fin)!= NULL ) {
      buf = strtok(NULL,separator);
      start_node = atoi(buf);
      start_node = atoi(buf);
      
      while(1){
      buf = strtok(NULL,separator);
      if( buf== NULL ) break;
      end_node = atoi(buf);
      buf = strtok(NULL,separator);
      w = atoi(buf);
      printf("\n %d ", w);
      matrix[start_node-1][end_node-1] = w;
      }
   }


   fclose(fin);
   start = clock();
   free(buf);
   fclose(fin);
   printf("\n");

   end:printf("<ENTER> to exit...");
   getchar();
   return 0;
}
