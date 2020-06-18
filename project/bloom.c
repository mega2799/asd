#include <stdlib.h>
#include "bloom.h"
//BF insertion 

void insertElem(const uint8_t* elem){
    int index = 0 ;                     
    while (index <= k) {                
        filter[hashFunction(elem, index++)] = 1;
    }
} 

//bf search
bool checkElem(const uint8_t* elem){
    int index = 1;
    while(index <= k){
        if(!filter[hashFunction(elem,index++)]) return false;
    }
    return true;
}  

void buildFilter(const uint8_t** dataset){
    filter = calloc(m,sizeof(bool));
    int index;      //ma va messo 0 o 1 ?  
    for (int o = 0; o < n;++o) { // n = valori nel file 65 000
        index = 1;
        while (index <= k) {
            filter[hashFunction(dataset[o],index++)]=1;
        }
    }
}

void selfCheck(const uint8_t** dataset, FILE* fout)
{
    int i;
    int good = 0;
    for (int j = 0; j < n; ++j)
    {
        i = 1;
        if (filter[hashFunction(dataset[j], i)])
        {
            ++good;
        }
    }
    fprintf(fout, "True positives (self-check): %d\n", good);
}

void nonElementsCheck(const uint8_t** dataset, FILE* fout){
    int exist = 0;
    int negat= 0;
    for (int i = 0; i < non_elements; ++i) {
        if (checkElem(dataset[i])) exist++;
        else negat++;
    }
  

    fprintf(fout, "True negatives: %d\n", negat);
    fprintf(fout, "False positives: %d\n", exist);
    fprintf(fout, "FPR: %f", (double)exist / non_elements);
}
