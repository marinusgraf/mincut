#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <random>
#include <sstream>
#include <string>

#include "timer.h"

struct UnionFind {
  std::vector<int> parent, rank;
  int sets;
  UnionFind(int n) : sets{n} {
    parent = std::vector<int>(n);
    rank = std::vector<int>(n);
    for (int k = 0; k < n; ++k) {
      parent[k] = k;
      rank[k] = 0;
    }
  }

  int find(int x) {
    if (x != parent[x]) {
      parent[x] = find(parent[x]);
      return parent[x];
    }
    return x;
  }

  bool link(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return false;

    if (rank[x] < rank[y]) {
      std::swap(x, y);
    }

    parent[y] = x;
    if (rank[x] == rank[y]) {
      rank[x] += 1;
    }
    --sets;
    return true;
  }
};

union Score {
  float f;
  uint32_t x;
};

struct Edge {
  int from, to, weight;
  Score s;
};

struct Graph {
  int n, m;
  std::vector<Edge> e;
};

Graph file_to_graph(const std::string path) {
  std::ifstream file(path);
  if (!file) {
    std::cerr << "Error: could not open file" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::string line;
  while (std::getline(file, line)) {
    if (line[0] != '#') break;
  }
  int n;
  int m;
  std::istringstream st(line);
  if (!(st >> n >> m)) {
    std::cerr << ("Error, first line does not contain node and edge count")
              << std::endl;
    exit(EXIT_FAILURE);
  }
  std::vector<Edge> e(m);
  std::vector<int> w(m);
  int from, to, weight;
  for (int k = 0; std::getline(file, line); ++k) {
    std::istringstream st(line);
    if (!(st >> from >> to >> weight)) {
      std::cerr << ("Error, first line does not contain node and edge count")
                << std::endl;
      exit(EXIT_FAILURE);
    }
    e[k] = Edge{from, to, weight};
  }
  return Graph{n, m, e};
}

void relabel(Graph& g, UnionFind& uf, const int first_idx) {
  int new_size = uf.sets;
  auto label = std::vector<int>(g.n, -1);
  for (int k = 0, j = 0; j < new_size; ++k) {
    if (uf.parent[k] == k) {
      label[k] = j;
      ++j;
    }
  }
  auto map = std::vector<std::vector<int>>(g.n, std::vector<int>(g.n, -1));
  auto e = std::vector<Edge>();
  e.reserve(g.e.size() - first_idx);
  int from, to;
  int idx;
  for (int i = first_idx; i < g.e.size(); ++i) {
    from = label[uf.find(g.e[i].from)];
    to = label[uf.find(g.e[i].to)];
    if (from == to) continue;
    if ((idx = map[from][to]) != -1) {
      e[idx].weight += g.e[i].weight;
    } else {
      e.push_back(Edge{from, to, g.e[i].weight, Score{0}});
      map[from][to] = map[to][from] = e.size() - 1;
    }
  }
  g.n = new_size;
  g.e = e;
}

void insertion_sort(std::vector<Edge>& arr, const int n) {
  for (int k = 1; k < n; ++k) {
    for (int j = k; j > 0 && arr[j - 1].s.f > arr[j].s.f; --j) {
      std::swap(arr[j], arr[j - 1]);
    }
  }
}

void radix_sort(std::vector<Edge>& arr, const int n) {
  if (n < 32) {
    insertion_sort(arr, n);
    return;
  }
  for (int r = 0; r < 32; r += 8) {
    int count[256] = {0};
    std::vector<Edge> tmp(n);

    for (int k = 0; k < n; ++k) {
      count[(arr[k].s.x >> r) & 0xff]++;
    }
    for (int k = 1; k < 256; ++k) {
      count[k] += count[k - 1];
    }
    for (int k = n - 1; k >= 0; --k) {
      tmp[--count[(arr[k].s.x >> r) & 0xff]] = arr[k];
    }
    for (int k = 0; k < n; ++k) {
      arr[k] = tmp[k];
    }
  }
}

void contract(Graph& g, const int t) {
  static std::mt19937 engine{std::random_device{}()};
  UnionFind uf{g.n};
  for (Edge& e : g.e) {
    float unif = std::uniform_real_distribution<float>{0.0, 1.0}(engine);
    float tmp = 1 - std::pow(1 - unif, (float)1 / e.weight);
    e.s = Score{tmp};
  }
  radix_sort(g.e, g.e.size());
  int k = 0;
  for (; uf.sets != t; ++k) {
    uf.link(g.e[k].from, g.e[k].to);
  }
  relabel(g, uf, k);
}

int karger(Graph& g) {
  contract(g, 2);
  return g.e[0].weight;
}

int karger_stein(Graph& g) {
  if (g.n <= 6) {
    return karger(g);
  } else {
    int t;
    const double invsq = 1 / std::sqrt(2);
    t = invsq * g.n;
    Graph h{g};
    contract(g, t);
    contract(h, t);
    return std::min(karger_stein(g), karger_stein(h));
  }
}

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cout << "invalid input" << std::endl;
    exit(EXIT_FAILURE);
  }
  Graph g = file_to_graph(std::string{argv[1]});
  // int karger_reps = g.n * g.n * log(g.n);
  int karger_stein_reps = log(g.n) * log(g.n);
  time_function(karger_stein, g, karger_stein_reps);
}