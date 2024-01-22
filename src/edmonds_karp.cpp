#include "adjmat.h"
#include "edmonds_karp.h"
#include "flow.h"

int st_maxflow(std::vector<std::vector<int>> e, int s, int t)
{
    int f = 0;
    std::vector<int> p(n, -1), d;
    while (bfs(e, p, s, t)[t] != -1)
    {
        f += augment(e, p, s, t);
    }
    return f;
}

int edmonds_karps(std::vector<std::vector<int>> &e)
{
    int mincut = INT_MAX;   
    for (int s = 0; s < n; ++s)
    {
        for (int t = s+1; t < n; ++t)
        {
            mincut = std::min(mincut, st_maxflow(e, s, t));
        }
    }
    return mincut;
}

int main(int argc, char** argv)
{
    if (argc != 2) 
    {
        std::cout << "invalid input" << std::endl;
        exit(EXIT_FAILURE);
    }
    file_to_adjmat(std::string{argv[1]});
    std::cout << n << std::endl;
    std::cout << edmonds_karps(e) << std::endl;
}