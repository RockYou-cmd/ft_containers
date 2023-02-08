#ifndef V_ITERATOR
#define V_ITERATOR
#include "iterators.h"

namespace ft
{
	template <typename T>
	class reverse_iterator
	{

	public:
	public:
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T *pointer;
		typedef T &reference;
		typedef std::random_access_iterator_tag iterator_category;

		reverse_iterator(pointer vdata)
		{
			it = vdata;
		};

		reference operator*()
		{
			return *it;
		}

		reverse_iterator operator+(int n)
		{
			it -= n;
			return *this;
		}

		reverse_iterator operator-(int n)
		{
			it += n;
			return *this;
		}

		reverse_iterator operator++()
		{
			--it;
			return *this;
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator tmp(it);
			it--;
			return tmp;
		}

		reverse_iterator operator--()
		{
			++it;
			return *this;
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator tmp(it);
			it++;
			return tmp;
		}

		reverse_iterator operator=(reverse_iterator other)
		{
			it = other.it;
			return (*this);
		}

		bool operator!=(const reverse_iterator &other)
		{
			return it != other.it;
		}

		bool operator==(const reverse_iterator &other)
		{
			return it == other.it;
		}

	private:
		pointer it;
	};

	//=================================================================

	template <typename T>
	class v_iterator
	{
	public:
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T *pointer;
		typedef T &reference;
		typedef std::random_access_iterator_tag iterator_category;
		v_iterator(pointer vdata)
		{
			it = vdata;
		};

		v_iterator operator=(v_iterator other)
		{
			it = other.it;
			return (*this);
		}

		reference operator*()
		{
			return (*it);
		}

		v_iterator operator++(int)
		{
			v_iterator tmp(it);
			it++;
			return tmp;
		}

		v_iterator operator++()
		{
			it++;
			return *this;
		}

		v_iterator operator+(int n) const
		{
			v_iterator tmp(*this);
			tmp.it += n;
			return tmp;
		}

		v_iterator operator-(int n)
		{
			v_iterator tmp(*this);
			tmp.it -= n;
			return tmp;
		}

		v_iterator operator--(int)
		{
			v_iterator tmp(it);
			it--;
			return tmp;
		}

		v_iterator operator--()
		{
			it--;
			return *this;
		}

		size_t DistanceToEnd(v_iterator other)
		{
			if (it > other.it)
			{
				std::cout << "error\n";
				exit(0);
			}
			int i = 0;
			while (it != other.it)
			{
				it++;
				i++;
			}
			return i;
		}

		size_t DistanceToBeg(v_iterator other)
		{
			if (it < other.it)
			{
				std::cout << "error\n";
				exit(0);
			}
			int i = 0;
			while (it != other.it)
			{
				other.it++;
				i++;
			}
			return i;
		}

		bool operator==(const v_iterator &other)
		{
			return it == other.it;
		}

		bool operator!=(const v_iterator &other)
		{

			return (it != other.it);
		}

		void addr()
		{
			std::cout << "it adrr : " << it << std::endl;
		}

	private:
		pointer it;
	};
}

#endif // V_ITERATOR