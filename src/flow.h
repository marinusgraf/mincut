#pragma once
#include <vector>

std::vector<int> bfs(std::vector<std::vector<int>> &e, std::vector<int> &p, int s, int t);

bool dfs(std::vector<std::vector<int>> e, std::vector<int>& p, std::vector<int> d, int s, int t);

int augment(std::vector<std::vector<int>> &e, std::vector<int> p, int s, int t);

int edmonds_karps(std::vector<std::vector<int>> &e);

int dinic(std::vector<std::vector<int>> e);

