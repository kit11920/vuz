#pragma once

#include <memory>

#include "MatrixImpl.hpp"
#include "MaxtrixConcepts.hpp"
// #include "BaseIterator.h"
#include "BaseIteratorImpl.hpp"

template <TypeForMatrix T>
class Matrix;

template <TypeForMatrix T>
class Iterator: public BaseIterator<T> // BaseIterator
{
    friend class Matrix<T>;

public:
    using iterator_category = random_access_iterator_tag;
    using value_type = T;
    using difference_type = ptrdiff_t;
    using pointer = T*;
    using reference = T&;

	Iterator() noexcept = default;
	Iterator(Iterator<T>&& iter) noexcept;
    explicit Iterator(const Iterator<T>& iter) noexcept;
	explicit Iterator(const Matrix<T> &mtrx) noexcept;

	// operator bool() const noexcept;

	T& operator*();
	// const T& operator*() const;

	T* operator->();
	// const T* operator->() const;

	difference_type distance(const Iterator<T> &other);
	difference_type operator -(const Iterator<T> &other);

	Iterator<T>& operator++() noexcept;
	Iterator<T> operator++(int) noexcept;

    Iterator<T>& operator--() noexcept;
	Iterator<T> operator--(int) noexcept;

	Iterator<T> operator+(const difference_type ind) const noexcept;
	Iterator<T> operator-(const difference_type ind) const noexcept;

	Iterator<T> &operator+=(const difference_type ind) noexcept;
	Iterator<T> &operator-=(const difference_type ind) noexcept;

	// auto operator<=>(const Iterator<T> &other) const {return this->index <=> other.index;};
	// // bool operator==(const Iterator<T> &other) const = default;
	
	T& operator [](size_t ind);
	// const T& operator [](size_t ind) const;

	

// protected:
    // void expride_exept_check(const size_t line) const;
    // void index_exept_check(const size_t line) const;

// private:
// 	weak_ptr<T[]> pdata;
};


