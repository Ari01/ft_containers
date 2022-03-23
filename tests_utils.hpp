/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_utils.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 16:21:46 by dchheang          #+#    #+#             */
/*   Updated: 2022/03/23 15:03:42 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_HPP
#define TESTS_HPP

#include "vector.hpp"
#include "iterator.hpp"

#if STD == 1
	using namespace std;
#else
	using namespace ft;
#endif

template <typename T>
void	print(vector<T> &v, std::string name)
{
	std::cout << name << " : ";
	for (size_t i = 0; i < v.size(); i++)
		std::cout << v[i] << " ";
	std::cout << std::endl;
}

/********************************* CONSTRUCTORS *********************************/

	/* SIZE CONST
	** @param n : size to initialize the container with
	** on success, prints size and capacity
	** on failure, throws bad alloc exception */
	template <typename T>
	void	test_size_construct(int n)
	{
		std::cout << "TEST vector(" << n << ")" << std::endl;
		try {
			vector<T> v(n);
			std::cout << "v.size = " << v.size() << ", v.capacity = " << v.capacity() << std::endl;
		} catch (std::bad_alloc &e) {
			std::cout << e.what() << std::endl;
		}
		std::cout << std::endl;
	}

	/* RANGE CONST
	** copies elements from range begin to end in container
	** and compares each element from the range and the container
	** on failure, prints test KO and the elems that differ
	** on success, prints every elems in the container
	** @param begin : start of range
	** @param end : end of range */
	template <typename T, typename iterator>
	void	test_range_construct(iterator begin, iterator end)
	{
		vector<T>	v(begin, end);
		iterator	ite;
		size_t		i = 0;

		std::cout << "range = ";
		for (ite = begin; ite != end; ite++)
			std::cout << *ite << " ";
		std::cout << std::endl;

		std::cout << "vector = ";
		while (begin != end)
		{
			if (v[i] != *begin)
			{
				std::cout << "TEST KO, v[" << i << "] = " << v[i] << " != " << *begin << std::endl;
				break ;
			}
			else
				std::cout << v[i] << " ";
			i++;
			begin++;
		}
		std::cout << std::endl << "capacity = " << v.capacity() << ", size = " << v.size() << std::endl;
		std::cout << std::endl;
	}

	/* COPY CONST
	** same as range const but copies elements from another vector instead of a range
	** @param v1 : the vector to copy */
	template <typename T>
	void	test_copy_construct(vector<T> v1)
	{
		vector<T>	v2(v1);
		size_t		len1;
		size_t		len2;
		size_t		capacity1;
		size_t		capacity2;

		len1 = v1.size();
		len2 = v2.size();
		capacity1 = v1.capacity();
		capacity2 = v2.capacity();
		if (len1 != len2)
			std::cout << "TEST KO, v1.size = " << len1 << " != " << len2 << std::endl;
		else if (capacity1 != capacity2)
			std::cout << "TEST KO, v1.capacity = " << capacity1 << " != " << capacity2 << std::endl;
		else
		{
			std::cout << "size1 = " << len1 << ", size2 = " << len2 << std::endl;
			std::cout << "capacity1 = " << capacity1 << ", capacity2 = " << capacity2 << std::endl;
			for (size_t i = 0; i < v1.size(); i++)
			{
				if (v1[i] != v2[i])
				{
					std::cout << "TEST KO, v1[" << i << "] = " << v1[i] << " != " << v2[i] << std::endl;
					break ;
				}
				else
					std::cout << v1[i] << " ";
			}
		}
		std::cout << std::endl << std::endl;
	}

	/* OPERATOR= : prints vector, new size and cap */
	template <typename T>
	void	test_affectation_operator(vector<T> src, vector<T> dst)
	{
		size_t	i;

		std::cout << "src = ";
		for (i = 0; i < src.size(); i++)
			std::cout << src[i] << " ";
		std::cout << std::endl;

		std::cout << "dst = ";
		for (i = 0; i < dst.size(); i++)
			std::cout << dst[i] << " ";
		std::cout << std::endl;

		std::cout << "dst capacity = " << dst.capacity() << std::endl;
		std::cout << "dst size = " << dst.size() << std::endl;
		std::cout << "dst = src" << std::endl;
		dst = src;
		std::cout << "dst capacity = " << dst.capacity() << std::endl;
		std::cout << "dst size = " << dst.size() << std::endl;

		std::cout << "final dst = ";
		for (i = 0; i < dst.size(); i++)
		{
			if (dst[i] != src[i])
			{
				std::cout << "TEST KO : dst[" << i << "] = " << dst[i] << " != " << src[i] << std::endl;
				break ;
			}
			else
				std::cout << dst[i] << " ";
		}
		std::cout << std::endl << std::endl;
	}

/********************************* ITERATORS *********************************/

	/* ITERATORS
	** prints vector.begin(), end() and operators from a random access iterator
	** @param v : the vector to get the iterators from */
	template <typename Container>
	void	test_iterators(Container v)
	{
		typename Container::iterator	begin;
		typename Container::iterator	end;
		size_t							tmp;
		size_t							len;

		len = v.size();
		end = v.end();
		tmp = len;

		print(v, "v");

		std::cout << "TEST begin++" << std::endl;
		for (begin = v.begin(); begin != end; begin++)
			std::cout << *(begin) << " ";

		std::cout << std::endl << std::endl << "TEST begin = 1 + begin" << std::endl;
		for (begin = v.begin(); begin != end; begin = 1 + begin)
			std::cout << *(begin) << " ";

		std::cout << std::endl << std::endl << "TEST begin = begin + 1" << std::endl;
		for (begin = v.begin(); begin != end; begin = begin + 1)
			std::cout << *(begin) << " ";

		std::cout << std::endl << std::endl << "TEST begin += 1" << std::endl;
		for (begin = v.begin(); begin != end; begin += 1)
			std::cout << *(begin) << " ";

		std::cout << std::endl << std::endl << "TEST --begin" << std::endl;
		for (begin = end - 1; tmp--; --begin)
			std::cout << *(begin) << " ";

		tmp = len;
		std::cout << std::endl << std::endl << "TEST begin = begin - 1" << std::endl;
		for (begin = end - 1; tmp--; begin = begin - 1)
			std::cout << *(begin) <<  " ";

		tmp = len;
		std::cout << std::endl << std::endl << "TEST begin -= 1" << std::endl;
		for (begin = end - 1; tmp--; begin -= 1)
			std::cout << *(begin) << " ";

		std::cout << std::endl << std::endl << "TEST begin == begin" << std::endl;
		if (v.begin() == v.begin())
			std::cout << "TEST OK" << std::endl;
		else
			std::cout << "TEST KO" << std::endl;
		
		std::cout << std::endl << "TEST begin[i]" << std::endl;
		begin = v.begin();
		for (size_t i = 0; i < v.size(); i++)
		{
			if (begin[i] != v[i])
				std::cout << "TEST KO : begin[" << i << "] = " << begin[i] << " != " << v[i] << std::endl;
			else
				std::cout << "begin[" << i << "] = " << begin[i] << std::endl;
		}
		std::cout << std::endl;

		std::cout << std::endl << "TEST begin->val" << std::endl;
	}

	/* BIDIR REVERSE ITERATORS
	** prints bidirectional reverse iterator instanciations and operators
	** @param container : the container to get the iterators from */
	template <typename Container>
	void	test_bidir_rev_iterators(Container container)
	{
		typedef typename Container::iterator	iterator;
		reverse_iterator<iterator>				rbegin(container.end());
		reverse_iterator<iterator>				rend(container.begin());
		reverse_iterator<iterator>				rtmp(rbegin);

		std::cout << "**init dereferencing and operator++" << std::endl;
		while (rtmp != rend)
		{
			std::cout << *rtmp << std::endl;
			rtmp++;
		}
		std::cout << std::endl;

		std::cout << "** operator--" << std::endl;
		while (rtmp != rbegin)
			std::cout << *(--rtmp) << std::endl;
		std::cout << std::endl;
}

	/* RANDOM REVERSE ITERATORS
	** same as bidir reverse iterators but with const reverse random access iterator */
	template <typename Container>
	void	test_random_rev_iterators(Container container)
	{
		typedef typename Container::const_reverse_iterator	rev_iterator;
		rev_iterator										rbegin(container.rbegin());
		rev_iterator										rend(container.rend());
		rev_iterator										rtmp(rbegin);

		test_bidir_rev_iterators(container);
		std::cout << "** operator+=" << std::endl;
		while (rtmp != rend)
		{
			std::cout << *rtmp << std::endl;
			rtmp += 1;
		}

		std::cout << std::endl << "** operator-=" << std::endl;
		while (rtmp != rbegin)
		{
			rtmp -= 1;
			std::cout << *rtmp << std::endl;
		}

		std::cout << std::endl << "** operator+" << std::endl;
		std::cout << "*(rtmp + 1) = " << *(rtmp + 1) << std::endl;
		std::cout << "*(1 + rtmp) = " << *(1 + rtmp) << std::endl;

		std::cout << std::endl << "** operator-" << std::endl;
		rtmp++;
		std::cout << "*(rtmp - 1) = " << *(rtmp - 1) << std::endl;
		rtmp--;

		std::cout << std::endl << "rbegin - rend = " << rbegin - rend << std::endl;
		std::cout << "rend - rbegin = " << rend - rbegin << std::endl << std::endl;
	}

/************************ CAPACITY **************************/

	/* RESIZE
	** prints all elems, capcity and size
	** can throw bad_alloc and length_error exceptions */
	template <typename T>
	void	test_resize(vector<T> v, size_t n)
	{
		print(v, "v");
		std::cout << "capacity = " << v.capacity() << ", size = " << v.size() << std::endl;
		std::cout << "v.resize(" << n << ")" << std::endl;
		try {
			v.resize(n);
			print(v, "v");
			std::cout << "capacity = " << v.capacity() << ", size = " << v.size() << std::endl;
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
		std::cout << std::endl;
	}

/************************ ACCESSORS **************************/
	/* AT
	** prints elem at pos
	** can throw out of range exception */
	template <typename T>
	void	test_at(vector<T> v, size_t pos)
	{
		try
		{
			std::cout << "v.at(" << pos << ") = " << v.at(pos);
		}
		catch (std::exception &e)
		{
			std::cout << "vector::_M_range_check";
		}
		std::cout << std::endl;
	}

	/* FRONT AND BACK
	** prints front and back elems */
	template <typename T>
	void	test_front_back(vector<T> v)
	{
		print(v, "v");
		std::cout << "front = " << v.front() << ", ";
		std::cout << "back = " << v.back() << std::endl << std::endl;
	}

/************************ MODIFIERS **************************/

	/* ASSIGN : assign elements from a range
	** prints all vector elems, its new size and capacity
	** can throw bad alloc exception if a reallocation happened */
	template <typename InputIterator>
	void	test_assign(vector<int> v, InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL)
	{
		InputIterator	ite;

		std::cout << "range = ";
		ite = first;
		while (ite != last)
			std::cout << *ite++ << " ";
		std::cout << std::endl;
		std::cout << "old capacity = " << v.capacity() << ", ";
		std::cout << "old size = " << v.size() << std::endl;
		std::cout << "v.assign(first, last)" << std::endl;
		try
		{
			v.assign(first, last);
			print(v, "v");
			std::cout << "new capacity = " << v.capacity() << ", ";
			std::cout << "new size = " << v.size() << std::endl << std::endl;
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	/* ASSIGN : same as before but assign n elements with value val instead of a range */
	template <typename T>
	void	test_assign(vector<T> &v, size_t n, const T& val)
	{
		std::cout << "old capacity = " << v.capacity() << ", ";
		std::cout << "old size = " << v.size() << std::endl;
		std::cout << "v.assign(" << n << ", " << val << ")" << std::endl;
		try
		{
			v.assign(n, val);
			print(v, "v");
			std::cout << "new capacity = " << v.capacity() << ", ";
			std::cout << "new size = " << v.size() << std::endl << std::endl;
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	/* PUSH BACK : adds elem at end of vector
	** prints the vector, its new size and capacity */
	template <typename T>
	void	test_push_back(vector<T> &v, const T& val)
	{
		print(v, "v");
		std::cout << "old capacity = " << v.capacity() << ", ";
		std::cout << "old size = " << v.size() << std::endl;
		try
		{
			v.push_back(val);
			print(v, "v");
			std::cout << "new capacity = " << v.capacity() << ", ";
			std::cout << "new size = " << v.size() << std::endl << std::endl;
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	/* POP BACK : destroys last elem in vector
	** prints the vector, its new size and capacity */
	template <typename T>
	void	test_pop_back(vector<T> &v)
	{
		print(v, "v");
		std::cout << "old capacity = " << v.capacity() << ", ";
		std::cout << "old size = " << v.size() << std::endl;
		v.pop_back();
		print(v, "v");
		std::cout << "new capacity = " << v.capacity() << ", ";
		std::cout << "new size = " << v.size() << std::endl << std::endl;
	}

	/* INSERT (position, val) : inserts single elem before position position
	** prints the vector, its new size and capacity and the elems in vector starting from
	** the iterator returned by insert */
	template <typename T>
	void	test_insert(vector<T> &v, typename vector<T>::iterator position, const T& val)
	{
		typename vector<T>::iterator	tmp;

		print(v, "v");
		std::cout << "old capacity = " << v.capacity() << ", ";
		std::cout << "old size = " << v.size() << std::endl;
		std::cout << "v.insert(pos " << position - v.begin() << ", " << val << ")" << std::endl;
		tmp = v.insert(position, val);
		print(v, "v");
		std::cout << "v starting from iterator returned by insert : ";
		while (tmp != v.end())
			std::cout << *tmp++ << " ";
		std::cout << std::endl << "new capacity = " << v.capacity() << ", ";
		std::cout << "new size = " << v.size() << std::endl;
		std::cout << std::endl;
	}

	/* INSERT (position, n, val) : inserts n elems before position postion */
	template <typename T>
	void	test_insert(vector<T> &v, typename vector<T>::iterator position, size_t n, const T& val)
	{
		print(v, "v");
		std::cout << "old capacity = " << v.capacity() << ", ";
		std::cout << "old size = " << v.size() << std::endl;
		std::cout << "v.insert(pos " << position - v.begin();
		std::cout << ", " << n << ", " << val << ")" << std::endl;
		v.insert(position, n, val);
		print(v, "v");
		std::cout << "new capacity = " << v.capacity() << ", ";
		std::cout << "new size = " << v.size() << std::endl;
		std::cout << std::endl;
	}

	/* INSERT (position, first, last) : inserts range from first to last before position position */
	template <typename T, typename InputIterator>
	void	test_insert(vector<T> &v, typename vector<T>::iterator position,
				InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL)
	{
		InputIterator	ite;

		print(v, "v");
		std::cout << "old capacity = " << v.capacity() << ", ";
		std::cout << "old size = " << v.size() << std::endl;
		std::cout << "range = ";
		for (ite = first; ite != last; ite++)
			std::cout << *ite << " ";
		std::cout << std::endl;

		std::cout << "v.insert(pos " << position - v.begin() << ", " << ft::distance(first, last) << ")" << std::endl;
		v.insert(position, first, last);
		print(v, "v");
		std::cout << "new capacity = " << v.capacity() << ", ";
		std::cout << "new size = " << v.size() << std::endl;
		std::cout << std::endl;
	}

	/* ERASE (position) : erase elem at position position
	** prints vector, its new capacity and size */
	template <typename T>
	void	test_erase(vector<T> v, size_t index)
	{
		print(v, "v");
		std::cout << "old capacity = " << v.capacity() << ", ";
		std::cout << "old size = " << v.size() << std::endl;
		std::cout << "v.erase(" << index << ")" << std::endl;
		v.erase(v.begin() + index);
		print(v, "v");
		std::cout << "new capacity = " << v.capacity() << ", ";
		std::cout << "new size = " << v.size() << std::endl << std::endl;
	}

	/* ERASE (first, last) : erase range of elems from first to last
	** prints vector, its new capacity and size */
	template <typename T>
	void	test_erase(vector<T> v, size_t start, size_t end)
	{
		print(v, "v");
		std::cout << "old capacity = " << v.capacity() << ", ";
		std::cout << "old size = " << v.size() << std::endl;
		std::cout << "v.erase(" << start << "-" << end << ")" << std::endl;
		v.erase(v.begin() + start, v.begin() + end);
		print(v, "v");
		std::cout << "new capacity = " << v.capacity() << ", ";
		std::cout << "new size = " << v.size() << std::endl << std::endl;
	}

	/* SWAP : swap contents of two vectors
	** prints the two vectors, their new cap and size */
	template <typename T>
	void	test_swap(vector<T> v1, vector<T> v2)
	{
		print(v1, "v1");
		std::cout << "v1 old capacity = " << v1.capacity() << ", ";
		std::cout << "v1 old size = " << v1.size() << std::endl;
		print(v2, "v2");
		std::cout << "v2 old capacity = " << v2.capacity() << ", ";
		std::cout << "v2 old size = " << v2.size() << std::endl;
	
		std::cout << std::endl << "v1.swap(v2)" << std::endl;
		v1.swap(v2);
		print(v1, "v1");
		std::cout << "v1 new capacity = " << v1.capacity() << ", ";
		std::cout << "v1 new size = " << v1.size() << std::endl;
		print(v2, "v2");
		std::cout << "v2 new capacity = " << v2.capacity() << ", ";
		std::cout << "v2 new size = " << v2.size() << std::endl << std::endl;
	}

/************************ NON MEMBER **************************/
	/* OPERATORS : prints v1 and v2 and the result of comparing the containers */
	template <typename T>
	void	test_operators(vector<T> v1, vector<T> v2)
	{
		print(v1, "v1");
		print(v2, "v2");
		std::cout << "v1 == v2 ? " << (v1 == v2) << std::endl;
		std::cout << "v1 != v2 ? " << (v1 != v2) << std::endl;
		std::cout << "v1 < v2 ? " << (v1 < v2) << std::endl;
		std::cout << "v1 <= v2 ? " << (v1 <= v2) << std::endl;
		std::cout << "v1 > v2 ? " << (v1 > v2) << std::endl;
		std::cout << "v1 >= v2 ? " << (v1 >= v2) << std::endl << std::endl;
	}

	/* SWAP : swaps elems from v1 and v2
	** prints v1 and v2, their new cap and new size*/
	template <typename T>
	void	test_swap_non_member(vector<T> v1, vector<T> v2)
	{
		print(v1, "v1");
		std::cout << "old cap = " << v1.capacity() << ", old size = " << v1.size() << std::endl;
		print(v2, "v2");
		std::cout << "old cap = " << v2.capacity() << ", old size = " << v2.size() << std::endl;
		std::cout << "swap(v1, v2)" << std::endl;
		swap(v1, v2);
		print(v1, "v1");
		std::cout << "new cap = " << v1.capacity() << ", new size = " << v1.size() << std::endl;
		print(v2, "v2");
		std::cout << "new cap = " << v2.capacity() << ", new size = " << v2.size() << std::endl;
		std::cout << std::endl;
	}

#endif
