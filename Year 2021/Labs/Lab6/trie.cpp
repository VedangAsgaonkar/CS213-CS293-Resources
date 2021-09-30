#include "trie.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

trie::trie(std::vector<std::string> &in_text)
    : text(in_text)
{
    root = new node();
    root->parent = new edge();
    root->parent->string_num = -1;
    // cout << root << endl;
    for (int i = 0; i < text.size(); i++) // for every string in text
    {
        cout << text[i] << endl;
        int index = 0;
        node *curr_node = root;
        bool complete = false;
        while (index < text[i].length()) // while the string has not ended
        {
            edge *curr_edge = curr_node->edge_list;
            bool found = false;
            while (curr_edge != nullptr) // while the current node has edges
            {

                if (text[curr_edge->string_num][curr_edge->start] != text[i][index])
                {
                    curr_edge = curr_edge->next;
                }
                else
                {
                    found = true;
                    for (int j = curr_edge->start; j < curr_edge->end; j++) // iterate over the characters of the edge
                    {
                        if (index == text[i].length())
                        {
                            // cout << "in here" << endl;
                            node *nextnode = curr_edge->child;
                            curr_edge->child = new node();
                            curr_edge->child->parent = curr_edge;
                            curr_edge->child->isEnd = true;
                            curr_edge->child->edge_list = new edge();
                            curr_edge->child->edge_list->origin = curr_edge->child;
                            nextnode->parent = curr_edge->child->edge_list;
                            curr_edge->child->edge_list->child = nextnode;
                            curr_edge->child->edge_list->start = j;
                            curr_edge->child->edge_list->string_num = curr_edge->string_num;
                            curr_edge->child->edge_list->end = curr_edge->end;
                            curr_edge->end = j;
                            curr_edge->string_num = i;
                            complete = true;
                            break;
                        }
                        if (complete)
                            break;
                        if (text[curr_edge->string_num][j] != text[i][index])
                        {
                            node *nextnode = curr_edge->child;
                            curr_edge->child = new node();
                            curr_edge->child->parent = curr_edge;
                            curr_edge->child->edge_list = new edge();
                            curr_edge->child->edge_list->origin = curr_edge->child;
                            curr_edge->child->edge_list->child = nextnode;
                            nextnode->parent = curr_edge->child->edge_list;
                            curr_edge->child->edge_list->start = j;
                            curr_edge->child->edge_list->string_num = curr_edge->string_num;
                            curr_edge->child->edge_list->end = curr_edge->end;
                            curr_edge->end = j;
                            curr_edge->child->edge_list->next = new edge();
                            curr_edge->child->edge_list->next->origin = curr_edge->child;
                            curr_edge->child->edge_list->next->child = new node();
                            curr_edge->child->edge_list->next->child->parent = curr_edge->child->edge_list->next;
                            curr_edge->child->edge_list->next->child->isEnd = true;
                            curr_edge->child->edge_list->next->string_num = i;
                            curr_edge->child->edge_list->next->start = index;
                            curr_edge->child->edge_list->next->end = text[i].length();
                            complete = true;
                            break;
                        }
                        if (complete)
                            break;
                        index++;
                        // cout << index << " in " << endl;
                    }
                    // cout << "here" << endl;
                    if (complete)
                        break;
                    // cout << index << " " << text[i].length() << endl;
                    if (index == text[i].length())
                    {
                        curr_edge->child->isEnd = true;
                        curr_edge->string_num = i;
                        complete = true;
                        // cout << "came out" << endl;
                    }
                    else
                    {
                        curr_node = curr_edge->child;
                        curr_edge = curr_node->edge_list;
                        found = false;
                    }
                }
                if (complete)
                    break;
            }
            if (complete)
                break;
            if (!found) // if there was no suitable edge
            {
                // cout << "hello" << endl;
                if (curr_node->edge_list == nullptr)
                {
                    curr_node->edge_list = new edge();
                    curr_node->edge_list->origin = curr_node;
                    curr_node->edge_list->child = new node();
                    curr_node->edge_list->string_num = i;
                    curr_node->edge_list->start = index;
                    curr_node->edge_list->end = text[i].length();
                    curr_node->edge_list->child->isEnd = true;
                    curr_node->edge_list->child->parent = curr_node->edge_list;
                    break;
                }
                else
                {
                    edge *active_edge = curr_node->edge_list;
                    while (active_edge->next != nullptr)
                    {
                        active_edge = active_edge->next;
                    }
                    active_edge->next = new edge();
                    active_edge->next->origin = active_edge->origin;
                    active_edge->next->child = new node();
                    active_edge->next->string_num = i;
                    active_edge->next->start = index;
                    active_edge->next->end = text[i].length();
                    active_edge->next->child->isEnd = true;
                    active_edge->next->child->parent = active_edge->next;
                    break;
                }
            }
        }
    }
}

int trie::find(const std::string &str) const
{
    // cout << str << endl;
    int index = 0;
    node *curr_node = root;
    bool complete = false;
    edge *curr_edge = curr_node->edge_list;
    while (index < str.length()) // while the string has not ended
    {
        bool found = false;
        while (curr_edge != nullptr) // while the current node has edges
        {
            // cout << curr_edge->string_num << " " << curr_edge->start << " " << curr_edge->end << endl;
            if (text[curr_edge->string_num][curr_edge->start] != str[index])
            {
                curr_edge = curr_edge->next;
            }
            else
            {
                // cout << "inside" << endl;
                found = true;
                for (int j = curr_edge->start; j < curr_edge->end; j++) // iterate over the characters of the edge
                {
                    // cout << "index " << index << endl;
                    if (index == str.length())
                    {
                        // cout << " : here : " << endl;
                        if (curr_edge->child->isEnd && j == curr_edge->end - 1)
                        {
                            // cout << "h0" << endl;
                            return curr_edge->string_num;
                        }
                        else
                        {
                            while (curr_node->parent->string_num != -1 && !curr_node->isEnd)
                            {
                                curr_node = curr_node->parent->origin;
                            }

                            // cout << "h1" << endl;
                            return curr_node->parent->string_num;
                        }
                        complete = true;
                        break;
                    }
                    if (complete)
                        break;
                    if (text[curr_edge->string_num][j] != str[index])
                    {
                        // cout << "h2" << endl;
                        while (curr_node->parent->string_num != -1 && !curr_node->isEnd)
                        {
                            curr_node = curr_node->parent->origin;
                        }
                        return curr_node->parent->string_num;
                        complete = true;
                        break;
                    }
                    if (complete)
                        break;
                    // cout << "reached" << endl;
                    index++;
                }
                if (complete)
                    break;
                // cout << "out" << endl;
                if (index == str.length())
                {
                    // cout << "yeah here" << endl;
                    // curr_edge->child->isEnd = true;
                    complete = true;
                    // cout << "sure" << endl;
                }
                else
                {
                    curr_node = curr_edge->child;
                    curr_edge = curr_node->edge_list;
                    found = false;
                }
            }
            if (complete)
                break;
        }
        if (complete)
            break;
        if (!found) // if there was no suitable edge
        {
            // cout << "h3" << endl;
            while (curr_node->parent->string_num != -1 && !curr_node->isEnd)
            {
                curr_node = curr_node->parent->origin;
            }
            return curr_node->parent->string_num;
        }
    }
    return curr_edge->string_num;
}