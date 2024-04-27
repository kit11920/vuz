#pragma once

#include <memory>
#include <cstdlib>

#include "MatrixImpl.hpp"
#include "MaxtrixConcepts.hpp"
// #include "BaseIterator.h"


template <TypeForMatrix T>
class BaseIterator
{
public:
    using iterator_category = random_access_iterator_tag;
    using value_type = T;
    using difference_type = ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    operator bool() const noexcept;

	const T& operator*() const;
	const T* operator->() const;

	// virtual BaseIterator<T>& operator++() noexcept;
	// virtual BaseIterator<T> operator++(int) noexcept;

    // virtual BaseIterator<T>& operator--() noexcept;
	// virtual BaseIterator<T> operator--(int) noexcept;

	// virtual BaseIterator<T> operator+(const difference_type ind) const noexcept;
	// virtual BaseIterator<T> operator-(const difference_type ind) const noexcept;

	// virtual BaseIterator<T> &operator+=(const difference_type ind) noexcept;
	// virtual BaseIterator<T> &operator-=(const difference_type ind) noexcept;

	auto operator<=>(const BaseIterator<T> &other) const {return this->index <=> other.index;};
	// bool operator==(const BaseIterator<T> &other) const = default;

	const T& operator [](size_t ind) const;

	virtual ~BaseIterator() = default;
protected:
    BaseIterator() noexcept = default;
    explicit BaseIterator(const BaseIterator &iterator) noexcept;
    
	weak_ptr<T[]> pdata;
    size_t index = 0;
    size_t size = 0;

	void expride_exept_check(const size_t line) const;
    void index_exept_check(const size_t line) const;

// private:
	
};



