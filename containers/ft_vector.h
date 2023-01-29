/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 15:57:07 by ncolomer          #+#    #+#             */
/*   Updated: 2023/01/29 07:15:31 by ael-korc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
#include "ft_containers.h"
#include "../iterators/v_iterator.h"

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class Vector
	{
		public:
			typedef 			T 								value_type;
			typedef 			std::allocator<T> 				allocator_type;
			typedef 			std::size_t 					size_type;
			typedef 			size_type 						difference_type;
			typedef 			value_type& 					reference;
			typedef 			const value_type& 				const_reference;
			typedef typename 	allocator_type::pointer 		pointer;
			typedef typename 	allocator_type::const_pointer 	const_pointer;
			typedef 			ft::v_iterator<T> 				iterator;
			typedef 			ft::v_iterator<const T> 		const_iterator;

		// default constructor
		Vector(): vcap(0) , vsize(0) {};

		// Fill constructor
		Vector(size_type nb, const value_type& val = value_type())
		{	
			std::cout << "constructed \n";
			data = _allocator.allocate(nb);
			for (int i = 0; i < nb; i ++)
				_allocator.construct(data + i, val);
		}
		// Vector& operator=(const Vector& other)
		// {
			
		// };
		// void reserve(size_type nsize)
		// {
		// 	if (nsize > cap)
		// 	{
				
		// 	}
		// }
		
		// push_back
		void push_back (const value_type& val)
		{
			if (vsize == vcap)
			{
				if (vcap == vsize)
				{
					size_type ncap;
					if (!vcap)
						ncap = 1;
					else
						ncap = vcap * 2;
					pointer tmp = _allocator.allocate(vsize);
					
				}
			}
		}
		
		size_type capacity() {return vcap;}
		private:
			size_type		vsize;
			size_type 		vcap;
			allocator_type _allocator;
			std::allocator<T>  data;
			pointer finish;
	};
}

#endif
