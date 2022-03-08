/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:27:27 by dchheang          #+#    #+#             */
/*   Updated: 2022/03/08 20:12:49 by dchheang         ###   ########.fr       */
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

	/********************** BIDIR ITERATOR  ***************************/
	template <typename T>
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

			// MEMBER OPERATORS
			reference	operator*()
			{
				return (*val);
			}

			pointer	operator->()
			{
				return (val);
			}

			BidirIte &operator++()
			{
				++val;
				return (*this);
			}

			BidirIte operator++(int)
			{
				BidirIte tmp(*this);

				++val;
				return (tmp);
			}

			BidirIte &operator--()
			{
				--val;
				return (*this);
			}

			BidirIte operator--(int)
			{
				BidirIte tmp(*this);

				--val;
				return (tmp);
			}

			// NON MEMBER OPERATORS
			friend bool operator==(BidirIte const& lhs, BidirIte const& rhs)
			{
				return (lhs.val == rhs.val);
			}

			friend bool operator!=(BidirIte const& lhs, BidirIte const& rhs)
			{
				return (lhs.val != rhs.val);
			}
	};

	/********************** RANDOM ITERATOR  ***************************/
	template <typename T>
	class RandomIte : public BidirIte<T>
	{
		public:
			typedef typename iterator<random_access_iterator_tag, T>::value_type		value_type;
			typedef typename iterator<random_access_iterator_tag, T>::difference_type	difference_type;
			typedef typename iterator<random_access_iterator_tag, T>::pointer			pointer;
			typedef typename iterator<random_access_iterator_tag, T>::reference			reference;
			typedef typename iterator<random_access_iterator_tag, T>::iterator_category	iterator_category;

		public:

			// CONSTS DESTS
			RandomIte() : BidirIte<T>() {}
			RandomIte(RandomIte const& other) : BidirIte<T>(other) {}
			RandomIte(pointer p) : BidirIte<T>(p) {}
			~RandomIte() {}

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
			friend RandomIte	operator+(RandomIte const& lhs, difference_type n)
			{
				RandomIte	tmp(lhs);

				tmp.val += n;
				return (tmp);
			}

			/*friend RandomIte	operator+(difference_type n, RandomIte const& rhs)
			{
				return (rhs.val + n);
			}*/

			friend RandomIte	operator-(RandomIte const& lhs, difference_type n)
			{
				RandomIte	tmp(lhs);

				tmp.val -= n;
				return (tmp);
			}

			friend RandomIte	operator-(RandomIte const& lhs, RandomIte const& rhs)
			{
				RandomIte	tmp;

				tmp.val = lhs.val - rhs.val;
				return (tmp);
			}
	};
}

#endif
