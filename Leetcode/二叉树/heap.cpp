#include "heap.h"
#include <vector>
#include <stdexcept>
using namespace std;

Heap::Heap(vector<int> vec) : data(vec) {}

int Heap::parent(int i)
{
    return (i - 1) / 2;
}
int Heap::left(int i)
{
    return 2 * i + 1;
}
int Heap::right(int i)
{
    return 2 * i + 2;
}

void bigHeap::siftUp(int idx)
{
    while (idx > 0)
    {
        int p = parent(idx);
        if(data[p] < data[idx])
        {
            swap(data[p], data[idx]);
            idx = p;
        }
        else
            break;
    }
}

void bigHeap::siftDown(int idx)
{
    while (true)
    {
        int l = left(idx), r = right(idx);
        if (l < data.size())
        {
            int b;
            if (r < data.size())
            {
                if (data[l] >= data[r])
                    b = l;
                else
                    b = r;
            }
            else
                b = l;

            if (data[b] > data[idx])
            {
                swap(data[b], data[idx]);
                idx = b;
            }
            else
                break;
        }
        else
            break;
    }
}

bigHeap::bigHeap(vector<int> vec) : Heap(vec)
{
    for (int i = vec.size() / 2 - 1; i >= 0; i--)
    {
        siftDown(i);
    }
}

int bigHeap::top()
{
    if (data.empty())
        throw runtime_error("Heap is empty");
    return data[0];
}

void bigHeap::pop()
{
    if (data.empty())
        throw runtime_error("Heap is empty");
    swap(data[0], data[data.size() - 1]);
    data.pop_back();
    siftDown(0);
}

void bigHeap::insert(int value)
{
    data.push_back(value);
    siftUp(data.size() - 1);
}

void smallHeap::siftUp(int idx)
{
    while (idx > 0)
    {
        int p = parent(idx);
        if (data[p] > data[idx])
        {
            swap(data[p], data[idx]);
            idx = p;
        }
        else
            break;
    }
}

void smallHeap::siftDown(int idx)
{
    while (true)
    {
        int l = left(idx), r = right(idx);
        if (l < data.size())
        {
            int s;
            if (r < data.size())
            {
                if (data[l] <= data[r])
                    s = l;
                else
                    s = r;
            }
            else
                s = l;

            if (data[s] < data[idx])
            {
                swap(data[s], data[idx]);
                idx = s;
            }
            else
                break;
        }
        else
            break;
    }
}

smallHeap::smallHeap(vector<int> vec) : Heap(vec)
{
    for (int i = vec.size() / 2 - 1; i >= 0; i--)
    {
        siftDown(i);
    }
}

int smallHeap::top()
{
    if (data.empty())
        throw runtime_error("Heap is empty");
    return data[0];
}

void smallHeap::pop()
{
    if (data.empty())
        throw runtime_error("Heap is empty");
    swap(data[0], data[data.size() - 1]);
    data.pop_back();
    siftDown(0);
}

void smallHeap::insert(int value)
{
    data.push_back(value);
    siftUp(data.size() - 1);
}