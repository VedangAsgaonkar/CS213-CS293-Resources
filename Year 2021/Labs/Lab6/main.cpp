#include <bits/stdc++.h>
#include "trie.h"
#include<fstream>
using namespace std;

int main()
{
    cout << "Enter file name" << endl;
    string filename;
    cin >> filename;
    fstream infile;
    infile.open(filename, ios::in);
    vector<string> text;    
    cout << "Inserting into trie" << endl;
    do
    {
        string in ;
        infile >> in ;
        text.push_back(in);
    }while (!infile.eof());
    
    infile.close();
    cout << "Finding in trie" << endl;
    trie *T = new trie(text);
    for (int i = 0; i < text.size(); i++)
        cout << T->find(text[i]) << endl;

    cout << "ENTERING INTERACTIVE MODE" << endl;
    while(true){
        string in;
        cin >> in ;
        if(in[0]=='!'){
            break;
        }
        else{
            cout << T->find(in) << endl;
        }
    }
}