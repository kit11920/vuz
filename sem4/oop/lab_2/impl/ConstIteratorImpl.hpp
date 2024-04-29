#pragma once
#include <memory>
#include <algorithm>
#include <ctime>
#include "ConstIterator.h"
#include "Exceptions.h"

#include <iterator>

using namespace std;

template <TypeForMatrix T>
ConstIterator<T>::ConstIterator(const ConstIterator<T>& iter) noexcept: BaseIterator<T>() 
{
    this->pdata = iter.pdata;
    this->size = iter.size;
    this->index = iter.index;
}

template <TypeForMatrix T>
ConstIterator<T>::ConstIterator(const ConstIterator<T>&& iter) noexcept: BaseIterator<T>(iter)
{
    this->pdata = iter.pdata;
    this->size = iter.size;
    this->index = iter.index;
}

template <TypeForMatrix T>
ConstIterator<T>::ConstIterator(const Iterator<T>& iter) noexcept: BaseIterator<T>(iter)
{
    this->pdata = iter.pdata;
    this->size = iter.size;
    this->index = iter.index;
}

template <TypeForMatrix T>
ConstIterator<T>::ConstIterator(const Matrix<T> &mtrx, const size_t index) noexcept   
{
    std::weak_ptr<T[]> tmpdata = mtrx.data;
    this->pdata = tmpdata;
    this->size = mtrx.rows * mtrx.cols;
    this->index = index;
}

template <TypeForMatrix T>
ConstIterator<T>::reference ConstIterator<T>::operator*() const
{

    this->expride_exeption(__LINE__);
    this->index_exeption(__LINE__);

    shared_ptr<T[]> a = this->pdata.lock();
    return *(a.get() + this->index);
};

template <TypeForMatrix T>
ConstIterator<T>::pointer ConstIterator<T>::operator->() const
{
    // const shared_ptr<T[]> a = this->pdata.lock();
    // return a.get() + this->index;

    this->expride_exeption(__LINE__);
    this->index_exeption(__LINE__);

    shared_ptr<T[]> a = this->pdata.lock();
    return {a->shared_from_this(), a.get() + this->index};
}

template <TypeForMatrix T>
ConstIterator<T>::reference ConstIterator<T>::operator[](const ConstIterator<T>::difference_type ind) const noexcept
{
    shared_ptr<T[]> tmp = this->pdata.lock();
    return *(tmp.get() + this->index + ind);
}

template <TypeForMatrix T>
ConstIterator<T>::difference_type ConstIterator<T>::operator -(const ConstIterator<T> &other) const
{
    return other.index - this->index;
}

template <TypeForMatrix T>
ConstIterator<T>::difference_type ConstIterator<T>::distance(const ConstIterator<T> &other) const
{
    return other.index - this->index;
}

template <TypeForMatrix T>
ConstIterator<T> &ConstIterator<T>::operator++() noexcept
{

    ++this->index;
    return *this;
}

template <TypeForMatrix T>
ConstIterator<T> ConstIterator<T>::operator++(int) noexcept
{
    ConstIterator<T> tmp(*this);
    ++this->index;
    return tmp;
}

template <TypeForMatrix T>
ConstIterator<T> &ConstIterator<T>::operator--() noexcept
{
    --this->index;
    return *this;
}

template <TypeForMatrix T>
ConstIterator<T> ConstIterator<T>::operator--(int) noexcept
{
    ConstIterator<T> tmp(*this);
    --this->index;
    return tmp;
}

template <TypeForMatrix T>
ConstIterator<T> ConstIterator<T>::operator+(const difference_type ind) const noexcept
{
    ConstIterator<T> tmp(*this);
    tmp += ind;
    return tmp;
}

template <TypeForMatrix T>
ConstIterator<T> operator+(const typename ConstIterator<T>::difference_type ind, const ConstIterator<T> &iter) noexcept
{
    return iter + ind;
}

template <TypeForMatrix T>
ConstIterator<T> ConstIterator<T>::operator-(const difference_type ind) const noexcept
{
    ConstIterator<T> tmp(*this);
    tmp -= ind;
    return tmp;
}

template <TypeForMatrix T>
ConstIterator<T> &ConstIterator<T>::operator+=(const difference_type ind) noexcept
{
    this->index += ind;
    return *this;
}

template <TypeForMatrix T>
ConstIterator<T> &ConstIterator<T>::operator-=(const difference_type ind) noexcept
{
    this->index -= ind;
    return *this;
}

template <TypeForMatrix T>
ConstIterator<T> &ConstIterator<T>::operator=(const ConstIterator<T> &iter)
{
    this->pdata = iter.pdata;
    this->size = iter.size;
    this->index = iter.index;
    return *this;
}

template <TypeForMatrix T>
ConstIterator<T> &ConstIterator<T>::operator=(const ConstIterator<T> &&iter)
{
    this->pdata = iter.pdata;
    this->size = iter.size;
    this->index = iter.index;
    return *this;
}