#include<iostream>
#include<chrono>
#include<string>
#include<cmath>
#include<fstream>
#include"DynamicDequeue.h"
using namespace std;

int main(){

    // code to store various run times
    // code has to be run twice, once with exponential, other time with linear
    string s("");
    for(int i=0 ; i<=19 ; i++){
        auto start = std::chrono::system_clock::now();

        DynamicDequeue d;
        
        for(int j=0 ; j<  round(pow(2,i)) ; j++){
            d.insertFront(j);
        }

        auto end = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        string power = to_string(i);
        string time = to_string(elapsed.count());
        s = s + power + "," + time + "\n";
    }

    fstream out_file;
    // out_file.open("linear.csv", ios::out) ;
    out_file.open("exponential.csv", ios::out) ;
    out_file << s ;
    out_file.close();
}
