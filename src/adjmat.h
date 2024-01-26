#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

int n, m;
std::vector<std::vector<int>> e;

void file_to_adjmat(std::string path)
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
    std::istringstream st(line);
    if (!(st >> n >> m))
    {
        std::cerr << ("Error, first line does not contain node and edge count") << std::endl;
        exit(EXIT_FAILURE);
    }
    e = std::vector<std::vector<int>>(n, std::vector<int>(n, 0));
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
            continue;
        if (e[src][dest] == 0)
        {
            e[src][dest] = weight;
        }
        else
        {
            e[src][dest] += weight;
        }
        e[dest][src] = e[src][dest];
    }
}