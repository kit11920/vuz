#pragma once
#include <memory>
#include <algorithm>
#include <ctime>
#include "ReverseIterator.h"
#include "Exceptions.h"

#include <iterator>

using namespace std;

template <TypeForMatrix T>
ReverseIterator<T>::ReverseIterator(const ReverseIterator<T>& iter) noexcept: BaseIterator<T>() 
{
    this->pdata = iter.pdata;
    this->size = iter.size;
    this->index = iter.index;
}

template <TypeForMatrix T>
ReverseIterator<T>::ReverseIterator(const ReverseIterator<T>&& iter) noexcept: BaseIterator<T>(iter)
{
    this->pdata = iter.pdata;
    this->size = iter.size;
    this->index = iter.index;
}

template <TypeForMatrix T>
ReverseIterator<T>::ReverseIterator(const Matrix<T> &mtrx) noexcept   
{
    std::weak_ptr<T[]> tmpdata = mtrx.data;
    this->pdata = tmpdata;
    this->size = mtrx.size();
    this->index = this->size - 1;
}

template <TypeForMatrix T>
ReverseIterator<T>::reference ReverseIterator<T>::operator*() const
{
    this->expride_exept_check(__LINE__);
    this->index_exept_check(__LINE__);

    shared_ptr<T[]> a = this->pdata.lock();
    return *(a.get() + this->index);
}

// template <TypeForMatrix T>
// const T& ReverseIterator<T>::operator*() const
// {

//     expride_exept_check(__LINE__);
//     index_exept_check(__LINE__);

//     const shared_ptr<T[]> a = pdata.lock();
//     return *(a.get() + index);
// };

template <TypeForMatrix T>
ReverseIterator<T>::pointer ReverseIterator<T>::operator->() const
{
    // shared_ptr<T[]> a = this->pdata.lock();
    // return a.get() + this->index;
    this->expride_exept_check(__LINE__);
    this->index_exept_check(__LINE__);

    shared_ptr<T[]> a = this->pdata.lock();
    return {a->shared_from_this(), a.get() + this->index};
}

template <TypeForMatrix T>
ReverseIterator<T>::reference ReverseIterator<T>::operator[](const ReverseIterator<T>::difference_type ind) const
{
    shared_ptr<T[]> tmp = this->pdata.lock();
    return *(tmp.get() + this->index + ind);
}

// template <TypeForMatrix T>
// const T* ReverseIterator<T>::operator->() const
// {
//     const shared_ptr<T[]> a = pdata.lock();
//     return a.get() + index;
// }

// template <TypeForMatrix T>
// ReverseIterator<T>::operator bool() const noexcept
// {
//     return !pdata.expired() && index < size;
// }

template <TypeForMatrix T>
ReverseIterator<T>::difference_type ReverseIterator<T>::operator -(const ReverseIterator<T> &other) const
{
    return other.index - this->index;
}

template <TypeForMatrix T>
ReverseIterator<T>::difference_type ReverseIterator<T>::distance(const ReverseIterator<T> &other) const
{
    return other.index - this->index;
}

template <TypeForMatrix T>
ReverseIterator<T> &ReverseIterator<T>::operator++() noexcept
{
    --this->index;
    return *this;
}

template <TypeForMatrix T>
ReverseIterator<T> ReverseIterator<T>::operator++(int) noexcept
{
    ReverseIterator<T> tmp(*this);
    --this->index;
    return tmp;
}

template <TypeForMatrix T>
ReverseIterator<T> &ReverseIterator<T>::operator--() noexcept
{
    ++this->index;
    return *this;
}

template <TypeForMatrix T>
ReverseIterator<T> ReverseIterator<T>::operator--(int) noexcept
{
    ReverseIterator<T> tmp(*this);
    ++this->index;
    return tmp;
}

template <TypeForMatrix T>
ReverseIterator<T> ReverseIterator<T>::operator+(const difference_type ind) const noexcept
{
    ReverseIterator<T> tmp(*this);
    tmp -= ind;
    return tmp;
}

template <TypeForMatrix T>
ReverseIterator<T> operator+(const typename ReverseIterator<T>::difference_type ind, const ReverseIterator<T> &iter) noexcept
{
    return iter + ind;
}

template <TypeForMatrix T>
ReverseIterator<T> ReverseIterator<T>::operator-(const difference_type ind) const noexcept
{
    ReverseIterator<T> tmp(*this);
    tmp += ind;
    return tmp;
}

template <TypeForMatrix T>
ReverseIterator<T> &ReverseIterator<T>::operator+=(const difference_type ind) noexcept
{
    this->index -= ind;
    return *this;
}

template <TypeForMatrix T>
ReverseIterator<T> &ReverseIterator<T>::operator-=(const difference_type ind) noexcept
{
    this->index += ind;
    return *this;
}

template <TypeForMatrix T>
ReverseIterator<T> &ReverseIterator<T>::operator=(const ReverseIterator<T> &iter)
{
    this->pdata = iter.pdata;
    this->size = iter.size;
    this->index = iter.index;
    return *this;
}

template <TypeForMatrix T>
ReverseIterator<T> &ReverseIterator<T>::operator=(const ReverseIterator<T> &&iter)
{
    this->pdata = iter.pdata;
    this->size = iter.size;
    this->index = iter.index;
    return *this;
}




// template <TypeForMatrix T>
// void ReverseIterator<T>::expride_exept_check(const size_t line) const
// {
//     if (pdata.expired())
//     {
//         time_t curTime = time(NULL);
//         throw ExpiredException(ctime(&curTime), __FILE__, line,
//                                typeid(*this).name(), __func__);
//     }
// }

// template <TypeForMatrix T>
// void ReverseIterator<T>::index_exept_check(const size_t line) const
// {
//     if (index >= size)
//     {
//         time_t curTime = time(NULL);
//         throw IterIndexException(ctime(&curTime), __FILE__, line, typeid(*this).name(), __func__);
//     }
// }

