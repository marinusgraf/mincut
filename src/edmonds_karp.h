#pragma once
#include "adjmat.h"

int bfs(Graph &g, std::vector<Edge*> &p, int s, int t)
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
                int v = e.dest;
                if (e.cap > 0 && !vis[v])
                {
                    if (u == s)
                    {
                        f[v] = e.cap;
                    }
                    else
                    {
                        f[v] = std::min(f[u], e.cap);
                    }
                    p[v] = &e;
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
    std::vector<Edge*> p(g.n), d;
    while ((f = bfs(g, p, s, t)) > 0)
    {
        m += f;
        for (int v = t; v != s; v = p[v]->src)
        {
            p[v]->cap -= f;
            p[v]->rev->cap = -p[v]->cap;
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
