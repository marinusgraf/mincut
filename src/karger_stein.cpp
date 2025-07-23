#include <random>

#include "adjmat.h"
#include "timer.h"

int rand_idx(const std::vector<int> &arr, const std::vector<int> &v) {
  int n = arr.size();
  static std::mt19937 engine(std::random_device{}());
  std::vector<int> acc = std::vector<int>(n, 0);
  acc[0] = arr[v[0]];
  for (int k = 1; k < n; ++k) {
    acc[k] = arr[v[k]] + acc[k - 1];
  }
  int r = std::uniform_int_distribution<int>(0, acc[n - 1] - 1)(engine);
  int low = 0, high = n, mid;
  while (low <= high) {
    mid = (low + high) / 2;
    if (mid == 0) {
      if (r < acc[mid]) {
        return v[0];
      } else {
        low = mid + 1;
        continue;
      }
    } else if (acc[mid - 1] <= r && r < acc[mid]) {
      return v[mid];
    } else if (acc[mid - 1] > r) {
      high = mid - 1;
    } else if (acc[mid] <= r) {
      low = mid + 1;
    }
  }
  return -1;
}

void contract(Graph &g, const int t) {
  static std::mt19937 engine{std::random_device{}()};
  std::vector<int> v(g.n);
  for (int k = 0; k < g.n; ++k) {
    v[k] = k;
  }
  int x, y, p;
  while (g.n != t) {
    x = rand_idx(g.d, v);
    y = rand_idx(g.w[x], v);
    g.d[x] = g.d[x] + g.d[y] - 2 * g.w[x][y];
    g.d[y] = g.w[x][y] = g.w[y][x] = 0;
    for (int k = 0; k < g.n; ++k) {
      if (v[k] == y) {
        p = k;
      }
      if (v[k] == x || v[k] == y) continue;

      g.w[x][v[k]] += g.w[y][v[k]];
      g.w[v[k]][x] = g.w[x][v[k]];
      g.w[y][v[k]] = g.w[v[k]][y] = 0;
    }
    v[p] = v[--g.n];
  }
  if (t == 2) {
    g.w[0][1] = g.d[x];
    return;
  }
  auto w = std::vector<std::vector<int>>(g.n, std::vector<int>(g.n));
  auto d = std::vector<int>(g.n);
  for (int i = 0; i < g.n; ++i) {
    d[i] = g.d[v[i]];
    for (int j = 0; j < g.n; ++j) {
      w[i][j] = g.w[v[i]][v[j]];
    }
  }
  g.w = w;
  g.d = d;
}

int karger(Graph &g) {
  contract(g, 2);
  return g.w[0][1];
}

int karger_stein(Graph &g) {
  if (g.n <= 6) {
    return karger(g);
  } else {
    int t;
    const double invsq = 1 / std::sqrt(2);
    t = invsq * g.n;
    Graph g1{g};
    contract(g, t);
    contract(g1, t);
    return std::min(karger_stein(g), karger_stein(g1));
  }
}

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "invalid or no input path" << std::endl;
    exit(EXIT_FAILURE);
  }
  Graph g = file_to_graph(std::string{argv[1]});
  // int karger_reps = g.n * g.n * log(g.n);
  int karger_stein_reps = log(g.n) * log(g.n);
  time_function(karger_stein, g, karger_stein_reps);
}
