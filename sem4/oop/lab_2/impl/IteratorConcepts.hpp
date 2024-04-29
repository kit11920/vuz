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

template<typename _In>
concept me_indirectly_readable_impl = requires(const _In in)
{
    typename iter_value_t<_In>;
    typename iter_reference_t<_In>;
    typename iter_rvalue_reference_t<_In>;
    { *in } -> same_as<iter_reference_t<_In>>;
    requires same_as<iter_reference_t<const _In>,
                iter_reference_t<_In>>;
    requires same_as<iter_rvalue_reference_t<const _In>,
                iter_rvalue_reference_t<_In>>;
};

template< class T >
concept me_movable =
    std::is_object_v<T> &&
    std::move_constructible<T> &&
    std::assignable_from<T&, T> &&
    std::swappable<T>;

template <typename I>
concept InputIterator = IteratorCon<I> &&
requires { typename I::iterator_category; }&&
EqualityComparable<I>&&
DerivedFrom<typename I::iterator_category, input_iterator_tag> &&
derived_from<__detail::__iter_concept<I>, input_iterator_tag> &&
requires { typename __detail::__iter_concept<I>; } && 
me_indirectly_readable_impl<I> &&
indirectly_readable<I> &&
me_movable<I> &&
weakly_incrementable<I> &&
input_or_output_iterator<I>;

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
DerivedFrom<typename I::iterator_category, random_access_iterator_tag> &&
derived_from<__detail::__iter_concept<I>, random_access_iterator_tag> &&
totally_ordered<I> && requires(const I& __i, const I& __s)
    {
      { __s - __i } -> same_as<iter_difference_t<I>>;
      { __i - __s } -> same_as<iter_difference_t<I>>;
    } && sized_sentinel_for<I, I> &&
requires(I __i, const I __j,
		  const iter_difference_t<I> __n)
      {
	{ __i += __n } -> same_as<I&>;
	{ __j +  __n } -> same_as<I>;
	{ __n +  __j } -> same_as<I>;
	{ __i -= __n } -> same_as<I&>;
	{ __j -  __n } -> same_as<I>;
	{  __j[__n]  } -> same_as<iter_reference_t<I>>;
      };

# pragma endregion

