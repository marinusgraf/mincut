#pragma once
#include "adjmat.h"

int bfs(Graph &g, std::vector<Edge> &p, int s, int t)
{
    std::vector<int> curr = {s}, next, f(g.n, -1);
    std::vector<bool> vis(g.n, false);
    vis[s] = true;
    while (curr.size() > 0)
    {
        next = {};
        for (int &u : curr)
        {
            for (Edge &e : g.adj[u])
            {
                int v = e.to;
                if (g.cap[e.id] > 0 && !vis[v])
                {
                    if (u == s)
                    {
                        f[v] = g.cap[e.id];
                    }
                    else
                    {
                        f[v] = std::min(f[u], g.cap[e.id]);
                    }
                    p[v] = e;
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
    std::vector<Edge> p(g.n), d;
    while ((f = bfs(g, p, s, t)) > 0)
    {
        m += f;
        for (int v = t; v != s; v = p[v].from)
        {
            g.cap[p[v].id] -= f;
            g.cap[p[v].id + 1] += f;
        }
    }
    return m;
}

int edmonds_karp(Graph &g)
{
    int mincut = INT_MAX;
    for (int s = 0; s < g.n; ++s)
    {
        for (int t = s + 1; t < g.n; ++t)
        {
            mincut = std::min(mincut, st_maxflow(g, s, t));
        }
    }
    return mincut;
}
