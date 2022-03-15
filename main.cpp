/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 10:19:30 by dchheang          #+#    #+#             */
/*   Updated: 2022/03/15 09:50:14 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <list>
#include <sys/time.h>
#include "tests_utils.hpp"

#if STD == 1
	using namespace std;
#else
	using namespace ft;
#endif

#ifndef TIME
# define TIME 0
#endif

#ifndef SANITIZE
# define SANITIZE 0
#endif

int main()
{
	struct timeval begin;
	struct timeval end;
	gettimeofday(&begin, NULL);

	/****************************** CONSTRUCTORS ****************************/

	std::cout << "***********SIZE CONSTRUCT TESTS*************" << std::endl;

	if (!SANITIZE)
	{
		std::cout << std::endl << "** FAILING CONSTRUCT TESTS" << std::endl;
		test_size_construct<int>(-1);
		test_size_construct<int>(2147483647);
	}

	std::cout << "** OK CONSTRUCT TESTS" << std::endl;
	test_size_construct<int>(0);
	test_size_construct<int>(150);

	std::cout << "***********RANGE CONSTRUCT TESTS*************" << std::endl;

	std::cout << std::endl << "** LIST TEST" << std::endl;
	// list filled with 0
	std::list<int> l;
	for (int i = 0; i < 10; i++)
		l.push_back(i);
	test_range_construct<int, std::list<int>::iterator>(l.begin(), l.end());

	std::cout << std::endl << "** VECTOR TEST" << std::endl;
	// empty strings
	vector<std::string> vs(10);
	for (size_t i = 0; i < vs.size(); i++)
		vs[i] = "";
	test_range_construct<std::string, vector<std::string>::iterator>(vs.begin(), vs.end());
	
	// hw + i strings
	std::string	stmp;
	stmp = "hw";
	for (size_t i = 0; i < vs.size(); i++)
		vs[i] = stmp + static_cast<char>(i + '0');
	test_range_construct<std::string, vector<std::string>::iterator>(vs.begin(), vs.end());
	test_range_construct<std::string, vector<std::string>::iterator>(vs.begin(), vs.begin());

	std::cout << std::endl << "** POINTER TEST" << std::endl;
	// filled with 0
	int *a = new int[10];
	for (int i = 0; i < 10; i++)
		a[i] = 0;
	test_range_construct<int, int *>(a, a + 10);

	// filled with i = 0-9
	for (int i = 0; i < 10; i++)
		a[i] = i;
	test_range_construct<int, int *>(a, a + 10);

	std::cout << std::endl << "** NULL ITERATORS" << std::endl;
	test_range_construct<int, int *>(NULL, NULL);
	// undefined behaviour test_range_construct<int, int *>(NULL, a + 9);
	// undefined behaviour test_range_construct<int, int *>(a, NULL);
	delete [] a;

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

	/****************************** ITERATORS ****************************/

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

	/**************************** REV ITERATORS **************************/
	std::cout << "*********** REV ITERATOR TESTS*************" << std::endl;
	std::cout << "** LIST 0-9" << std::endl;
	test_bidir_rev_iterators(l);

/*	std::cout << "** VECTOR hw0-9" << std::endl;
	test_random_rev_iterators(vs);*/

	std::cout << "** VECTOR 0-9" << std::endl;
	test_random_rev_iterators(v1);

	/**************************** CAPACITY **************************/

	std::cout << "********** CAPACITY TESTS ******************" << std::endl;
	std::cout << "** MAX SIZE" << std::endl;
	std::cout << "vector int max size = " << v1.max_size() << std::endl;
	std::cout << "vector string max size = " << vs.max_size() << std::endl << std::endl;

	std::cout << "** RESIZE" << std::endl;
	test_resize(v1, 5);
	test_resize(v1, 10);
	test_resize(v1, 0);
	test_resize(vs, 12);
	test_resize(vs, 10);
	test_resize(vs, 20);
	test_resize(vs, 5);
	test_resize(vs, 0);
	test_resize(vs, -1);
	//test_resize(vs, 2147483647);

	std::cout << "** EMPTY" << std::endl;
	v1.resize(0);
	if (!v1.empty())
		std::cout << "TEST KO : vector should be empty" << std::endl;
	else
		std::cout << "TEST OK" << std::endl;
	v1.resize(1);
	if (v1.empty())
		std::cout << "TEST KO : vector should not be empty";
	else
		std::cout << "TEST OK" << std::endl;

	/****************************** OPERATORS ****************************/

	std::cout << "*********** OPERATOR TESTS*************" << std::endl;
	std::cout << "** OPERATOR =" << std::endl;
	vector<int> test1(5);
	for (int i = 0; i < 5; i++)
		test1[i] = 5;

	vector<int> test2(20);
	for (int i = 0; i < 20; i++)
		test2[i] = 20;

	vector<int> test3(10);
	for (int i = 0; i < 10; i++)
		test3[i] = 10;

	test_affectation_operator(test1, test3);
	test_affectation_operator(test1, test2);
	test_affectation_operator(test1, test1);

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

	gettimeofday(&end, NULL);
	if (TIME)
		std::cout << "time : " << end.tv_usec - begin.tv_usec << "us" << std::endl;
	return 0;
}
