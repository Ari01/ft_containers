/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:01:40 by dchheang          #+#    #+#             */
/*   Updated: 2022/02/24 16:50:01 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			// MEMBER TYPES
			typedef T										value_type;
			typedef Alloc									allocator_type;
			typedef typename allocator_type::reference		reference;
			typedef typename allocator_type::pointer		pointer;
			typedef	typename allocator_type::const_pointer	const_pointer;
			typedef std::ptrdiff_t							difference_type;
			typedef	size_t									size_type;
			//iterator
			//const_iterator
			//reverse_iterator
			//const_reverse_iterator

			/********************************** CONSTRUCTORS *****************************/

			/* DEFAULT : initializes default allocator and saves copy in _allocator */
			explicit vector (const allocator_type& alloc = allocator_type()) :
				_alloc(alloc), _begin(NULL), _end(NULL), _capacity(0) {}

			/* SIZE : uses allocator.alloc() to allocate memory space for n elements of type T
			** @param n : number of elements to insert
			** @param val : value to fill the array with
			** @exception : alloc() throws std::bad_alloc if allocation failed */
			explicit vector (size_type n, const value_type& val = value_type(),
							 const allocator_type& alloc = allocator_type())
			{
				_alloc = alloc;
				_begin = _alloc.allocate(n);
				_end = _begin;
				_capacity += n;
				for (size_type i = 0; i < n; i++)
					_alloc.construct(_end++, val);
			}

			/* RANGE : fills vector with elements from range first included to last not included
			** @param first : beginning of range
			** @param last : end of range */
			template <class InputIterator>
			vector (InputIterator first, InputIterator last,
					const allocator_type& alloc = allocator_type());
			vector (const vector& x);

			/********************************** ACCESSORS ********************************/
			reference	operator[] (size_type n)
			{
				reference ret = *(_begin + n);
				return (ret);
			}

			private:
				// ATTRIBUTES
				allocator_type	_alloc;
				pointer			_begin;
				pointer			_end;
				size_type		_capacity;


	};
}

#endif
