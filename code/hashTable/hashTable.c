#include "hashTable.h"

// nota: l'implementazione suppone coincidenza tra chiave e valore
// quindi key = val

// funzione che modula il digest di una funzione hash in base alla dimensione
// della tabella hash, in modo che lo spazio di indirizzamento coincida con m
uint32_t hashMapping(uint32_t h)
{
    return h % m;
}

// funzione che calcola la funzione hash utilizzata dalla hash table
uint32_t hashFunction(const uint8_t* key)
{
    return hashMapping(hash_murmur3_32(key,KEY_LENGTH,123));
}


// allocate node for val and insert in the table
void insertNode(const uint8_t* val)
{
   Node *p, *p0;
   uint32_t bucket;  // hash table index of chain with val

   // insert node at beginning of list
   bucket = hashFunction(val);
   if ((p = malloc(sizeof(Node))) == 0)
   {
      fprintf (stderr, "out of memory (insertNode)\n");
      exit(1);
   }
   p0 = hashTable[bucket];
   hashTable[bucket] = p;
   p->next = p0;
   p->data = strdup(val);
}


// delete node containing val from the table
void deleteNode(const uint8_t* val)
{
   Node *p0, *p;
   uint32_t bucket;
   uint32_t chain_pos;

   // find the node to delete
   bucket = hashFunction(val);
   p = p0 = hashTable[bucket];
   chain_pos = findNode(val);

   // elemento non trovato
   if(chain_pos == 0) return;
   // l'elemento è l'unico nodo della catena
   if(p->next == NULL)
   {
       free(p);
       hashTable[bucket] = NULL;
   }
   //catena composta da più elementi
   else
   {
      //l'elemento è in testa alla lista
      if(chain_pos==1)
      {
         hashTable[bucket] = p->next;
         free(p);
         return;
      }
      //l'elemento non è in testa alla lista
      else
      {
         for(int j = 1; j < chain_pos; j++)
         {
            p0 = p;
            p = p->next;
         }
         p0->next = p->next;
         free(p);
      }

   }
}

// find node containing val
// ritorna 0 se non trova il valore, diversamente da 1 a n in base alla posizione nella chain
uint32_t findNode (const uint8_t* val)
{
   Node *p;
   uint32_t i=0;

   p = hashTable[hashFunction(val)];
   while (p)
   {
      i++;
      if(strncmp((char *)p->data,(char *)val,KEY_LENGTH) == 0) return i;
      else p = p->next;
   }
   return 0;
}

// stampa a video la tabella hash
void printTable(int n, int stats)
{
    Node *p;
    int i,j,chainLength,maxChainLength,nullBuckets;
    double num,den,chiSquaredSum = 0;
    chainLength = 0;
    maxChainLength = 0;
    nullBuckets = 0;
    for(i=0; i<m; i++)
    {
        p = hashTable[i];
        printf("\n[Bucket %d]: ",i);
        j = 0;
        while(p)
        {
            j++;
            printf("(Nodo %d: '%.*s')-->",j,KEY_LENGTH,p->data);
            p = p->next;
        }
        if(j==0) nullBuckets++;
        if(j > maxChainLength) maxChainLength = j;
        num = pow((double)j-(double)n/m,2);
        den = (double)n/m;
        chiSquaredSum += num/den;
        chainLength += j;
    }

    if(stats)
    {
        printf("\n");
        printf("\nFattore di carico: %.2f",(double)n/m);
        printf("\nLunghezza massima delle catene di overflow: %d",maxChainLength);
        printf("\nLunghezza media delle catene di overflow: %.2f",(double)chainLength/(m-nullBuckets));
        printf("\nChi-squared sum: x^2 = %.2f",chiSquaredSum);
    }

}
