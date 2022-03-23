/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapTest.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:35:35 by dchheang          #+#    #+#             */
/*   Updated: 2022/03/23 17:16:25 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <map>
#include "MapTest.hpp"
#include "iterator.hpp"
#include "vector.hpp"

#if STD == 1
	using namespace std;
#else
	using namespace ft;
#endif

// CONSTRUCTORS
void	MapTest::testConstructor()
{
	vector<int>	v(10);
	map<std::string, int> m;
	map<std::string, int> m(v.begin(), v.end());
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

