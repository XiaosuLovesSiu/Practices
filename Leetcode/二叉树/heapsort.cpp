#include "heap.h"
#include <vector>
#include <iostream>

int main()
{
    int n;
    std::cout << "please input the size of the vector.";
    std::cin >> n;
    std::cout << "please input the vector in need of sorting." << std::endl;
    std::vector<int> vec(n,0);
    for(int i=0;i<n;i++)
    {
        std::cin >> vec[i]; 
    }
    smallHeap sheap(vec);

    for(int i=0;i<n;i++)
    {
        std::cout << sheap.top() << ' ';
        sheap.pop();
    }
    std::cout << std::endl;
    int ex;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    return 0;
}

/*
void smallHeap::pop()
{
    if (data.empty())
        throw runtime_error("Heap is empty");
    swap(data[0], data[data.size() - 1]);
    data.pop_back();
    siftDown(0);
}
*/