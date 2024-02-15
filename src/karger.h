#pragma once
#include "adjmat.h"
#include <random>

Graph contract(Graph g, int t)
{
    std::vector<bool> merged(g.n, false);
    static std::mt19937 engine(std::random_device{}());
    std::vector<int> p(g.n);
    for (int k = 0; k < g.n; ++k)
    {
        p[k] = k;
    }
    int u, v;
    while (g.n != t)
    {
        u = std::discrete_distribution<int>{g.d.begin(), g.d.end()}(engine);
        v = std::discrete_distribution<int>{g.w[u].begin(), g.w[u].end()}(engine);
        g.d[u] = g.d[u] + g.d[v] - 2*g.w[u][v];
        g.d[v] = g.w[u][v] = g.w[v][u] = 0;
        for (int w = 0; w < g.n; ++w)
        {
            if (w == u || w == v) continue;
            g.w[u][w] += g.w[v][w];
            g.w[w][u] += g.w[w][v];
            g.w[v][w] = g.w[w][v] = 0;
        }
        p[v] = p[--g.n];
    }
    auto w = std::vector<std::vector<int>>(n,std::vector<int>(n));
    auto d = std::vector<int>(n);
    int new_row = 0, new_col = 0;
    for (int old_row = 0; old_row < g.n && new_row < n; ++old_row)
    {
        if (merged[old_row])
        {
            continue;
        }
        new_col = 0;
        for (int old_col = 0; old_col < g.n && new_col < n; ++old_col)
        {
            if(merged[old_col])
            {
                continue;
            }
            w[new_row][new_col] = g.w[old_row][old_col];
            ++new_col;
        }
        ++new_row;
    }
    int k = 0;
    for (int i = 0; i < g.n; ++i)
    {
        if(merged[i])
        {
            continue;
        }
        d[k] = g.d[i];
        ++k;
    }
    g.n = n;
    g.w = w;
    g.d = d;
    return g;
    
}

int karger(Graph g)
{
    g = contract(g, 2);
    return g.w[0][1];
}

int karger_stein(Graph g)
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
