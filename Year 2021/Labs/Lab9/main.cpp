#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <stack>

struct Node
{
    std::string label;
    std::vector<Node *> adjacency_list;
    bool visited;
    Node *parent;
    Node()
    {
        visited = false;
        parent = nullptr;
    }
};

int main()
{
    std::cout << "Enter M : ";
    int M;
    std::cin >> M;
    std::cout << "Enter N : ";
    int N;
    std::cin >> N;

    std::vector<Node *> graph;
    for (int j = 1; j < N; j++)
    {
        for (int i = 1; i < M; i++)
        {
            Node *n = new Node();
            n->label = "(" + std::to_string(i) + "," + std::to_string(j) + ")";
            graph.push_back(n);
        }
    }

    std::cout << "Enter horizontal links" << std::endl;

    for (int j = 0; j < N ; j++)
    {
        for (int i = 0; i < M-1 ; i++)
        {
            int x;
            std::cin >> x;
            if (x == 0 && j >= 1 && j < N-1)
            {
                graph[i + (j - 1) * (M - 1)]->adjacency_list.push_back(graph[i + (j) * (M - 1)]);
                graph[i + (j) * (M - 1)]->adjacency_list.push_back(graph[i + (j - 1) * (M - 1)]);
            }
        }
    }

    std::cout << "Enter vertical links" << std::endl;

    for (int j = 0; j < N - 1; j++)
    {
        for (int i = 0; i < M ; i++)
        {
            int x;
            std::cin >> x;
            if (x == 0 && i >= 1 && i < M-1 )
            {
                graph[i - 1 + j * (M - 1)]->adjacency_list.push_back(graph[i + j * (M - 1)]);
                graph[i + j * (M - 1)]->adjacency_list.push_back(graph[i - 1 + j * (M - 1)]);
            }
        }
    }

    std::queue<Node *> Q;
    Q.push(graph[0]);
    graph[0]->visited = true;
    std::string final_label = "(" + std::to_string(M - 1) + "," + std::to_string(N - 1) + ")";
    Node *n = nullptr;
    bool flag = false;
    while (!Q.empty())
    {
        n = Q.front();
        Q.pop();
        if (n->label == final_label)
        {
            flag = true;
            break;
        }
        for (Node *u : n->adjacency_list)
        {
            if (!u->visited)
            {
                u->visited = true;
                u->parent = n;
                Q.push(u);
            }
        }
    }

    std::stack<std::string> path;

    if (flag)
    {
        while (n != nullptr)
        {
            path.push(n->label);
            n = n->parent;
        }
    }

    while (!path.empty())
    {
        std::cout << path.top();
        path.pop();
    }
}