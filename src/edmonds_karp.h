#pragma once
#include <vector>

std::vector<int> bfs(std::vector<std::vector<int>> &e, std::vector<int> &p, int s, int t);

int augment(std::vector<std::vector<int>> &e, std::vector<int> p, int s, int t);

int st_maxflow(std::vector<std::vector<int>> e, int s, int t);

int edmonds_karps(std::vector<std::vector<int>> &e);
