#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>


struct Edge 
{
    int src, dest, cap;
    Edge *rev;
};

struct Path
{
    Edge *curr, *prev;
};

struct Graph 
{
    int n, m;
    std::vector<std::vector<Edge>> adj;
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
    int n, m, src, dest, cap;
    std::istringstream st(line);
    if (!(st >> n >> m))
    {
        std::cerr << ("Error, first line does not contain node and edge count") << std::endl;
        exit(EXIT_FAILURE);
    }
    Graph g{n, m, std::vector<std::vector<Edge>>(n, std::vector<Edge>())};
    std::vector<Edge> e;
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
            src = vals[0]; dest = vals[1]; cap = vals[2];
            if (src == dest) continue;

            e.push_back({src,dest,cap});
            e.push_back({dest,src,cap});
            e[e.size() - 2].rev = &e[e.size() - 1];
            e[e.size() - 1].rev = &e[e.size() - 2];
            g.adj[src].push_back(std::move(e[e.size() - 2]));
            g.adj[dest].push_back(std::move(e[e.size() - 1]));
    }
    return g;
}