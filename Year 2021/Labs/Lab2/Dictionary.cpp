#include "Dictionary.h"
#include<cmath>
#include<string.h>
#include<iostream>
using namespace std;

Dictionary::Dictionary(){
    N = ARRAY_SIZE;
    A = new Entry[N];
    for(int i=0 ; i<N ; i++){
        A[i].frequency = NULL_ENTRY;
    }
}

int Dictionary::hashValue(char *key){
    int hash = 0;
    double digest = 0;
    int size = 0;
    for(int i=0 ; key[i] != '\0' ; i++){
        size ++;
    }
    for(int i= size-1 ; i>=0 ; i--){
        digest = (digest*HORNER_CONSTANT + (key[i] >= 'A' ? key[i]-'A'+'a' : key[i])*PHI) - floor(digest*HORNER_CONSTANT + (key[i] >= 'A' ? key[i]-'A'+'a' : key[i])*PHI);
    }
    hash = ((int)floor(ARRAY_SIZE*digest))%ARRAY_SIZE ;
    return hash;
}

int Dictionary::findFreeIndex(char *key){
    int index = hashValue(key);
    for(int i=0 ; i<ARRAY_SIZE ; i++ ){
        cout << "Checking at index " << ((index+i)%ARRAY_SIZE) << endl ;
        if(A[(index+i)%ARRAY_SIZE].frequency == NULL_ENTRY || A[(index+i)%ARRAY_SIZE].frequency == TOMBSTONE || strcasecmp(key,A[(index+i)%ARRAY_SIZE].key) == 0){
            cout << "Placing at index " << ((index+i)%ARRAY_SIZE) << endl ;
            return (index+i)%ARRAY_SIZE;
        }
    }
    cout << "Array full" << endl;
    return -1;
}

struct Entry* Dictionary::get(char *keya){
    int index = hashValue(keya);
    if(index >= 0){
        for(int i=0 ; i<ARRAY_SIZE ; i++ ){
            if(A[(index+i)%ARRAY_SIZE].frequency == NULL_ENTRY){
                return new Entry;
            }
            if(A[(index+i)%ARRAY_SIZE].frequency == TOMBSTONE){
                continue;
            }
            if(strcasecmp(keya,A[(index+i)%ARRAY_SIZE].key) == 0){
                return &A[(index+i)%ARRAY_SIZE] ;
            }
        }
        return new Entry;
    }
    else{
        return new Entry;
    }
}

bool Dictionary::put(struct Entry e){
    int index = findFreeIndex(e.key);
    if(index >=0 ){
        if(A[index].frequency == TOMBSTONE || A[index].frequency == NULL_ENTRY){
            for(int i=0 ; e.key[i]!='\0' ; i++){
                A[index].key[i] = e.key[i];
            }
            A[index].frequency = e.frequency;
        }
        else{
            A[index].frequency += e.frequency;
        }
        cout << "Hash value of " << e.key << " is " << index << endl ; 
        return true;
    }
    else{
        return false;
    }
}

bool Dictionary::remove(char *key){
    int index = hashValue(key);
    if(index>=0){
        for(int i=0 ; i<ARRAY_SIZE ; i++){
            if(A[(index+i)%ARRAY_SIZE].frequency == NULL_ENTRY){
                return false;
            }
            if(A[(index+i)%ARRAY_SIZE].frequency == TOMBSTONE){
                continue;
            }
            if(strcasecmp(key,A[(index+i)%ARRAY_SIZE].key) == 0){
                A[(index+i)%ARRAY_SIZE].frequency = TOMBSTONE;
                return true;
            }
        } 
        return false;
    }
    else{
        return false;
    }
}