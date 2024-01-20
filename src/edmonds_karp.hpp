#include "util.hpp"

std::vector<int> shortest_path(std::vector<std::vector<int>> &e, int s, int t)
{
    int n = e[0].size();
    std::vector<bool> visited(n, false);
    visited[s] = true;
    std::vector<int> frontier = {s}, next, parent(n, 0);
    std::iota(parent.begin(), parent.end(), 0);
    while (frontier.size() > 0)
    {
        next = {};
        for (int &v : frontier)
        {
            for (int u = 0; u < n; ++u)
            {
                if (e[v][u] > 0 && !visited[u])
                {
                    parent[u] = v;
                    visited[u] = true;
                    next.push_back(u);
                    if (u == t) return parent;
                }
            }
        }
        frontier = next;
    }
    return parent;
}

int augment (std::vector<std::vector<int>> &e, int s, int t)
{
    std::vector<int> parent = shortest_path(e, s, t);
    if (parent[t] == t) return 0;
    int bottleneck{INT_MAX};
    int v = t;
    do
    {
        bottleneck = std::min(bottleneck, e[v][parent[v]]);
        v = parent[v];
    }
    while (v != s);
    v = t;
    do
    {
        e[v][parent[v]] -= bottleneck;
        e[parent[v]][v] = e[v][parent[v]];
        v = parent[v];
    }
    while (v != s);
    return bottleneck;
}

int st_maxflow(std::vector<std::vector<int>> e, int s, int t)
{
    int maxflow = 0;
    int augmented;
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
