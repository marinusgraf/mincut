#include "adjmat.h"
#include "edmonds_karp.h"

int bfs(std::vector<std::vector<int>> &e, std::vector<int> &p, int s, int t)
{
    std::vector<int> curr = {s}, next, d(n, -1), f(n, -1);
    d[s] = 0;
    for (int l = 0; curr.size() > 0; ++l)
    {
        next = {};
        for (int &u : curr)
        {
            for (int v = 0; v < n; ++v)
            {
                if (e[u][v] > 0 && d[v] == -1)
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
                    d[v] = l;
                    next.push_back(v);
                }
            }
        }
        curr = next;
    }
    return f[t];
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
            e[v][p[v]] += f;
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

int main(int argc, char** argv)
{
    if (argc != 2) 
    {
        std::cout << "invalid input" << std::endl;
        exit(EXIT_FAILURE);
    }
    file_to_adjmat(std::string{argv[1]});
    std::cout << edmonds_karps(e) << std::endl;
}