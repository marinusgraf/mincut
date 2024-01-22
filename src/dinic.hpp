#include "util.hpp"

std::vector<int> level(std::vector<std::vector<int>> e, int s, int t)
{
    int n = e[0].size();
    std::vector<bool> visited(n, false);
    visited[s] = true;
    std::vector<int> frontier = {s}, next, dist(n, -1);
    int level = 0;
    dist[s] = 0;
    while (frontier.size() > 0)
    {
        next = {};
        for (int &v : frontier)
        {
            for (int u = 0; u < n; ++u)
            {
                if (e[v][u] > 0 && !visited[u])
                {
                    dist[u] = ++level;
                    visited[u] = true;
                    next.push_back(u);
                    if (u == t) return dist;
                }
            }
        }
        frontier = next;
    }
    return dist;
}

bool dfs(std::vector<std::vector<int>> e, std::vector<int>& p, std::vector<int> d, int s, int t)
{
    if (s == t) return true;
    for (int v = 0; v < e[s].size(); ++v)
    {
        if (e[s][v] > 0 && (d[v] == d[s] + 1))
        {
            p[v] = s;
            dfs(e, p, d, v, t);
        } 
    }
    return false;
}

int augment(std::vector<std::vector<int>> &e, int s, int t)
{
    int f = 0, n = e[0].size(); 
    std::vector<int> d, p(n);
    std::iota(p.begin(), p.end(), 0);
    d = level(e, s, t);
    if (d[t] == -1) return 0;
    int bottleneck;
    while (dfs(e, p, d, s, t))
    {
        bottleneck = INT_MAX;
        int v;
        for (v = t; v != s; v = p[v])
        {
            bottleneck = std::min(bottleneck, e[v][p[v]]);
        }
        v = t;
        for (v = t; v != s; v = p[v])
        {
            e[v][p[v]] -= bottleneck;
            e[p[v]][v] = e[v][p[v]];
        }
        f += bottleneck;
    }
    return f;
}

int st_maxflow(std::vector<std::vector<int>> e, int s, int t)
{
    int maxflow = 0, augmented;
    while ((augmented = augment(e, s, t)) > 0)
    {   
        maxflow += augmented;
    }
    return maxflow;
}

int dinic(std::vector<std::vector<int>> &e)
{
    int n = e[0].size(), mincut = INT_MAX;
    for (int s = 0; s < n; ++s)
    {
        for (int t = s + 1; t < n; ++t)
        {
            mincut = std::min(mincut, st_maxflow(e, s, t));
        }
    }
    return mincut;
}