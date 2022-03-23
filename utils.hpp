/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:22:56 by dchheang          #+#    #+#             */
/*   Updated: 2022/03/23 14:52:15 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft
{

	/* ENABLE IF : has a public member typedef type equal to T if B is true
	** otherwhise there is no member typedef */

	template<bool B, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> { typedef T type; };

	/* INTEGRAL CONSTANT : base type to derive is integral from */
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


	/* IS INTEGRAL : checks whether T is an integral type
	** (bool, char, char16_t, char_32t short, int, long, long long)
	** provides member constant value which is true or false depending on if T is an integral */

	template<class T>	struct is_integral : false_type  {};
	template<>			struct is_integral<bool> : public true_type {};
	template<>			struct is_integral<char> : public true_type {};
	//template<>		struct is_integral<char16_t> : public true_type {};
	//template<>		struct is_integral<char32_t> : public true_type {};
	template<>			struct is_integral<wchar_t> : public true_type {};
	template<>			struct is_integral<signed char> : public true_type {};
	template<>			struct is_integral<short> : public true_type {};
	template<>			struct is_integral<int> : public true_type {};
	template<>			struct is_integral<long> : public true_type {};
	template<>			struct is_integral<long long> : public true_type {};
	template<>			struct is_integral<unsigned char> : public true_type {};
	template<>			struct is_integral<unsigned short> : public true_type {};
	template<>			struct is_integral<unsigned int> : public true_type {};
	template<>			struct is_integral<unsigned long> : public true_type {};
	template<>			struct is_integral<unsigned long long> : public true_type {};

	/* EQUAL (==) : Compares the elements in the range [first1,last1)
	** with those in the range beginning at first2, using ==
	** @return : true if all of the elements in both ranges match */
	template <class InputIterator1, class InputIterator2>
	bool	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}

	/* EQUAL (pred) : Compares the elements in the range [first1,last1)
	** with those in the range beginning at first2, using ==
	** @return : true if all of the elements in both ranges match */
	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool	equal(InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1 != last1)
		{
			if (!(pred(*first1, *first2)))
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}

	/* LEXICOGRAPHICAL_COMPARE (<)
	** @return true if the range [first1,last1) compares lexicographically less than the range [first2,last2)
	** @return false otherwhise */
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return (false);
			else if (*first1 < *first2)
				return (true);
			first1++;
			first2++;
		}
		return (first2 != last2);
	}

	/* LEXICOGRAPHICAL_COMPARE (comp) */
	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2, *first1))
				return (false);
			else if (comp(*first1, *first2))
				return (true);
			first1++;
			first2++;
		}
		return (first2 != last2);
	}
}

#endif
