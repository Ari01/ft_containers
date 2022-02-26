/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators_traits.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:27:27 by dchheang          #+#    #+#             */
/*   Updated: 2022/02/26 12:01:41 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	template <class T>
	struct iterator_traits {
		typedef typename T::value_type			value_type;
		typedef typename T::difference_type		difference_type;
		typedef typename T::iterator_category	iterator_category;
		typedef typename T::pointer				pointer;
		typedef typename T::reference			reference;
	};

	template	<class	T>
	struct	iterator_traits<T*>	{
		typedef	T							value_type;
		typedef	ptrdiff_t					difference_type;
		typedef	random_access_iterator_tag	iterator_category;
		typedef	T*							pointer;
		typedef	T&							reference;
	};

	template	<class	T>
	struct	iterator_traits<const T*>	{
		typedef	T							value_type;
		typedef	ptrdiff_t					difference_type;
		typedef	random_access_iterator_tag	iterator_category;
		typedef	const T*					pointer;
		typedef	const T&					reference;
	};
}
