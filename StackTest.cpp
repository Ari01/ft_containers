/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StackTest.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 15:50:59 by dchheang          #+#    #+#             */
/*   Updated: 2022/04/18 17:14:26 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "StackTest.hpp"

#if STD == 1
	using namespace std;
#else
	using namespace ft;
#endif

// INIT
StackTest::StackTest()
{
	int	tmp[10];

	for (int i = 0; i < 10; i++)
		tmp[i] = i;
	v10.insert(v10.begin(), &tmp[0], &tmp[10]);
	l10.insert(l10.begin(), &tmp[0], &tmp[10]);
	d10.insert(d10.begin(), &tmp[0], &tmp[10]);
}

// CONSTRUCTOR
void	StackTest::testConstructor()
{
	stack<int>	empty;
	stack<int, vector<int> >		vs(v10);
	stack<int, std::list<int> >		ls(l10);
	stack<int, std::deque<int> >	ds(d10);

	std::cout << "********* CONSTRUCTOR *********\n";

	printStack(empty, "empty");
	printStack(vs, "vector stack");
	printStack(ls, "list stack");
	printStack(ds, "deque stack");
	std::cout << std::endl;
}

void	StackTest::testPush()
{
	stack<int>						dflt;
	stack<int, vector<int> >		vs;
	stack<int, std::list<int> >		ls;
	stack<int, std::deque<int> >	ds;

	std::cout << "********* PUSH *********\n";

	for (int i = 0; i < 10; i++)
	{
		dflt.push(i);
		vs.push(i);
		ls.push(i);
		ds.push(i);
	}
	printStack(dflt, "dflt");
	printStack(vs, "vs");
	printStack(ls, "ls");
	printStack(ds, "ds");
	std::cout << std::endl;
}

void	StackTest::testOperators()
{
	stack<int>						dflt1;
	stack<int>						dflt2;
	stack<int, vector<int> >		vs1;
	stack<int, vector<int> >		vs2;
	stack<int, std::list<int> >		ls1;
	stack<int, std::list<int> >		ls2;
	stack<int, std::deque<int> >	ds1;
	stack<int, std::deque<int> >	ds2;

	std::cout << "********* OPERATORS *********\n";
	std::cout << "** EMPTY STACKS" << std::endl;
	std::cout << "-------------------" << std::endl;
	testOp(dflt1, dflt2);
	testOp(vs1, vs2);
	testOp(ls1, ls2);
	testOp(ds1, ds2);

	dflt1.push(0);
	dflt2.push(1);
	vs1.push(0);
	vs2.push(1);
	ls1.push(0);
	ls2.push(1);
	ds1.push(0);
	ds2.push(1);

	std::cout << "** SAME STACKS" << std::endl;
	std::cout << "-------------------" << std::endl;
	testOp(dflt1, dflt1);
	testOp(vs1, vs1);
	testOp(ls1, ls1);
	testOp(ds1, ds1);

	std::cout << "** STACK s1 < STACK s2" << std::endl;
	std::cout << "-------------------" << std::endl;
	testOp(dflt1, dflt2);
	testOp(vs1, vs2);
	testOp(ls1, ls2);
	testOp(ds1, ds2);
}

void	StackTest::run()
{
	testConstructor();
	testPush();
	testOperators();
}
