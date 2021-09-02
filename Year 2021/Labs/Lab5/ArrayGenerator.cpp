#include<iostream>
#include"QuickSort.h"
#include<random>
#include<cmath>
using namespace std;

int* ArrayGenerator::randomArray(int n){
    int* arr = new int[n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand();
    }    
    return arr;
}

//Consider a sorted array V of length n, having its elements from the set S
//Now consider any permutation P of this array i.e. P : S -> S is a bijection
//Produce a directed graph in having its nodes as 0,1,2 ... n-1 and there is an edge
//from i to j iff P(V)[j] = V[i]
//that is each edge points from an index in the array to the index to which the element
//from the original index was displaced
//then each connected component of this graph is a cycle
//the minimum number of swaps needed to restore a cycle of size r to its original form is r-1
//hence if the graph has k connected component cycles, then n-k swaps are needed to restore the permutation P(V)
//to the original array V.
//We use the minimum number of swaps as out metric for the amount by which the sorted array is disturbed


int* ArrayGenerator::almostSorted(int n, double fraction){
    int* arr = new int[n];
    arr[0] = abs(rand())%100;
    for (int i = 1; i < n; i++)
    {
        arr[i] = arr[i-1]+abs(rand())%100;
    }
    int m = (int)floor(n*fraction);
    int index = rand()%(n-m-2);
    int t = arr[index];
    for(int i=index ; i<index+m-1 ; i++){
        arr[i] = arr[i+1] ;
    }
    arr[index+m-1] = t;   
    return arr; 
}

int* ArrayGenerator::almostReversed(int n, double fraction){
    int* arr = new int[n];
    arr[n-1] = abs(rand())%100;
    for (int i = n-1; i >=1; i--)
    {
        arr[i-1] = arr[i]+abs(rand())%100;
    }
    int m = (int)floor(n*fraction);
    int index = rand()%(n-m-2);
    int t = arr[index];
    for(int i=index ; i<index+m-1 ; i++){
        arr[i] = arr[i+1] ;
    }
    arr[index+m-1] = t;   
    return arr; 
}