#include "hashTable.h"
#include "hash.h"
#define PRINT_OUTPUT 1

// Main
// argv[1] = nome del dataset da processare e salvare in tabella hash
// argv[2] = dimensione della tabella hash (m)
int main (int argc, char* argv[])
{
   char *line[LINE_LENGTH];
   uint8_t *key;
   uint8_t *buf;
   const char *separator = ",";
   uint32_t digest;
   int n;
   clock_t start, end;

   //dimensione dell'area primaria della tabella hash
   m = atoi(argv[2]);

   key = (uint8_t*) calloc(KEY_LENGTH, sizeof(uint8_t));

   printf("\nLettura del file %s\n\n",argv[1]);

   FILE* fin = fopen(argv[1] ,"r");
   if(fin == NULL ) goto end;

   //conteggio il numero di elementi da inserire in tabella hash
   n = 0;
   while ( fgets((char*)line, LINE_LENGTH, fin)!= NULL ) n++;
   rewind(fin);

   ////////// PROVA FUNZIONI HASH //////////
   while (fgets((char*)line,LINE_LENGTH,fin)!= NULL )
   {
      // legge la chiave (parte che precede il separatore)
      buf = (uint8_t*)strtok((char*)line, separator);
      // legge il valore (parte che segue il separatore)
      key = (uint8_t*)strtok(NULL, separator);
      // calcola l'hash digest della key letta
      digest = hash_modulus(key,71327);
      if(PRINT_OUTPUT) printf("hash_modulus('%.*s')\t->\tDigest: %lu\t",KEY_LENGTH,key,(long unsigned int)digest);
      digest = hash_murmur3_32(key,KEY_LENGTH,123);
      if(PRINT_OUTPUT) printf("hash_murmur('%.*s')\t->\tDigest: %lu",KEY_LENGTH,key,(long unsigned int)digest);
      if(PRINT_OUTPUT) printf("\n");
   }

   ////////// COSTRUZIIONE TABELLA HASH //////////
   printf("\nCostruzione della tabella hash...\n");
   start = clock();

   rewind(fin);

   if ((hashTable = malloc(m * sizeof(Node *))) == 0)
   {
      printf ("Hash table out of memory\n");
      goto end;
   }
   for(int i=0; i<m; i++) hashTable[i] = NULL;

   while (fgets((char*)line,LINE_LENGTH,fin)!= NULL )
   {
      // legge la chiave (parte che precede il separatore)
      buf = (uint8_t*)strtok((char*)line, separator);
      // legge il valore (parte che segue il separatore)
      key = (uint8_t*)strtok(NULL, separator);
      // inserisce l'elemento in tabella hash
      insertNode(key);
   }

   end = clock();

   rewind(fin);

   if(PRINT_OUTPUT) printTable(n,1);
   if(PRINT_OUTPUT) printf("\n\nTempo di esecuzione medio insert: %f sec\n",(double)(end-start)/CLOCKS_PER_SEC/n);


   ////////// CANCELLAZIONE ELEMENTI (data.csv) //////////
   /*printf("Cancellazione di alcuni elementi dalla tabella hash...\n");
   char* delKey1 = "AAAA";
   char* delKey2 = "CCCC";
   char* delKey3 = "3000";
   char* delKey4 = "CAAA";
   deleteNode((uint8_t*)delKey1);
   deleteNode((uint8_t*)delKey2);
   deleteNode((uint8_t*)delKey3);
   deleteNode((uint8_t*)delKey4);
   if(PRINT_OUTPUT) printTable(n,0);*/


   ////////// RICERCA //////////
   /*printf("\n\nRicerca degli elementi nella tabella hash...\n");
   start = clock();

   uint32_t f;
   int findCount = 0;
   while (fgets((char*)line,LINE_LENGTH,fin)!= NULL )
   {
      // legge la chiave (parte che precede il separatore)
      buf = (uint8_t*)strtok((char*)line, separator);
      // legge il valore (parte che segue il separatore)
      key = (uint8_t*)strtok(NULL, separator);
      // inserisce l'elemento in tabella hash
      f = findNode(key);
      if(f==0)
      {
         //printf("error: valore del dataset di costruzione non trovato.");
         //exit(0);
      }
      else findCount++;
   }

   end = clock();

   if(PRINT_OUTPUT) printf("\nNumero di elementi trovati: %d",findCount);
   if(PRINT_OUTPUT) printf("\nTempo di esecuzione medio search: %f sec\n",(double)(end-start)/CLOCKS_PER_SEC/n);*/

   free(hashTable);

   free(key);
   free(buf);
   fclose(fin);
   printf("\n");

   end:printf("<ENTER> to exit...");
   getchar();
   return 0;
}
