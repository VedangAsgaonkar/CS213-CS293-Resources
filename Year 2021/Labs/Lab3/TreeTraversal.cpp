#include<iostream>
#include"TreeTraversal.h"
using namespace std;

Tree::Tree(){
    root = nullptr;
}

struct Node* Tree::deduce_tree(char *pre_order, char *in_order, int N){
    char ch = pre_order[0];
    int rootpos = -1 ;
    for(int i=0 ; i<N ; i++){
        if(in_order[i] == ch){
            rootpos = i ;
            break;
        }
    }
    if(rootpos==-1){
        return nullptr;
    }
    else{
        if(N==1){;
            Node* n= new Node();
            n->key = ch ;
            return n;
        }
        else{
            Node* n= new Node();
            n->key = ch;
            Node* l = nullptr;
            Node* r = nullptr;
            if(rootpos>0){
                l = deduce_tree(&pre_order[1], in_order, rootpos);
                
                if(l==nullptr){
                    return nullptr;
                }
                
            }
            if(rootpos<N-1){
                r = deduce_tree(&pre_order[rootpos+1], &in_order[rootpos+1] , N-1-rootpos);
                if(r==nullptr){
                    return nullptr;
                }
            }
            n->left = l;
            n->right = r;
            if(l!=nullptr) n->left->parent = n;
            if(r!=nullptr) n->right->parent = n;
            return n;
        }
    }
}

void Tree::external(struct Node* nd,TraversalType_e tt){
    cout << nd->key;
}
void Tree::left(struct Node* nd,TraversalType_e tt){
    if(tt==PRE_ORDER){
        cout << nd->key;
    }
}
void Tree::below(struct Node* nd,TraversalType_e tt){
    if(tt==IN_ORDER){
        cout << nd->key;
    }
}
void Tree::right(struct Node* nd,TraversalType_e tt){
    if(tt==PRE_ORDER){
        cout << nd->key;
    }
}

void Tree::traverse(struct Node* nd, TraversalType_e tt){
    if(nd->left == nullptr && nd->right == nullptr){
        external(nd,tt);
    }
    else{
        if(nd->left != nullptr){
            left(nd->left,tt);
            traverse(nd->left,tt);
        }
        below(nd,tt);
        if(nd->right != nullptr){
            traverse(nd->right,tt);
            right(nd->right,tt);            
        }
        if(tt==POST_ORDER){
            cout << nd->key;
        }
    }
}

int main(){
    char str1[32];
    char str2[32];
    cin >> str1  ;
    cin >> str2;
    int l1 = 0, l2=0 ;
    for(int i=0 ; str1[i] != '\0' ; i++){
        l1 ++ ;
    }
    for(int i=0 ; str2[i] != '\0' ; i++){
        l2 ++ ;
    }
    if(l1==l2){
        Tree* T = new Tree(str1, str2, l1);
        if( T->root != nullptr){
            T->traverse(T->root, POST_ORDER);
            cout << endl;
        }
        else{
            cout << "Incorrect input" <<endl; 
        }
    }

}