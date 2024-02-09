#pragma once
#include "adjmat.h"

int bfs(Graph &g, std::vector<int> &p, int s, int t)
{
    std::vector<int> curr = {s}, next, f(g.n, -1);
    std::vector<bool> vis(g.n, false);
    vis[s] = true;
    while (curr.size() > 0)
    {
        next = {};
        for (int &u : curr)
        {
            for (int v = 0; v < g.n; ++v)
            {
                if (g.c[u][v] > 0 && !vis[v])
                {
                    if (u == s)
                    {
                        f[v] = g.c[u][v];
                    }
                    else
                    {
                        f[v] = std::min(f[u], g.c[u][v]);
                    }
                    p[v] = u;
                    vis[v] = true;
                    next.push_back(v);
                }
            }
        }
        curr = next;
    }
    return f[t];
}

int st_maxflow(Graph g, int s, int t)
{
    int f, m = 0;
    std::vector<int> p(g.n, -1), d;
    while ((f = bfs(g, p, s, t)) > 0)
    {
        m += f;
        for (int v = t; v != s; v = p[v])
        {
            g.c[p[v]][v] -= f;
            g.c[v][p[v]] += f;
        }
    }
    return m;
}

int edmonds_karps(Graph &g)
{
    int mincut = INT_MAX;
    for (int t = 1; t < g.n; ++t)
    {
        mincut = std::min(mincut, st_maxflow(g, 0, t));
    }
    return mincut;
}
