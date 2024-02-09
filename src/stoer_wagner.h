#pragma once
#include "adjmat.h"

struct Node
{
    int id, key;
};

struct MaxHeap
{
    std::vector<Node> a;

    void insert(Node v)
    {
        a.push_back(v);
        int idx = a.size() - 1;
        up_heapify(idx);
    }
    Node extract_max()
    {
        Node ret = a[0];
        std::swap(a[0], a[a.size() - 1]);
        a.pop_back();
        down_heapify(0);
        return ret;
    }
    void up_heapify(int i)
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
    void down_heapify(int idx)
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
    int find(int id)
    {
        for (int i = 0; i < a.size(); ++i)
        {
            if (id == a[i].id)
                return i;
        }
        return -1;
    }

    void increase_key(int id, int s)
    {
        if (s <= 0)
            return;
        int idx = find(id);
        a[idx].key += s;
        up_heapify(idx);
    }
};

int stoer_wagner(Graph g)
{
    int k = g.n;
    int min_cut = INT_MAX;
    std::vector<bool> merged(g.n, false);
    while (k > 1)
    {
        int max;
        int s = 0, t = 0;
        MaxHeap q;
        for (int v = 1; v < g.n; ++v)
        {
            if (!merged[v])
                q.insert(Node{v, g.c[0][v]});
        }
        while (q.a.size() > 0)
        {
            s = t;
            Node tmp = q.extract_max();
            t = tmp.id;
            max = tmp.key;
            for (Node &v : q.a)
            {
                q.increase_key(v.id, g.c[v.id][t]);
            }
        }
        min_cut = std::min(min_cut, max);
        merged[t] = true;
        for (int v = 0; v < g.n; ++v)
        {
            g.c[s][v] += g.c[t][v];
            g.c[v][s] = g.c[s][v];
        }
        --k;
    }
    return min_cut;
}