#pragma once
#include <numeric>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <thread>
#include <random>
#include "karger.hpp"


void thread_work(int (*func)(Graph g), Graph g, const int repetitions, std::atomic<int> &result)
{
    for(int i = 0; i < repetitions; ++i)
    {
        result = std::min(result.load(), func(g));
    }
}

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
        if (line[0] != '#') break;
    }
    int n; int m;
    std::istringstream st(line);
    if (!(st >> n >> m))
    {
        std::cerr << ("Error, first line does not contain node and edge count") << std::endl;
        exit(EXIT_FAILURE);
    }
    std::vector<Edge> edges;
    edges.reserve(m);
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
            if (src == dest) continue; //ignore self edges
            edges.push_back(Edge{src, dest, weight});
    }
    return Graph{UnionFind{n}, std::move(edges)};
}

std::vector<std::vector<int>> file_to_adjmat(std::string path)
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
    int n; int m;
    std::istringstream st(line);
    if (!(st >> n >> m))
    {
        std::cerr << ("Error, first line does not contain node and edge count") << std::endl;
        exit(EXIT_FAILURE);
    }
    std::vector<std::vector<int>> mat(n, std::vector<int>(n, 0));
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
            if (src == dest) continue; //ignore self-edge
            if (mat[src][dest] == 0)
            {
                mat[src][dest] = weight;
            }
            else
            {
                mat[src][dest] += weight; //add multiedges
            }
            mat[dest][src] = mat[src][dest];
    }
    return mat;

}