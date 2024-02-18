#pragma once
#include "adjmat.h"
#include "timer.h"
#include <thread>
#include <random>

inline Graph contract(Graph &g, int t)
{
    static std::mt19937 engine(std::random_device{}());
    std::vector<int> v(g.n);
    for (int k = 0; k < g.n; ++k)
    {
        v[k] = k;
    }
    int x, y, p;
    while (g.n != t)
    {
        x = std::discrete_distribution<int>{g.d.begin(), g.d.end()}(engine);
        y = std::discrete_distribution<int>{g.w[x].begin(), g.w[x].end()}(engine);
        g.d[x] = g.d[x] + g.d[y] - 2*g.w[x][y];
        g.d[y] = g.w[x][y] = g.w[y][x] = 0;
        for (int k = 0; k < g.n; ++k)
        {   
            if (v[k] == y)
            {
                p = k;
            }
            if (v[k] == x || v[k] == y) 
                continue;
            
            g.w[x][v[k]] += g.w[y][v[k]];
            g.w[v[k]][x] = g.w[x][v[k]];
            g.w[y][v[k]] = g.w[v[k]][y] = 0;
        }
        v[p] = v[--g.n];
    }
    if (t == 2)
    {
        g.w[0][1] = g.d[x];
        return g;
    }
    auto w = std::vector<std::vector<int>>(g.n,std::vector<int>(g.n));
    auto d = std::vector<int>(g.n);
    for (int i = 0; i < g.n; ++i)
    {
        d[i] = g.d[v[i]];
        for (int j = 0; j < g.n; ++j)
        {
            w[i][j] = g.w[v[i]][v[j]];
        }
    }
    g.w = w;
    g.d = d;
    return g;
    
}

inline int karger(Graph g)
{
    g = contract(g, 2);
    return g.w[0][1];
}

inline int karger_stein(Graph g)
{
    if (g.n <= 6)
    {
        return karger(g);
    }
    else
    {
        int t = std::ceil(g.n / std::sqrt(2) + 1);
        return std::min
        (
            karger_stein(contract(g, t)),
            karger_stein(contract(g, t))
        );
    }
}

int main(int argc, char** argv)
{

    if (argc != 2) 
    {
        std::cout << "invalid or no input path" << std::endl;
        exit(EXIT_FAILURE);
    }
    Graph g = file_to_graph(std::string{argv[1]});
    int reps = log(g.n) * log(g.n);
    time_function(karger_stein, g, reps);
}