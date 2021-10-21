#include <iostream>
#include <vector>
#include <random>
#include <unordered_set>
#include <tuple>
#include <deque>
#include <stack>

std::vector<std::vector<int>> randomGraph(int n)
{
    std::vector<std::vector<int>> graph;
    for (int i = 0; i < n; i++)
    {
        std::vector<int> v;
        graph.push_back(v);
    }
    int count = 0;
    while (count != 2 * n)
    {
        int start = rand() % n;
        int end = rand() % n;
        if (start == end)
            continue;
        bool flag = false;
        for (auto &u : graph[start])
        {
            if (u == end)
            {
                flag = true;
            }
        }
        if (!flag)
        {
            graph[start].push_back(end);
            graph[end].push_back(start);
            count++;
        }
    }
    return graph;
}

enum TraversalType
{
    BFS,
    DFS
};

int select(std::deque<int> &S, TraversalType T)
{
    if (T == TraversalType::DFS)
    {
        return S.back();
    }
    else if (T == TraversalType::BFS)
    {
        return S.front();
    }
}

void remove(std::deque<int> &S, TraversalType T)
{
    if (T == TraversalType::DFS)
    {
        S.pop_back();
    }
    else if (T == TraversalType::BFS)
    {
        S.pop_front();
    }
}

void traverse(std::vector<std::vector<int>> &graph, TraversalType T)
{
    std::vector<bool> visited(graph.size(), false);
    int i = 0;
    while (i < graph.size())
    {
        if (!visited[i])
        {
            std::deque<int> S;
            S.push_back(i);
            std::cout << i << std::endl;
            visited[i] = true;
            while (!S.empty())
            {
                for (int j=0 ; j < graph[select(S, T)].size() ; j++)
                {
                    int u = graph[select(S,T)][j];
                    // std::cout << "in with u=" << u << std::endl;
                    if (!visited[u])
                    {
                        std::cout << u << std::endl;
                        S.push_back(u);
                        visited[u] = true;
                    }
                    // std::cout << "top is " << select(S, T) << std::endl;
                }
                // std::cout << "removing " << select(S, T) << std::endl;
                remove(S, T);
            }
        }
        i++;
    }
}

std::vector<int> dfsForOddCycle(std::vector<std::vector<int>> &graph)
{
    std::vector<int> out;
    std::vector<bool> visited(graph.size(), false);
    std::vector<int> depth(graph.size());
    std::vector<int> parent(graph.size());
    int i = 0;
    while (i < graph.size())
    {
        if (!visited[i])
        {
            std::stack<int> S;
            S.push(i);
            visited[i] = true;
            parent[i] = -1;
            depth[i] = 0;
            while (!S.empty())
            {
                for (int j=0 ; j < graph[S.top()].size() ; j++)
                {
                    int u = graph[S.top()][j];
                    if (!visited[u])
                    {
                        visited[u] = true;
                        depth[u] = depth[S.top()] + 1;
                        parent[u] = S.top();
                        S.push(u);
                    }
                    else
                    {
                        if ((depth[S.top()] - depth[u]) % 2 == 0)
                        {
                            int x = S.top();
                            while (x != u)
                            {
                                out.push_back(x);
                                x = parent[x];
                            }
                            out.push_back(x);
                            return out;
                        }
                    }
                }
                S.pop();
            }
        }
        i++;
    }
    return out;
}

int main()
{
    std::cout << "Adjacency List" << std::endl;
    std::vector<std::vector<int>> graph = randomGraph(7);
    for (int i = 0; i < graph.size(); i++)
    {
        std::cout << i << " : ";
        for (int j = 0; j < graph[i].size(); j++)
        {
            std::cout << graph[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "BFS" << std::endl;
    traverse(graph, TraversalType::BFS);
    std::cout << "DFS" << std::endl;
    traverse(graph, TraversalType::DFS);
    std::cout << "odd cycle" << std::endl;
    std::vector<int> cycle = dfsForOddCycle(graph);
    for (int i = 0; i < cycle.size(); i++)
    {
        std::cout << cycle[i] << std::endl;
    }
}