/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 10:19:30 by dchheang          #+#    #+#             */
/*   Updated: 2022/03/07 11:54:21 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <list>
#include "vector.hpp"
#include "tests_utils.hpp"

#if STD == 1
	using namespace std;
#else
	using namespace ft;
#endif

int main()
{
	std::cout << "***********SIZE CONSTRUCT TESTS*************" << std::endl;
	std::cout << "FAILING CONSTRUCS TESTS" << std::endl;
	std::size_t n = -1;
	test_size_construct<int>(n);
	test_size_construct<int>(n, 10);
	test_size_construct<int>(n, -1);

	std::cout << std::endl << "OK CONSTRUCTS TESTS" << std::endl;
	n = 0;
	test_size_construct<int>(n, 0);
	test_size_construct<int>(n, 5);
	n = 10;
	test_size_construct<int>(n, -1);
	test_size_construct<int>(n);
	test_size_construct<int>(n, 0);
	test_size_construct<int>(n, -2147483648);
	test_size_construct<int>(n, 2147483647);
	std::cout << std::endl;

	std::cout << std::endl << "STRING TESTS" << std::endl;
	std::string s = "";
	test_size_construct<std::string>(n, s);
	s = "hello world!";
	test_size_construct<std::string>(n, s);

	std::cout << "***********RANGE CONSTRUCT TESTS*************" << std::endl;
	std::vector<int> l(10, 1);
	std::cout << l.end() - 1 - l.begin() << std::endl;

	std::cout << "*********** ITERATOR TESTS*************" << std::endl;
	vector<int> v(10);
	std::cout << "v = ";
	for (int i = 0; i < 10; i++)
	{
		v[i] = i;
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;
	test_iterators(v);
/*	std::list<int> l(10, 0);
	std::list<int>::iterator begin;
	std::list<int>::iterator end;

	test_range_construct(begin, end);*/


/*	int *a = new int(1);
	std::vector<int *> v1;
	v1.push_back(a);
	std::vector<int *> v2(1);
	v2[0] = a;
	std::cout << *v2[0] << std::endl;
	delete(a);
	v1.clear();
	std::cout << *v2[0] << std::endl;
	std::cout << v2.size() << std::endl;
	std::vector<char> myvector;
	char c = 'a';

	std::cout << "capacity = " << myvector.capacity() << std::endl;
	std::cout << "size = " << myvector.size() << std::endl;
	std::cout << "add char" << std::endl;
	myvector.push_back(c);
	std::cout << "capacity = " << myvector.capacity() << std::endl;
	std::cout << "size = " << myvector.size() << std::endl;

	for (int i = ' '; i < '~'; i++)
	{
		myvector.insert(myvector.end(), i);
		std::cout << "capacity = " << myvector.capacity() << std::endl;
		std::cout << "size = " << myvector.size() << std::endl;
	}
	for (size_t i = 0; i < myvector.size(); i++)
	{
		myvector.pop_back();
		std::cout << "capacity = " << myvector.capacity() << std::endl;
		std::cout << "size = " << myvector.size() << std::endl;

	}*/

  return 0;
}
