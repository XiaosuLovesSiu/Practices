#pragma once
#include <vector>
#include <stdexcept>

class Heap
{
protected:
    std::vector<int> data;

    Heap(std::vector<int> vec);

    int parent(int i);

    int left(int i);

    int right(int i);

    virtual void siftUp(int idx) = 0;
    virtual void siftDown(int idx) = 0;
};

class bigHeap : public Heap
{
public:
    void siftUp(int idx) override;

    void siftDown(int idx) override;

    bigHeap(std::vector<int> vec);

    int top();

    void pop();

    void insert(int value);
};

class smallHeap : public Heap
{
public:
    void siftUp(int idx) override;

    void siftDown(int idx) override;

    smallHeap(std::vector<int> vec);

    int top();

    void pop();

    void insert(int value);
};