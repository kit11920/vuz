#include "BaseMatrix.h"
using namespace std;


BaseMatrix::BaseMatrix(const size_t rows_new, const size_t cols_new)
{
    rows = rows_new;
    cols = cols_new;
}

size_t BaseMatrix::size() const noexcept
{
    return rows * cols;
}

bool BaseMatrix::is_empty() const noexcept
{
    return this->size() == 0;
}

BaseMatrix::operator bool() const noexcept
{
    return !this->is_empty();
}

size_t BaseMatrix::get_rows() const noexcept
{
    return rows;
}

size_t BaseMatrix::get_cols() const noexcept
{
    return cols;
}

BaseMatrix::~BaseMatrix() = default;
