#include"BST.h"
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<cstdio>
#include<chrono>
#include<random>
#include<string>
using namespace std;

BST::BST(){
    root = nullptr;
}

void BST::external(struct Node* nd,TraversalType_e tt){
    cout << nd->key << endl;
}
void BST::left(struct Node* nd,TraversalType_e tt){
    if(tt==PRE_ORDER){
        cout << nd->key <<endl;
    }
}
void BST::below(struct Node* nd,TraversalType_e tt){
    if(tt==IN_ORDER){
        cout << nd->key << endl;
    }
}
void BST::right(struct Node* nd,TraversalType_e tt){
    if(tt==POST_ORDER){
        cout << nd->key << endl;
    }
}

void BST::traverse(struct Node* nd, TraversalType_e tt){
    if(nd->left == nullptr && nd->right == nullptr){
        external(nd,tt);
    }
    else{
        left(nd,tt);
        if(nd->left != nullptr){
            traverse(nd->left,tt);
        }
        below(nd,tt);
        if(nd->right != nullptr){
            traverse(nd->right,tt);           
        }
        right(nd,tt);
    }
}

struct Node *BST::min(){
    Node* n= root;
    if(n==nullptr){
        return nullptr;
    }
    else{
        while(n->left != nullptr){
            n = n->left;
        }
    }
    return n;
}

struct Node *BST::max(){
    Node* n= root;
    if(n==nullptr){
        return nullptr;
    }
    else{
        while(n->right != nullptr){
            n = n->right;
        }
    }
    return n;
}

struct Node *BST::search(char *s){
    Node* n = root;
    while(true){
        if(n==nullptr){
            break;
        }
        int val = strcmp(n->key,s);
        if(val==0){
            return n;
        }
        else if(val>0){
            n = n->left;
        }
        else{
            n = n->right;
        }
    }
    return nullptr;
}

bool BST::insert(struct Node n){
    if(root==nullptr){
        Node* m = new Node();
        strcpy(m->key,n.key);
        root = m;
        root->height = 1 ;
        return true;
    }
    Node* node = root;
    while(true){
        int val = strcmp(node->key,n.key);
        if(val==0){
            return false;
        }
        else if(val>0){
            if(node->left==nullptr){
                Node* m = new Node();
                strcpy(m->key,n.key);
                node->left = m ;
                m->parent = node;
                m->height = 1;
                node = m;
                while (node->parent!=nullptr){
                    cout << node->parent->key << endl;
                    if(node->parent->left==nullptr ){
                        node->parent->height = node->parent->right->height + 1 ;
                    }
                    else if(node->parent->right==nullptr){
                        node->parent->height = node->parent->left->height + 1 ;
                    }
                    else{
                        node->parent->height = std::max( node->parent->left->height , node->parent->right->height )+1;
                    }     
                    node = node->parent;                 
                } 
                return true;
            }
            else{
                node = node->left;
            }
        }
        else{
            if(node->right==nullptr){
                Node* m = new Node();
                strcpy(m->key,n.key);
                node->right = m ;
                m->parent = node;
                m->height = 1;
                node = m;
                while (node->parent!=nullptr){
                    cout << node->parent->key << endl;
                    if(node->parent->left==nullptr ){
                        node->parent->height = node->parent->right->height + 1 ;
                    }
                    else if(node->parent->right==nullptr){
                        node->parent->height = node->parent->left->height + 1 ;
                    }
                    else{
                        node->parent->height = std::max( node->parent->left->height , node->parent->right->height )+1;
                    }  
                    node = node->parent;                  
                }
                return true;
            }
            else{
                node = node->right;
            }
        }
    }
}

struct Node *BST::successor(struct Node *n){
    Node* k = BST::search(n->key);
    if(k->right!=nullptr){
        Node* m= k->right;
        while(m->left != nullptr){
            m = m->left;
        }        
        return m;
    }
    else{
        Node* m = k ;
        while(m->parent!=nullptr){
            if(m->parent->left == m){
                return m->parent;
            }
            m = m->parent;
        }
        return nullptr;
    }
}

struct Node *BST::predecessor(struct Node *n){
    Node* k = BST::search(n->key);
    if(k->left!=nullptr){
        Node* m= k->left;
        while(m->right != nullptr){
            m = m->right;
        }        
        return m;
    }
    else{
        Node* m = k ;
        while(m->parent!=nullptr){
            if(m->parent->right == m){
                return m->parent;
            }
            m = m->parent;
        }
        return nullptr;
    }
}

bool BST::remove(char *s){
    Node* n = BST::search(s);
    Node* par = nullptr;
    if(n==nullptr){
        return false;
    }   
    else{
        if(n->left==nullptr && n->right ==nullptr){
            par = n->parent;
            if(par==nullptr){
                root = nullptr;
            }
            else{
                if(n->parent->left == n){
                    n->parent->left = nullptr;
                }
                else{
                    n->parent->right = nullptr;
                }
            }
            delete n;
        }
        else if(n->left==nullptr && n->right!=nullptr){
            par = n->parent;
            if(par==nullptr){
                root = n->right;
            }
            else{
                if(n->parent->left == n){
                    n->parent->left = n->right;
                }
                else{
                    n->parent->right = n->right;
                }
            }

            delete n;
        }
        else if(n->left!=nullptr && n->right==nullptr){
            par = n->parent;
            if(par==nullptr){
                root = n->left;
            }
            else{
                if(n->parent->left == n){
                    n->parent->left = n->left;
                }
                else{
                    n->parent->right = n->left;
                }
            }
            delete n;
        }
        else{
            Node* s = BST::successor(n);
            Node* p = BST::predecessor(n);
            char* str = s->key;
            n->key = p->key;
            BST::remove(s->key);
            n->key = str;
        }
        while (par!=nullptr ){
            if(par->left==nullptr && par->right!=nullptr){
                par->height = par->right->height + 1 ;
            }
            else if(par->right==nullptr && par->left!=nullptr){
                par->height = par->left->height + 1 ;
            }
            else if(par->right==nullptr && par->left==nullptr){
                par->height = 1;
            }
            else{
                par->height = std::max( par->left->height , par->right->height )+1;
            }  
            par = par->parent;                    
        }  
        return true;
    }
}

char* intToString(int x){
    char* str = new char[32];
    int i=0 ;
    while(x>0){
        str[i] = x%10+'0';
        x = x/10;
        i++;
    }
    str[i] = '\0';
    return str;
}

int main(){    

    //time tests    
    cout << "Performing time checks" << endl;
    cout << "Time check outputs" << endl ;
    for(int i=1; i<=10 ; i++){
        auto start = std::chrono::system_clock::now();
        BST* T = new BST();
        srand(0);
        for(int j=0 ; j<100000*i ; j++){
            int num = rand()%1000000;
            Node* n =new Node();
            int a = 10;
            char *intStr = intToString(a);
            n->key = intStr;
            T->insert(*n);
        }
        auto end = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        delete T;
        string time = to_string(elapsed.count());
        cout << "input size " << i << ", time " << time << endl;
    }    

    //interactive mode
    cout << "Done" << endl;
    cout << "Entering interactive mode" << endl;
    BST* T = new BST();
    while(true){
        char str[32];
        cin >> str;
        if(str[0]=='#'){ //exit and print traversal
            break;
        }
        else if(str[0]=='!'){ //delete
           T->remove(&str[1]);
        }
        else if(str[0]=='?'){ //search and return height
            Node* n = T->search(&str[1]);
            if(n!=nullptr){
                cout << n->height << endl;
            }
            else{
                cout << "Not found" << endl;
            }            
        }
        else if(str[0]=='+'){ //successor
            Node* n =new Node();
            n->key = &str[1];
            Node* m = T->successor(n);
            if(m!=nullptr){
                cout << m->key << endl;
            }
            else{
                cout << "Not found" << endl;
            }
        }
        else if(str[0]=='-'){ //predecessor
            Node* n =new Node();
            n->key = &str[1];
            Node* m = T->predecessor(n);
            if(m!=nullptr){
                cout << m->key << endl;
            }
            else{
                cout << "Not found" << endl;
            }
        }
        else{ //insert
            Node* n =new Node();
            n->key = str;
            T->insert(*n);
        }       
        // cout << "ok" << endl;
    }
    cout << "Inorder Traversal" << endl;
    T->traverse(T->root, IN_ORDER) ;
}
