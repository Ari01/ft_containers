/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapTest.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:26:18 by dchheang          #+#    #+#             */
/*   Updated: 2022/03/23 17:11:54 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPTEST
#define MAPTEST

class MapTest
{
	public:
		virtual ~MapTest() = 0;

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
		static void	run();
};

#endif
