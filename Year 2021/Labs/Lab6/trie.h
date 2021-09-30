#ifndef _TRIE_H_
#define _TRIE_H_

#include<string>
#include<vector>

struct node;
struct edge;

class edge{
    public:
    int string_num ;
    int start ;
    int end ;
    node* origin;
    node* child;
    edge* next;
    edge(){
        origin = nullptr;
        next = nullptr;
        child = nullptr;
    }
};

class node{
    public:
    edge* edge_list;
    edge* parent;
    bool isEnd;
    node(){
        edge_list = nullptr;
        isEnd = false;
        parent = nullptr;
    }
};

class trie
{
private:
    node* root;
    std::vector<std::string>& text;
public:
    trie(std::vector<std::string>& in_text);
    int find(const std::string& str) const;
};

#endif