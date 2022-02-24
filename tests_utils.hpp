/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_utils.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 16:21:46 by dchheang          #+#    #+#             */
/*   Updated: 2022/02/24 17:29:45 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if STD == 1
	using namespace std;
#else
	using namespace ft;
#endif

template <typename T>
void	test_size_construct(std::size_t n)
{
	std::cout << "TEST vector(" << n << ")" << std::endl;
	try {
		vector<T> v(n);
		for (size_t i = 0; i < n; i++)
		{
			if (v[i])
				std::cout << "TEST KO, v[" << i << "] != " << n << std::endl;
			else if (DEBUG)
				std::cout << "v[" << i << "] = " << v[i] << std::endl; 
		}
		std::cout << std::endl;
	} catch (std::bad_alloc e) {
		std::cout << e.what() << std::endl;
	}
}

template <typename T>
void	test_size_construct(std::size_t n, T val)
{
	std::cout << "TEST vector(" << n << ", " << val << ")" << std::endl;
	try {
		vector<T> v(n, val);
		for (size_t i = 0; i < n; i++)
		{
			if (v[i] != val)
				std::cout << "TEST KO, v[" << i << "] = " << v[i] << " != " << val << std::endl;
			else if (DEBUG)
				std::cout << "v[" << i << "] = " << v[i] << std::endl; 
		}
		std::cout << std::endl;
	} catch (std::bad_alloc e) {
		std::cout << e.what() << std::endl;
	}
}

template <typename ite>
void	test_range_construct(ite begin, ite end)
{
	vector<int> v(begin, end);
}
