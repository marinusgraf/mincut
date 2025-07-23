#pragma once
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

struct Edge {
  int from, to, cap;
};

struct Network {
  int n, m;
  std::vector<Edge> e;
  std::vector<std::vector<int>> adj;
};

Network file_to_network(std::string path) {
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
  auto adj = std::vector<std::vector<int>>(n, std::vector<int>());
  auto e = std::vector<Edge>(2 * m);
  int from, to, cap;
  for (int curr = 0; std::getline(file, line); curr += 2) {
    std::istringstream st(line);
    if (!(st >> from >> to >> cap)) {
      std::cerr << ("file has incorrect edge format") << std::endl;
      exit(EXIT_FAILURE);
    }
    e[curr] = Edge{from, to, cap};
    e[curr + 1] = Edge{to, from, cap};
    adj[from].push_back(curr);
    adj[to].push_back(curr + 1);
  }
  return Network{n, m, e, adj};
}
