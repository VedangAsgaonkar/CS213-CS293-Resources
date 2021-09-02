#include"QuickSort.h"
#include<iostream>
#include<random>
#include<bits/stdc++.h>
using namespace std;

std::pair<long long int,long long int> Sort::QSP1(int* arr, int n)
{
    if(n==1){
        return {0,0};
    }
    else{
        long long int swap = 0;
        long long int comp = 0 ;
        int i=0;
        int j=n-1;
        int pivot = arr[0];
        while(i<=j){
            if(arr[i]>=pivot && arr[j]<pivot){ 
                comp += 2;
                swap += 2;
                int t = arr[i];
                arr[i] = arr[j];
                arr[j] = t;
                i++;
                j--;
                continue;
            }
            if(arr[i]<pivot){
                comp += 1;
                i++;
            }
            if(arr[j]>=pivot){
                comp += 1;
                j--;
            }
        }
        if(i>0){
            std::pair<long long int,long long int> a = QSP1(&arr[i],n-i);
            std::pair<long long int,long long int> b = QSP1(arr,i);
            return {swap+a.first+b.first,comp+a.second+b.second};
        }
        else{
            std::pair<long int,long int> a = QSP1(&arr[1],n-1);
            return {swap+a.first,comp+a.second};
        }       
    }
}
/*
learnt a new thing here. If it is to be sorted in ascending order and had we done <= or >, we would have got stuck on an array where
the first element is maximum. Similarly with < or >=, we would get stuck on an array with first element as minimum.
*/

std::pair<long long int,long long int> Sort::QSRP(int* arr, int n){
    if(n==1){
        return {0,0};
    }
    else{
        long long int swap = 0;
        long long int comp = 0 ;
        int i=0 ; 
        int j = n-1;
        int x = rand()%n;   
        if(x==n-1){
            x--;
        }
        int pivot = arr[x];
        // cout << "pivot : " << pivot << endl;
        while(i<=j){
            if(arr[i]>=pivot && arr[j]<pivot){ 
                comp += 2;
                swap += 2;
                int t = arr[i];
                arr[i] = arr[j];
                arr[j] = t;
                i++;
                j--;
                continue;
            }
            if(arr[i]<pivot){
                comp += 1;
                i++;
            }
            if(arr[j]>=pivot){
                comp += 1;
                j--;
            }
        }
        // cout << "i : " << i << "j : " << j << endl;
        // for (int k = 0; k < n; k++)
        // {
        // cout << arr[k];
        // }
        // cout << endl;
        if(i>0 && j<n-1){
            // cout << "Hemlo" << endl;
            std::pair<long long int,long long int> a = QSRP(&arr[i],n-i);
            std::pair<long long int,long long int> b = QSRP(arr,i);  
            return {swap+a.first+b.first,comp+a.second+b.second};         
        }
        if(i==0){      
            int t = arr[x];
            arr[x] = arr[0];
            arr[0] = t ;     
            swap ++; 
            std::pair<long long int,long long int> a = QSRP(&arr[1],n-1);
            return {swap+a.first,comp+a.second};

        }
        if(j==n-1){
            int t = arr[x];
            arr[x] = arr[n-1];
            arr[n-1] = t ; 
            swap++;
            std::pair<long long int, long long int> a = QSRP(arr,n-2);
            return {swap+a.first,comp+a.second};
        }
    }
}

std::pair<long long int,long long int> Sort::BuSo(int* arr, int n){
    long long int comp = 0;
    long long int swap = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n-1; j++)
        {   comp ++;
            if(arr[j]>arr[j+1])
            {
                int t = arr[j];
                arr[j] = arr[j+1];
                arr[j+1]=t;
                swap++;
            }   
        }   
        
    }
    return {swap,comp};    
}