#pragma once 
#include <initializer_list>
#include <memory>
#include <iterator>
#include "BaseMatrix.h"
#include "MaxtrixConcepts.hpp"
#include "IteratorImpl.hpp"
#include "ConstIteratorImpl.hpp"
#include "ReverseIteratorImpl.hpp"
#include "ConstReverseIteratorImpl.hpp"
#include "Exceptions.h"

using namespace std;

template <TypeForMatrix T>
class Iterator;

template <TypeForMatrix T>
class ReverseIterator;

template <TypeForMatrix T>
class Matrix: public BaseMatrix
{
    friend class Iterator<T>;
    friend class ConstIterator<T>;
    friend class ReverseIterator<T>;
    friend class ConstReverseIterator<T>;
public:
    #pragma region Constructors
    Matrix() noexcept: BaseMatrix() {};
    Matrix(const size_t rows, const size_t cols);

    Matrix(Matrix<T> &&mtr) noexcept;
    explicit Matrix(const Matrix<T> &mtr);
    Matrix(initializer_list<initializer_list<T>> lst);

    template <Convertable<T> U> // from U to T
    explicit Matrix(const Matrix<U> &mtr);
    template <Convertable<T> U> 
    Matrix(initializer_list<initializer_list<U>> lst);

    template <ContainerMatrix<T> U>  
    Matrix(const U& con, const size_t rows, const size_t cols);

    #pragma endregion Constructors

    ~Matrix() override;

    #pragma region It_is_conteiner
    // using size_type = size_t; --> BaseMatrix
    // size_t size() const noexcept; --> BaseMatrix
    using value_type = T;
    using iterator = Iterator<T>;
    using const_iterator = ConstIterator<T>;
    using reverse_iterator = ReverseIterator<T>;
    using const_reverse_iterator = ConstReverseIterator<T>;

    Iterator<T> begin() const noexcept;
	Iterator<T> end() const noexcept;
	ReverseIterator<T> rbegin() const noexcept;
	ReverseIterator<T> rend() const noexcept;
    ConstIterator<T> cbegin() const noexcept;
	ConstIterator<T> cend() const noexcept;
    ConstReverseIterator<T> crbegin() const noexcept;
	ConstReverseIterator<T> crend() const noexcept;

    #pragma endregion It_is_conteiner

    #pragma region Assignment
    Matrix<T>& operator=(const Matrix<T> &mtrx);
    Matrix<T>& operator=(Matrix<T> &&mtrx) noexcept;
    Matrix<T>& operator=(std::initializer_list<std::initializer_list<T>> elems);

    template <Convertable<T> U> 
    Matrix<T>& operator=(const Matrix<U> &mtrx);
    template <Convertable<T> U> 
    Matrix<T>& operator=(std::initializer_list<std::initializer_list<U>> elems);
    #pragma endregion Assignment

    #pragma region Informating
    bool is_same_size(const BaseMatrix &mtrx) const noexcept;
    bool is_square() const noexcept;
    bool is_zero() const noexcept;
    bool is_empty() const noexcept;
    bool is_identity() const noexcept;
    template <Convertable<T> U> 
    bool is_multiplicating(const Matrix<U> &mtrx) const noexcept;
    #pragma endregion Informating

    #pragma region Comparison
    bool operator==(const Matrix<T> &mtrx) const noexcept;
    bool operator!=(const Matrix<T> &mtrx) const noexcept;
    bool is_equal(const Matrix<T> &mtrx) const noexcept;
    bool is_not_equal(const Matrix<T> &mtrx) const noexcept;
    #pragma endregion Comparison
    
	#pragma region ExceptionChecks
    void rows_index_except_check(size_t ind_row, const char *filename, const size_t line) const;
    void col_index_except_check(size_t ind_row, const char *filename, const size_t line) const;
    template <Convertable<T> U> 
    void multiplicating_except_check(const Matrix<U> &mtrx, const char *filename, const size_t line) const;
    template <Convertable<T> U> 
    void same_size_except_check(const Matrix<U> &mtrx, const char *filename, const size_t line) const;
    void square_except_check(const char *filename, const size_t line) const;
    void zero_det_except_check(const char *filename, const size_t line) const;
    #pragma endregion ExceptionChecks

    #pragma region Unary
    Matrix<T> operator-() const;
    #pragma endregion Unary

    #pragma region Add
    template <Convertable<T> U> 
    decltype(auto) operator+(const Matrix<U> &mtr) const;
    template <Convertable<T> U> 
    decltype(auto) operator+(const U &val) const;
    template <Convertable<T> U> 
    decltype(auto) operator+=(const Matrix<U> &mtr);
    template <Convertable<T> U> 
    decltype(auto)  add(const Matrix<U> &mtr) const;
    #pragma endregion Add

    #pragma region Sub
    template <Convertable<T> U> 
    decltype(auto) operator-(const Matrix<U> &mtr) const;
    template <Convertable<T> U> 
    decltype(auto) operator-(const U &val) const; 
    template <Convertable<T> U> 
    decltype(auto) operator-=(const Matrix<U> &mtr);
    template <Convertable<T> U> 
    decltype(auto) sub(const Matrix<U> &mtr) const;
    #pragma endregion Sub

    #pragma region Mul
    template <Convertable<T> U> 
    decltype(auto) operator*(const Matrix<U> &mtr) const; 
    template <Convertable<T> U> 
    decltype(auto) operator^(const Matrix<U> &mtr) const; 
    template <Convertable<T> U> 
    decltype(auto) operator*(const U &val) const;
    template <Convertable<T> U> 
    decltype(auto) operator*=(const Matrix<U> &mtr);
    template <Convertable<T> U> 
    decltype(auto) mul(const Matrix<U> &mtr) const;
    #pragma endregion Mul

    #pragma region Div
    template <Convertable<T> U> 
    decltype(auto) operator/(const Matrix<U> &mtr) const; 
    template <Convertable<T> U> 
    decltype(auto) operator/(const U &val) const;
    template <Convertable<T> U> 
    decltype(auto) operator/=(const Matrix<U> &mtr);
    template <Convertable<T> U> 
    decltype(auto) div(const Matrix<U> &mtr) const;
    #pragma endregion Div

    #pragma region SpecificOperations
    void make_zero_matrix() noexcept;
    void make_identity();
    Matrix<T> transpose() const;
    decltype(auto) get_det() const;
    Matrix<T> inverted() const;
    #pragma endregion SpecificOperations
    
    class MatrixLine
    {
    public:
        MatrixLine(const Matrix<T> &mtrx, const size_t index_row) try
        {
            if (index_row >= mtrx.get_rows())
            {
                time_t curTime = time(NULL);
                throw ColIndexException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);
            }

            index_this_row = index_row; 
            arr = mtrx.data;
            lenarr = mtrx.get_cols();
        }
        catch (...)
        {
            throw;
        }

        T& operator[](size_t ind) const
        {
            if (ind >= lenarr)
            {
                time_t curTime = time(NULL);
                throw ColIndexException(ctime(&curTime), __FILE__, __LINE__, typeid(*this).name(), __func__);

            }

            return *(arr.get() + index_this_row * lenarr + ind);
        }

        ~MatrixLine() = default;


    private:
        std::shared_ptr<T[]> arr;
        size_t index_this_row;
        size_t lenarr = 0;
    };

    #pragma region Indexing
    MatrixLine operator[](size_t ind_row);
    const MatrixLine operator[](size_t ind_row) const;
    T &get_value(size_t i, size_t j) const;
    T get_elem(size_t i) const;
    #pragma endregion Indexing


protected:
    void allocate(const size_t rows, const size_t cols);
    void exclude_copy(Matrix<T> &dst, const size_t ex_row, const size_t ex_col) const;

private:
    std::shared_ptr<T[]> data;
};

// template <typename T, typename U>
// requires TypeForMatrix<T> && Convertable<U, T>
template <TypeForMatrix T> 
Matrix<T> operator+(const T &val, const Matrix<T> &mtr);

template <TypeForMatrix T> 
Matrix<T> operator*(const T &val, const Matrix<T> &mtr);
