#pragma once
#include "adjmat.h"

std::vector<int> level(std::vector<std::vector<int>> &e, int s, int t)
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

int dfs(std::vector<std::vector<int>> &e, std::vector<int> d, std::vector<int> &f, int &u, int &t)
{
    if (f[u] == 0)
    {
        return 0;
    }
    if (u == t)
    {
        return INT_MAX;
    }
    for (int v = 0; v < n; ++v)
    {
        if (d[v] == d[u] + 1 && e[u][v] > 0)
        {
            f[v] = std::min(f[u], e[u][v]);
            int tmp;
            if ((tmp = dfs(e, d, f, v, t)) > 0)
            {
                f[v] = std::min(f[v], tmp);
                e[u][v] -= f[v];
                return f[v];
            }
            else
            {
                f[v] = 0;
            }
        }
    }
    f[u] = 0;
    return 0;
}

int st_maxflow(std::vector<std::vector<int>> e, int s, int t)
{
    int m = 0, x = 0;
    std::vector<int> d, f, p(n);
    while ((d = level(e, s, t))[t] != -1)
    {
        x = 0;
        do
        {
            f = std::vector<int>(n, -1);
            f[s] = INT_MAX;
            m += x;
        } while ((x = dfs(e, d, f, s, t)) > 0);
        
    }
    return m;
}

int dinic(std::vector<std::vector<int>> &e)
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
