#pragma once
#include <memory>
#include <algorithm>
#include <ctime>
#include "Iterator.h"
#include "Exceptions.h"

#include <iterator>

using namespace std;

template <TypeForMatrix T>
Iterator<T>::Iterator(const Iterator<T>& iter) noexcept: BaseIterator<T>::BaseIterator(iter) 
{
    cout << "(const Iterator<T>& iter)" << endl;
    this->pdata = iter.pdata;
    this->size = iter.size;
    this->index = iter.index;
}

template <TypeForMatrix T>
Iterator<T>::Iterator(Iterator<T>&& iter) noexcept //: BaseIterator<T>::BaseIterator(iter)
{
    cout << "(const Iterator<T>&& iter)" << endl;
    this->pdata = iter.pdata;
    this->size = iter.size;
    this->index = iter.index;
}

template <TypeForMatrix T>
Iterator<T>::Iterator(const Matrix<T> &mtrx, const size_t index) noexcept   
{
    std::weak_ptr<T[]> tmpdata = mtrx.data;
    this->pdata = tmpdata;
    this->size = mtrx.rows * mtrx.cols;
    this->index = index;
}

template <TypeForMatrix T>
Iterator<T>::reference Iterator<T>::operator*() const
{
    this->expride_exeption(__LINE__);
    this->index_exeption(__LINE__);

    shared_ptr<T[]> a = this->pdata.lock();
    return *(a.get() + this->index);
}

// template <TypeForMatrix T>
// const T& Iterator<T>::operator*() const
// {

//     expride_exeption(__LINE__);
//     index_exeption(__LINE__);

//     const shared_ptr<T[]> a = pdata.lock();
//     return *(a.get() + index);
// };

template <TypeForMatrix T>
Iterator<T>::pointer Iterator<T>::operator->() const
{
    this->expride_exeption(__LINE__);
    this->index_exeption(__LINE__);
    // shared_ptr<T[]> a = this->pdata.lock();
    // return a.get() + this->index;

    shared_ptr<T[]> a = this->pdata.lock();
    return {a->shared_from_this(), a.get() + this->index};
    // shared_ptr<T[]> a = this->pdata.lock();
    // return shared_ptr<T[]>(a.get() + this->index);
}

template <TypeForMatrix T>
Iterator<T>::reference Iterator<T>::operator[](const Iterator<T>::difference_type ind) const noexcept
{
    shared_ptr<T[]> tmp = this->pdata.lock();
    return *(tmp.get() + this->index + ind);
}

// template <TypeForMatrix T>
// const T* Iterator<T>::operator->() const
// {
//     const shared_ptr<T[]> a = pdata.lock();
//     return a.get() + index;
// }

// template <TypeForMatrix T>
// Iterator<T>::operator bool() const noexcept
// {
//     return !pdata.expired() && index < size;
// }

template <TypeForMatrix T>
Iterator<T>::difference_type Iterator<T>::operator -(const Iterator<T> &other) const noexcept
{
    return other.index - this->index;
}

template <TypeForMatrix T>
Iterator<T>::difference_type Iterator<T>::distance(const Iterator<T> &other) const noexcept
{
    return other.index - this->index;
}

template <TypeForMatrix T>
Iterator<T> &Iterator<T>::operator++() noexcept
{

    ++this->index;
    return *this;
}

template <TypeForMatrix T>
Iterator<T> Iterator<T>::operator++(int) noexcept
{
    Iterator<T> tmp(*this);
    ++this->index;
    return tmp;
}

template <TypeForMatrix T>
Iterator<T> &Iterator<T>::operator--() noexcept
{
    --this->index;
    return *this;
}

template <TypeForMatrix T>
Iterator<T> Iterator<T>::operator--(int) noexcept
{
    Iterator<T> tmp(*this);
    --this->index;
    return tmp;
}

template <TypeForMatrix T>
Iterator<T> Iterator<T>::operator+(const difference_type ind) const noexcept
{
    Iterator<T> tmp(*this);
    tmp += ind;
    return tmp;
}

template <TypeForMatrix T>
Iterator<T> operator+(const typename Iterator<T>::difference_type ind, const Iterator<T> &iter) noexcept
{
    return iter + ind;
}


template <TypeForMatrix T>
Iterator<T> Iterator<T>::operator-(const difference_type ind) const noexcept
{
    Iterator<T> tmp(*this);
    tmp -= ind;
    return tmp;
}

template <TypeForMatrix T>
Iterator<T> &Iterator<T>::operator+=(const difference_type ind) noexcept
{
    this->index += ind;
    return *this;
}

template <TypeForMatrix T>
Iterator<T> &Iterator<T>::operator-=(const difference_type ind) noexcept
{
    this->index -= ind;
    return *this;
}

template <TypeForMatrix T>
Iterator<T> &Iterator<T>::operator=(const Iterator<T> &iter)
{
    this->pdata = iter.pdata;
    this->size = iter.size;
    this->index = iter.index;
    return *this;
}

template <TypeForMatrix T>
Iterator<T> &Iterator<T>::operator=(const Iterator<T> &&iter)
{
    this->pdata = iter.pdata;
    this->size = iter.size;
    this->index = iter.index;
    return *this;
}


// template <TypeForMatrix T>
// const T& Iterator<T>::operator [](size_t ind) const
// {
//     const shared_ptr<T[]> tmp = pdata.lock();
//     return *(tmp.get() + this->index + ind);
// }

// template <TypeForMatrix T>
// T& Iterator<T>::operator [](size_t ind)
// {
//     shared_ptr<T[]> tmp = this->pdata.lock();
//     return *(tmp.get() + this->index + ind);
// }




// template <TypeForMatrix T>
// void Iterator<T>::expride_exeption(const size_t line) const
// {
//     if (pdata.expired())
//     {
//         time_t curTime = time(NULL);
//         throw ExpiredException(ctime(&curTime), __FILE__, line,
//                                typeid(*this).name(), __func__);
//     }
// }

// template <TypeForMatrix T>
// void Iterator<T>::index_exeption(const size_t line) const
// {
//     if (index >= size)
//     {
//         time_t curTime = time(NULL);
//         throw IterIndexException(ctime(&curTime), __FILE__, line, typeid(*this).name(), __func__);
//     }
// }

