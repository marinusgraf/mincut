#include "flow.h"
#include "adjmat.h"

std::vector<int> bfs(std::vector<std::vector<int>> &e, std::vector<int> &p, int s, int t)
{
    std::vector<bool> visited(n, false);
    std::vector<int> curr = {s}, next, d(n, -1);
    for (int l = 0; curr.size() > 0; ++l)
    {
        next = {};
        for (int &u : curr)
        {
            d[u] = l;
            visited[u] = true;
            for (int v = 0; v < n; ++v)
            {
                if (e[u][v] > 0 && !visited[v])
                {
                    p[v] = u;
                    next.push_back(v);
                }
            }
        }
        curr = next;
    }
    return d;
}

bool dfs(std::vector<std::vector<int>> e, std::vector<int>& p, std::vector<int> d, int s, int t)
{
    std::vector<int> stack;
    stack.push_back(s);
    int u;
    while(stack.size() > 0)
    {
        u = stack[stack.size() - 1];
        stack.pop_back();
        if (u == t) return true;
        for (int v = 0; v < e[u].size(); ++v)
        {
            if (e[u][v] > 0 && (d[v] == d[u] + 1))
            {
                stack.push_back(v);
                p[v] = u;
            }
        }
    }
    return false;
}

int augment(std::vector<std::vector<int>> &e, std::vector<int> p, int s, int t)
{
    int bottleneck{INT_MAX};
    int v;
    for (v = t; v != s; v = p[v])
    {
        bottleneck = std::min(bottleneck, e[v][p[v]]);
    }
    for (v = t; v != s; v = p[v])
    {
        e[v][p[v]] -= bottleneck;
        e[p[v]][v] = e[v][p[v]];
    }
    return bottleneck;
}

int edmonds_karps(std::vector<std::vector<int>> &e)
{
    int mincut = INT_MAX;   
    for (int s = 0; s < n; ++s)
    {
        for (int t = s + 1; t < n; ++t)
        {
            int f = 0;
            std::vector<int> p(n, -1), d;
            while (bfs(e, p, s, t)[t] != -1)
            {
                f += augment(e, p, s, t);
            }
            mincut = std::min(mincut, f);
        }
    }
    return mincut;
}

int dinic(std::vector<std::vector<int>> e)
{
    int mincut = INT_MAX;
    for (int s = 0; s < n; ++s)
    {
        for (int t = s + 1; t < n; ++t)
        {
            int f = 0;
            std::vector<int> p(n,-1), d;
            for (d = bfs(e, p, s, t); d[t] != -1; d = bfs(e, p, s, t))
            {
                while (dfs(e, p, d, s, t))
                {   
                    f += augment(e, p, s, t);
                }
            }
            mincut = std::min(mincut, f);
        }
    }
    return mincut;
}
