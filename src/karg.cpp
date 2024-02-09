#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <random>


struct Graph
{
    int n, m;
    std::vector<std::vector<int>> w;
    std::vector<int> d;
};

Graph file_to_adjmat(std::string path)
{
    int n,m;
    std::ifstream file(path);
    if (!file)
    {
        std::cerr << "Error: could not open file" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string line;
    while (std::getline(file, line))
    {
        if (line[0] != '#') break;
    }
    std::istringstream st(line);
    if (!(st >> n >> m))
    {
        std::cerr << ("Error, first line does not contain node and edge count") << std::endl;
        exit(EXIT_FAILURE);
    }
    std::vector<std::vector<int>> w = std::vector<std::vector<int>>(n, std::vector<int>(n, 0));
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
            if (i < 3) vals[2] = 1;
            src = vals[0]; dest = vals[1]; weight = vals[2];
            if (src == dest) continue;
            if (w[src][dest] == 0)
            {
                w[src][dest] = weight;
            }
            else
            {
                w[src][dest] += weight; 
            }
            w[dest][src] = w[src][dest];
    }
    std::vector<int> d(n,0);
    for (int u = 0; u < n; ++u)
    {
        for (int v = 0; v < n; ++v)
        {
            d[u] += w[u][v];
        }
    }
    return Graph{n, m, w, d};
}

Graph contract(Graph g, int t)
{
    static std::default_random_engine engine{std::random_device{}()};
    std::vector<bool> merged(g.n, false);
    int u, v;
    int n = g.n;
    while (n != t)
    {
        u = std::discrete_distribution<>{g.d.begin(), g.d.end()}(engine);
        v = std::discrete_distribution<>{g.w[u].begin(), g.w[u].end()}(engine);
        merged[v] = true;
        g.d[u] = g.d[u] + g.d[v] - 2*g.w[u][v];
        g.d[v] = g.w[u][v] = g.w[v][u] = 0;
        for (int w = 0; w < g.n; ++w)
        {
            if (w == u || w == v) continue;
            g.w[u][w] += g.w[v][w];
            g.w[w][u] += g.w[w][v];
            g.w[v][w] = g.w[w][v] = 0;
        }
        --n;
    }
    auto w = std::vector<std::vector<int>>(n,std::vector<int>(n));
    auto d = std::vector<int>(n);
    int new_row = 0, new_col = 0;
    for (int old_row = 0; old_row < g.n; ++old_row)
    {
        if (merged[old_row])
        {
            continue;
        }
        new_col = 0;
        for (int old_col = 0; old_col < g.n; ++old_col)
        {
            if(merged[old_col])
            {
                continue;
            }
            w[new_row][new_col] = g.w[old_row][old_col];
            ++new_col;
        }
        ++new_row;
    }
    int k = 0;
    for (int i = 0; i < g.n; ++i)
    {
        if(merged[i])
        {
            continue;
        }
        d[k] = g.d[i];
        ++k;
    }
    g.n = n;
    g.w = w;
    g.d = d;
    return g;
    
}

int karger(Graph &g)
{
    g = contract(g, 2);
    return g.w[0][1];
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
        return std::min
        (
            karger_stein(contract(g, t)),
            karger_stein(contract(g, t))
        );
    }
}

int main(int argc, char **argv)
{
    Graph g = file_to_adjmat(argv[1]);
    std::cout << karger_stein(g) << std::endl;
    return 0;
}