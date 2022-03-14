/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:01:40 by dchheang          #+#    #+#             */
/*   Updated: 2022/03/14 09:04:38 by dchheang         ###   ########.fr       */
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
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef	typename allocator_type::const_pointer		const_pointer;
			typedef ptrdiff_t									difference_type;
			typedef	size_t										size_type;
			typedef RandomIte <value_type>						iterator;
			typedef RandomIte <const value_type>				const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

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
							 const allocator_type& alloc = allocator_type()) :
							 _alloc(alloc), _begin(NULL), _end(NULL), _capacity(0)
			{
				if (n > 0)
				{
					_alloc = alloc;
					_begin = _alloc.allocate(n);
					_end = _begin;
					_capacity = n;
					for (size_type i = 0; i < n; i++)
						_alloc.construct(_end++, val);
				}
			}

			/* RANGE : fills vector with elements from range first included to last not included
			** @param first : beginning of range
			** @param last : end of range */
			template <class InputIterator>
			vector (InputIterator first, InputIterator last,
					const allocator_type& alloc = allocator_type()) :
					_alloc(alloc), _begin(NULL), _end(NULL), _capacity(0)
			{
				InputIterator	ite;

				if (first != last)
				{
					for (ite = first; ite != last; ite++)
						_capacity++;
					_alloc = alloc;
					_begin = _alloc.allocate(_capacity);
					_end = _begin;
					while (first != last)
					{
						_alloc.construct(_end++, *first);
						first++;
					}
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

			/* DESTRUCTOR : destroy all elements in vector and deallocate memory */
			~vector ()
			{
				pointer	tmp;

				tmp = _begin;
				while (tmp != _end)
					_alloc.destroy(tmp++);
				_alloc.deallocate(_begin, _capacity);
			}

			/* OPERATOR= : copies elements from another vector
			** if x.size() > this->capacity(), causes reallocation
			** @param x : the vector to copy */
			vector& operator=(const vector& x)
			{
				size_t	xlen;
				pointer	ite;

				xlen = x.size();
				ite = _begin;
				if (xlen > _capacity)
				{
					while (ite != _end)
						_alloc.destroy(ite++);
					_alloc.deallocate(_begin, _capacity);
					_capacity = xlen;
					_begin = _alloc.allocate(xlen);
				}
				_end = _begin;
				for (size_t i = 0; i < xlen; i++)
					_alloc.construct(_end++, x[i]);
				return (*this);
			}


			/********************************** CAPACITY ********************************/
			/* SIZE : returns number of elements in vector */
			size_type	size() const
			{
				return (_end - _begin);
			}

			/* MAX SIZE : returns the theoretical maximum number of elements that vector can hold */
			size_type	max_size() const
			{
				return (_alloc.max_size());
			}

			/* RESIZE : resizes the container so that it contains n elements
			** @param n : the new size of vector
			** @param val : value to initialize elements with
			** if n < vector.size(), destroys elements past n
			** if n > vector.size(), inserts elements at the end of vector initialized to the value val
			** if n > vector.capacity(), reallocates memory
			** if exception is thrown, content of vector remains unchanged */
			void	resize(size_type n, value_type val = value_type())
			{
				size_type	len;
				pointer		tmp;

				len = size();
				tmp = _begin;
				if (n > _capacity)
				{
					if (_capacity * 2 >= n)
						reserve(_capacity * 2);
					else
						reserve(n);
				}
				else if (n < len)
				{
					while (tmp != _end)
						_alloc.destroy(tmp++);
					_end = _begin + n;
				}
				while (len++ < n)
					_alloc.construct(_end++, val);
			}



			/* CAPACITY : returns number of space currently allocated for the vector */
			size_type	capacity() const
			{
				return (_capacity);
			}

			/* EMPTY : test whether vector is empty */
			bool	empty() const
			{
				return (!size());
			}

			/* RESERVE : requests that vector capacity be at least enough to contain n elements
			** if n is greater than current capacity, causes reallocation
			** @param n : capacity size request */
			void reserve (size_type n)
			{
				pointer	begin;
				pointer end;
				pointer	tmp;

				begin = _begin;
				tmp = begin;
				end = _end;
				if (n > max_size())
					throw std::length_error("vector::_M_default_append");
				if (n > _capacity)
				{
					while (_begin != _end)
						_alloc.destroy(_begin++);
					_begin = _alloc.allocate(n);
					_end = _begin;
					_capacity = n;
					while (tmp != end)
						_alloc.construct(_end++, *tmp++);
					_alloc.deallocate(begin, end - begin);
				}
			}

			/********************************** ACCESSORS ********************************/

			reference	operator[] (size_type n) const
			{
				reference ret = *(_begin + n);
				return (ret);
			}



			/********************************** ITERATORS ********************************/
			iterator	begin()
			{
				return (iterator(_begin));
			}

			const_iterator	begin() const
			{
				return (const_iterator(_begin));
			}

			iterator	end()
			{
				return (iterator(_end));
			}

			const_iterator	end() const
			{
				return (const_iterator(_end));
			}

			reverse_iterator	rbegin()
			{
				return (reverse_iterator(_end));
			}

			const_reverse_iterator	rbegin() const
			{
				return (const_reverse_iterator (_end));
			}

			reverse_iterator	rend()
			{
				return (reverse_iterator(_begin));
			}

			const_reverse_iterator	rend() const
			{
				return (reverse_iterator(_end));
			}

			/********************************** OPERATORS ********************************/
	};
}

#endif
