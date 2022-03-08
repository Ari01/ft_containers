/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 10:19:30 by dchheang          #+#    #+#             */
/*   Updated: 2022/03/08 21:27:31 by dchheang         ###   ########.fr       */
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

	std::cout << std::endl << "** FAILING CONSTRUCS TESTS" << std::endl;
	std::size_t n = -1;
	test_size_construct<int>(n);
	n = 2147483647;
	test_size_construct<int>(n);

	std::cout << "** OK CONSTRUCTS TESTS" << std::endl;
	n = 0;
	test_size_construct<int>(n);
	n = 150;
	test_size_construct<int>(n);

	std::cout << "***********RANGE CONSTRUCT TESTS*************" << std::endl;
	std::cout << std::endl << "** LIST TEST" << std::endl;
	std::list<int> l(10);
	test_range_construct<int, std::list<int>::iterator>(l.begin(), l.end());

	std::cout << std::endl << "** VECTOR TEST" << std::endl;
	vector<std::string> vs(10);
	test_range_construct<std::string, vector<std::string>::iterator>(vs.begin(), vs.end());
	
	std::string	stmp;
	stmp = "hw";
	for (size_t i = 0; i < vs.size(); i++)
		vs[i] = stmp + static_cast<char>(i + '0');
	test_range_construct<std::string, vector<std::string>::iterator>(vs.begin(), vs.end());

	std::cout << std::endl << "** POINTER TEST" << std::endl;
	int *a = new int[10];
	vector<int> v(10);
	test_range_construct<int, int *>(a, a + 10);

	for (int i = 0; i < 10; i++)
		a[i] = i;
	test_range_construct<int, int *>(a, a + 10);

	std::cout << "*********** COPY TESTS*************" << std::endl;

	std::cout << std::endl << "** Int tests" << std::endl;
	// FILLED WITH 0
	vector<int> v1(10);
	test_copy_construct(v1);

	// FILLED WITH i from 0 to 10
	for (size_t i = 0; i < v1.size(); i++)
		v1[i] = i;
	test_copy_construct(v1);

	std::cout << std::endl << "** String tests" << std::endl;
	// EMPTY STRINGS
	vector<std::string> vss(10);
	test_copy_construct(vss);

	// STRINGS WITH HW + i
	test_copy_construct(vs);

	std::cout << "*********** ITERATOR TESTS*************" << std::endl;

	// v filled with ints from 0 to 10
	vector<int> v2(10);
	std::cout << "v = ";
	for (int i = 0; i < 10; i++)
	{
		v2[i] = i;
		std::cout << v2[i] << " ";
	}
	std::cout << std::endl;
	test_iterators(v2);

	// v filled with strings hw + i
	std::cout << "v = ";
	for (int i = 0; i < 10; i++)
	{
		vs[i] = stmp + static_cast<char>(i + '0');
		std::cout << vs[i] << " ";
	}
	std::cout << std::endl;
	test_iterators(vs);

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
