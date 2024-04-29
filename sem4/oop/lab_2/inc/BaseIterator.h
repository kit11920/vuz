#pragma once

#include <memory>
#include <cstdlib>

#include "MatrixImpl.hpp"
#include "MaxtrixConcepts.hpp"

using namespace std;

template <TypeForMatrix T>
class BaseIterator
{
public:
    operator bool() const noexcept;

	const T& operator*() const;
	const T* operator->() const;

	auto operator<=>(const BaseIterator<T> &other) const {return this->index <=> other.index;};

	virtual ~BaseIterator() = default;
protected:
    BaseIterator() noexcept = default;
    explicit BaseIterator(const BaseIterator &iterator) noexcept;
    
	weak_ptr<T[]> pdata;
    size_t index = 0;
    size_t size = 0;

	void expride_exeption(const size_t line) const;
    void index_exeption(const size_t line) const;	
};



