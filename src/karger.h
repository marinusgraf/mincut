#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <thread>
#include <random>

struct Edge 
{
    int from, to;
};

struct Graph
{
    int n;
    std::vector<Edge> e;
    std::vector<int> w, parent, rank;

    Graph(int n) : n{n}
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
        --n;
    }

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
    int n, m;
    std::istringstream st(line);
    if (!(st >> n >> m))
    {
        std::cerr << ("Error, first line does not contain node and edge count") << std::endl;
        exit(EXIT_FAILURE);
    }
    Graph g{n};
    g.e = std::vector<Edge>(m);
    g.w = std::vector<int>(m);
    int src, dest, weight;
    for (int k = 0; std::getline(file, line) && k < m; ++k)
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
            continue; // ignore self edges
        g.e[k] = Edge{src, dest};
        g.w[k] = weight;
    }
    return g;
}

Graph contract(Graph g, int t)
{
    int idx;
    int m = g.e.size();
    auto self_edge = [&g](Edge e)
    {
        return g.find(e.from) == g.find(e.to);
    };
    static std::default_random_engine engine{std::random_device{}()};
    std::discrete_distribution<> dist{g.w.begin(), g.w.end()};
    while (g.n != t)
    {
        idx = dist(engine);
        g.link(g.e[idx].from, g.e[idx].to);
    }
    int i = 0;
    while (i < m)
    {
        if (self_edge(g.e[i]))
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
    int res = 0;
    for (int i = 0; i < g.w.size(); ++i)
    {
        res += g.w[i];
    }
    return res;
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

void thread_work(int (*func)(Graph g), Graph g, const int repetitions, std::atomic<int> &result)
{
    for (int i = 0; i < repetitions; ++i)
    {
        result = std::min(result.load(), func(g));
    }
}
