/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 10:19:30 by dchheang          #+#    #+#             */
/*   Updated: 2022/03/28 16:30:49 by dchheang         ###   ########.fr       */
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

	std::cout << "**********************" << std::endl;
	std::cout << "**** VECTOR TESTS ****" << std::endl;
	std::cout << "**********************" << std::endl << std::endl;
	run_vector_tests();

	std::cout << "**********************" << std::endl;
	std::cout << "***** MAP TESTS ******" << std::endl;
	std::cout << "**********************" << std::endl << std::endl;
	MapTest	maptest;
	maptest.run();

	gettimeofday(&end, NULL);
	if (TIME)
		std::cout << "time : " << end.tv_usec - begin.tv_usec << "us" << std::endl;
	return 0;
}
