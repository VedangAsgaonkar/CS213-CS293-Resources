#include "DynamicDequeue.h"

DynamicDequeue::DynamicDequeue(){
    N = INIT_SIZE;
    f = 0;
    r = 0;
    A = new double[N];
}

bool DynamicDequeue::isEmpty(){
    if( f == r ){
        return true;
    }
    else{
        return false;
    }
}

bool DynamicDequeue::isFull(){
    if( (r>f) ? ((r-f)%N == N-1 ) : ( (f-r)%N == 1 ) ){
        return true;
    }
    else{
        return false;
    }
}

void DynamicDequeue::grow(){
    unsigned int oldN = N;
    N = nextSizeExponential();
    // N = nextSizeLinear();
    double* B = new double[N];
    unsigned int j=0;
    for(unsigned int i=f ; i != r ; i = (i+1)%oldN){
        B[j] = A[i];
        j++;
    }
    f = 0 ;
    r = j ;
    delete[] A;
    A = B ;
}

unsigned int DynamicDequeue::size(){
    return (r>f) ? (r-f) : ((N+r)-f)%N ;
}

void DynamicDequeue::insertFront(double x){
    if(isFull()){
        grow();
        A[r] = x ;
        r = (r+1)%N ;
    }
    else{
        A[r] = x ;
        r = (r+1)%N ;
    }
}

void DynamicDequeue::insertRear(double x){
    if(isFull()){
        grow();
        f = (f>0) ? (f-1) : (N-1) ;
        A[f] = x ;
    }
    else{
        f = (f>0) ? (f-1) : (N-1) ;
        A[f] = x ;
    }
}

bool DynamicDequeue::removeFront(double *x){
    if(isEmpty()){
        x = nullptr;
        return false;
    }
    else{
        r = (r>0) ? (r-1) : (N-1) ;
        *x = A[r] ;
        return true ;
    }
}

bool DynamicDequeue::removeRear(double *x){
    if(isEmpty()){
        x = nullptr;
        return false;
    }
    else{
        *x = A[f];
        f = (f+1)%N ;
        return true;
    }
}

bool DynamicDequeue::front(double *x){
    if(isEmpty()){
        x = nullptr;
        return false;
    }
    else{
        unsigned int front = (r>0) ? (r-1) : (N-1) ;
        *x = A[front] ;
        return true ;
    }
}

bool DynamicDequeue::rear(double *x){
    if(isEmpty()){
        x = nullptr;
        return false;
    }
    else{
        *x = A[f];
        return true;
    }
}