#include "util.hpp"

std::vector<int> shortest_path(std::vector<std::vector<int>> &e, int s, int t)
{
    int n = e[0].size();
    std::vector<bool> visited(n, false);
    visited[s] = true;
    std::vector<int> frontier = {s}, next, p(n, 0);
    std::iota(p.begin(), p.end(), 0);
    while (frontier.size() > 0)
    {
        next = {};
        for (int &v : frontier)
        {
            for (int u = 0; u < n; ++u)
            {
                if (e[v][u] > 0 && !visited[u])
                {
                    p[u] = v;
                    visited[u] = true;
                    next.push_back(u);
                    if (u == t) return p;
                }
            }
        }
        frontier = next;
    }
    return p;
}

int augment (std::vector<std::vector<int>> &e, int s, int t)
{
    std::vector<int> p = shortest_path(e, s, t);
    if (p[t] == t) return 0;
    int bottleneck{INT_MAX};
    int v = t;
    do
    {
        bottleneck = std::min(bottleneck, e[v][p[v]]);
        v = p[v];
    }
    while (v != s);
    v = t;
    do
    {
        e[v][p[v]] -= bottleneck;
        e[p[v]][v] = e[v][p[v]];
        v = p[v];
    }
    while (v != s);
    return bottleneck;
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

int edmonds_karps(std::vector<std::vector<int>> &e)
{
    int n = e[0].size();
    int mincut = INT_MAX;   
    for (int s = 0; s < n; ++s)
    {
        for (int t = s+1; t < n; ++t)
        {
            mincut = std::min(mincut, st_maxflow(e, s, t));
        }
    }
    return mincut;
}
