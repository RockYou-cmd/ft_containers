/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 15:57:07 by ncolomer          #+#    #+#             */
/*   Updated: 2023/02/09 17:22:03 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
#include "ft_containers.h"
#include "../iterators/v_iterator.h"
#include <iterator>     // std::distance
namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef 			T 								value_type;
			typedef 			std::allocator<T> 				allocator_type;
			typedef 			std::size_t 					size_type;
			typedef 			std::size_t 					difference_type;
			typedef 			value_type& 					reference;
			typedef 			const value_type& 		1		const_reference;
			typedef typename 	allocator_type::pointer 		pointer;
			typedef typename 	allocator_type::const_pointer 	const_pointer;
			typedef 			ft::v_iterator<T> 				iterator;
			typedef 			ft::v_iterator<const T> 		const_iterator;
			typedef 			ft::reverse_iterator<T> 		reverse_iterator;

		// default constructor
		vector(): vcap(0) , vsize(0) {};

		// Fill constructor
		vector(size_type nb, const value_type& val = value_type()) : vsize(nb) , vcap(nb) 
		{	
			std::cout << "constructed " << nb << "\n";
			bdata = _allocator.allocate(10);
			for (int i = 0; i < nb; i ++)
				_allocator.construct(bdata + i, val);
			edata = bdata + nb;
			
		}

		vector& operator=(const vector& other)
		{
			// std::cout << "here----------\n";
			if (this != &other && other.vcap > 0)
			{
				if (vcap > 0)
				{
					for(int i = 0; i < vsize; i ++)
						_allocator.destroy(bdata + i);
					_allocator.deallocate(bdata, vcap);
				}
				bdata = _allocator.allocate(other.vcap);
				for (int i = 0; i < other.vsize; i ++)
					_allocator.construct(bdata + i, *(other.bdata + i));
				vcap = other.vcap;
				vsize = other.vsize;
			}
			return *this;
		}
		// begin()
		iterator begin()
		{
			return iterator(bdata);
		}
		
		// end()
		iterator end()
		{
			return iterator(bdata + vsize);
		}
		
		reverse_iterator rbegin()
		{
			return reverse_iterator(bdata + (vsize - 1));
		}
	
		reverse_iterator rend()
		{
			return reverse_iterator(bdata);
		}

		size_type size()
		{
			return vsize;
		}
		
		size_type max_size()
		{
			return (_allocator.max_size());
		}
		
		bool empty()
		{
			std::cout << "VSIZE : " << vsize << std::endl;
			return (vsize ? 0 : 1);
		}
		
		reference at(size_type n)
		{
			if (n < vcap && n >= 0)
				return bdata[n];
			std::cout << "error\n";
			exit(0);
		}

		reference operator[](size_type n)
		{
			return at(n);
		}

		reference front()
		{
			return at(0);
		}
		
		reference back()
		{
			return vsize ? bdata[vsize - 1] : bdata[0];
		}

		// push_back	
		void push_back (const value_type& val)
		{
			if (vcap == vsize)
			{
				size_type ncap;
				if (!vcap)
					ncap = 1;
				else
					ncap = vcap * 2;
				pointer tmp = _allocator.allocate(ncap);
				int i;
				for (i = 0; i < vsize; i ++)
				{
					_allocator.construct(tmp + i, *(bdata + i));
					_allocator.destroy(bdata + i);
				}
				if (vcap > 0)
				_allocator.deallocate(bdata, vcap);
				bdata = tmp;
				vcap = ncap;
			}
			_allocator.construct(bdata + vsize, val);
			vsize++;
			edata = bdata + vsize;
		}
		
		void pop_back ()
		{
			_allocator.destroy(edata - 1);
			vsize--;
		}

		void resize(size_type n, value_type val = value_type())
		{
			if (n < 0)
				return;
			if (n > vcap)
			{
				pointer tmp = _allocator.allocate(n);
				for (int i = 0; i < n; i ++)
				{
					if (i < vsize)
						_allocator.construct(tmp + i, *(bdata + i));
					else
						_allocator.construct(tmp + i, val);
				}
				for (int i = 0; i < vsize; i ++)
					_allocator.destroy(bdata + i);
				_allocator.deallocate(bdata, vcap);
				bdata = tmp;
				vsize = n;
				vcap = n;
			}
			else if (n == 0)
			{
				for (int i = 0; i < vsize; i ++)
					_allocator.destroy(bdata + i);
				vsize = 0;
			}
			else if (n <= vcap)
			{
				for (int i = 0; i < vcap; i ++)
				{
					if (i < vsize && i < n)
						continue;
					if (i < n)
						_allocator.construct(bdata + i, val);
				}
				vsize = n;
			}
				
		}
		
		void reserve(size_type ncap)
		{
			if (ncap <= vcap)
				return;
			pointer ndata = _allocator.allocate(ncap);
			for (size_type i = 0; i < vsize; ++i)
			{
				_allocator.construct(ndata + i, *(bdata + i));
				_allocator.destroy(bdata + i);
			}
			_allocator.deallocate(bdata, vcap);
			bdata = ndata;
			vcap = ncap;
    	}

	 	iterator insert (iterator position, const value_type& val)
		{
			int distance = position.DistanceToEnd(bdata + vsize);
			if (vcap == vsize)
				reserve(vcap * 2);
    		iterator it(bdata + vsize);
    		for (int i = 0; i < distance; i ++)
			{
				*it = *(it - 1);
				it --;
			}
    		*it = val;
			vsize++;
			return it;
		}
		
	 	void insert (iterator position, size_type n, const value_type& val)
		{
			int enddist = position.DistanceToEnd(bdata + vsize);
			if ((vcap - vsize) < n)
				reserve(vcap + n);
			iterator final_end = ((end() + n) - 1);
			iterator current_end = (end() - 1);
			int fnldist = enddist + n;
			for (int i = 0; i < fnldist; i ++)
			{
				if (i < enddist)
				{
					*final_end = *current_end;
					current_end --;
					
				}
				else
					*final_end = val;
				final_end --;
			}
			vsize += n;
		}
		
		template <class InputIterator>
    	void insert (iterator position, InputIterator first, InputIterator last)
		{
			int n = 0;
			InputIterator tmpf = first;
			InputIterator tmpl = last;
			while(tmpf != tmpl)
			{
				tmpl--;
				n ++;
			}
			int enddist = position.DistanceToEnd(bdata + vsize);
			if ((vcap - vsize) < n)
				reserve(vcap + n);
			iterator final_end = ((end() + n) - 1);
			iterator current_end = (end() - 1);
			int fnldist = enddist + n;
			for (int i = 0; i < fnldist; i ++)
			{
				if (i < enddist)
				{
					*final_end = *current_end;
					current_end --;
				}
				else
				{
					last --;
					*final_end = *last;
				}
				final_end --;
				//
			}
			vsize += n;
		}

		void clear()
		{
			for (int i = 0; i < vsize; i ++)
				_allocator.destroy(bdata + i);
			vsize = 0;
		}
		
		void assign (const size_type n, value_type val)
		{
			if (n > vcap)
				reserve(n);
			clear();
			for (int i = 0; i < n; i++)
				_allocator.construct(bdata + i, val);
			vsize = n;
		}

		template <class InputIterator>
  		void assign (InputIterator first, InputIterator last)
		{
			int n = 0;
			std::cout << "heere\n";
			InputIterator tmpf = first;
			InputIterator tmpl = last;
			while(tmpf != tmpl)
			{
				tmpl--;
				n ++;
			}
			if (n > vcap)
				reserve(n);
			clear();
			for (int i = 0; i < n; i++)
				_allocator.construct(bdata + i, *(first + i));
			vsize = n;
		}
		
		void swap (vector& x)
		{
			assign(x.begin(), x.end() - 1);
		}

		size_type capacity()
		{
			return vcap;
		}
		







		void print()
		{
			for (int i = 0; i < vsize; i ++)	
				std::cout << bdata[i] << std::endl;
			std::cout << "capacity :  " << vcap << std::endl;
			std::cout << "size :  " << vsize << std::endl;
		}
		private:
			pointer			bdata;
			size_type		vsize;
			size_type 		vcap;
			allocator_type _allocator;
			pointer			edata;
	};
}

#endif

		// void push_front (const value_type& val)
		// {
			// std::cout << *(bdata);
		// 	if (vcap == vsize)
		// 	{
		// 		size_type ncap;
		// 		if (!vcap)
		// 			ncap = 1;
		// 		else
		// 			ncap = vcap * 2;
		// 		pointer tmp = _allocator.allocate(ncap);
		// 		int i = 0;
		// 		_allocator.construct(tmp, val);
		// 		_allocator.destroy(bdata);
		// 		for (i = 1; i <= vsize; i ++)
		// 		{
		// 			_allocator.construct(tmp + i, bdata[i - 1]);
		// 			_allocator.destroy(bdata + i);
		// 		}
		// 		_allocator.deallocate(bdata, vcap);
		// 		bdata = tmp;
		// 		vcap = ncap;
		// 	}
		// 	else
		// 	{
		// 		for(int i = vsize; i > 0; i--)
		// 			*(bdata + i) = *(bdata + (i - 1));
		// 		_allocator.construct(bdata, val);	
		// 	}
		// 	vsize++;
		// }