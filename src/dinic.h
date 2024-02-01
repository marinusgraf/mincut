#pragma once
#include "adjmat.h"

std::vector<int> level(Graph &g, int s, int t)
{
    std::vector<int> frontier = {s}, next, d(g.n, -1);
    d[s] = 0;
    for (int l = 1; frontier.size() > 0; ++l)
    {
        next = {};
        for (int &u : frontier)
        {
            for (Edge &e : g.adj[u])
            {
                if (e.cap > 0 && d[e.dest] == -1)
                {
                    next.push_back(e.dest);
                    d[e.dest] = l;
                }
            }
        }
        frontier = next;
    }
    return d;
}

int dfs(Graph &g, std::vector<int> &d, std::vector<bool> &vis, int flow, int u, int t)
{
    if (u == t)
        return flow;
    vis[u] = true;
    for (Edge &e : g.adj[u])
    {
        if (!vis[e.dest] && e.cap > 0 && d[e.dest] == d[u] + 1)
        {
            int push = std::min(flow, e.cap);
            int f;
            if ( (f = dfs(g, d, vis, push, e.dest, t)) > 0)
            {
                e.cap -= f;
                (*e.rev).cap += f;
                return f;
            }
        }
    }
    return 0;    
}

int st_maxflow(Graph g, int s, int t)
{
    int m = 0, f = 0;
    std::vector<int> d, p(g.n);
    std::vector<bool> vis;
    while ((d = level(g, s, t))[t] != -1)
    {
       do
       {
            vis = std::vector<bool>(g.n, false);
            m += f;
       } while ((f = dfs(g, d, vis, INT_MAX, s, t)) > 0);
       
    }
    return m;
}

int dinic(Graph &g)
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
