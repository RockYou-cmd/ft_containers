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
		v_iterator(){};
	};
}


#endif //V_ITERATOR