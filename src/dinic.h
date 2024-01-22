#include <vector>

bool dfs(std::vector<std::vector<int>> e, std::vector<int>& p, std::vector<int> d, int s, int t);

int augment(std::vector<std::vector<int>> &e, int s, int t);

int st_maxflow(std::vector<std::vector<int>> e, int s, int t);

int dinic(std::vector<std::vector<int>> e);