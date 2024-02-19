#include <numeric>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <random>
#include "timer.h"

struct UnionFind
{
    std::vector<int> parent, rank;

    UnionFind(int n)
    {
        parent = std::vector<int>(n);
        rank = std::vector<int>(n);
        for (int k = 0; k < n; ++k)
        {
            parent[k] = k;
            rank[k] = 0;
        }
    }

    int find(int x)
    {
        if (x != parent[x])
        {
            parent[x] = find(x);
        }
        return parent[x];
    }

    bool link(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
            return false;

        if (rank[x] < rank[y])
        {
            std::swap(x, y);
        }

        parent[y] = x;
        if (rank[x] == rank[y])
        {
            rank[x] += 1;
        }
        return true;
    }
};

struct Edge
{
    int from, to;
};

struct Graph
{
    int n, m;
    std::vector<Edge> e;
    std::vector<int> w;
};

Graph file_to_graph(std::string path)
{
    std::ifstream file(path);
    if (!file)
    {
        std::cerr << "Error: could not open file" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string line;
    while (std::getline(file, line))
    {
        if (line[0] != '#')
            break;
    }
    int n;
    int m;
    std::istringstream st(line);
    if (!(st >> n >> m))
    {
        std::cerr << ("Error, first line does not contain node and edge count") << std::endl;
        exit(EXIT_FAILURE);
    }
    std::vector<Edge> e(m);
    std::vector<int> w(m);
    int from, to, weight;
    for (int k = 0; std::getline(file, line); ++k)
    {
        std::istringstream st(line);
        if (!(st >> from >> to >> weight))
        {
            std::cerr << ("Error, first line does not contain node and edge count") << std::endl;
            exit(EXIT_FAILURE);
        }
        e[k] = Edge{from, to};
        w[k] = weight;
    }
    return Graph{n, m, std::move(e), std::move(w)};
}

Graph contract(Graph &g, const int t)
{
    UnionFind uf{g.n};
    static std::default_random_engine engine{std::random_device{}()};
    int rand_idx;
    std::discrete_distribution<int> dist{g.w.begin(), g.w.end()};
    auto label = std::vector<int>(g.n, -1);

    while (g.n != t)
    {
        rand_idx = dist(engine);
        g.n -= uf.link(g.e[rand_idx].from, g.e[rand_idx].to);
    }
    for (int k = 0, j = 0; j < g.n; ++k)
    {
        if (uf.parent[k] == k)
        {
            label[k] = j;
            ++j;
        }
    }
    auto map = std::vector<std::vector<int>>(g.n, std::vector<int>(g.n, -1));
    auto e = std::vector<Edge>();
    auto w = std::vector<int>();
    e.reserve(g.n * g.n);
    w.reserve(g.n * g.n);
    int from, to;
    int idx;
    for (int k = 0; k < g.e.size(); ++k)
    {
        from = label[uf.find(g.e[k].from)];
        to = label[uf.find(g.e[k].to)];
        if (from == to)
            continue;
        if ((idx = map[from][to]) != -1)
        {
            w[idx] += g.w[k];
        }
        else
        {
            e.push_back(Edge{from, to});
            w.push_back(g.w[k]);
            map[from][to] = map[to][from] = e.size() - 1;
        }
    }
    g.e = e;
    g.w = w;
    return g;
}

int karger(Graph g)
{
    return contract(g, 2).w[0];
}

int karger_stein(Graph g)
{
    if (g.n <= 6)
    {
        return karger(g);
    }
    else
    {
        int t = std::ceil(g.n / std::sqrt(2) + 1);
        return std::min(
            karger_stein(contract(g, t)),
            karger_stein(contract(g, t)));
    }
}

int main(int argc, char **argv)
{

    if (argc != 2)
    {
        std::cout << "invalid input" << std::endl;
        exit(EXIT_FAILURE);
    }
    Graph g = file_to_graph(std::string{argv[1]});
    int reps = log(g.n) * log(g.n);
    time_function(karger_stein, g, reps);
}