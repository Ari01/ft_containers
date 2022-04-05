/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapTest.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:35:35 by dchheang          #+#    #+#             */
/*   Updated: 2022/04/05 15:18:34 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "iterator.hpp"
#include "MapTest.hpp"
#include "utils.hpp"

#if STD == 1
	using namespace std;
	namespace ns = std;
	#include <map>
	#include <vector>
#else
	using namespace ft;
	namespace ns = ft;
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

// PAIR TESTS
void	MapTest::testPairConstructor()
{
	std::cout << "** PAIR CONSTRUCTOR" << std::endl;
	pair <std::string,double> product1;                     // default constructor
	pair <std::string,double> product2 ("tomatoes", 2.30);   // value init
	pair <std::string,double> product3 (product2);          // copy constructor

	product1 = ns::make_pair(std::string("lightbulbs"), 0.99);
	product2.first = "shoes";                  // the type of first is string
	product2.second = 39.90;                   // the type of second is double

	std::cout << "The price of " << product1.first << " is $" << product1.second << '\n';
	std::cout << "The price of " << product2.first << " is $" << product2.second << '\n';
	std::cout << "The price of " << product3.first << " is $" << product3.second << '\n';
	std::cout << "--------------------------------" << std::endl;
}

void	MapTest::testPairAffectation()
{
	pair <std::string,int> planet, homeplanet;

	std::cout << "** PAIR AFFECTATION" << std::endl;
	planet = ns::make_pair("Earth",6371);
	homeplanet = planet;
	std::cout << "Home planet: " << homeplanet.first << '\n';
	std::cout << "Planet size: " << homeplanet.second << '\n';
	std::cout << "--------------------------------" << std::endl;
}

void	MapTest::testOperators()
{
	pair<int,char> foo (10,'z');
	pair<int,char> bar (90,'a');

	std::cout << "** PAIR OPERATORS" << std::endl;
	std::cout << "foo = (10, 'z'), bar = (90, 'a')" <<  std::endl;
	if (foo==bar) std::cout << "foo and bar are equal\n";
	if (foo!=bar) std::cout << "foo and bar are not equal\n";
	if (foo< bar) std::cout << "foo is less than bar\n";
	if (foo> bar) std::cout << "foo is greater than bar\n";
	if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
	if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
	std::cout << std::endl;

	bar.first = 10;
	std::cout << "foo = (10, 'z'), bar = (10, 'a')" <<  std::endl;
	if (foo==bar) std::cout << "foo and bar are equal\n";
	if (foo!=bar) std::cout << "foo and bar are not equal\n";
	if (foo< bar) std::cout << "foo is less than bar\n";
	if (foo> bar) std::cout << "foo is greater than bar\n";
	if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
	if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
	std::cout << "--------------------------------" << std::endl;
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
	// PAIR
	testPairConstructor();
	testPairAffectation();
	testOperators();

	// MAP
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
