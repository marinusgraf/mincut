#pragma once
#include "adjmat.h"

int bfs(std::vector<std::vector<int>> &e, std::vector<int> &p, int s, int t)
{
    std::vector<int> curr = {s}, next, f(n, -1);
    std::vector<bool> vis(n, false);
    vis[s] = true;
    while (curr.size() > 0)
    {
        next = {};
        for (int &u : curr)
        {
            for (int v = 0; v < n; ++v)
            {
                if (e[u][v] > 0 && !vis[v])
                {
                    if (u == s)
                    {
                        f[v] = e[u][v];
                    }
                    else
                    {
                        f[v] = std::min(f[u], e[u][v]);
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

int st_maxflow(std::vector<std::vector<int>> e, int s, int t)
{
    int f, m = 0;
    std::vector<int> p(n, -1), d;
    while ((f = bfs(e, p, s, t)) > 0)
    {
        m += f;
        for (int v = t; v != s; v = p[v])
        {
            e[p[v]][v] -= f;
        }
    }
    return m;
}

int edmonds_karps(std::vector<std::vector<int>> &e)
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
