#pragma once

#include <memory>

#include "MatrixImpl.hpp"
#include "MaxtrixConcepts.hpp"
#include "BaseIterator.h"
#include "ReverseIterator.h"

template <TypeForMatrix T>
class Matrix;

template <TypeForMatrix T>
class ConstReverseIterator: public BaseIterator<T>
{
    friend class Matrix<T>;

public:
    using iterator_category = random_access_iterator_tag;
    using value_type = T;
    using difference_type = ptrdiff_t;
    using pointer = T*;
    using reference = T&;

	ConstReverseIterator() noexcept = default;
	ConstReverseIterator(const ConstReverseIterator<T>&& iter) noexcept;
    explicit ConstReverseIterator(const ConstReverseIterator<T>& iter) noexcept;
    ConstReverseIterator(const ReverseIterator<T>& iter) noexcept;
	explicit ConstReverseIterator(const Matrix<T> &mtrx) noexcept;

	// operator bool() const noexcept;
	ConstReverseIterator<T>& operator=(const ConstReverseIterator<T>& iter) noexcept;

	const T& operator*() const;
	const T* operator->() const;

	difference_type distance(const ConstReverseIterator<T> &other) const ;
	difference_type operator -(const ConstReverseIterator<T> &other) const ;

	ConstReverseIterator<T>& operator++() noexcept;
	ConstReverseIterator<T> operator++(int) noexcept;

    ConstReverseIterator<T>& operator--() noexcept;
	ConstReverseIterator<T> operator--(int) noexcept;

	ConstReverseIterator<T> operator+(const difference_type ind) const noexcept;
	ConstReverseIterator<T> operator-(const difference_type ind) const noexcept;

	ConstReverseIterator<T> &operator+=(const difference_type ind) noexcept;
	ConstReverseIterator<T> &operator-=(const difference_type ind) noexcept;

	// auto operator<=>(const ConstReverseIterator<T> &other) const {return this->index <=> other.index;};
	
	// const T& operator [](size_t ind) const;

	

// protected:
//     void expride_exept_check(const size_t line) const;
//     void index_exept_check(const size_t line) const;

// private:
// 	weak_ptr<T[]> pdata;
};


