#pragma once

#include <memory>

#include "MatrixImpl.hpp"
#include "MaxtrixConcepts.hpp"
#include "BaseIterator.h"

template <TypeForMatrix T>
class Matrix;

template <TypeForMatrix T>
class ConstIterator: public BaseIterator<T>
{
    friend class Matrix<T>;

public:
    using iterator_category = random_access_iterator_tag;
    using value_type = T;
    using difference_type = ptrdiff_t;
    using pointer = T*;
    using reference = T&;

	ConstIterator() noexcept = default;
	ConstIterator(const ConstIterator<T>&& iter) noexcept;
    ConstIterator(const Iterator<T>& iter) noexcept;
    explicit ConstIterator(const ConstIterator<T>& iter) noexcept;
	explicit ConstIterator(const Matrix<T> &mtrx) noexcept;

	// operator bool() const noexcept;

	const T& operator*() const;
	const T* operator->() const;

	difference_type distance(const ConstIterator<T> &other) const;
	difference_type operator -(const ConstIterator<T> &other) const;

	ConstIterator<T>& operator++() noexcept;
	ConstIterator<T> operator++(int) noexcept;

    ConstIterator<T>& operator--() noexcept;
	ConstIterator<T> operator--(int) noexcept;

	ConstIterator<T> operator+(const difference_type ind) const noexcept;
	ConstIterator<T> operator-(const difference_type ind) const noexcept;

	ConstIterator<T> &operator+=(const difference_type ind) noexcept;
	ConstIterator<T> &operator-=(const difference_type ind) noexcept;

	// auto operator<=>(const ConstIterator<T> &other) const {return this->index <=> other.index;};

	// const T& operator [](size_t ind) const;

// protected:
//     // void expride_exept_check(const size_t line) const;
//     // void index_exept_check(const size_t line) const;

// private:
// 	weak_ptr<T[]> pdata;
};


