#include "ringvector.h"

template <typename T>
T ringvector<T>::at(size_t ind)
{
    return rvec[ind%sz];
}

template <typename T>
size_t ringvector<T>::size()
{
    return sz;
}

template <typename T>
void ringvector<T>::push_back(T obj)
{
    rvec.push_back(obj);
    sz++;
}

template <typename T>
ringvector<T>::ringvector(std::vector<T> tvec) : rvec(tvec), sz(tvec.size()) {}

