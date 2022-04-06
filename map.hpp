/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:01:44 by dchheang          #+#    #+#             */
/*   Updated: 2022/04/06 10:55:23 by dchheang         ###   ########.fr       */
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
				friend class map;
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
			/************ CONSTRUCTORS **********/
			/* default */
			explicit map (const key_compare& comp = key_compare(),
							const allocator_type& alloc = allocator_type()) :
							tree(value_compare(comp))
							{
								(void)alloc;	
							}

			/* range */
			template <class InputIterator>
			map (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) :
				tree(value_compare(comp))
			{
				(void)alloc;
				InputIterator	ite;

				for (ite = first; ite != last; ite++)
					tree.insert(*ite);
			}

			/* copy */
			map (const map& x) : tree(value_compare(key_compare()))
			{
				const_iterator	ite;

				for (ite = x.begin(); ite != x.end(); ite++)
					tree.insert(*ite);
			}

			/************ ITERATORS **********/
			iterator	begin()
			{
				return (iterator(tree.min(tree.getRoot())));
			}

			const_iterator	begin() const
			{
				return (const_iterator(tree.min(tree.getRoot())));
			}

			iterator	end()
			{
				return (iterator());
			}

			const_iterator	end() const
			{
				return (const_iterator());
			}

			/************ MODIFIERS **********/
			/* INSERT (val) */
			pair<iterator, bool> insert (const value_type& val)
			{
				pair<Node<value_type>*, bool>	tmp(tree.insert(val));

				return (make_pair(iterator(tmp.first), tmp.second));
			}

			/* INSERT (hint) */
			iterator insert (iterator position, const value_type& val)
			{
				return (iterator(tree.insert(position->base(), val)));
			}

			/* INSERT (range) */
			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				InputIterator	ite;

				for (ite = first; ite != last; ite++)
					tree.insert(*ite);
			}
	};
}

#endif
