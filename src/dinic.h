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

int dfs(std::vector<std::vector<int>> &e, std::vector<int> &d, std::vector<bool> &vis, int flow, int u, int t)
{
    if (u == t)
        return flow;
    vis[u] = true;
    for (int v = 0; v < n; ++v)
    {
        if (!vis[v] && e[u][v] > 0 && d[v] == d[u] + 1)
        {
            int push = std::min(flow, e[u][v]);
            int f;
            if ( (f = dfs(e, d, vis, push, v, t)) > 0)
            {
                e[u][v] -= f;
                e[v][u] += f;
                return f;
            }
        }
    }
    return 0;    
}

int st_maxflow(std::vector<std::vector<int>> e, int s, int t)
{
    int m = 0, f = 0;
    std::vector<int> d, p(n);
    std::vector<bool> vis;
    while ((d = level(e, s, t))[t] != -1)
    {
       do
       {
            vis = std::vector<bool>(n, false);
            m += f;
       } while ((f = dfs(e, d, vis, INT_MAX, s, t)) > 0);
       
    }
    return m;
}

int dinic(std::vector<std::vector<int>> &e)
{
    int mincut = INT_MAX;
    for (int t = 1; t < n; ++t)
    {
        mincut = std::min(mincut, st_maxflow(e, 0, t));
    }
    return mincut;
}
