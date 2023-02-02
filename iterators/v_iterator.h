#ifndef V_ITERATOR
#define V_ITERATOR
#include "iterators.h"

namespace ft
{
	template <typename T>
	class v_iterator
	{
		public:
		typedef T 								value_type;
		typedef ptrdiff_t 						difference_type;
		typedef T* 								pointer;
		typedef T& 								reference;
		typedef std::random_access_iterator_tag iterator_category;
		v_iterator(pointer vdata)
		{
			it = vdata;
		};
		value_type operator*()
		{
			return (*it);
		}
		
		value_type operator++(int)
		{
			it += 1;
			return *(it - 1);
		}

		value_type operator++()
		{
			it += 1;
			return *it;
		}

		value_type operator--(int)
		{
			it -= 1;
			return *(it + 1);
		}

		value_type operator--()
		{
			it -= 1;
			return *it;
		}

		bool operator==(const pointer& other)
		{
			return *it == *(other->it);
		}

		bool operator!=(const pointer& other)
		{
			return *it != *(other->it);
		}
		private :
			pointer it;
	};
}


#endif //V_ITERATOR