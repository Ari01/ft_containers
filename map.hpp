/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:01:44 by dchheang          #+#    #+#             */
/*   Updated: 2022/04/05 15:44:32 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include "utils.hpp"
#include "iterator.hpp"
#include "binary_tree.hpp"

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>,
				class Alloc = std::allocator<pair<const Key,T> > >
	class map
	{
		public:
			typedef Key														key_type;
			typedef T														mapped_type;
			typedef pair<const key_type, mapped_type>						value_type;
			typedef Compare													key_compare;
			typedef Alloc													allocator_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef TreeIte<value_type>										iterator;
			typedef TreeIte<const value_type>								const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
			typedef typename allocator_type::size_type						size_type;

			// nested class function to compare elements (see value_comp)
			class value_compare : public std::binary_function<value_type, value_type, bool>
			{
				protected:
					key_compare		comp;
					value_compare	(key_compare c) : comp(c) {}

				public:
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};

		private:
			BinaryTree<value_type, value_compare>	tree;

		public:
			// CONSTRUCTORS
			/* default */
			explicit map (const key_compare& comp = key_compare(),
							const allocator_type& alloc = allocator_type()) :
							tree(value_compare(comp)) {}

			/* range */
			template <class InputIterator>
			map (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) :
				tree(value_compare(comp))
			{
				insert(first, last);
			}

			/* copy */
			map (const map& x) : tree(value_compare(key_compare()))
			{
				insert(x.begin(), x.last());
			}
	};
}

#endif
