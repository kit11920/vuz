#pragma once
# include <iostream>
# include <iterator>

using namespace std;

template <typename I>
concept IteratorCon = requires()
{
    typename I::value_type;
    typename I::difference_type;
    typename I::pointer;
    typename I::reference;
};

template <typename T, typename U>
concept DerivedFrom = is_base_of<U, T>::value;  // true если U - базовый класс T

# pragma region Input_Iterator
template<typename T>
concept EqualityComparable = requires(T a, T b)
{
    { a == b } -> same_as<bool>;
    { a != b } -> same_as<bool>;
};

template <typename I>
concept InputIterator = IteratorCon<I> &&
requires { typename I::iterator_category; }&&
EqualityComparable<I>&&
DerivedFrom<typename I::iterator_category, input_iterator_tag>;

# pragma endregion

# pragma region Forward_Iterator
template <typename I>
concept Incrementable = requires(I it)
{
    { ++it } -> same_as<I&>;
    { it++ } -> same_as<I>;
};

template <typename I>
concept ForwardIterator = InputIterator<I> &&
Incrementable<I> &&
DerivedFrom<typename I::iterator_category, forward_iterator_tag>;

# pragma endregion

# pragma region Bidirectional_Iterator
template <typename I>
concept Decrementable = requires(I it)
{
    { --it } -> same_as<I&>;
    { it-- } -> same_as<I>;
};

template <typename I>
concept BidirectionalIterator = ForwardIterator<I> &&
Decrementable<I> &&
DerivedFrom<typename I::iterator_category, bidirectional_iterator_tag>;

# pragma endregion

# pragma region Random_Access_Iterator
template <typename I>
concept RandomAccess = requires(I it, typename I::difference_type n)
{
    { it + n } -> same_as<I>;
    { it - n } -> same_as<I>;
    { it += n } -> same_as<I&>;
    { it -= n } -> same_as<I&>;
    { it[n] } -> same_as<typename I::reference>;
};

template <typename I>
concept Distance = requires(I it1, I it2)
{
    { it2 - it1 } -> convertible_to<typename I::difference_type>;
};

template <typename I>
concept RandomAccessIterator = BidirectionalIterator<I> &&
RandomAccess<I> && Distance<I> &&
DerivedFrom<typename I::iterator_category, random_access_iterator_tag>;

# pragma endregion

