/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:27:27 by dchheang          #+#    #+#             */
/*   Updated: 2022/05/31 16:14:35 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>

namespace ft
{
	/*********************** ITERATOR TAGS ****************************/
	/* Empty structs to distinguish different iterator types
	** Algorithms used/called on iterators differ from one type to another */

	// INPUT : can be incremented and dereferenced as rvalue
	struct input_iterator_tag {};

	// OUTPUT : can be dereferenced as lvalue
	struct output_iterator_tag {};

	// FORWARD : default constructible, multipass, forward only
	struct forward_iterator_tag : public input_iterator_tag {};

	// BIDIRECTIONAL : can be decremented
	struct bidirectional_iterator_tag : public forward_iterator_tag {};

	// RANDOM : supports arithmetic operators, inequality and operator []
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};


	/********************** ITERATOR TRAITS ***************************/
	/* defines properties of iterators */
	template <class T>
	struct iterator_traits
	{
		typedef typename T::value_type			value_type;
		typedef typename T::difference_type		difference_type;
		typedef typename T::iterator_category	iterator_category;
		typedef typename T::pointer				pointer;
		typedef typename T::reference			reference;
	};

	/* pointer that can be used as iterator specialization */
	template <class	T>
	struct iterator_traits<T*>
	{
		typedef	T							value_type;
		typedef	ptrdiff_t					difference_type;
		typedef	random_access_iterator_tag	iterator_category;
		typedef	T*							pointer;
		typedef	T&							reference;
	};

	/* const pointer specialization */
	template <class	T>
	struct iterator_traits<const T*>
	{
		typedef	T							value_type;
		typedef	ptrdiff_t					difference_type;
		typedef	random_access_iterator_tag	iterator_category;
		typedef	const T*					pointer;
		typedef	const T&					reference;
	};
	
	/********************** ITERATOR  *********************************/
	/* Base iterator class to derive from */
	template <class Category, class T, class Distance = ptrdiff_t,
				class Pointer = T*, class Reference = T&>
	class iterator
	{
		public:
			typedef T         value_type;
			typedef Distance  difference_type;
			typedef Pointer   pointer;
			typedef Reference reference;
			typedef Category  iterator_category;
	};

	/********************** DISTANCE **********************************/
	template< class InputIt >
	typename iterator_traits<InputIt>::difference_type distance( InputIt first, InputIt last )
	{
		typename iterator_traits<InputIt>::difference_type	ret;

		ret = 0;
		while (first++ != last)
			ret++;
		return (ret);
	}

	/********************** BIDIR ITERATOR  ***************************/
/*	template <typename T>
	class BidirIte : public iterator<bidirectional_iterator_tag, T>
	{
		public:
			typedef typename iterator<bidirectional_iterator_tag, T>::value_type		value_type;
			typedef typename iterator<bidirectional_iterator_tag, T>::difference_type	difference_type;
			typedef typename iterator<bidirectional_iterator_tag, T>::pointer			pointer;
			typedef typename iterator<bidirectional_iterator_tag, T>::reference			reference;
			typedef typename iterator<bidirectional_iterator_tag, T>::iterator_category	iterator_category;

		protected:
			pointer	val;
		
		public:
			// CONSTS DESTS
			BidirIte() : val(NULL) {}
			BidirIte(pointer p) : val(p) {}
			BidirIte(BidirIte const& other) : val(other.val) {}
			BidirIte &operator=(BidirIte const& other)
			{
				if (this != &other)
					val = other.val;
				return (*this);
			}
			~BidirIte() {}

			};*/

	/********************** RANDOM ITERATOR  ***************************/
	template <typename T>
	class RandomIte : public iterator<random_access_iterator_tag, T>
	{
		public:
			typedef typename iterator<random_access_iterator_tag, T>::value_type		value_type;
			typedef typename iterator<random_access_iterator_tag, T>::difference_type	difference_type;
			typedef typename iterator<random_access_iterator_tag, T>::pointer			pointer;
			typedef typename iterator<random_access_iterator_tag, T>::reference			reference;
			typedef typename iterator<random_access_iterator_tag, T>::iterator_category	iterator_category;

		private:
			pointer	val;

		public:

			// CONSTS DESTS
			RandomIte() : val(NULL) {}
			RandomIte(pointer p) : val(p) {}
			
			template <typename TT>
			RandomIte(RandomIte<TT> const& other)
			{
				this->val = other.base();
			}

			RandomIte &operator=(RandomIte const& other)
			{
				if (this != &other)
					val = other.val;
				return (*this);
			}

			~RandomIte() {}

			// ACCESSORS
			pointer	base() const
			{
				return (val);
			}

			// MEMBER OPERATORS
			reference	operator*()
			{
				return (*val);
			}

			pointer	operator->()
			{
				return (val);
			}

			RandomIte &operator++()
			{
				++val;
				return (*this);
			}

			RandomIte operator++(int)
			{
				RandomIte tmp(*this);

				++val;
				return (tmp);
			}

			RandomIte &operator--()
			{
				--val;
				return (*this);
			}

			RandomIte operator--(int)
			{
				RandomIte tmp(*this);

				--val;
				return (tmp);
			}

			// MEMBER OPERATORS
			RandomIte	&operator+=(difference_type n)
			{
				this->val += n;
				return (*this);
			}

			RandomIte	&operator-=(difference_type n)
			{
				this->val -= n;
				return (*this);
			}

			reference	operator[](difference_type n)
			{
				return *(this->val + n);
			}

			// NON MEMBER OPERATORS
			friend bool operator==(RandomIte<T> const& lhs, RandomIte<T> const& rhs)
			{
				return (lhs.base() == rhs.base());
			}

			template <typename T2>
			friend bool operator==(RandomIte<T> const& lhs, RandomIte<T2> const& rhs)
			{
				return (lhs.base() == rhs.base());
			}

			friend bool operator!=(RandomIte<T> const& lhs, RandomIte<T> const& rhs)
			{
				return (lhs.base() != rhs.base());
			}

			template <typename T2>
			friend bool operator!=(RandomIte<T> const& lhs, RandomIte<T2> const& rhs)
			{
				return (lhs.base() != rhs.base());
			}

			friend RandomIte	operator+(RandomIte const& lhs, difference_type n)
			{
				RandomIte	tmp(lhs);

				tmp.val += n;
				return (tmp);
			}

			friend RandomIte	operator+(difference_type n, RandomIte const& rhs)
			{
				RandomIte	tmp(rhs);

				tmp.val += n;
				return (tmp);
			}

			friend RandomIte	operator-(RandomIte const& lhs, difference_type n)
			{
				RandomIte	tmp(lhs);

				tmp.val -= n;
				return (tmp);
			}

			friend difference_type	operator-(RandomIte const& lhs, RandomIte const& rhs)
			{
				return (lhs.val - rhs.val);
			}

			template <typename T2>
			friend difference_type	operator-(RandomIte<T> const& lhs, RandomIte<T2> const& rhs)
			{
				return (lhs.base() - rhs.base());
			}

			friend bool	operator<(RandomIte const& lhs, RandomIte const& rhs)
			{
				return (lhs.val < rhs.val);
			}

			template <typename T2>
			friend bool	operator<(RandomIte<T> const& lhs, RandomIte<T2> const& rhs)
			{
				return (lhs.base() < rhs.base());
			}

			friend bool	operator<=(RandomIte const& lhs, RandomIte const& rhs)
			{
				return (lhs.base() <= rhs.base());
			}

			template <typename T2>
			friend bool	operator<=(RandomIte<T> const& lhs, RandomIte<T2> const& rhs)
			{
				return (lhs.base() <= rhs.base());
			}

			friend bool	operator>(RandomIte const& lhs, RandomIte const& rhs)
			{
				return (lhs.val > rhs.val);
			}

			template <typename T2>
			friend bool	operator>(RandomIte<T> const& lhs, RandomIte<T2> const& rhs)
			{
				return (lhs.base() > rhs.base());
			}

			friend bool	operator>=(RandomIte const& lhs, RandomIte const& rhs)
			{
				return (lhs.val >= rhs.val);
			}

			template <typename T2>
			friend bool	operator>=(RandomIte<T> const& lhs, RandomIte<T2> const& rhs)
			{
				return (lhs.base() >= rhs.base());
			}
	};

	/********************** REVERSE ITERATOR  ***************************/
	template <class Iterator>
	class reverse_iterator
	{
		// TYPES
		public:
			typedef Iterator												iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;

		// ATTRIBUTES
		private:
			iterator_type	ite;

		// CONSTS
		public:
			/** default */
			reverse_iterator() : ite() {}

			/** initialize */
			explicit reverse_iterator(iterator_type it) : ite(it) {}

			/** copy */
			template <class Iter>
			reverse_iterator(const reverse_iterator<Iter>& rev_it) : ite(rev_it.base()) {}

			/****************************** ACCESSORS *****************************/

			/* BASE : returns base operator */
			iterator_type base() const { return (ite); }

			/****************************** OPERATORS *****************************/

			// MEMBER OPS
			reference	operator*() const
			{
				iterator_type	tmp = ite;

				return (*(--tmp));
			}

			reverse_iterator operator+ (difference_type n) const
			{
				return (reverse_iterator(ite - n));
			}

			reverse_iterator& operator++()
			{
				ite--;
				return (*this);
			}

			reverse_iterator  operator++(int)
			{
				reverse_iterator	tmp(*this);

				++(*this);
				return (tmp);
			}

			reverse_iterator& operator+= (difference_type n)
			{
				ite -= n;
				return (*this);
			}

			reverse_iterator operator- (difference_type n) const
			{
				return (reverse_iterator(ite + n));
			}

			reverse_iterator& operator--()
			{
				ite++;
				return (*this);
			}

			reverse_iterator  operator--(int)
			{
				reverse_iterator	tmp(*this);

				--(*this);
				return (tmp);
			}

			reverse_iterator& operator-= (difference_type n)
			{
				ite += n;
				return (*this);
			}

			pointer operator->() const
			{
				return (&(operator*()));
			}

			reference operator[] (difference_type n)
			{
				return (ite[-n - 1]);
			}

			// NON MEMBER OPS
			friend bool operator== (const reverse_iterator& lhs, const reverse_iterator& rhs)
			{
				return (lhs.ite == rhs.ite);
			}

			template <typename IteType>
			friend bool operator== (const reverse_iterator& lhs, const reverse_iterator<IteType>& rhs)
			{
				return (lhs.base() == rhs.base());
			}

			friend bool operator!= (const reverse_iterator& lhs, const reverse_iterator& rhs)
			{
				return (lhs.ite != rhs.ite);
			}

			template <typename IteType>
			friend bool operator!= (const reverse_iterator& lhs, const reverse_iterator<IteType>& rhs)
			{
				return (lhs.base() != rhs.base());
			}

			friend bool operator<  (const reverse_iterator& lhs, const reverse_iterator& rhs)
			{
				return (lhs.ite > rhs.ite);
			}

			template <typename IteType>
			friend bool operator<  (const reverse_iterator& lhs, const reverse_iterator<IteType>& rhs)
			{
				return (lhs.base() > rhs.base());
			}

			friend bool operator<= (const reverse_iterator& lhs, const reverse_iterator& rhs)
			{
				return (lhs.ite >= rhs.ite);
			}

			template <typename IteType>
			friend bool operator<= (const reverse_iterator& lhs, const reverse_iterator<IteType>& rhs)
			{
				return (lhs.base() >= rhs.base());
			}

			friend bool operator>  (const reverse_iterator& lhs, const reverse_iterator& rhs)
			{
				return (lhs.ite < rhs.ite);
			}

			template <typename IteType>
			friend bool operator>  (const reverse_iterator& lhs, const reverse_iterator<IteType>& rhs)
			{
				return (lhs.base() < rhs.base());
			}

			friend bool operator>= (const reverse_iterator& lhs, const reverse_iterator& rhs)
			{
				return (lhs.ite <= rhs.ite);
			}

			template <typename IteType>
			friend bool operator>= (const reverse_iterator& lhs, const reverse_iterator<IteType>& rhs)
			{
				return (lhs.base() <= rhs.base());
			}

			friend reverse_iterator operator+ (difference_type n, const reverse_iterator& rev_it)
			{
				return (rev_it + n);
			}

			friend difference_type operator- (const reverse_iterator& lhs, const reverse_iterator& rhs)
			{
				return (rhs.ite - lhs.ite);
			}

			template <typename IteType>
			friend difference_type operator- (const reverse_iterator& lhs, const reverse_iterator<IteType>& rhs)
			{
				return (rhs.base() - lhs.base());
			}
	};
}

#endif
