#pragma once

#include <memory>
#include <limits.h>

#include "MatrixImpl.hpp"
#include "MaxtrixConcepts.hpp"
#include "BaseIterator.h"

template <TypeForMatrix T>
class Matrix;

template <TypeForMatrix T>
class ReverseIterator: public BaseIterator<T>
{
    friend class Matrix<T>;

public:
    using iterator_category = random_access_iterator_tag;
    using value_type = T;
    using difference_type = ptrdiff_t;
    using pointer = shared_ptr<T[]>; //T*; // shared_ptr специальный конструктор котрый будеь держать весь класс подвязывает к др указателю
    using reference = T&; 
	
	ReverseIterator() noexcept = default;
	ReverseIterator(const ReverseIterator<T>&& iter) noexcept;
    ReverseIterator(const ReverseIterator<T>& iter) noexcept;
	explicit ReverseIterator(const Matrix<T> &mtrx, const size_t index = SIZE_MAX) noexcept;

	// operator bool() const noexcept;

	reference operator*() const;
	// const T& operator*() const;

	pointer operator->() const;
	// const T* operator->() const;

	reference operator[](const difference_type ind) const noexcept;

	difference_type distance(const ReverseIterator<T> &other) const;
	difference_type operator -(const ReverseIterator<T> &other) const;

	ReverseIterator<T>& operator++() noexcept;
	ReverseIterator<T> operator++(int) noexcept;

    ReverseIterator<T>& operator--() noexcept;
	ReverseIterator<T> operator--(int) noexcept;

	ReverseIterator<T> operator+(const difference_type ind) const noexcept;
	ReverseIterator<T> operator-(const difference_type ind) const noexcept;

	ReverseIterator<T> &operator+=(const difference_type ind) noexcept;
	ReverseIterator<T> &operator-=(const difference_type ind) noexcept;

	ReverseIterator<T> &operator=(const ReverseIterator<T> &iter);
	ReverseIterator<T> &operator=(const ReverseIterator<T> &&iter);

	auto operator<=>(const ReverseIterator<T> &other) const noexcept {return this->index <=> other.index;};
	
	// T& operator [](size_t ind);
	// const T& operator [](size_t ind) const;
};

template <TypeForMatrix T>
ReverseIterator<T> operator+(const typename ReverseIterator<T>::difference_type ind, const ReverseIterator<T> &iter) noexcept;
