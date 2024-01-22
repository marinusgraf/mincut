#include "stoer_wagner.h"
#include "adjmat.h"

void MaxHeap::insert(Node v)
{
    a.push_back(v);
    int idx = a.size() - 1;
    up_heapify(idx);
}
Node MaxHeap::extract_max()
{
    Node ret = a[0];
    std::swap(a[0], a[a.size() - 1]);
    a.pop_back();
    down_heapify(0);
    return ret;
}
void MaxHeap::up_heapify(int i)
{
    int p;
    while ((p = (i - 1) / 2) >= 0)
    {
        if (a[i].key <= a[p].key)
            break;
        std::swap(a[i], a[p]);
        i = p;
    }
}
void MaxHeap::down_heapify(int idx)
{
    int last_idx = a.size() - 1;
    if (idx > last_idx)
        return;
    int left_idx = 2 * idx + 1;
    int right_idx = left_idx + 1;
    int max_idx = idx;
    if (left_idx <= last_idx && a[left_idx].key > a[max_idx].key)
    {
        max_idx = left_idx;
    }
    if (right_idx <= last_idx && a[right_idx].key > a[max_idx].key)
    {
        max_idx = right_idx;
    }
    if (max_idx != idx)
    {
        std::swap(a[idx], a[max_idx]);
        down_heapify(max_idx);
    }
}
int MaxHeap::find(int id)
{
    for (int i = 0; i < a.size(); ++i)
    {
        if (id == a[i].id)
            return i;
    }
    return -1;
}

void MaxHeap::increase_key(int id, int s)
{
    if (s <= 0)
        return;
    int idx = find(id);
    a[idx].key += s;
    up_heapify(idx);
}

int stoer_wagner(std::vector<std::vector<int>> e)
{
    int n = e[0].size();
    int k = n;
    int min_cut = INT_MAX;
    std::vector<bool> merged(n, false);
    while (k > 1)
    {
        int max;
        int s = 0, t = 0;
        MaxHeap q;
        for (int v = 1; v < n; ++v)
        {
            if (!merged[v])
                q.insert(Node{v, e[0][v]});
        }
        while (q.a.size() > 0)
        {
            s = t;
            Node tmp = q.extract_max();
            t = tmp.id;
            max = tmp.key;
            for (Node &v : q.a)
            {
                q.increase_key(v.id, e[v.id][t]);
            }
        }
        min_cut = std::min(min_cut, max);
        merged[t] = true;
        for (int v = 0; v < n; ++v)
        {
            e[s][v] += e[t][v];
            e[v][s] = e[s][v];
        }
        --k;
    }
    return min_cut;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "invalid input" << std::endl;
        exit(EXIT_FAILURE);
    }
    file_to_adjmat(std::string{argv[1]});
    std::cout << stoer_wagner(e) << std::endl;
}