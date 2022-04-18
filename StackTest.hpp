/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StackTest.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 15:41:32 by dchheang          #+#    #+#             */
/*   Updated: 2022/04/18 17:08:21 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACKTEST_HPP
#define STACKTEST_HPP

#include <deque>
#include <list>

#if STD == 1
	#include <vector>
	#include <stack>
	namespace ns = std;
#else
	#include "vector.hpp"
	#include "stack.hpp"
	namespace ns = ft;
#endif

class StackTest
{
	private:
		ns::vector<int>		v10;
		std::list<int>		l10;
		std::deque<int>		d10;

		template <typename T, typename Container>
		void	printStack(ns::stack<T, Container> s, std::string name)
		{
			std::cout << name << "(" << s.size() << ") : ";
			while (!s.empty())
			{
				std::cout << s.top() << " ";
				s.pop();
			}
			std::cout << std::endl;
		}

		template <typename T, typename Container>
		void	testOp(ns::stack<T, Container> s1, ns::stack<T, Container> s2)
		{
			std::cout << "s1 == s2 ? ";
			s1 == s2 ? std::cout << "1\n" : std::cout << "0\n";
			std::cout << "s1 != s2 ? ";
			s1 != s2 ? std::cout << "1\n" : std::cout << "0\n";
			std::cout << "s1 < s2 ? ";
			s1 < s2 ? std::cout << "1\n" : std::cout << "0\n";
			std::cout << "s1 <= s2 ? ";
			s1 <= s2 ? std::cout << "1\n" : std::cout << "0\n";
			std::cout << "s1 > s2 ? ";
			s1 > s2 ? std::cout << "1\n" : std::cout << "0\n";
			std::cout << "s1 >= s2 ? ";
			s1 >= s2 ? std::cout << "1\n" : std::cout << "0\n";
			std::cout << std::endl;
		}

	public:
		StackTest();
		~StackTest() {}

		// CONSTRUCTOR
		void	testConstructor();

		// CAPACITY
		void	testEmpty();
		void	testSize();
		
		// ACCESSORS
		void	testTop();

		// MODIFIERS
		void	testPush();
		void	testPop();

		// OPERATORS
		void	testOperators();

		void	run();
};

#endif
