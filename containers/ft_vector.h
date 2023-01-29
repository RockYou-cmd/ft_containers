/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-korc <ael-korc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 15:57:07 by ncolomer          #+#    #+#             */
/*   Updated: 2023/01/29 19:38:52 by ael-korc         ###   ########.fr       */
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
		Vector(size_type nb, const value_type& val = value_type()) : vsize(nb) , vcap(nb) 
		{	
			std::cout << "constructed \n";
			bdata = _allocator.allocate(nb);
			for (int i = 0; i < nb; i ++)
				_allocator.construct(bdata + i, val);
			edata = bdata + nb - 1;
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
			if (vcap == vsize)
			{
				size_type ncap;
				if (!vcap)
					ncap = 1;
				else
					ncap = vcap * 2;
				pointer tmp = _allocator.allocate(vsize);
				for (int i = 0; i < vsize; i ++)	
					tmp[i] = bdata[i];
				for (int i = 0; i < vsize; i ++)
					std::cout << bdata[i] << std::endl;
				for (int i = 0; i < vsize; i ++)
					_allocator.destroy(bdata + i);
				_allocator.deallocate(bdata, vsize);	
				std::cout << "afte deallocate \n";
				for (int i = 0; i < vsize; i ++)
					std::cout << bdata[i] << std::endl;
				// for (int i = 0; i < vsize; i ++)	
					// std::cout << tmp[i] << std::endl;
							
			}
		}
		
		size_type capacity() {return vcap;}
		private:
			size_type		vsize;
			size_type 		vcap;
			allocator_type _allocator;
			pointer  bdata;
			pointer edata;
	};
}

#endif
