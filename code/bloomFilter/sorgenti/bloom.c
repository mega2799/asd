#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "hash.h"


#include "bloom.h"
//BF insertion 

void insertElem(const uint8_t* elem){
    int index = 0 ;
                                        //elem dovrebbe essere una stringa
    while (index<=k) filter[hashFunction(elem,index++)] = 1;
} 

//bf search
bool checkElem(const uint8_t* elem){
    int index = 0;
    while(index <= k){
        if(!filter[hashFunction(elem,index++)]) return false;
    }
    return true;
}   
void buildFilter(const uint8_t** dataset){
    bool* filter = (bool*)calloc(m,sizeof(bool*));
    int index = 0;
    while(index < m){
        insertElem(dataset[index]);
    }
}
void selfCheck(const uint8_t** dataset, FILE* fout){
    return;
}
void nonElementsCheck(const uint8_t** dataset, FILE* fout){
    return;
}