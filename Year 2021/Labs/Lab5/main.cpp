#include<iostream>
#include"QuickSort.h"
#include<chrono>
#include<bits/stdc++.h>
using namespace std;

int main(){
    srand(time(0));
    int N = 1e4;
    for (int i = 1; i <= 20; i++)
    {
        int* arr = ArrayGenerator::almostSorted(i*N,0.1);

        auto start = std::chrono::system_clock::now();

        std::pair<long long int,long long int> data = Sort::QSP1(arr,i*N);
    
        auto end = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        delete[] arr;

        string time = to_string(elapsed.count());
        cout << i*N << "," << time << "," << data.first << "," << data.second << endl;
    }
        
}