#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>


struct Edge 
{
    int from, to, id;
};

struct Graph 
{
    int n, m;
    std::vector<std::vector<Edge>> adj;
    std::vector<int> cap;
};

Graph file_to_adjmat(std::string path)
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
        if (line[0] != '#') break;
    }
    int n, m, from, to, cap, id;
    std::istringstream st(line);
    if (!(st >> n >> m))
    {
        std::cerr << ("Error, first line does not contain node and edge count") << std::endl;
        exit(EXIT_FAILURE);
    }
    Graph g{n, m, std::vector<std::vector<Edge>>(n, std::vector<Edge>()), std::vector<int>(2*m)};
    int size = 0;
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
            from = vals[0]; to = vals[1]; cap = vals[2];
            if (from == to) continue;
            id = size;
            g.adj[from].push_back(Edge{from, to, id});
            g.adj[to].push_back(Edge{to, from, id + 1});
            g.cap[id] = cap;
            g.cap[id+1] = cap;
            size += 2;
    }
    return g;
}