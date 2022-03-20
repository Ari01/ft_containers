/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_utils.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 16:21:46 by dchheang          #+#    #+#             */
/*   Updated: 2022/03/19 17:31:17 by user42           ###   ########.fr       */
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
void	print(vector<T> &v)
{
	std::cout << "vector : ";
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

		print(v);

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
		print(v);
		std::cout << "capacity = " << v.capacity() << ", size = " << v.size() << std::endl;
		std::cout << "v.resize(" << n << ")" << std::endl;
		try {
			v.resize(n);
			print(v);
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
		print(v);
		std::cout << "front = " << v.front() << ", ";
		std::cout << "back = " << v.back() << std::endl << std::endl;
	}

/************************ MODIFIERS **************************/

	/* ASSIGN : assign elements from a range
	** prints all vector elems, its new size and capacity
	** can throw bad alloc exception if a reallocation happened */
	template <typename InputIterator>
	void	test_assign(vector<int> &v, InputIterator first, InputIterator last,
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
			print(v);
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
			print(v);
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
		print(v);
		std::cout << "old capacity = " << v.capacity() << ", ";
		std::cout << "old size = " << v.size() << std::endl;
		try
		{
			v.push_back(val);
			print(v);
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
		print(v);
		std::cout << "old capacity = " << v.capacity() << ", ";
		std::cout << "old size = " << v.size() << std::endl;
		v.pop_back();
		print(v);
		std::cout << "new capacity = " << v.capacity() << ", ";
		std::cout << "new size = " << v.size() << std::endl << std::endl;
	}

	/* INSERT (position, val) : inserts single elem before position position
	** prints the vector, its new size and capacity */
	template <typename T>
	void	test_insert(vector<T> &v, typename vector<T>::iterator position, const T& val)
	{
		print(v);
		std::cout << "old capacity = " << v.capacity() << ", ";
		std::cout << "old size = " << v.size() << std::endl;
		v.insert(position, val);
		print(v);
		std::cout << "new capacity = " << v.capacity() << ", ";
		std::cout << "new size = " << v.size() << std::endl;
		std::cout << std::endl;
	}

/************************ OPERATORS **************************/

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

#endif
