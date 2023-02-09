#ifndef ITERATORS
#define ITERATORS


#include <cstddef>
#include <iterator>
#include <iostream>

template <typename Iterator>
struct iterator_traits
{
    typedef typename Iterator::reference reference;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::iterator_category iterator_category;
};

template <typename T>
struct iterator_traits<T*>
{
    typedef std::random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef T& reference;
};



#endif //ITERATORS