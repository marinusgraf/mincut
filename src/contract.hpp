#include <vector>
#include <algorithm>
#include <random>

struct UnionFind
{ 
    int sets;
    std::vector<int> parent, rank;

    UnionFind(int n) : sets{n}
    {
        parent.reserve(n); rank.reserve(n);
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
        if (x == y) return; 

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

struct Edge { int src, dest, weight; };

struct Graph { UnionFind partition; std::vector<Edge> edges;}; 

Graph contract(Graph g, const int resulting_size)
{
    int rand_idx;
    std::vector<double> weights;
    weights.reserve(g.edges.size());
    for (auto &e : g.edges) 
    {
        weights.push_back(e.weight);
    }
    static std::default_random_engine engine{std::random_device{}()};
    std::discrete_distribution<int> dist{weights.begin(), weights.end()};
    while (g.partition.sets != resulting_size)
    { 
        rand_idx = dist(engine);
        g.partition.link(g.edges[rand_idx].src, g.edges[rand_idx].dest);
    }
    auto is_self_edge = [&g] (Edge edge) //non-self edge
    {
        return g.partition.find(edge.src) == g.partition.find(edge.dest);
    };
    std::erase_if(g.edges, is_self_edge);
    return g;
}

int karger(Graph g)
{
    g = contract(g, 2);
    int ret = 0;
    for (auto &e : g.edges)
    {
        ret += e.weight;
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
        return std::min
        (
            karger_stein(contract(g, contracted_graph_size)),
            karger_stein(contract(g, contracted_graph_size))
        );
    }
}