/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:01:40 by dchheang          #+#    #+#             */
/*   Updated: 2022/03/08 21:12:46 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include "iterator.hpp"

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		/****************************** TYPES *****************************/
		public:
			typedef T										value_type;
			typedef Alloc									allocator_type;
			typedef typename allocator_type::reference		reference;
			typedef typename allocator_type::pointer		pointer;
			typedef	typename allocator_type::const_pointer	const_pointer;
			typedef ptrdiff_t								difference_type;
			typedef	size_t									size_type;
			typedef RandomIte <value_type>					iterator;
			typedef RandomIte <const value_type>			const_iterator;
			//const_iterator
			//reverse_iterator
			//const_reverse_iterator

		/****************************** ATTRIBUTES *****************************/
		private:
			allocator_type	_alloc;
			pointer			_begin;
			pointer			_end;
			size_type		_capacity;

		public:
			/****************************** CONSTRUCTORS *****************************/

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
				_capacity = n;
				for (size_type i = 0; i < n; i++)
					_alloc.construct(_end++, val);
			}

			/* RANGE : fills vector with elements from range first included to last not included
			** @param first : beginning of range
			** @param last : end of range */
			template <class InputIterator>
			vector (InputIterator first, InputIterator last,
					const allocator_type& alloc = allocator_type())
			{
				size_t			n = 0;
				InputIterator	ite;

				for (ite = first; ite != last; ite++)
					n++;
				_alloc = alloc;
				_begin = _alloc.allocate(n);
				_end = _begin;
				_capacity = n;
				while (first != last)
				{
					_alloc.construct(_end++, *first);
					first++;
				}
			}

			/* COPY : copies another vector
			** @param x : vector to copy */
			vector (const vector& x)
			{
				size_type	len;

				len = x.size();
				_alloc = x._alloc;
				_begin = _alloc.allocate(len);
				_end = _begin;
				_capacity = len;
				for (size_type i = 0; i < len; i++)
					_alloc.construct(_end++, x[i]);
			}

			/********************************** ACCESSORS ********************************/
			size_type	size() const
			{
				return (_end - _begin);
			}

			size_type	capacity() const
			{
				return (_capacity);
			}

			reference	operator[] (size_type n) const
			{
				reference ret = *(_begin + n);
				return (ret);
			}

			/********************************** ITERATOR ********************************/
			iterator	begin()
			{
				return (iterator(_begin));
			}

			iterator	end()
			{
				return (iterator(_end));
			}
	};
}

#endif
