#ifndef ITERATORS
#define ITERATORS


#include <cstddef>
#include <iterator>
#include <iostream>


template <typename Iterator>
class iterator_traits
{
    iterator_traits()
    {
        std::cout << "hhh\n";
    }
    typedef typename Iterator::reference reference;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::iterator_category iterator_category;
};

template <typename T>
class iterator_traits<T*>
{
    typedef std::random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef T& reference;
};

template<bool B, typename T = void>
struct enable_if {};

template<typename T>
struct enable_if<true, T> {
    typedef T type;
};


template <typename T>
struct is_integral {
  static const bool value = false;
};

template <>
struct is_integral<short> {
  static const bool value = true;
};

template <>
struct is_integral<unsigned short> {
  static const bool value = true;
};

template <>
struct is_integral<int> {
  static const bool value = true;
};

template <>
struct is_integral<unsigned int> {
  static const bool value = true;
};

template <>
struct is_integral<long> {
  static const bool value = true;
};

template <>
struct is_integral<unsigned long> {
  static const bool value = true;
};

template <>
struct is_integral<char> {
  static const bool value = true;
};


#endif //ITERATORS