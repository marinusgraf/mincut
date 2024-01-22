#pragma once
#include <vector>

int st_maxflow(std::vector<std::vector<int>> e, int s, int t);

int edmonds_karps(std::vector<std::vector<int>> &e);

int bfs(std::vector<std::vector<int>> &e, std::vector<int> &p, int s, int t);

int augment(std::vector<std::vector<int>> &e, std::vector<int> p, int s, int t);