/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:01:44 by dchheang          #+#    #+#             */
/*   Updated: 2022/04/17 18:37:50 by dchheang         ###   ########.fr       */
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
			map (const map& x) : tree(x.tree) {}

			/* destructor */
			~map() {}

			/* operator= */
			map&	operator=(const map& x)
			{
				if (this != &x)
					tree = x.tree;
				return (*this);
			}

			/************ ITERATORS **********/
			iterator	begin()
			{
				Node<value_type> *root;

				root = tree.getRoot();
				return (iterator(tree.min(root), root));
			}

			const_iterator	begin() const
			{
				Node<value_type> *root;

				root = tree.getRoot();
				return (const_iterator(tree.min(root), root));
			}

			iterator	end()
			{
				return (iterator(NULL, tree.getRoot()));
			}

			const_iterator	end() const
			{
				return (const_iterator(NULL, tree.getRoot()));
			}

			reverse_iterator rbegin()
			{
				return (reverse_iterator(end()));
			}

			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(end()));
			}

			reverse_iterator rend()
			{
				return (reverse_iterator(begin()));
			}

			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(begin()));
			}

			/************ CAPACITY **********/
			/* EMPTY */
			bool	empty() const
			{
				return (!tree.size());
			}

			/* SIZE */
			size_type	size() const
			{
				return (tree.size());
			}

			/* MAX SIZE */
			size_type	max_size() const
			{
				return (tree.getAlloc().max_size());
			}

			/************ ACCESSORS **********/
			/* OPERATOR [] */
			mapped_type& operator[] (const key_type& k)
			{
				return (insert(ft::make_pair(k, mapped_type())).first->second);
			}

			/************ MODIFIERS **********/
			/* INSERT (val) */
			pair<iterator, bool> insert (const value_type& val)
			{
				pair<Node<value_type>*, bool>	tmp(tree.insert(val));

				return (ft::make_pair(iterator(tmp.first, tree.getRoot()), tmp.second));
			}

			/* INSERT (hint) */
			iterator insert (iterator position, const value_type& val)
			{
				return (iterator(tree.insert(position.base(), val), tree.getRoot()));
			}

			/* INSERT (range) */
			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				InputIterator	ite;

				for (ite = first; ite != last; ite++)
					tree.insert(*ite);
			}

			/* ERASE (hint) */
			void erase (iterator position)
			{
				tree.erase(position.base());
			}

			/* ERASE (key) */
			size_type erase (const key_type& k)
			{
				Node<value_type>	*ptr;

				ptr = tree.find(ft::make_pair(k, mapped_type()));
				if (ptr)
				{
					tree.erase(ptr);
					return (1);
				}
				return (0);
			}

			/* ERASE (range) */
			void erase (iterator first, iterator last)
			{
				iterator	ite;
				iterator	tmp;

				ite = first;
				while (ite != last)
				{
					tmp = ite;
					ite++;
					tree.erase(tmp.base());
				}
			}

			/* SWAP */
			void swap (map& x)
			{
				tree.swap(x.tree);
			}

			/* CLEAR */
			void clear ()
			{
				tree.destroy();
			}

			/************ OBSERVERS **********/
			/* KEY_COMP() */
			key_compare key_comp() const
			{
				return (key_compare());
			}

			/* VALUE_COMP() */
			value_compare	value_comp() const
			{
				return (value_compare(key_compare()));
			}

			/************ OPERATIONS **********/
			/* FIND */
			iterator find (const key_type& k)
			{
				Node<value_type>	*tmp;

				tmp = tree.find(ft::make_pair(k, mapped_type()));
				if (tmp)
					return (iterator(tmp, tree.getRoot()));
				return (end());
			}

			/* const FIND */
			const_iterator find (const key_type& k) const
			{
				Node<value_type>	*tmp;

				tmp = tree.find(ft::make_pair(k, mapped_type()));
				if (tmp)
					return (const_iterator(tmp, tree.getRoot()));
				return (end());
			}

			/* COUNT */
			
	};
}

#endif
