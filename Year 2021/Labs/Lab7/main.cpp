#include "heap.h"
#include <iostream>
#include <random>
#include <chrono>
#include <string>
using namespace std;

int main()
{
    srand(0);
    for (int N = 5*1e2; N <= 5*1e5; N *= 10)
    {
        int* arr = new int[N];
        for(int i=0 ; i<N ;i++){
            arr[i] = rand()%100000;
        }
        heap h(arr,N,2*N);
        int swaps = 0;
        auto start = std::chrono::system_clock::now();
        for(int i=0 ; i<N/5 ; i++){
            h.insert(rand()%100000, swaps);
        }
        auto end = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        string time = to_string(elapsed.count());
        cout <<  N << "," << swaps << ","<< time << endl;  
        delete[] arr;
    }
}