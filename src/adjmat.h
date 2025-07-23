#pragma once
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

struct Graph {
  int n, m;
  std::vector<std::vector<int>> w;
  std::vector<int> d;
};

Graph file_to_graph(std::string path) {
  std::ifstream file(path);
  if (!file) {
    std::cerr << "Error: could not open file" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::string line;
  while (std::getline(file, line)) {
    if (line[0] != '#') break;
  }
  std::istringstream st(line);
  int n, m;
  if (!(st >> n >> m)) {
    std::cerr << ("Error, first line does not contain node and edge count")
              << std::endl;
    exit(EXIT_FAILURE);
  }
  auto w = std::vector<std::vector<int>>(n, std::vector<int>(n, 0));
  int from, to, weight;
  while (std::getline(file, line)) {
    std::istringstream st(line);
    if (!(st >> from >> to >> weight)) {
      std::cerr << ("Error, format is wrong") << std::endl;
      exit(EXIT_FAILURE);
    }
    w[from][to] = w[to][from] = weight;
  }
  auto d = std::vector<int>(n, 0);
  for (int u = 0; u < n; ++u) {
    for (int v = 0; v < n; ++v) {
      d[u] += w[u][v];
    }
  }
  return Graph{n, m, w, d};
}