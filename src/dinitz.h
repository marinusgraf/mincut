#pragma once
#include "network.h"

std::vector<int> level(Network &g, int s)
{
    std::vector<int> frontier = {s}, next, l(g.n, -1);
    l[s] = 0;
    int v;
    for (int level = 1; frontier.size() > 0; ++level)
    {
        next = {};
        for (int &u : frontier)
        {
            for (int idx : g.adj[u])
            {
                v = g.e[idx].to;
                if (g.e[idx].cap > 0 && l[v] == -1)
                {
                    next.push_back(v);
                    l[v] = level;
                }
            }
        }
        frontier = next;
    }
    return l;
}

int dfs(Network &g, std::vector<int> &l, int flow, int u, int t)
{
    if (u == t)
    {
        return flow;
    }
    int v;
    for (int idx : g.adj[u])
    {
        int &cap = g.e[idx].cap;
        int &r_cap = g.e[idx ^ 1].cap;
        v = g.e[idx].to;
        if (cap > 0 && l[v] == l[u] + 1)
        {
            int push = std::min(flow, cap);
            int f;
            if ( (f = dfs(g, l, push, v, t)) > 0)
            {
                cap -= f;
                r_cap += f;
                return f;
            }
            else
            {
                l[v] = -1;
            }
        }
    }
    return 0;    
}

int st_maxflow(Network g, int s, int t)
{
    int m = 0, f = 0;
    std::vector<int> l;
    while ((l = level(g, s))[t] != -1)
    {
       while ((f = dfs(g, l, INT_MAX, s, t)) > 0)
       {
            m += f;
       }  
    }
    return m;
}

int dinitz(Network g)
{
    int mincut = INT_MAX;
    for (int t = 1; t < g.n; ++t)
    {
        mincut = std::min(mincut, st_maxflow(g, 0, t));
    }
    return mincut;
}
