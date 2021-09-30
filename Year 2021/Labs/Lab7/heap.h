#ifndef _HEAP_H_
#define _HEAP_H_

#define MAX_DIM 1<<20

class heap
{
private:
    int *arr;
    long long int size;
    long long int card;

public:
    heap(long long int size);
    heap(int *in_arr, long long int card ,long long int size);
    bool insert(int elem, int& swaps);
    int getMin() const;
    int deleteMin(int& swaps);
    ~heap();
};

#endif _HEAP_H_