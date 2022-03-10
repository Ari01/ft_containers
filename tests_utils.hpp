/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_utils.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 16:21:46 by dchheang          #+#    #+#             */
/*   Updated: 2022/03/10 04:15:48 by dchheang         ###   ########.fr       */
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

// CONSTRUCTORS
template <typename T>
void	test_size_construct(int n)
{
	std::cout << "TEST vector(" << n << ")" << std::endl;
	try {
		vector<T> v(n);
		std::cout << "v.size = " << v.size() << ", v.capacity = " << v.capacity() << std::endl;
	} catch (std::bad_alloc e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << std::endl;
}

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

// ITERATORS
template <typename T>
void	test_iterators(vector<T> v)
{
	typename vector<T>::iterator	begin;
	typename vector<T>::iterator	end;
	size_t							tmp;
	size_t							len;

	len = v.size();
	end = v.end();
	tmp = len;
	std::cout << "TEST begin++" << std::endl;
	for (begin = v.begin(); begin != end; begin++)
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

	std::cout << std::endl << std::endl;
}

// OPERATORS
template <typename T>
void	test_affectation_operator(vector<T> src, vector<T> dst)
{
	std::cout << "src = ";
	for (size_t i = 0; i < src.size(); i++)
		std::cout << src[i] << " ";
	std::cout << std::endl;

	std::cout << "dst = ";
	for (size_t i = 0; i < dst.size(); i++)
		std::cout << dst[i] << " ";
	std::cout << std::endl;

	std::cout << "dst capacity = " << dst.capacity() << std::endl;
	std::cout << "dst size = " << dst.size() << std::endl;
	dst = src;
	std::cout << "dst capacity = " << dst.capacity() << std::endl;
	std::cout << "dst size = " << dst.size() << std::endl;

	for (size_t i = 0; i < dst.size(); i++)
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
