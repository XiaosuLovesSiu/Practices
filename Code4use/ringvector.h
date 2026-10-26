#pragma once
#include <vector>

template <typename T>
class ringvector
{
private:
    std::vector<T> rvec;
    size_t sz;
public:
    ringvector(std::vector<T> tvec);
    T at(size_t ind);
    size_t size();
    void push_back(T obj);
};