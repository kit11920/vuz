#pragma once

#include <cstddef>
#include <memory>
using namespace std;

// Абстрактный базовый класс
class BaseMatrix
{
public:
    using size_type = size_t;

    // BaseMatrix() noexcept = default;
    BaseMatrix(const size_t rows_new = 0, const size_t cols_new = 0);
    virtual ~BaseMatrix() = 0;

    size_t size() const noexcept;
    bool is_empty() const noexcept;
    operator bool() const noexcept;
    size_t get_rows() const noexcept;
    size_t get_cols() const noexcept;

protected:
    size_t rows = 0;
    size_t cols = 0;
    // shared_ptr<size_t> rows;
    // shared_ptr<size_t> cols;
};
