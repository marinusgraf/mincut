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

int dfs(std::vector<std::vector<int>> &e, std::vector<int> &d, std::vector<bool> &vis, int f, int &u, int &t)
{
    vis[u] = true;
    if (u == t)
    {
        return f;
    }
    for (int v = 0; v < n; ++v)
    {
        if (!vis[v] && d[v] == d[u] + 1 && e[u][v] > 0)
        {
            f = std::min(f, e[u][v]);
            int push;
            if ((push = dfs(e, d, vis, f, v, t)) > 0)
            {
                f = std::min(f, push);
                e[u][v] -= f;
                return std::min(f, push);
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
        vis = std::vector<bool>(n, false);
        while ( (f = dfs(e, d, vis, INT_MAX, s, t)) > 0)
        {
            m += f;
        }
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
