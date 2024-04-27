#include <iostream>
#include <iterator>

#include "IteratorConcepts.hpp"
#include "MatrixImpl.hpp"

using namespace std;

template <TypeForMatrix T>
void print_mtrx(const Matrix<T> &mtrx)
{
    cout << "Matrix:" << endl;
    for (size_t i = 0; i < mtrx.get_rows(); ++i)
    {
        for (size_t j = 0; j < mtrx.get_cols(); ++j)
            cout << mtrx[i][j] << " ";
        cout << endl;
    }
}

template <typename Con, typename T>
void g(Con&, T&)
{
    cout << "not container" << endl;
}

template <typename Con, typename T>
requires TypeForMatrix<T> && ContainerMatrix<Con, T>
void g(Con&, T&)
{
    cout << "It is container!!" << endl;
}

void container_test(void)
{
    Matrix<int> m1 = {{1, 2, 3}, {4, 5, 6}};
    g(m1, m1[0][0]);
}


void constructors_test(void)
{
    // cout << "Matrix()";
    Matrix<int> m0;

    // cout << "Matrix(const initializer_list<initializer_list<U>> lst)";
    Matrix<int> m1 = {{1, 2, 3}, {4, 5, 6}};
    m1 = m1 + 1;
    m1 = 1 + m1;
    print_mtrx(m1);

    Matrix<int> m2(m1);

    Matrix<int> me(2, 3);
    me = m1 + m2;
    me = me + Matrix{{1, 2, 3}, {4, 5, 6}};
    Matrix md = {{0.1, 0.2, 0.3}, {0.4, 0.5, 0.6}};
    md = md + m1;
    md = me;
    md += md;
    m1 *= m1;
    md = md + 1;
    md.transpose();
    for (auto elem: m1)
            cout << elem << " ";
    cout << endl;

    Matrix m3(move(m2));

    try
    {
        Matrix<int> me(1, 2);

        m1[1][2] = 10;
        cout << "m1[1][2] = " << m1[1][2] << endl;
    }
    catch(const BaseMatrixException &err)
    {
        std::cerr << err.what() << '\n';
    }

    cout << "Matrix msq:" << endl;
    Matrix msq = {{3.0, 5.0, -2.0}, {1.0, -3.0, 2.0}, {6.0, 7.0, -3.0}};
    print_mtrx(msq);
    cout << "Det = " << msq.get_det() << endl;
    Matrix inv = msq.inverted();
    print_mtrx(inv);
    cout << "Expected:" << endl;
    Matrix expect = {{-5, 1, 4}, {15, 3, -8}, {25, 9, -14}};
    print_mtrx(expect);


    Matrix small = {{1}};
    try
    {
        msq + small;
    }
    catch(const BaseMatrixException& e)
    {
        std::cerr << e.what() << '\n';
    }
    

    
    
}

template <typename T>
void f(T&)
{
    cout << "NOT ITERATOR!" << endl;
}

template <RandomAccessIterator T>
void f(T&)
{
    cout << "It is RandomAccessIterator in expamples!" << endl;
}

template <std::random_access_iterator T>
void f(T&)
{
    cout << "It is std::random_access_iterator!" << endl;
}


void iterator_test(void)
{
    Matrix<int> m1 = {{1, 2, 3}, {4, 5, 6}};
    for (size_t i = 0; i < m1.get_rows(); ++i)
    {
        for (size_t j = 0; j < m1.get_cols(); ++j)
            cout << m1.get_value(i, j) << " ";
        cout << endl;
    }

    Iterator it(m1);
    f(it);
    try
    {
        *it;
    }
    catch(const BaseMatrixException &e)
    {
        cout << e.what() << '\n';
    }
    
    
    try
    {
        cout << "Iteration: ";
        for (auto elem: m1)
            cout << elem;
        cout << endl;
        cout << "iter ind=2:" << it[2] << endl;
        it += 5;
        it -= 3;
        cout << "iter 0 += 5 -= 3  = " << *it << endl;

        Iterator<int> it2(it);
        cout << "it2 bases it: " << *it2 << endl;

        it2++;
        Iterator it3 = it2++;
        Iterator it4 = it--;
        cout << "it2++ -> it3 = " << *it3 << endl;
        cout << "it-- -> it4 = " << *it4 << endl;
        cout << "cmp it3 < it4 = " << (it3 < it4) << endl;
        cout << "cmp it3 == it4 = " << (it3 == it4) << endl;
        cout << "it3 - it4 = " << it3 - it4 << endl;
        cout << "it3 + 2 = " << *(it3 + static_cast<ptrdiff_t>(2)) << endl;
        cout << "it4 - 2 = " << *(it4 - static_cast<ptrdiff_t>(2)) << endl;
        

        ReverseIterator<int> rit = m1.rbegin();
        cout << "Reverse Iteration: ";
        for (ReverseIterator ri = m1.rbegin(); ri != m1.rend() - static_cast<ptrdiff_t>(1); ++ri)
            cout << *ri;
        cout << endl;

    }
    catch(const BaseMatrixException &err)
    {
        std::cerr << err.what() << '\n';
    }

    // cout << static_assert(std::random_access_iterator<it>, "no");
}