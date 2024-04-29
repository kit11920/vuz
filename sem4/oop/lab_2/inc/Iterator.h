#pragma once

#include <memory>

#include "MatrixImpl.hpp"
#include "MaxtrixConcepts.hpp"
#include "BaseIteratorImpl.hpp"

template <TypeForMatrix T>
class Matrix;

template <TypeForMatrix T>
class Iterator: public BaseIterator<T>
{
    friend class Matrix<T>;	// УДАЛИИИИИИ

public:
    using iterator_category = random_access_iterator_tag;
	// using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*; //shared_ptr<T[]>;  // shared_ptr специальный конструктор котрый будеь держать весь класс подвязывает к др указателю
    using reference = T&; // const

	Iterator() noexcept = default;
	Iterator(Iterator<T>&& iter) noexcept;
    Iterator(const Iterator<T>& iter) noexcept; // if make it explicit (std::vector<int>(m1.begin(), tt);) wouldn't work
	explicit Iterator(const Matrix<T> &mtrx) noexcept;

	reference operator*() const;
	// const T& operator*() const;

	pointer operator->() const;
	// const T* operator->() const;

	reference operator[](const difference_type ind) const;

	difference_type distance(const Iterator<T> &other) const;
	difference_type operator -(const Iterator<T> &other) const;

	Iterator<T>& operator++() noexcept;
	Iterator<T> operator++(int) noexcept;

    Iterator<T>& operator--() noexcept;
	Iterator<T> operator--(int) noexcept;

	Iterator<T> operator+(const difference_type ind) const noexcept;
	Iterator<T> operator-(const difference_type ind) const noexcept;

	Iterator<T> &operator+=(const difference_type ind) noexcept;
	Iterator<T> &operator-=(const difference_type ind) noexcept;

	Iterator<T> &operator=(const Iterator<T> &iter);
	Iterator<T> &operator=(const Iterator<T> &&iter);

	auto operator<=>(const Iterator<T> &other) const {return this->index <=> other.index;};
	
	// T& operator [](size_t ind);
	// const T& operator [](size_t ind) const;
};


template <TypeForMatrix T>
Iterator<T> operator+(const typename Iterator<T>::difference_type ind, const Iterator<T> &iter) noexcept;


