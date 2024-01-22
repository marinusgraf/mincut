#pragma once
#include "adjmat.h"

struct Node { int id, key;};

struct MaxHeap
{
    std::vector<Node> a;

    void insert(Node v);

    Node extract_max();

    void up_heapify(int i);

    void down_heapify(int idx);

    int find(int id);

    void increase_key(int id, int s);
};