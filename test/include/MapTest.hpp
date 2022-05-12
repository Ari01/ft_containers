/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapTest.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:26:18 by dchheang          #+#    #+#             */
/*   Updated: 2022/05/12 08:47:06 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPTEST
#define MAPTEST

#include <list>

#if STD == 1
	namespace ns = std;
	#include <vector>
	#include <map>
#else
	namespace ns = ft;
	#include "vector.hpp"
	#include "map.hpp"
#endif

class MapTest
{
	private:
		ns::vector<ns::pair<std::string, int> >		empty_vector;
		ns::vector<ns::pair<std::string, int> >		v10;
		ns::map<std::string, int>					empty_map;
		ns::map<std::string, int>					m10;
		std::list<ns::pair<std::string, int> >		l;

	public:
		MapTest();
		~MapTest() {}

		// PAIR
		void	testPairConstructor();
		void	testPairAffectation();
		void	testOperators();

		// CONSTRUCTORS
		void	testConstructor();
		void	testAffect();

		// ITERATORS
		void	testIterator();

		// CAPACITY
		void	testEmpty();
		void	testSize();
		void	testMaxSize();

		// ACCESSORS
		void	testAccess();

		// MODIFIERS
		void	testInsert();
		void	testErase();
		void	testSwap();
		void	testClear();
		void	testKeyComp();
		void	testValueComp();

		// OPERATIONS
		void	testFind();
		void	testCount();
		void	testLowerBound();
		void	testUpperBound();
		void	testEqualRange();

		// RUN
		void	run();
};

#endif
