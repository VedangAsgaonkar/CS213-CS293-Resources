#include "heap.h"
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;

heap::heap(long long int size)
{
    if (size <= MAX_DIM)
    {
        this->arr = new int[size];
        this->size = size;
        this->card = 0;
    }
    else
    {
        this->arr = nullptr;
        this->size = 0;
        this->card = 0;
    }
}

heap::heap(int *in_arr, long long int card ,long long int size)
{
    if (size <= MAX_DIM)
    {
        this->size = size;
        this->card = 0;
        this->arr = new int[size];
        for (int i = 0; i < card; i++)
        {
            this->arr[i] = in_arr[i];
            this->card++;
        }
        int k = (int)floor(log2(card + 1)) - 1;
        for (int i = (1 << (k + 1)) - 2; i >= 0; i--)
        {
            int child1 = i * 2 + 1;
            int child2 = i * 2 + 2;
            if (child1 > card - 1)
            {
                continue;
            }
            else if (child2 > card - 1)
            {
                int t = arr[child1];
                arr[child1] = std::max(arr[i], t);
                arr[i] = std::min(arr[i], t);
            }
            else
            {
                int j = i;
                while (child1 < card)
                {
                    if (child2 < card)
                    {
                        int mn = min(arr[child2], arr[child1]);
                        if (mn < arr[j])
                        {
                            if (mn == arr[child1])
                            {
                                int t = arr[j];
                                arr[j] = arr[child1];
                                arr[child1] = t;
                                j = child1;
                            }
                            else
                            {
                                int t = arr[j];
                                arr[j] = arr[child2];
                                arr[child2] = t;
                                j = child2;
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                    else
                    {
                        if (arr[j] > arr[child1])
                        {
                            int t = arr[j];
                            arr[j] = arr[child1];
                            arr[child1] = t;
                            j = child1;
                        }
                        else
                        {
                            break;
                        }
                    }
                    child1 = j * 2 + 1;
                    child2 = j * 2 + 2;
                }
            }
        }
    }
    else
    {
        this->arr = nullptr;
        this->size = 0;
        this->card = 0;
    }
}

bool heap::insert(int elem, int& swaps)
{
    if (card < size)
    {
        arr[card] = elem;
        card++;
        swaps ++ ;
        int i = card - 1;
        while (i > 0)
        {
            int parent = (int)(ceil(i / 2)) - 1;
            if (arr[parent] <= arr[i])
            {
                break;
            }
            else
            {
                int t = arr[parent];
                arr[parent] = arr[i];
                arr[i] = t;
                i = parent;
                swaps ++ ;
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}

int heap::getMin() const
{
    return arr[0];
}

int heap::deleteMin(int& swaps)
{
    int m = arr[0];
    arr[0] = arr[card - 1];
    swaps ++ ;
    card--;
    int i = 0;
    int child1 = i * 2 + 1;
    int child2 = i * 2 + 2;
    while (child1 < card)
    {
        if (child2 < card)
        {
            int mn = min(arr[child2], arr[child1]);
            if (mn < arr[i])
            {
                if (mn == arr[child1])
                {
                    int t = arr[i];
                    arr[i] = arr[child1];
                    arr[child1] = t;
                    i = child1;
                    swaps ++ ;
                }
                else
                {
                    int t = arr[i];
                    arr[i] = arr[child2];
                    arr[child2] = t;
                    i = child2;
                    swaps ++ ;
                }
            }
            else
            {
                break;
            }
        }
        else
        {
            if (arr[i] > arr[child1])
            {
                int t = arr[i];
                arr[i] = arr[child1];
                arr[child1] = t;
                i = child1;
                swaps ++ ;
            }
            else
            {
                break;
            }
        }
        child1 = i * 2 + 1;
        child2 = i * 2 + 2;
    }
    return m;
}

heap::~heap()
{
    delete[] arr;
}