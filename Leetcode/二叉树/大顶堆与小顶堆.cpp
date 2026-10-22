#include <vector>
#include <stdexcept>
using namespace std;

class Heap
{
protected:
    vector<int> data;

    Heap(vector<int> vec) : data(vec) {}

    int parent(int i)
    {
        return (i - 1) / 2;
    }
    int left(int i)
    {
        return 2 * i + 1;
    }
    int right(int i)
    {
        return 2 * i + 2;
    }
    virtual void siftUp(int idx) = 0;
    virtual void siftDown(int idx) = 0;
};

class bigHeap : public Heap
{
public:
    void siftUp(int idx)
    {
        while (idx > 0)
        {
            int p = parent(idx);
            if (data[p] < data[idx])
            {
                swap(data[p], data[idx]);
                idx = p;
            }
            else
                break;
        }
    }

    void siftDown(int idx)
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
                        b = data[l];
                    else
                        b = data[r];
                }
                else
                    b = data[l];

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

    bigHeap(vector<int> vec) : Heap(vec)
    {
        for (int i = vec.size() / 2 - 1; i >= 0; i--)
        {
            siftDown(i);
        }
    }

    int top()
    {
        if (data.empty())
            throw runtime_error("Heap is empty");
        return data[0];
    }

    void pop()
    {
        if (data.empty())
            throw runtime_error("Heap is empty");
        swap(data[0], data[data.size() - 1]);
        data.pop_back();
        siftDown(0);
    }

    void insert(int value)
    {
        data.push_back(value);
        siftUp(data.size() - 1);
    }
};

class smallHeap : public Heap
{
public:
    void siftUp(int idx)
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

    void siftDown(int idx)
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
                        s = data[l];
                    else
                        s = data[r];
                }
                else
                    s = data[l];

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

    smallHeap(vector<int> vec) : Heap(vec)
    {
        for (int i = vec.size() / 2 - 1; i >= 0; i--)
        {
            siftDown(i);
        }
    }

    int top()
    {
        if (data.empty())
            throw runtime_error("Heap is empty");
        return data[0];
    }

    void pop()
    {
        if (data.empty())
            throw runtime_error("Heap is empty");
        swap(data[0], data[data.size() - 1]);
        data.pop_back();
        siftDown(0);
    }

    void insert(int value)
    {
        data.push_back(value);
        siftUp(data.size() - 1);
    }
};