/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:01:40 by dchheang          #+#    #+#             */
/*   Updated: 2022/05/24 18:36:33 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <stdexcept>
#include "iterator.hpp"
#include "utils.hpp"

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		/****************************** TYPES *****************************/
		public:
			typedef T														value_type;
			typedef Alloc													allocator_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef	typename allocator_type::const_pointer					const_pointer;
			typedef RandomIte <value_type>									iterator;
			typedef RandomIte <const value_type>							const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
			typedef	typename allocator_type::size_type						size_type;

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
					const allocator_type& alloc = allocator_type(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL) :
					_alloc(alloc), _begin(NULL), _end(NULL), _capacity(0)
			{
				if (first != last)
				{
					_capacity = ft::distance(first, last);
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
			vector (const vector& x) : _alloc(x._alloc), _begin(NULL), _end(NULL)
			{
				size_type		len;

				len = x.size();
				if (len)
					_begin = _alloc.allocate(len);
				_end = _begin;
				_capacity = len;
				for (size_type i = 0; i < len; i++)
					_alloc.construct(_end++, x[i]);
			}

			/* DESTRUCTOR : destroy all elements in vector and deallocate memory */
			~vector ()
			{
				clear();
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
				while (ite != _end)
					_alloc.destroy(ite++);
				if (xlen > _capacity)
				{
					_alloc.deallocate(_begin, _capacity);
					_capacity = xlen;
					_begin = _alloc.allocate(xlen);
				}
				_end = _begin;
				for (size_t i = 0; i < xlen; i++)
					_alloc.construct(_end++, x[i]);
				return (*this);
			}

			/********************************** ITERATORS ********************************/
			/* begin : returns iterator pointing on first elem in vector */
			iterator	begin()
			{
				return (iterator(_begin));
			}

			/* const begin : returns const iterator pointing on first elem in vector */
			const_iterator	begin() const
			{
				return (const_iterator(_begin));
			}

			/* end : returns iterator pointing on past the end in vector */
			iterator	end()
			{
				return (iterator(_end));
			}

			/* const end : returns const iterator pointing on past the end in vector */
			const_iterator	end() const
			{
				return (const_iterator(_end));
			}

			/* rbegin : returns reverse_iterator pointing on past the end - 1 in vector */
			reverse_iterator	rbegin()
			{
				return (reverse_iterator(_end));
			}

			/* const rbegin : returns const reverse_iterator pointing past the end - 1 in vector */
			const_reverse_iterator	rbegin() const
			{
				return (const_reverse_iterator (_end));
			}

			/* rend : returns reverse_iterator pointing on first elem in vector -1,
			** which is past the end in the reverse iterator */
			reverse_iterator	rend()
			{
				return (reverse_iterator(_begin));
			}
			/* const rend : returns const_reverse_iterator pointing on first elem in vector -1,
			** which is past the end in the reverse iterator */
			const_reverse_iterator	rend() const
			{
				return (const_reverse_iterator(_begin));
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

			/* RESIZE : resizes the container so that it contains n elements initialized to val
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
				tmp = _begin + n;

				if (n > _capacity)
					len * 2 >= n ? reserve(len * 2) : reserve(n);
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
				pointer	old_begin;
				pointer	old_end;
				size_t	len;

				old_begin = _begin;
				old_end = _end;
				len = size();
				if (n > max_size())
					throw std::length_error("vector::_M_fill_insert");
				if (n > _capacity)
				{
					_begin = _alloc.allocate(n);
					_end = _begin;
					_capacity = n;
					while (old_begin != old_end)
					{
						_alloc.construct(_end++, *old_begin);
						_alloc.destroy(old_begin++);
					}
					old_begin -= len;
					_alloc.deallocate(old_begin, len);
				}
			}

			/********************************** ACCESSORS ********************************/
			/* operator[] : returns reference on element n
			** @param n : index of element to return
			** undefined behaviour if n is out of range */
			reference	operator[] (size_type n)
			{
				return (*(_begin + n));
			}

			const_reference	operator[] (size_type n) const
			{
				return (*(_begin + n));
			}

			/* at : same as operator[] but throws out of range exception if n is out of bounds
			** @param n : index of element to return */
			reference	at(size_type n)
			{
				if (n >= size() || n < 0)
					throw std::out_of_range("vector::_M_range_check");
				return (*(_begin + n));
			}

			/* const at : returns const reference on element n
			** @param n : index of element to return */
			const_reference	at(size_type n) const
			{
				if (n >= size() || n < 0)
					throw std::out_of_range("vector::_M_range_check");
				return (*(_begin + n));
			}

			/* front : returns reference to first elem in vector
			** calling this function on empty vector causes undefined behaviour */
			reference	front()
			{
				return (*_begin);
			}

			/* const front : returns const_reference to first elem in vector */
			const_reference	front() const
			{
				return (*_begin);
			}

			/* back : returns reference to last elem in vector
			** call on empty vector causes undefined behaviour */
			reference	back()
			{
				return (*(_end - 1));
			}

			/* const back : returns const_reference to last elem in vector */
			const_reference	back() const
			{
				return (*(_end - 1));
			}

			/* get_allocator : returns allocator */
			allocator_type get_allocator() const
			{
				return (_alloc);
			}

			/********************************** MODIFIERS ********************************/
			/* ASSIGN : assigns new content to vector
			** @param first and last : elements are constructed in range between first and last */
			template <class InputIterator>
			void assign (InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL)
			{
				size_type	len;
				pointer		old_begin;
				pointer		tmp;

				old_begin = _begin;
				tmp = old_begin;
				len = ft::distance(first, last);
				if (len > _capacity)
				{
					_begin = _alloc.allocate(len);
					_capacity = len;
					while (tmp != _end)
						_alloc.destroy(tmp++);
					_alloc.deallocate(old_begin, _end - old_begin);
				}
				else
				{
					while (tmp != _end)
						_alloc.destroy(tmp++);
				}
				_end = _begin;
				while (first != last)
					_alloc.construct(_end++, *first++);
			}

			/* ASSIGN : assigns new content to vector
			** @param n, val : n elements constructed and initialized to a copy of val */
			void	assign (size_type n, const value_type &val)
			{
				pointer		old_begin;
				pointer		tmp;

				old_begin = _begin;
				tmp = old_begin;
				if (n > _capacity)
				{
					_begin = _alloc.allocate(n);
					_capacity = n;
					while (tmp != _end)
						_alloc.destroy(tmp++);
					_alloc.deallocate(old_begin, _end - old_begin);
				}
				else
				{
					while (tmp != _end)
						_alloc.destroy(tmp++);
				}
				_end = _begin;
				for (size_t i = 0; i < n; i++)
					_alloc.construct(_end++, val);
			}

			/* PUSH_BACK : adds elem at end of vector
			** @param : val, the elem to add
			** if alloc.construct is not supported with val, it causes undefined behaviour */
			void	push_back(const value_type &val)
			{
				if (size() + 1 > _capacity)
					_capacity ? reserve (_capacity * 2) : reserve(1);
				_alloc.construct(_end++, val);
			}

			/* POP_BACK : destroys last elem in vector
			** if vector is empty(), causes undefined behaviour */
			void	pop_back()
			{
				_alloc.destroy(--_end);
			}

			/* INSERT (1) : insert single element in vector at position position
			** @param position : the position to insert the elem in
			** @param val : the element to insert
			** @return : an iterator that points to the first elem newly inserted
			** if position is invalid or if alloc.construct is not supported with val, this
			** causes undefined behaviour */
			iterator	insert(iterator position, const value_type &val)
			{
				size_type		len;
				difference_type	dist;
				iterator		ite;

				len = size();
				dist = position - begin();
				if (position == end())
					push_back(val);
				else
				{
					resize(len + 1);
					position = begin() + dist;
					for (ite = end() - 1; ite != position; ite--)
						*ite = *(ite - 1);
					*ite = val;
				}
				return (begin() + dist);

			/*	pointer			tmp;
				difference_type	dist;
				size_type		len;
				pointer			old_begin;
				pointer			old_end;

				old_begin = _begin;
				old_end = _end;
				dist = position - begin();
				len = size();
				if (empty() || position == end())
					push_back(val);
				else if (len + 1 > _capacity)
				{
					tmp = _begin;
					_capacity *= 2;
					_begin = _alloc.allocate(_capacity);
					_end = _begin;
					while (tmp != old_end)
					{
						if (tmp == old_begin + dist)
							_alloc.construct(_end++, val);
						_alloc.construct(_end++, *tmp);
						_alloc.destroy(tmp++);
					}
					_alloc.deallocate(old_begin, len);
				}
				else
				{
					_alloc.construct(_end, *(_end - 1));
					_end++;
					for (iterator ite = end() - 2; ite != position; ite--)
						*ite = *(ite - 1);
					*position = val;
					return (position);
				}
				return (begin() + dist);*/
			}

			/* INSERT (2) : insert n elements initialized with value val before position position
			** @param position : position to insert elems at
			** @param n : number of elements to insert
			** @param val : value to initialize new elems with */
		    void insert (iterator position, size_type n, const value_type& val)
			{
				size_type		len;
				iterator		ite;
				difference_type	dist;

				len = size();
				dist = position - begin();
				resize(len + n);
				position = begin() + dist;
				for (ite = end() - 1; ite >= position + n; ite--)
					*ite = *(ite - n);
				while (ite >= position)
					*ite-- = val;
			}

			/* INSERT (3) : insert elems in range from first to last before position position
			** @param position : position to insert elems at
			** @param first : begin of range
			** @param last : end of range */
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL)
			{
				size_t		len;
				size_t		pos_index;
				size_t		n;
				iterator	ite;

				pos_index = position - begin();
				n = ft::distance(first, last);
				len = size();
				resize(len + n);
				position = begin() + pos_index;
				if (len)
				{
					for (ite = end() - 1; ite - n >= position; ite--)
						*ite = *(ite - n);
					ite = position;
				}
				else
					ite = begin();
				while (first != last)
					*ite++ = *first++;
			}

			/* ERASE (1) : removes the element at position
			** @param position : the position of the element to remove 
			** @return : an iterator pointing to the new pos of the element following the one removed
			** invalid position causes undefined behaviour */
			iterator	erase(iterator position)
			{
				iterator	ret;
				iterator	end_ite;

				end_ite = end();
				ret = position;
				while (position < end_ite - 1)
				{
					*position = *(position + 1);
					position++;
				}
				_alloc.destroy(position.base());
				_end--;
				return (ret);
			}

			/* ERASE (2) : removes the range of elements from first to last */
			iterator	erase(iterator first, iterator last)
			{
				iterator		ite;
				iterator		tmp;
				iterator		end_ite;

				end_ite = end();
				tmp = last;
				for (ite = first; ite != end_ite; ite++)
				{
					if (tmp != end_ite)
						*ite = *tmp++;
					else
						_alloc.destroy(ite.base());
				}
				_end -= last - first;
				return (first);
			}

			/* SWAP : swap the elems of two vectors */
			void	swap(vector &x)
			{
				pointer		begintmp = _begin;
				pointer		endtmp = _end;
				size_type	captmp = _capacity;

				_begin = x._begin;
				_end = x._end;
				_capacity = x._capacity;
				x._begin = begintmp;
				x._end = endtmp;
				x._capacity = captmp;
			}

			/* CLEAR : destroys all elems in vector */
			void	clear()
			{
				pointer	tmp;

				tmp = _begin;
				while (tmp != _end)
					_alloc.destroy(tmp++);
				_end = _begin;
			}

			/********************************** NON MEMBER ********************************/
			/* OPERATOR== : if lhs.size == rhs.size, compares each elements in both container using equal
			** returns false at the first mismatch, otherwhise returns true */
			friend bool operator== (const vector& lhs, const vector& rhs)
			{
				if (lhs.size() != rhs.size())
					return (false);
				return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
			}

			friend bool operator!= (const vector& lhs, const vector& rhs)
			{
				return (!(lhs == rhs));
			}

			/* OPERATOR< : lexicographical compare between lhs and rhs elements */ 
			friend bool operator< (const vector& lhs, const vector& rhs)
			{
				return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
			}

			friend bool operator<= (const vector& lhs, const vector& rhs)
			{
				return (!(rhs < lhs));
			}

			friend bool operator> (const vector& lhs, const vector& rhs)
			{
				return (rhs < lhs);
			}

			friend bool operator>= (const vector& lhs, const vector& rhs)
			{
				return (!(lhs < rhs));
			}

			/* SWAP : swaps elements from x and y */
			friend void swap (vector& x, vector& y)
			{
				x.swap(y);
			}
	};
}

#endif
