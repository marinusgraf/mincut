#pragma once
#include "adjmat.h"

struct Node
{
    int id, key, idx;
};

struct MaxHeap
{
    std::vector<Node> a;

    void build()
    {
        for (int idx = (a.size() / 2) - 1; idx >= 0; --idx)
        {
            down_heapify(idx);
        }
    }
 
    Node extract_max()
    {
        Node ret = a[0];
        std::swap(a[0], a[a.size() - 1]);
        a.pop_back();
        a[0].idx = 0;
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
            std::swap(a[i].idx, a[p].idx);
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
            std::swap(a[idx].idx, a[max_idx].idx);
            down_heapify(max_idx);
        }
    }

    void increase_key(Node node, int s)
    {
        if (s <= 0)
            return;
        a[node.idx].key += s;
        up_heapify(node.idx);
    }
};

int stoer_wagner(Graph g)
{
    int min_cut = INT_MAX;
    std::vector<int> v(g.n);
    for (int k = 0; k < g.n; ++k)
    {
        v[k] = k;
    }
    while (g.n > 1)
    {
        int max;
        int s = 0, t = 0;
        MaxHeap q{std::vector<Node>(g.n - 1)};
        for (int k = 1; k < g.n; ++k)
        {
                q.a[k-1] = Node{k, g.w[0][v[k]], k - 1};
        }
        q.build();
        while (q.a.size() > 0)
        {
            s = t;
            Node tmp = q.extract_max();
            t = tmp.id;
            max = tmp.key;
            for (Node &node : q.a)
            {
                q.increase_key(node, g.w[v[node.id]][v[t]]);
            }
        }
        min_cut = std::min(min_cut, max);
        for (int k = 0; k < g.n; ++k)
        {
            g.w[v[s]][v[k]] += g.w[v[t]][v[k]];
            g.w[v[k]][v[s]] = g.w[v[s]][v[k]];
        }
        v[t] = v[--g.n];
    }
    return min_cut;
}

int stoer_wagner2(Graph g)
{
    int min_cut = INT_MAX;
    std::vector<bool> merged(g.n, false);
    int k = g.n;
    while (k > 1)
    {
        int max;
        int s = 0, t = 0;
        MaxHeap q;
        q.a.reserve(k-1);
        for (int v = 1; v < g.n; ++v)
        {
                q.a.push_back(Node{v, g.w[0][v], (int) q.a.size()});
        }
        q.build();
        while (q.a.size() > 0)
        {
            s = t;
            Node tmp = q.extract_max();
            t = tmp.id;
            max = tmp.key;
            for (Node &node : q.a)
            {
                q.increase_key(node, g.w[node.id][t]);
            }
        }
        min_cut = std::min(min_cut, max);
        merged[t] = true;
        for (int v = 0; v < g.n; ++v)
        {
            if (!merged[v])
            {
                g.w[s][v] += g.w[t][v];
                g.w[v][s] = g.w[s][v];
            }
        }
        --k;
    }
    return min_cut;
}