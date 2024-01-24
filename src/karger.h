#pragma once
#include <numeric>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <thread>
#include <random>

struct UnionFind
{
    int sets;
    std::vector<int> parent, rank;

    UnionFind(int n) : sets{n}
    {
        parent.reserve(n);
        rank.reserve(n);
        for (int i = 0; i < n; ++i)
        {
            parent.push_back(i);
            rank.push_back(0);
        }
    }

    int find(int x)
    {
        while (x != parent[x])
        {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }

    void link(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
            return;

        if (rank[x] < rank[y])
        {
            std::swap(x, y);
        }

        parent[y] = x;
        if (rank[x] == rank[y])
        {
            rank[x] += 1;
        }
        --sets;
    }
};

struct Edge
{
    int src, dest;
};

struct Graph
{
    UnionFind partition;
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
    std::vector<Edge> e;
    e.reserve(m);
    std::vector<int> w;
    w.reserve(m);
    int src, dest, weight;
    while (std::getline(file, line))
    {
        int vals[3];
        int i;
        for (i = 0; i < 3 && line.length() > 0; ++i)
        {
            int pos = line.find(" ");
            vals[i] = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
        }
        if (i < 3)
            vals[2] = 1;
        src = vals[0];
        dest = vals[1];
        weight = vals[2];
        if (src == dest)
            continue; // ignore self e
        e.push_back(Edge{src, dest});
        w.push_back(weight);
    }
    return Graph{UnionFind{n}, std::move(e), std::move(w)};
}

Graph contract(Graph g, const int resulting_size)
{
    int rand_idx;
    int m = g.e.size();
    static std::default_random_engine engine{std::random_device{}()};
    std::discrete_distribution<int> dist{g.w.begin(), g.w.end()};
    while (g.partition.sets != resulting_size)
    {
        rand_idx = dist(engine);
        g.partition.link(g.e[rand_idx].src, g.e[rand_idx].dest);
    }
    auto self_loop = [&g](Edge edge)
    {
        return g.partition.find(edge.src) == g.partition.find(edge.dest);
    };

    int i = 0;
    while (i < m)
    {
        if (self_loop(g.e[i]))
        {
            --m;
            g.e[i] = g.e[m];
            g.w[i] = g.w[m];
        }
        else
        {
            ++i;
        }
    }
    g.e.resize(i);
    g.w.resize(i);
    return g;
}

int karger(Graph g)
{
    g = contract(g, 2);
    int ret = 0;
    for (auto &w : g.w)
    {
        ret += w;
    }
    return ret;
}

int karger_stein(Graph g)
{
    if (g.partition.sets <= 6)
    {
        return karger(g);
    }
    else
    {
        int contracted_graph_size = std::ceil(g.partition.sets / std::sqrt(2) + 1);
        return std::min(
            karger_stein(contract(g, contracted_graph_size)),
            karger_stein(contract(g, contracted_graph_size)));
    }
}

void thread_work(int (*func)(Graph g), Graph g, const int repetitions, std::atomic<int> &result)
{
    for (int i = 0; i < repetitions; ++i)
    {
        result = std::min(result.load(), func(g));
    }
}
