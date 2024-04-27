#pragma once 

#include "IteratorConcepts.hpp"
#include <concepts>
using namespace std;

// Концепт для типов которые может содержать матрица
// с этим типом можно выполнять те же операции что с матрицей
template <typename T>
concept TypeForMatrix = requires(T a, T b)
{
    {a + b} -> same_as<T>;
    {a - b} -> same_as<T>;
    {a * b} -> same_as<T>;
    {a / b} -> same_as<T>;
    {a < b} -> convertible_to<bool>;
    {a > b} -> convertible_to<bool>;
    {a <= b} -> convertible_to<bool>;
    {a >= b} -> convertible_to<bool>;
    {a == b} -> convertible_to<bool>;
    {a != b} -> convertible_to<bool>;
    a = b;
};


template <typename From, typename To>
concept Convertable = convertible_to<From, To>; // && TypeForMatrix<To>;

template <typename C>  
concept Container = requires(C con)
{
    typename C::value_type;
    typename C::size_type;
    typename C::iterator;
    typename C::const_iterator;

    { con.size() } noexcept -> same_as<typename C::size_type>;
    { con.end() } noexcept -> same_as<typename C::iterator>;
    { con.begin() } noexcept -> same_as<typename C::iterator>;
    { con.rend() } noexcept -> same_as<typename C::reverse_iterator>;
    { con.rbegin() } noexcept -> same_as<typename C::reverse_iterator>;
    { con.cend() } noexcept -> same_as<typename C::const_iterator>;
    { con.cbegin() } noexcept -> same_as<typename C::const_iterator>;
};

template <typename Con, typename T>
concept ContainerMatrix = Container<Con> && 
                        Convertable<typename Con::value_type, T> && 
                        RandomAccessIterator<typename Con::iterator>;

// template <typename Con, typename T>
// concept ContainerMatrix = Convertable<typename Con::value_type, T> && 
//                         RandomAccessIterator<typename Con::iterator>;
