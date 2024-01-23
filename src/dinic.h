#pragma once
#include "adjmat.h"

std::vector<int> level(std::vector<std::vector<int>> e, int s, int t)
{
    std::vector<int> frontier = {s}, next, d(n, -1);
    d[s] = 0;
    for (int l = 1; frontier.size() > 0; ++l)
    {
        next = {};
        for (int &u : frontier)
        {
            for (int v = 0; v < n; ++v)
            {
                if (e[u][v] > 0 && d[v] == -1)
                {
                    next.push_back(v);
                    d[v] = l;
                }
            }
        }
        frontier = next;
    }
    return d;
}

int dfs(std::vector<std::vector<int>> &e, std::vector<int> d, int f, int u, int t)
{
    if (u == t)
    {
        return f;
    }
    for (int v = 0; v < n; ++v)
    {
        if (d[v] == d[u] + 1 && e[u][v] > 0)
        {
            int tmp;
            if( (tmp = dfs(e, d, std::min(f, e[u][v]), v, t)) > 0) 
            {
                e[u][v] -= tmp;
                e[v][u] += tmp;
                return tmp;
            }
            
        }
    }
    return 0;
}

int st_maxflow(std::vector<std::vector<int>> e, int s, int t)
{
    int m = 0, f; 
    std::vector<int> d, p(n);
    while ((d = level(e, s, t))[t] != -1)
    {
        while ((f = dfs(e, d, INT_MAX, s, t)) > 0)
        {
            m += f;
        }
    }
    return m;
}

int dinic(std::vector<std::vector<int>> e)
{
    int mincut = INT_MAX;
    for (int s = 0; s < n; ++s)
    {
        for (int t = s + 1; t < n; ++t)
        {
            mincut = std::min(mincut, st_maxflow(e, s, t));
        }
    }
    return mincut;
}

