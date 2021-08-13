#include "Dictionary.h"
#include<iostream>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false) ; cin.tie(NULL) ; cout.tie(NULL) ;
    Dictionary Dict;
    while(true){
        char str[32];
        cin >> str;
        if(str[0]=='?'){
            Entry* e = Dict.get(&str[1]);
            cout << e->frequency << endl;
        }
        else if(str[0]=='!'){
            bool b = Dict.remove(&str[1]);
            cout << b << endl;
        }
        else if(str[0]=='#'){
            break;
        }
        else{
            Entry e;
            e.key = str;
            e.frequency = 1;
            bool b = Dict.put(e);
            cout << b << endl;
        }
    }
}