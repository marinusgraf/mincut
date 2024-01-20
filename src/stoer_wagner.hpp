#include "util.hpp"

int stoer_wagner(std::vector<std::vector<int>> &mat)
{
    int n = mat[0].size();
    int k = n;
    std::vector<int> dist(n);
    std::vector<bool> del(n, false); 
    int min_cut = INT_MAX;
    while (k > 1)
    {
        std::vector<bool> A(n, false);
        A[0] = true; 
        int size_A = 1;
        dist = mat[0];
        int curr = 0, prev = 0;
        while(true)
        {
            if (size_A == k)
            {
                min_cut = std::min(min_cut, dist[curr]);
                del[curr] = true;
                for (int i = 0; i < n; ++i)
                {
                    mat[prev][i] += mat[curr][i];
                    mat[i][prev] = mat[prev][i];
                }
                --k;
                break;
            }
            prev = curr;
            int max_dist = 0;
            for (int v = 1; v < n; ++v)
            {
                if (dist[v] > max_dist && !A[v] && !del[v])
                {
                    max_dist = dist[v];
                    curr = v;
                }
            }
            A[curr] = true;
            ++size_A;
            for (int v = 1; v < n; ++v)
            {
                if (!A[v] && !del[v])
                {
                    dist[v] += mat[curr][v];
                }
            }
        }

    }
    return min_cut;
}