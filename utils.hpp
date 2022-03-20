/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:22:56 by dchheang          #+#    #+#             */
/*   Updated: 2022/03/19 17:57:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft
{

	/* ENABLE IF
	** has a public member typedef type equal to T if B is true
	** otherwhise there is no member typedef */

	template<bool B, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> { typedef T type; };

	/* INTEGRAL CONSTANT
	** base type to derive is integral from */
	template<class T, T v>
	struct	integral_constant
	{
		typedef T							value_type;
		typedef integral_constant<T,v>		type;
		static const T						value = v;
		const value_type operator()() const	{ return (v); }
	};

	// bool specialization
	typedef integral_constant<bool, true>	true_type;
	typedef integral_constant<bool, false>	false_type;


	/* IS INTEGRAL
	** checks whether T is an integral type (bool, char, char16_t, char_32t short, int, long, long long)
	** provides member constant value which is true or false depending on if T is an integral */

	template<class T>
	struct	is_integral : false_type  {};
	
	template<>
	struct	is_integral<bool> : public true_type {};

	template<>
	struct	is_integral<char> : public true_type {};

	/*template<>
	struct	is_integral<char16_t> : public true_type {};

	template<>
	struct	is_integral<char32_t> : public true_type {};*/

	template<>
	struct	is_integral<wchar_t> : public true_type {};

	template<>
	struct	is_integral<signed char> : public true_type {};

	template<>
	struct	is_integral<short> : public true_type {};

	template<>
	struct	is_integral<int> : public true_type {};

	template<>
	struct	is_integral<long> : public true_type {};

	template<>
	struct	is_integral<long long> : public true_type {};

	template<>
	struct	is_integral<unsigned char> : public true_type {};

	template<>
	struct	is_integral<unsigned short> : public true_type {};

	template<>
	struct	is_integral<unsigned int> : public true_type {};

	template<>
	struct	is_integral<unsigned long> : public true_type {};

	template<>
	struct	is_integral<unsigned long long> : public true_type {};
}

#endif
