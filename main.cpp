/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 10:19:30 by dchheang          #+#    #+#             */
/*   Updated: 2022/03/24 15:59:29 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sys/time.h>
#include "VectorTest.hpp"
#include "MapTest.hpp"

#ifndef TIME
# define TIME 0
#endif

int main()
{
	struct timeval begin;
	struct timeval end;
	gettimeofday(&begin, NULL);

	//	VECTOR TESTS
	run_vector_tests();

	// MAP TESTS
	MapTest	maptest;
	maptest.run();

	gettimeofday(&end, NULL);
	if (TIME)
		std::cout << "time : " << end.tv_usec - begin.tv_usec << "us" << std::endl;
	return 0;
}
