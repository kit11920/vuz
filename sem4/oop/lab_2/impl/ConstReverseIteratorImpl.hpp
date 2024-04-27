#pragma once
#include <memory>
#include <algorithm>
#include <ctime>
#include "ConstReverseIterator.h"
#include "Exceptions.h"

#include <iterator>

using namespace std;

template <TypeForMatrix T>
ConstReverseIterator<T>::ConstReverseIterator(const ConstReverseIterator<T>& iter) noexcept: BaseIterator<T>() 
{
    this->pdata = iter.pdata;
    this->size = iter.size;
    this->index = iter.index;
}

template <TypeForMatrix T>
ConstReverseIterator<T>::ConstReverseIterator(const ConstReverseIterator<T>&& iter) noexcept: BaseIterator<T>(iter)
{
    this->pdata = iter.pdata;
    this->size = iter.size;
    this->index = iter.index;
}

template <TypeForMatrix T>
ConstReverseIterator<T>::ConstReverseIterator(const ReverseIterator<T>& iter) noexcept: BaseIterator<T>(iter)
{
    this->pdata = iter.pdata;
    this->size = iter.size;
    this->index = iter.index;
}

template <TypeForMatrix T>
ConstReverseIterator<T>::ConstReverseIterator(const Matrix<T> &mtrx) noexcept   
{
    std::weak_ptr<T[]> tmpdata = mtrx.data;
    this->pdata = tmpdata;
    this->size = mtrx.size();
    this->index = this->size - 1;
}

template <TypeForMatrix T>
const T& ConstReverseIterator<T>::operator*() const
{

    this->expride_exept_check(__LINE__);
    this->index_exept_check(__LINE__);

    const shared_ptr<T[]> a = this->pdata.lock();
    return *(a.get() + this->index);
};
template <TypeForMatrix T>
const T* ConstReverseIterator<T>::operator->() const
{
    const shared_ptr<T[]> a = this->pdata.lock();
    return a.get() + this->index;
}

// template <TypeForMatrix T>
// ConstReverseIterator<T>::operator bool() const noexcept
// {
//     return !pdata.expired() && index < size;
// }

template <TypeForMatrix T>
ConstReverseIterator<T>& ConstReverseIterator<T>::operator=(const ConstReverseIterator<T>& iter) noexcept
{
    this->pdata.reset(iter.pdata);
    this->size = iter.size;
    this->index = iter.index;
}

template <TypeForMatrix T>
ConstReverseIterator<T>::difference_type ConstReverseIterator<T>::operator -(const ConstReverseIterator<T> &other) const
{
    return other.index - this->index;
}

template <TypeForMatrix T>
ConstReverseIterator<T>::difference_type ConstReverseIterator<T>::distance(const ConstReverseIterator<T> &other) const
{
    return other.index - this->index;
}

template <TypeForMatrix T>
ConstReverseIterator<T> &ConstReverseIterator<T>::operator++() noexcept
{
    --this->index;
    return *this;
}

template <TypeForMatrix T>
ConstReverseIterator<T> ConstReverseIterator<T>::operator++(int) noexcept
{
    ConstReverseIterator<T> tmp(*this);
    --this->index;
    return tmp;
}

template <TypeForMatrix T>
ConstReverseIterator<T> &ConstReverseIterator<T>::operator--() noexcept
{
    ++this->index;
    return *this;
}

template <TypeForMatrix T>
ConstReverseIterator<T> ConstReverseIterator<T>::operator--(int) noexcept
{
    ConstReverseIterator<T> tmp(*this);
    ++this->index;
    return tmp;
}

template <TypeForMatrix T>
ConstReverseIterator<T> ConstReverseIterator<T>::operator+(const difference_type ind) const noexcept
{
    ConstReverseIterator<T> tmp(*this);
    tmp -= ind;
    return tmp;
}

template <TypeForMatrix T>
ConstReverseIterator<T> ConstReverseIterator<T>::operator-(const difference_type ind) const noexcept
{
    ConstReverseIterator<T> tmp(*this);
    tmp += ind;
    return tmp;
}

template <TypeForMatrix T>
ConstReverseIterator<T> &ConstReverseIterator<T>::operator+=(const difference_type ind) noexcept
{
    this->index -= ind;
    return *this;
}

template <TypeForMatrix T>
ConstReverseIterator<T> &ConstReverseIterator<T>::operator-=(const difference_type ind) noexcept
{
    this->index += ind;
    return *this;
}

// template <TypeForMatrix T>
// const T& ConstReverseIterator<T>::operator [](size_t ind) const
// {
//     const shared_ptr<T[]> tmp = pdata.lock();
//     return *(tmp.get() + this->index - ind);
// }

// template <TypeForMatrix T>
// void ConstReverseIterator<T>::expride_exept_check(const size_t line) const
// {
//     if (pdata.expired())
//     {
//         time_t curTime = time(NULL);
//         throw ExpiredException(ctime(&curTime), __FILE__, line,
//                                typeid(*this).name(), __func__);
//     }
// }

// template <TypeForMatrix T>
// void ConstReverseIterator<T>::index_exept_check(const size_t line) const
// {
//     if (index >= size)
//     {
//         time_t curTime = time(NULL);
//         throw IterIndexException(ctime(&curTime), __FILE__, line, typeid(*this).name(), __func__);
//     }
// }

