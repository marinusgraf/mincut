#include "network.h"
#include "timer.h"

int bfs(Network &g, std::vector<int> &p, int s, int t) {
  std::vector<int> curr = {s}, next, flow(g.n, -1);
  std::vector<bool> vis(g.n, false);
  vis[s] = true;
  int v, cap;
  while (curr.size() > 0) {
    next = {};
    for (int &u : curr) {
      for (int &idx : g.adj[u]) {
        v = g.e[idx].to;
        cap = g.e[idx].cap;
        if (cap > 0 && !vis[v]) {
          if (u == s) {
            flow[v] = cap;
          } else {
            flow[v] = std::min(flow[u], cap);
          }
          p[v] = idx;
          vis[v] = true;
          next.push_back(v);
        }
      }
    }
    curr = next;
  }
  return flow[t];
}

int st_maxflow(Network g, int s, int t) {
  int f, m = 0;
  std::vector<int> p(g.n, -1);
  while ((f = bfs(g, p, s, t)) > 0) {
    m += f;
    for (int v = t; v != s; v = g.e[p[v]].from) {
      g.e[p[v]].cap -= f;
      g.e[p[v] ^ 1].cap += f;
    }
  }
  return m;
}

int edmonds_karp(Network &g) {
  int mincut = INT_MAX;
  for (int t = 1; t < g.n; ++t) {
    mincut = std::min(mincut, st_maxflow(g, 0, t));
  }
  return mincut;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "invalid input" << std::endl;
    exit(EXIT_FAILURE);
  }
  Network g = file_to_network(std::string{argv[1]});
  time_function(edmonds_karp, g);
}
