#pragma once
#include <memory>
#include <algorithm>
#include <ctime>
#include "Exceptions.h"
#include "BaseIterator.h"

#include <iterator>

using namespace std;


// template <TypeForMatrix T>
// BaseIterator::BaseIterator() noexcept
// {
//     index = 0;
//     size = 0;
// }

// template <TypeForMatrix T>
// BaseIterator::BaseIterator(const BaseIterator &iterator) noexcept
// {
//     index = iterator.index;
//     size = iterator.size;
// }

template <TypeForMatrix T>
BaseIterator<T>::BaseIterator(const BaseIterator<T>& iter) noexcept
{
    pdata = iter.pdata;
    size = iter.size;
    index = iter.index;
}

template <TypeForMatrix T>
const T& BaseIterator<T>::operator*() const
{

    expride_exept_check(__LINE__);
    index_exept_check(__LINE__);

    const shared_ptr<T[]> a = pdata.lock();
    return *(a.get() + index);
};

template <TypeForMatrix T>
const T* BaseIterator<T>::operator->() const
{
    const shared_ptr<T[]> a = pdata.lock();
    return a.get() + index;
}


template <TypeForMatrix T>
BaseIterator<T>::operator bool() const noexcept
{
    return !pdata.expired() && index < size;
}

// template <TypeForMatrix T>
// BaseIterator<T> &BaseIterator<T>::operator++() noexcept
// {
//     ++index;
//     return *this;
// }

// template <TypeForMatrix T>
// BaseIterator<T> BaseIterator<T>::operator++(int) noexcept
// {
//     BaseIterator<T> tmp(*this);
//     ++index;
//     return tmp;
// }

// template <TypeForMatrix T>
// BaseIterator<T> &BaseIterator<T>::operator--() noexcept
// {
//     --index;
//     return *this;
// }

// template <TypeForMatrix T>
// BaseIterator<T> BaseIterator<T>::operator--(int) noexcept
// {
//     BaseIterator<T> tmp(*this);
//     --index;
//     return tmp;
// }

// template <TypeForMatrix T>
// BaseIterator<T> BaseIterator<T>::operator+(const difference_type ind) const noexcept
// {
//     BaseIterator<T> tmp(*this);
//     tmp += ind;
//     return tmp;
// }

// template <TypeForMatrix T>
// BaseIterator<T> BaseIterator<T>::operator-(const difference_type ind) const noexcept
// {
//     BaseIterator<T> tmp(*this);
//     tmp -= ind;
//     return tmp;
// }

// template <TypeForMatrix T>
// BaseIterator<T> &BaseIterator<T>::operator+=(const difference_type ind) noexcept
// {
//     index += ind;
//     return *this;
// }

// template <TypeForMatrix T>
// BaseIterator<T> &BaseIterator<T>::operator-=(const difference_type ind) noexcept
// {
//     index -= ind;
//     return *this;
// }


template <TypeForMatrix T>
void BaseIterator<T>::expride_exept_check(const size_t line) const
{
    if (pdata.expired())
    {
        time_t curTime = time(NULL);
        throw ExpiredException(ctime(&curTime), __FILE__, line,
                               typeid(*this).name(), __func__);
    }
}

template <TypeForMatrix T>
void BaseIterator<T>::index_exept_check(const size_t line) const
{
    if (index >= size)
    {
        time_t curTime = time(NULL);
        throw IterIndexException(ctime(&curTime), __FILE__, line, typeid(*this).name(), __func__);
    }
}



