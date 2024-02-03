#pragma once
#include "adjlist.h"

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
                if (g.cap[e.id] > 0 && d[e.to] == -1)
                {
                    next.push_back(e.to);
                    d[e.to] = l;
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
        if (!vis[e.to] && g.cap[e.id] > 0 && d[e.to] == d[u] + 1)
        {
            int push = std::min(flow, g.cap[e.id]);
            int f;
            if ( (f = dfs(g, d, vis, push, e.to, t)) > 0)
            {
                g.cap[e.id] -= f;
                g.cap[e.id + 1] += f;
                return f;
            }
        }
    }
    return 0;    
}

int st_maxflow(Graph g, int s, int t)
{
    int maxflow = 0, flow = 0;
    std::vector<int> d, p(g.n);
    std::vector<bool> vis;
    while ((d = level(g, s, t))[t] != -1)
    {
       do
       {
            vis = std::vector<bool>(g.n, false);
            maxflow += flow;
       } while ((flow = dfs(g, d, vis, INT_MAX, s, t)) > 0);
       
    }
    return maxflow;
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
