#pragma once

#include <memory>

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
    using pointer = T*;
    using reference = T&;

	ReverseIterator() noexcept = default;
	ReverseIterator(const ReverseIterator<T>&& iter) noexcept;
    explicit ReverseIterator(const ReverseIterator<T>& iter) noexcept;
	explicit ReverseIterator(const Matrix<T> &mtrx) noexcept;

	// operator bool() const noexcept;
	ReverseIterator<T>& operator=(const ReverseIterator<T>& iter) noexcept;

	reference operator*();
	// const T& operator*() const;

	T* operator->();
	// const T* operator->() const;

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

	// auto operator<=>(const ReverseIterator<T> &other) const {return this->index <=> other.index;};
	// // bool operator==(const ReverseIterator<T> &other) const {return this->index == other.index;};
	
	T& operator [](size_t ind);
	// const T& operator [](size_t ind) const;

	

// protected:
//     void expride_exept_check(const size_t line) const;
//     void index_exept_check(const size_t line) const;

// private:
// 	weak_ptr<T[]> pdata;
};


