/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapTest.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:35:35 by dchheang          #+#    #+#             */
/*   Updated: 2022/03/25 15:45:54 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <iostream>
#include "iterator.hpp"
#include "MapTest.hpp"

#if STD == 1
	using namespace std;
	#include <map>
	#include <vector>
#else
	using namespace ft;
	#include "vector.hpp"
#endif

// PRINT MAP
template <typename T1, typename T2>
void	printMap(map<T1, T2> m, std::string name)
{
	typename map<T1, T2>::iterator	ite;

	std::cout << name << " : " << std::endl;
	for (ite = m.begin(); ite != m.end(); ite++)
		std::cout << "(" << ite->first << ", " << ite->second << ")" << std::endl;
	std::cout << std::endl;
}

// MAP TEST INIT
MapTest::MapTest()
{
	std::string	s = "a";

	for (int i = 0; i < 10; i++, s[0]++)
		v10.push_back(pair<std::string, int>(s, i));
	m10.insert(v10.begin(), v10.end());
}

// CONSTRUCTORS
void	MapTest::testConstructor()
{
	map<std::string, int> empty;
	printMap(empty, "empty map");

	map<std::string, int> range(v10.begin(), v10.end());
	printMap(range, "range from vector");

	map<std::string, int> range2(range.begin(), range.end());
	printMap(range2, "range from map");

	map<std::string, int> copy(range);
	printMap(copy, "copy from range");
}

void	MapTest::testAffect()
{

}

// ITERATORS
void	MapTest::testIterator()
{

}

// CAPACITY
void	MapTest::testEmpty()
{

}

void	MapTest::testSize()
{

}

void	MapTest::testMaxSize()
{

}

// ACCESSORS
void	MapTest::testAccess()
{

}

// MODIFIERS
void	MapTest::testInsert()
{

}

void	MapTest::testErase()
{

}

void	MapTest::testSwap()
{

}

void	MapTest::testClear()
{

}

void	MapTest::testKeyComp()
{

}

void	MapTest::testValueComp()
{

}

// OPERATIONS
void	MapTest::testFind()
{

}

void	MapTest::testCount()
{

}

void	MapTest::testLowerBound()
{

}

void	MapTest::testUpperBound()
{

}

void	MapTest::testEqualRange()
{

}

// RUN
void	MapTest::run() 
{
	testConstructor();
	testAffect();
	testIterator();
	testEmpty();
	testSize();
	testMaxSize();
	testAccess();
	testInsert();
	testErase();
	testSwap();
	testClear();
	testKeyComp();
	testValueComp();
	testFind();
	testCount();
	testLowerBound();
	testUpperBound();
	testEqualRange();
}
*/
