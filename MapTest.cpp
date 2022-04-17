/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapTest.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:35:35 by dchheang          #+#    #+#             */
/*   Updated: 2022/04/17 18:48:11 by dchheang         ###   ########.fr       */
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
	#include "map.hpp"
	#include "vector.hpp"
#endif

// PRINT MAP
template <typename T1, typename T2>
void	printMap(map<T1, T2> m, std::string name)
{
	typename map<T1, T2>::iterator	ite;

	std::cout << name << " : " << std::endl;
	std::cout << "size = " << m.size() << std::endl;
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
	std::cout << "********* CONSTRUCTORS *********" << std::endl;
	std::cout << "** DEFAULT" << std::endl;
	std::cout << "-------------------" << std::endl;
	map<std::string, int> empty;
	printMap(empty, "empty map");

	std::cout << "** RANGE" << std::endl;
	std::cout << "-------------------" << std::endl;
	map<std::string, int> range(v10.begin(), v10.end());
	printMap(range, "range from vector");

	map<std::string, int> range2(range.begin(), range.end());
	printMap(range2, "range from map");

	std::cout << "** COPY" << std::endl;
	std::cout << "-------------------" << std::endl;
	map<std::string, int> copy(range);
	printMap(copy, "copy from map");
}

void	MapTest::testAffect()
{
	map<std::string, int> dst;

	std::cout << "** OPERATOR=" << std::endl;
	std::cout << "-------------------" << std::endl;

	// empty map
	dst = empty_map;
	printMap(dst, "test = emptyMap");

	// m10
	dst = m10;
	printMap(dst, "test = m10");

	// other m10
	map<std::string, int>	src;
	std::string				stmp = "k";
	for (int i = 0; i < 10; i++)
	{
		src.insert(ns::make_pair(stmp, i));
		stmp[0]++;
	}
	dst = src;
	printMap(dst, "dst = other m10");
}

// ITERATORS
void	MapTest::testIterator()
{
	map<std::string, int> m(m10);

	std::cout << "********* REVERSE ITERATORS *********\n";
	ns::reverse_iterator<typename map<std::string, int>::iterator>	rbegin(m.end());
	ns::reverse_iterator<typename map<std::string, int>::iterator>	rend(m.begin());
	ns::reverse_iterator<typename map<std::string, int>::iterator>	rtmp(rbegin);

	std::cout << "** iterator++\n";
	std::cout << "-------------------" << std::endl;
	while (rtmp != rend)
	{
		std::cout << rtmp->first << std::endl;
		rtmp++;
	}
	
	std::cout << "\n** iterator--\n";
	std::cout << "-------------------" << std::endl;
	while (rtmp != rbegin)
	{
		--rtmp;
		std::cout << rtmp->first << std::endl;
	}
	std::cout << std::endl;
}

// CAPACITY
void	MapTest::testEmpty()
{
	std::cout << "********* CAPACITY *********" << std::endl;
	std::cout << "** EMPTY" << std::endl;
	std::cout << "-------------------" << std::endl;

	// empty
	map<std::string, int>	m;
	m.empty() ? std::cout << "TEST 1 OK\n" : std::cout << "TEST 2 KO\n";
	
	// single elem
	m.insert(make_pair("a", 0));
	m.empty() ? std::cout << "TEST 2 KO\n" : std::cout << "TEST 2 OK\n";

	// range
	m.insert(m10.begin(), m10.end());
	m.empty() ? std::cout << "TEST 2 KO\n" : std::cout << "TEST 2 OK\n\n";
}

void	MapTest::testMaxSize()
{
	map<std::string, int>	m;

	std::cout << "** MAX SIZE" << std::endl;
	std::cout << "-------------------" << std::endl;
	std::cout << "max size = " << m.max_size() << std::endl << std::endl;
}

// ACCESSORS
void	MapTest::testAccess()
{
	map<std::string, int>	m(m10);

	std::cout << "********* ELEMENT ACCESS *********" << std::endl;
	std::cout << "m[b] = " << m["b"] << std::endl;
	std::cout << "m[z] = " << m["z"] << std::endl;
	printMap(m, "abcdefghijz");
}

// MODIFIERS
void	MapTest::testInsert()
{
	typedef map<std::string, int>::iterator	iterator;
	map<std::string, int>					m;
	pair<iterator, bool>					p;
	iterator								ite;

	std::cout << "********* MODIFIERS *********" << std::endl;
	std::cout << "** INSERT" << std::endl;
	std::cout << "-------------------" << std::endl;

	// insert (s)
	std::cout << "insert (s, -1)" << std::endl;
	p = m.insert(pair<std::string, int>("s", -1));
	std::cout << (*p.first).first;
	p.second ? std::cout << " inserted\n" : std::cout << " already exists\n";

	// insert (s)
	std::cout << "\ninsert (s, 0)" << std::endl;
	p = m.insert(pair<std::string, int>("s", 0));
	std::cout << (*p.first).first;
	p.second ? std::cout << " inserted\n" : std::cout << " already exists\n";

	// insert (position, s)
	std::cout << "\ninsert (m.begin, pair(s, 5))" << std::endl;
	ite = m.insert(m.begin(), pair<std::string, int>("s", 5));
	ite->first == "s" ? std::cout << "TEST OK\n" : std::cout << "TEST KO\n";

	// insert (position, t)
	std::cout << "\ninsert (m.begin, pair(t, 0))" << std::endl;
	ite = m.insert(m.begin(), pair<std::string, int>("t", 0));
	ite->first == "t" ? std::cout << "TEST OK\n" : std::cout << "TEST KO\n";

	// insert (position, a)
	std::cout << "\ninsert (m.begin, pair(a, 0))" << std::endl;
	ite = m.insert(m.begin(), pair<std::string, int>("a", 0));
	ite->first == "a" ? std::cout << "TEST OK\n" : std::cout << "TEST KO\n";

	// insert (begin = a, end = j)
	std::cout << "\ninsert (m10.begin, m10.end)" << std::endl;
	m.insert(m10.begin(), m10.end());
	printMap(m, "abcdefghijst");
}

void	MapTest::testErase()
{
	std::cout << "** ERASE" << std::endl;
	std::cout << "-------------------" << std::endl;

	map<std::string, int>	m;

	// erase(key)
	std::cout << "empty map\n";
	std::cout << "erase(a) = " << m.erase("a") << std::endl;

	std::cout << "\nm = abcdefghij\n";
	m.insert(m10.begin(), m10.end());
	std::cout << "erase(z) = " << m.erase("z") << std::endl;
	std::cout << "erase(d) = " << m.erase("d") << std::endl;

	// erase(position)
	std::cout << "\nerase(m.begin)\n";
	m.erase(m.begin());
	printMap(m, "bcefghij");

	// erase(range)
	std::cout << "erase(m.begin, m.end)\n";
	m.erase(m.begin(), m.end());
	printMap(m, "empty");
}

void	MapTest::testSwap()
{	
	typedef typename map<std::string, int>::iterator	iterator;
	iterator											begin1, begin2, end1, end2;
	map<std::string, int>								m1(m10);
	map<std::string, int>								m2;
	std::string											stmp;

	std::cout << "** SWAP\n";
	std::cout << "-------------------" << std::endl;

	// init
	stmp = "k";
	for (int i = 0; i < 20; i++, stmp[0]++)
		m2.insert(ns::make_pair(stmp, i));
	printMap(m1, "m1");
	printMap(m2, "m2");
	begin1 = m1.begin();
	end1 = m1.end();
	begin2 = m2.begin();
	end2 = m2.end();

	// swap
	std::cout << "m1.swap(m2)\n";
	m1.swap(m2);
	
	// print
	printMap(m1, "m1");
	printMap(m2, "m2");
}

void	MapTest::testClear()
{
	map<std::string, int>	m(m10);
	map<std::string, int>	empty;

	std::cout << "** CLEAR\n";
	std::cout << "-------------------" << std::endl;

	empty.clear();
	printMap(empty, "empty");
	m.clear();
	printMap(m, "m10");
}

// OBSERVERS
void	MapTest::testKeyComp()
{
	map<std::string, int>					m(m10);
	map<std::string, int>::key_compare		comp = m.key_comp();
	std::string								end = m.rbegin()->first;
	map<std::string, int>::iterator			ite = m.begin();

	std::cout << "********* OBSERVERS *********" << std::endl;
	std::cout << "** key_compare()" << std::endl;
	std::cout << "-------------------" << std::endl;
	while (comp(ite->first, end))
	{
		std::cout << ite->first << std::endl;
		ite++;
	}
	std::cout << std::endl;
}

void	MapTest::testValueComp()
{
	map<std::string, int>					m(m10);
	map<std::string, int>::value_compare	comp = m.value_comp();
	pair<std::string, int>					end = *m.rbegin();
	map<std::string, int>::iterator			ite = m.begin();

	std::cout << "** value_compare()" << std::endl;
	std::cout << "-------------------" << std::endl;
	while (comp(*ite, end))
	{
		std::cout << ite->first << std::endl;
		ite++;
	}
	std::cout << std::endl;
}

// OPERATIONS
void	MapTest::testFind()
{
	map<std::string, int>::iterator	ite;

	std::cout << "********* OPERATIONS *********" << std::endl;
	std::cout << "** FIND\n";
	std::cout << "-------------------" << std::endl;

	std::cout << "empty.find(a) : ";
	ite = empty_map.find("a");
	ite == empty_map.end() ? std::cout << "TEST OK\n" : std::cout << "TEST KO\n";

	std::cout << "m10.find(z) : ";
	ite = m10.find("z");
	ite == m10.end() ? std::cout << "TEST OK\n" : std::cout << "TEST KO\n";

	std::cout << "m10.find(j) : ";
	ite = m10.find("j");
	std::cout << ite->first << " found" << std::endl;
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
	// MAP
	testConstructor();
	testAffect();
	testIterator();
	testEmpty();
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
