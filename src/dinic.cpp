#include "dinic.h"
#include "adjmat.h"

std::vector<int> level(std::vector<std::vector<int>> e, int s, int t)
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

int augment(std::vector<std::vector<int>> &e, std::vector<int> &p, int s, int t)
{
    int bottleneck = INT_MAX;
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
    int f = 0; 
    std::vector<int> d, p(n);
    while ( (d = level(e, s, t))[t] != -1)
    {
        while (dfs(e, p, d, s, t))
        {
            f += augment(e, p, s, t);
        }
    }
    return f;
}

int dinic(std::vector<std::vector<int>> e)
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
    std::cout << dinic(e) << std::endl;
    
}