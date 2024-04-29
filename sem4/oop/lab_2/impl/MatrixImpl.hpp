#pragma once

#include <ctime>
#include <typeinfo> 
#include "Matrix.h"
// #include "BaseMatrix.hpp"
// #include "MaxtrixConcepts.hpp"
#include "Exceptions.h"
#include "IteratorImpl.hpp"

using namespace std;

#pragma region Constructors
template <TypeForMatrix T>
Matrix<T>::Matrix(const size_t cols, const size_t rows): BaseMatrix(rows, cols)
{
    if (!rows and !cols) return;

    allocate(rows, cols);
    for (size_t i = 0; i < rows * cols; ++i)
    {
        data[i] = 0;
    }
}

template <TypeForMatrix T>
Matrix<T>::Matrix(Matrix<T> &&mtr) noexcept: BaseMatrix(mtr.rows, mtr.cols)
{
    this->data = mtr.data;
    mtr.data.reset();
}

template <TypeForMatrix T>
Matrix<T>::Matrix(const Matrix<T> &mtr): BaseMatrix(mtr.rows, mtr.cols)
{
    if (!rows and !cols) return;

    allocate(mtr.rows, mtr.cols);
    for (size_t i = 0; i < mtr.rows * mtr.cols; ++i)
    {
        data[i] = mtr.data[i];
    }
}

template <TypeForMatrix T>
Matrix<T>::Matrix(const initializer_list<initializer_list<T>> lst): BaseMatrix(lst.size(), lst.begin()->size())
{
    if (!rows and !cols) return;

    allocate(rows, cols);
    auto elem_i = lst.begin();
    for (size_t i = 0; elem_i < lst.end(); i++, elem_i++)
    {
        auto elem_j = elem_i->begin();

        for (size_t j = 0; elem_j < elem_i->end(); j++, elem_j++)
            data[i * cols + j] = *elem_j;
    }

}


template <TypeForMatrix T>
template <Convertable<T> U>
Matrix<T>::Matrix(const Matrix<U> &mtr): BaseMatrix(mtr.rows, mtr.cols)
{
    if (!rows and !cols) return;

    allocate(mtr.rows, mtr.cols);
    for (size_t i = 0; i < mtr.rows * mtr.colsl; ++i)
    {
        data[i] = mtr.data[i];
    }
}

template <TypeForMatrix T>
template <Convertable<T> U>
Matrix<T>::Matrix(const U **mtrx, const size_t cols, const size_t rows): BaseMatrix(rows, cols)
{
    if (!rows and !cols) return;

    allocate(rows, cols);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            data[i * cols + j] = mtrx[i][j];
}

template <TypeForMatrix T>
template <Convertable<T> U>
Matrix<T>::Matrix(const initializer_list<initializer_list<U>> lst): BaseMatrix(lst.size(), lst.begin()->size())
{
    if (!rows and !cols) return;

    allocate(rows, cols);
    auto elem_i = lst.begin();
    for (size_t i = 0; elem_i < lst.end(); i++, elem_i++)
    {
        auto elem_j = elem_i->begin();

        for (size_t j = 0; elem_j < elem_i->end(); j++, elem_j++)
            data[i * cols + j] = *elem_j;
    }

}

template <TypeForMatrix T>
template <ContainerConvertableAssignable<T> U>  
Matrix<T>::Matrix(const U& con, const size_t cols, const size_t rows)
{
    if (!rows and !cols) return;
    
    this->cols = cols;
    if (rows == 0)
        this->rows = (con.end() - con.begin()) / cols;
    else
        this->rows = rows;

    allocate(this->rows, this->cols);
    size_t i = 0;
    for (auto it = con.begin(); i < this->size && it != con.end(); ++it)
    {
        data[i] = *it;
        ++i;
    }
}


#pragma endregion Constructors

template <TypeForMatrix T>
Matrix<T>::~Matrix() = default;
// {
//     data.reset();
// }


#pragma region It_is_conteiner

template <TypeForMatrix T>
Iterator<T> Matrix<T>::begin() const noexcept
{
    Iterator<T> tmp(*this);
    return tmp;
}

template <TypeForMatrix T>
Iterator<T> Matrix<T>::end() const noexcept
{
    Iterator<T> tmp(*this, this->size());
    // tmp.index = this->size();
    return tmp;
}

template <TypeForMatrix T>
ReverseIterator<T> Matrix<T>::rbegin() const noexcept
{
    ReverseIterator<T> tmp(*this, this->size() - 1);
    // tmp.index = this->size() - 1;
    return tmp;
}

template <TypeForMatrix T>
ReverseIterator<T> Matrix<T>::rend() const noexcept
{
    ReverseIterator<T> tmp(*this);
    return tmp;
}

template <TypeForMatrix T>
ConstIterator<T> Matrix<T>::cbegin() const noexcept
{
    ConstIterator<T> tmp(*this);
    return tmp;
}

template <TypeForMatrix T>
ConstIterator<T> Matrix<T>::cend() const noexcept
{
    ConstIterator<T> tmp(*this, this->size());
    // tmp.index = this->size();
    return tmp;
}

template <TypeForMatrix T>
ConstReverseIterator<T> Matrix<T>::crbegin() const noexcept
{
    ConstReverseIterator<T> tmp(*this, this->size() - 1);
    // tmp.index = this->size() - 1;
    return tmp;
}

template <TypeForMatrix T>
ConstReverseIterator<T> Matrix<T>::crend() const noexcept
{
    ConstReverseIterator<T> tmp(*this);
    return tmp;
}

#pragma endregion It_is_conteiner

#pragma region Assignment

template <TypeForMatrix T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& mtr)
{
    data.reset();   
    rows = mtr.get_rows();
    cols = mtr.get_cols();
    allocate(rows, cols);

    for (size_t i = 0; i < rows * cols; i++)
        data[i] = mtr.data[i];

    return *this;
}

template <TypeForMatrix T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& mtr) noexcept
{
    data.reset();   
    rows = mtr.get_rows();
    cols = mtr.get_cols();
    data = mtr.data;
    mtr.data.reset();

    return *this;
}

template <TypeForMatrix T>
Matrix<T>& Matrix<T>::operator=(std::initializer_list<std::initializer_list<T>> elems)
{
    data.reset();   
    rows = elems.size();
    cols = elems.begin()->size();
    allocate(rows, cols);

    auto elem_i = elems.begin();
    for (size_t i = 0; elem_i < elems.end(); i++, elem_i++)
    {
        auto elem_j = elem_i->begin();
        for (size_t j = 0; elem_j < elem_i->end(); j++, elem_j++)
            data[i * cols + j] = *elem_j;
    }

    return *this;
}

template <TypeForMatrix T>
template <Convertable<T> U>
Matrix<T>& Matrix<T>::operator=(const Matrix<U>& mtr)
{
    data.reset();   
    rows = mtr.get_rows();
    cols = mtr.get_cols();
    allocate(rows, cols);

    for (size_t i = 0; i < rows * cols; i++)
        data[i] = mtr.get_elem(i);

    return *this;
}

template <TypeForMatrix T>
template <Convertable<T> U>
Matrix<T>& Matrix<T>::operator=(std::initializer_list<std::initializer_list<U>> elems)
{
    data.reset();   
    rows = elems.size();
    cols = elems.begin()->size();
    allocate(rows, cols);

    auto elem_i = elems.begin();
    for (size_t i = 0; elem_i < elems.end(); i++, elem_i++)
    {
        auto elem_j = elem_i->begin();
        for (size_t j = 0; j < elem_i->end(); j++, elem_j++)
            data[i * cols + j] = *elem_j;
    }

    return *this;
}


#pragma endregion Assignment

#pragma region Informating

template <TypeForMatrix T>
bool Matrix<T>::is_same_size(const BaseMatrix &mtrx) const noexcept
{
    return rows == mtrx.get_rows() && cols == mtrx.get_cols();
}

template <TypeForMatrix T>
bool Matrix<T>::is_square() const noexcept
{
    return rows == cols;
}

template <TypeForMatrix T>
bool Matrix<T>::is_zero() const noexcept
{
    bool res = true;
    for (size_t i = 0; res && i < this->size(); ++i)
        if (data[i] != 0)
            res = false;
    return res;
}

template <TypeForMatrix T>
bool Matrix<T>::is_empty() const noexcept
{
    return this->size == 0;
}

template <TypeForMatrix T>
bool Matrix<T>::is_identity() const noexcept
{
    bool res = true;
    for (size_t i = 0; res && i < rows; ++i)
        for (size_t j = 0; res && j < cols; ++j)
            if (i != j && data[i] != 0)
                res = false;
            else if (data[i] != 1)
                res = false;
    return res;
}

template <TypeForMatrix T>
template <Convertable<T> U> 
bool Matrix<T>::is_multiplicating(const Matrix<U> &mtrx) const noexcept
{
    return cols == mtrx.rows;
}

#pragma endregion Informating

#pragma region Comparison

template <TypeForMatrix T>
bool Matrix<T>::operator==(const Matrix<T> &mtrx) const noexcept
{
    if (!this->is_same_size(mtrx))
        return false;
    
    bool res = true;
    for (size_t i = 0; res && i < this->size(); ++i)
        if (data[i] != mtrx.data[i])
            res = false;
    return res;
}

template <TypeForMatrix T>
bool Matrix<T>::operator!=(const Matrix<T> &mtrx) const noexcept
{
    return !(*this == mtrx);
}

template <TypeForMatrix T>
bool Matrix<T>::is_equal(const Matrix<T> &mtrx) const noexcept
{
    return *this == mtrx;
}

template <TypeForMatrix T>
bool Matrix<T>::is_not_equal(const Matrix<T> &mtrx) const noexcept
{
    return *this != mtrx;
}
#pragma endregion Comparison

#pragma region Indexing
template <TypeForMatrix T>
Matrix<T>::MatrixLine Matrix<T>::operator[](size_t ind_row)
{
    return MatrixLine(*this, ind_row);
}

template <TypeForMatrix T>
const Matrix<T>::MatrixLine Matrix<T>::operator[](size_t ind_row) const
{
    const MatrixLine m(*this, ind_row);
    return m;
}

template <TypeForMatrix T>
T &Matrix<T>::get_value(size_t i, size_t j) const
{
    return *(data.get() + i * cols + j);
}

template <TypeForMatrix T>
T Matrix<T>::get_elem(size_t i) const
{
    return *(data.get() + i);
}

#pragma endregion Indexing

#pragma region ExceptionChecks
template <TypeForMatrix T>
void Matrix<T>::rows_index_exception(size_t ind_row, const char *filename, const size_t line) const
{
    if (ind_row >= rows)
    {
        time_t curTime = time(NULL);
        throw RowIndexException(ctime(&curTime), filename, line, typeid(*this).name(), __func__);
    }
}

template <TypeForMatrix T>
void Matrix<T>::col_index_exception(size_t ind_row, const char *filename, const size_t line) const

{
    if (ind_row >= rows)
    {
        time_t curTime = time(NULL);
        throw ColIndexException(ctime(&curTime), filename, line, typeid(*this).name(), __func__);
    }
}

template <TypeForMatrix T>
template <Convertable<T> U> 
void Matrix<T>::multiplicating_exception(const Matrix<U> &mtrx, const char *filename, const size_t line) const
{
    if (!this->is_multiplicating(mtrx))
    {
        time_t curTime = time(NULL);
        throw MultiplicatingException(ctime(&curTime), filename, line, typeid(*this).name(), __func__);
    }
}

template <TypeForMatrix T>
template <Convertable<T> U> 
void Matrix<T>::same_size_exception(const Matrix<U> &mtrx, const char *filename, const size_t line) const
{
    if (!is_same_size(mtrx))
    {
        time_t curTime = time(NULL);
        throw SizeMtrxsForOperationException(ctime(&curTime), filename, line, typeid(Matrix<T>).name(), __func__);
    }
}

template <TypeForMatrix T>
void Matrix<T>::square_exception(const char *filename, const size_t line) const
{
    if (!this->is_square())
    {
        time_t curTime = time(NULL);
        throw NeedSquareMtrxException(ctime(&curTime), filename, line, typeid(*this).name(), __func__);
    }
}

template <TypeForMatrix T>
void Matrix<T>::zero_det_exception(const char *filename, const size_t line) const
{
    if (get_det() - 0 < 0.0005)
    {
        time_t curTime = time(NULL);
        throw ZeroDetException(ctime(&curTime), filename, line, typeid(*this).name(), __func__);
    }
}

#pragma endregion ExceptionChecks

#pragma region Unary
template <TypeForMatrix T>
Matrix<T> Matrix<T>::operator-() const
{
    Matrix<T> res(*this);
    for (size_t i = 0; i < this->size(); i++)
        res.data[i] += -res.data[i];

    return res;
}
#pragma endregion Unary

#pragma region Addition
template <TypeForMatrix T>
template <Convertable<T> U>
decltype(auto) Matrix<T>::operator+(const Matrix<U> &mtrx) const
{
    same_size_exception(mtrx, __FILE__, __LINE__);

    Matrix<T> res(*this);
    for (size_t i = 0; i < this->size(); i++)
        res.data[i] = res.data[i] + mtrx.get_elem(i);

    return res;
}

template <TypeForMatrix T>
template <Convertable<T> U>
decltype(auto) Matrix<T>::operator+(const U &val) const
{
    Matrix<T> res(*this);
    for (size_t i = 0; i < this->size(); i++)
        res.data[i] += val;

    return res;
}

template <TypeForMatrix T> 
Matrix<T> operator+(const T &val, const Matrix<T> &mtr)
{
    return mtr + val;
}

template <TypeForMatrix T>
template <Convertable<T> U>
decltype(auto)  Matrix<T>::add(const Matrix<U> &mtrx) const
{
    return this + mtrx;
}

template <TypeForMatrix T>
template <Convertable<T> U>
Matrix<T> &Matrix<T>::operator+=(const Matrix<U> &mtrx)
{
    same_size_exception(mtrx, __FILE__, __LINE__);

    for (size_t i = 0; i < this->size(); i++)
        data[i] += mtrx.get_elem(i);

    return *this;
}

#pragma endregion Addition

#pragma region Sub
template <TypeForMatrix T>
template <Convertable<T> U>
decltype(auto)  Matrix<T>::operator-(const Matrix<U> &mtrx) const
{
    same_size_exception(mtrx, __FILE__, __LINE__);

    Matrix<T> res(*this);
    for (size_t i = 0; i < this->size(); i++)
        res.data[i] -= mtrx.get_elem(i);

    return res;
}

template <TypeForMatrix T>
template <Convertable<T> U>
decltype(auto) Matrix<T>::operator-(const U &val) const
{
    Matrix<T> res(*this);
    for (size_t i = 0; i < this->size(); i++)
        res.data[i] -= val;

    return res;
}

template <TypeForMatrix T>
template <Convertable<T> U>
decltype(auto)  Matrix<T>::sub(const Matrix<U> &mtrx) const
{
    return this - mtrx;
}

template <TypeForMatrix T>
template <Convertable<T> U>
Matrix<T> &Matrix<T>::operator-=(const Matrix<U> &mtrx)
{
    same_size_exception(mtrx, __FILE__, __LINE__);

    for (size_t i = 0; i < this->size(); i++)
        data[i] -= mtrx.get_elem(i);

    return *this;
}

#pragma endregion Sub

#pragma region Mul
template <TypeForMatrix T>
template <Convertable<T> U>
decltype(auto) Matrix<T>::operator*(const Matrix<U> &mtrx) const
{
    same_size_exception(mtrx, __FILE__, __LINE__);

    Matrix<T> res(*this);
    for (size_t i = 0; i < this->size(); i++)
        res.data[i] *= mtrx.get_elem(i);

    return res;
}

template <TypeForMatrix T>
template <Convertable<T> U>
decltype(auto) Matrix<T>::operator^(const Matrix<U> &mtrx) const
{

    Matrix<T> res(rows, mtrx->cols);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < mtrx->cols; ++j) 
        {
            res.data[i * cols + j] = 0;
            for (size_t k = 0; k < cols; ++k) 
                res.data[i * cols + j] += data[i * cols + k] * mtrx.get_elem(k * cols + j); //A[i][k] * B[k][j];
        }
    return res;
}

template <TypeForMatrix T>
template <Convertable<T> U>
decltype(auto) Matrix<T>::operator*(const U &val) const
{
    Matrix<T> res(*this);
    for (size_t i = 0; i < this->size(); i++)
        res.data[i] *= val;

    return res;
}

template <TypeForMatrix T> 
Matrix<T> operator*(const T &val, const Matrix<T> &mtr)
{
    return mtr * val;
}

template <TypeForMatrix T>
template <Convertable<T> U>
decltype(auto) Matrix<T>::mul(const Matrix<U> &mtrx) const
{
    return this * mtrx;
}

template <TypeForMatrix T>
template <Convertable<T> U>
Matrix<T> &Matrix<T>::operator*=(const Matrix<U> &mtrx)
{
    same_size_exception(mtrx, __FILE__, __LINE__);

    for (size_t i = 0; i < this->size(); i++)
        data[i] *= mtrx.get_elem(i);

    return *this;
}

#pragma endregion Mul

#pragma region Div
template <TypeForMatrix T>
template <Convertable<T> U>
decltype(auto) Matrix<T>::operator/(const Matrix<U> &mtrx) const
{
    same_size_exception(mtrx, __FILE__, __LINE__);

    Matrix<T> res(*this);
    for (size_t i = 0; i < this->size(); i++)
        res.data[i] /= mtrx.get_elem(i);

    return res;
}

template <TypeForMatrix T>
template <Convertable<T> U>
decltype(auto) Matrix<T>::operator%(const Matrix<U> &mtrx) const
{
    return *this ^ mtrx.inverted();
}

template <TypeForMatrix T>
template <Convertable<T> U>
decltype(auto) Matrix<T>::operator/(const U &val) const
{
    Matrix<T> res(*this);
    for (size_t i = 0; i < this->size(); i++)
        res.data[i] /= val;

    return res;
}

template <TypeForMatrix T>
template <Convertable<T> U>
decltype(auto) Matrix<T>::div(const Matrix<U> &mtrx) const
{
    return this / mtrx;
}

template <TypeForMatrix T>
template <Convertable<T> U>
Matrix<T> &Matrix<T>::operator/=(const Matrix<U> &mtrx)
{
    same_size_exception(mtrx, __FILE__, __LINE__);

    for (size_t i = 0; i < this->size(); i++)
        data[i] /= mtrx.get_elem(i);

    return *this;
}

#pragma endregion Div

#pragma region SpecificOperations

template <TypeForMatrix T>
Matrix<T> Matrix<T>::make_zero_matrix(const size_t cols, const size_t rows)
{
    Matrix<T> res(cols, rows);
    allocate(rows, cols);
    res.convert_to_zero_matrix();
    return res;
}

template <TypeForMatrix T>
Matrix<T> Matrix<T>::make_identity_matrix(const size_t size)
{
    Matrix<T> res(size, size);
    res.allocate(size, size);
    res.convert_to_identity();
    return res;
}

template <TypeForMatrix T>
void Matrix<T>::convert_to_zero_matrix() noexcept
{
    for (size_t i = 0; i < this->size(); ++i)
        data[i] = 0;
}

template <TypeForMatrix T>
void Matrix<T>::convert_to_identity() noexcept
{
    square_exception(__FILE__, __LINE__);

    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            if (i != j)
                data[i * cols + j] = 0;
            else
                data[i * cols + j] = 1;
}

template <TypeForMatrix T>
Matrix<T> Matrix<T>::transpose() const
{
    Matrix<T> res(*this);
    res.rows = cols;
    res.cols = rows;

    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            res.data[j * rows + i] = data[i * cols + j];

    return res;
}

// копирует в dst матрицу на без опреденных рядов
template <TypeForMatrix T>
void Matrix<T>::exclude_copy(Matrix<T> &dst, const size_t ex_row, const size_t ex_col) const
{
    square_exception(__FILE__, __LINE__);
    // check valid tmp dst
    if (rows != dst.get_rows() + 1 || cols != dst.get_cols() + 1)
    {
        time_t curTime = time(NULL);
        throw ExcludeCopyMtrxException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
    }

    size_t row_index, col_index;

    for (size_t i = 0; i < rows- 1; i++)
        for (size_t j = 0; j < cols - 1; j++)
        {
            row_index = i >= ex_row ? i + 1 : i;
            col_index = j >= ex_col ? j + 1 : j;
            dst.data[i * dst.get_cols() + j] = data[row_index *cols + col_index];
        }
    // return resm;
}

template <TypeForMatrix T>
T Matrix<T>::get_det() const
{ 
    square_exception(__FILE__, __LINE__);

    if (rows == 2)
        return data[0] * data[3] - data[2] * data[1];
    if (rows == 1)
        return get_elem(0);

    Matrix<T> tmp(rows - 1, cols - 1);
    T res = 0; 

    for (size_t i = 0; i < rows; i++)
    {
        exclude_copy(tmp, 0, i);
        T minor = tmp.get_det();

        if (i % 2 == 1)
            minor = -minor;

        res += minor * data[i];
    }

    return res;
}

template <TypeForMatrix T>
Matrix<T> Matrix<T>::inverted() const
{
    square_exception(__FILE__, __LINE__);
    zero_det_exception(__FILE__, __LINE__);

    Matrix<T> res(rows, cols);
    Matrix<T> tmp(rows - 1, cols - 1);
    T value = 0;
    // auto det = get_det();

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
        {
            exclude_copy(tmp, i, j);
            for (auto elem: tmp)
                cout << elem;
            value = tmp.get_det();
            cout << " " << value << endl;

            if ((i + j) % 2 == 1)
                value = -value;

            res.data[j * cols + i] = value;
        }

    return res;
}

#pragma endregion SpecificOperations





#pragma region ProtectedPart
template <TypeForMatrix T>
void Matrix<T>::allocate(const size_t rows, const size_t cols)
{   
    int line;
    try
    {
        line = __LINE__ + 1;
        data.reset(new T[rows * cols]);
    }
    catch (std::bad_alloc &error)
    {
        time_t tm = time(NULL);
        throw MemoryExcetion(ctime(&tm), __FILE__, line, typeid(*this).name(), __func__);
    }
    
}



#pragma region ProtectedPart