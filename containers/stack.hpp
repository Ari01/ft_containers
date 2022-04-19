/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 15:25:00 by dchheang          #+#    #+#             */
/*   Updated: 2022/04/19 18:01:32 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef T								value_type;
			typedef Container						container_type;
			typedef typename Container::size_type	size_type;
		
		protected:
			container_type	c;

		public:
			// CONSTRUCTOR
			explicit stack (const container_type& ctnr = container_type()) : c(ctnr) {}

			// CAPACITY
			/* empty */
			bool	empty() const { return (c.empty()); }

			/* size */
			size_type	size() const { return (c.size()); }

			// ACCESSORS
			/* top */
			value_type&	top() { return (c.back()); }

			/* const top */
			const value_type&	top() const { return (c.back()); }

			// MODIFIERS
			/* push */
			void	push (const value_type& val) { c.push_back(val); }

			/* pop */
			void	pop() { c.pop_back(); }

			// OPERATORS
			friend bool operator== (const stack& lhs, const stack& rhs)
			{
				return (lhs.c == rhs.c);
			}

			friend bool operator!= (const stack& lhs, const stack& rhs)
			{
				return (lhs.c != rhs.c);
			}

			friend bool operator<  (const stack& lhs, const stack& rhs)
			{
				return (lhs.c < rhs.c);
			}

			friend bool operator<= (const stack& lhs, const stack& rhs)
			{
				return (lhs.c <= rhs.c);
			}

			friend bool operator>  (const stack& lhs, const stack& rhs)
			{
				return (lhs.c > rhs.c);
			}

			friend bool operator>= (const stack& lhs, const stack& rhs)
			{
				return (lhs.c >= rhs.c);
			}
	};
}

#endif
