/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 10:19:30 by dchheang          #+#    #+#             */
/*   Updated: 2022/03/22 18:26:18 by dchheang         ###   ########.fr       */
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
	std::cout << "***********DEFAULT CONSTRUCT TESTS*************" << std::endl;
	vector<int> empty_vector;

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
	std::cout << "_____________________________" << std::endl;
	// list filled with 0
	std::list<int> l;
	for (int i = 0; i < 10; i++)
		l.push_back(i);
	test_range_construct<int, std::list<int>::iterator>(l.begin(), l.end());

	std::cout << std::endl << "** VECTOR TEST" << std::endl;
	std::cout << "_____________________________" << std::endl;
	// empty strings
	vector<std::string> vs(10);
	for (size_t i = 0; i < vs.size(); i++)
		vs[i] = "";
	test_range_construct<std::string, vector<std::string>::iterator>(vs.begin(), vs.end());
	std::cout << "after clear vs.capacity = " << vs.capacity() << std::endl;
	
	// hw + i strings
	std::string	stmp;
	stmp = "hw";
	for (size_t i = 0; i < vs.size(); i++)
		vs[i] = stmp + static_cast<char>(i + '0');
	test_range_construct<std::string, vector<std::string>::iterator>(vs.begin(), vs.end());
	test_range_construct<std::string, vector<std::string>::iterator>(vs.begin(), vs.begin());

	std::cout << std::endl << "** POINTER TEST" << std::endl;
	std::cout << "_____________________________" << std::endl;
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
	std::cout << "_____________________________" << std::endl;
	// FILLED WITH 0
	vector<int> v1(10);
	test_copy_construct(v1);

	// FILLED WITH i from 0 to 10
	for (size_t i = 0; i < v1.size(); i++)
		v1[i] = i;
	test_copy_construct(v1);

	std::cout << std::endl << "** String tests" << std::endl;
	std::cout << "_____________________________" << std::endl;
	// EMPTY STRINGS
	vector<std::string> vss(10);
	test_copy_construct(vss);

	// STRINGS WITH HW + i
	test_copy_construct(vs);

	/****************************** ITERATORS ****************************/

	const vector<int> cv(v1);

	std::cout << "*********** ITERATOR TESTS*************" << std::endl;
	// v filled with ints from 0 to 10
	test_iterators(v1);

	// v filled with strings hw + i
	test_iterators(vs);
	test_iterators(cv);

	/**************************** REV ITERATORS **************************/

	std::cout << "*********** REV ITERATOR TESTS*************" << std::endl;
	std::cout << "** LIST 0-9" << std::endl;
	test_bidir_rev_iterators(l);

	std::cout << "** VECTOR hw0-9" << std::endl;
	test_random_rev_iterators(vs);

	std::cout << "** VECTOR 0-9" << std::endl;
	test_random_rev_iterators(v1);

	std::cout << "** CONST VECTOR 0-9" << std::endl;
	test_random_rev_iterators(cv);

	/**************************** CAPACITY **************************/

	std::cout << "********** CAPACITY TESTS ******************" << std::endl;
	std::cout << "** MAX SIZE" << std::endl;
	std::cout << "_____________________________" << std::endl;
	std::cout << "vector int max size = " << v1.max_size() << std::endl;
	std::cout << "vector string max size = " << vs.max_size() << std::endl << std::endl;

	// RESIZE OK TESTS
	std::cout << "** RESIZE" << std::endl;
	std::cout << "_____________________________" << std::endl;
	test_resize(v1, 5);
	test_resize(v1, 10);
	test_resize(vs, 0);
	test_resize(vs, 12);
	test_resize(vs, 10);
	test_resize(vs, 20);
	test_resize(vs, 5);
	test_resize(vs, 0);

	// RESIZE THROWING EXCEPTION TESTS
	if (!SANITIZE)
	{
		test_resize(vs, -1);
		test_resize(vs, 2147483647);
	}

	// EMPTY TESTS
	std::cout << "** EMPTY" << std::endl;
	std::cout << "_____________________________" << std::endl;
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
	std::cout << std::endl;
	v1.resize(10);
	for (int i = 0; i < 10; i++)
		v1[i] = i;

	/****************************** ACCESSORS ****************************/

	std::cout << "************ ACCESSOR TESTS ************" << std::endl;
	std::cout << std::endl << "** AT" << std::endl;
	std::cout << "_____________________________" << std::endl;

	// OK TESTS
	test_at(v1, 0);
	test_at(v1, 9);

	// FAILING THROWING EXCEPTION TESTS
	if (!SANITIZE)
	{
		test_at(v1, 10);
		test_at(v1, 20);
		test_at(v1, 2147483647);
		test_at(v1, -1);
	}

	std::cout << std::endl << "** FRONT" << std::endl;
	std::cout << "_____________________________" << std::endl;
	test_front_back(cv);
	test_front_back(v1);
	test_front_back(vs);

	/****************************** MODIFIERS ****************************/
	std::cout << "********** MODIFIER TESTS ************" << std::endl;
	{
		vector<int>	vtmp;

		/** ASSIGN */
		std::cout << std::endl << "** ASSIGN RANGE" << std::endl;
		std::cout << "_____________________________" << std::endl;
		test_assign(vtmp, l.begin(), l.end());
		test_assign(vtmp, v1.begin(), v1.end());
		test_assign(vtmp, v1.begin(), v1.end() - 1);
		test_assign(vtmp, v1.begin(), v1.begin() + 1);
		test_assign(vtmp, v1.begin(), v1.begin());

		std::cout << "** ASSIGN VALUES" << std::endl; 
		std::cout << "_____________________________" << std::endl;
		// OK TESTS
		test_assign(vtmp, 10, 0);
		test_assign(vtmp, 20, 9);

		// EXCEPTION THROWING TESTS
		if (!SANITIZE)
		{
			test_assign(vtmp, 2147483647, 1);
			test_assign(vtmp, vtmp.max_size(), 1);
		}

		/** PUSH_BACK AND POP_BACK */
		std::cout << std::endl << "** PUSH_BACK, POP BACK" << std::endl;
		std::cout << "_____________________________" << std::endl;
		test_push_back(vtmp, 0);
		test_push_back(vtmp, 1);
		test_push_back(empty_vector, -1);
		test_pop_back(vtmp);
		test_pop_back(vtmp);
		test_pop_back(empty_vector);

		/** INSERT */
		std::cout << std::endl << "** INSERT SINGLE ELEM" << std::endl;
		std::cout << "_____________________________" << std::endl;
		vector<int> vtmp2;
		test_insert(vtmp2, vtmp2.begin(), -42);
		test_insert(vtmp2, vtmp2.end(), -42);
		test_insert(v1, v1.begin(), -42);
		test_insert(v1, v1.end() - 1, -42);
		test_insert(v1, v1.end(), -42);
		test_insert(v1, v1.begin() + 5, -42);
	}

	std::cout << "** INSERT N ELEMS" << std::endl;
	std::cout << "_____________________________" << std::endl;
	// empty vector
	{
		vector<int> vtmp;
		test_insert(vtmp, vtmp.begin(), 2, -1);
		test_insert(vtmp, vtmp.begin(), 10, -1);
		test_insert(vtmp, vtmp.begin(), 2, -1);

		// vector 0-9
		vector<int> v10(10);
		for (int i = 0; i < 10; i++)
			v10[i] = i;
		test_insert(v10, v10.begin(), 5, -1);
		test_insert(v10, v10.end(), 5, -1);
		test_insert(v10, v10.end(), 5, -1);
	}
	std::cout << "** INSERT RANGE" << std::endl;
	std::cout << "_____________________________" << std::endl;
	{
		vector<int>	vtmp;
		vector<int> v1(10);
		for (int i = 0; i < 10; i++)
			v1[i] = i;

		test_insert(vtmp, vtmp.begin(), v1.begin(), v1.end());
		vtmp.resize(0);
		test_insert(vtmp, vtmp.end(), v1.begin(), v1.end());
		test_insert(vtmp, vtmp.end(), l.begin(), l.end());
		test_insert(v1, v1.begin(), vtmp.begin(), vtmp.end());
		test_insert(v1, v1.end(), vtmp.begin(), vtmp.end());
		test_insert(v1, v1.begin() + 5, vtmp.begin(), vtmp.end());
	}

	{
		std::cout << "** ERASE SINGLE ELEM" << std::endl;
		std::cout << "_____________________________" << std::endl;
		vector<int> v1(10);
		for (int i = 0; i < 10; i++)
			v1[i] = i;
		test_erase(v1, 0);
		test_erase(v1, 5);
		test_erase(v1, 9);

		std::cout << "** ERASE RANGE" << std::endl;
		std::cout << "_____________________________" << std::endl;
		test_erase(v1, 0, 0);
		test_erase(v1, 0, 1);
		test_erase(v1, 9, 10);
		test_erase(v1, 0, 5);
		test_erase(v1, 5, 10);

		std::cout << "** SWAP" << std::endl;
		std::cout << "_____________________________" << std::endl;
		vector<int> v2(20);
		vector<int> v3(5);
		vector<int> v4(0);
	
		test_swap(v1, v2);
		test_swap(v2, v1);
		test_swap(v1, v3);
		test_swap(v1, v4);
		test_swap(v4, v1);
	}

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

	gettimeofday(&end, NULL);
	if (TIME)
		std::cout << "time : " << end.tv_usec - begin.tv_usec << "us" << std::endl;
	return 0;
}
