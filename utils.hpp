/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 13:11:45 by adidion           #+#    #+#             */
/*   Updated: 2022/03/25 14:42:40 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

#include <type_traits>

namespace ft
{
	template <bool, typename T = void>
	struct enable_if {};

	template <typename T>
	struct enable_if<true, T> { typedef T type; };

	typedef	std::integral_constant<bool, true> true_type;
	typedef std::integral_constant<bool, false> false_type;
	template <class T> struct is_integral : public false_type {};
	template <class T> struct is_integral<const T> : public is_integral<T> {};
	template <class T> struct is_integral<volatile const T> : public is_integral<T>{};
	template <class T> struct is_integral<volatile T> : public is_integral<T>{};
	template<> struct is_integral<unsigned char> : public true_type {};
	template<> struct is_integral<unsigned short> : public true_type{};
	template<> struct is_integral<unsigned int> : public true_type{};
	template<> struct is_integral<unsigned long> : public true_type{};
	template<> struct is_integral<unsigned long long> : public true_type{};
	
	template<> struct is_integral<signed char> : public true_type{};
	template<> struct is_integral<short> : public true_type{};
	template<> struct is_integral<int> : public true_type{};
	template<> struct is_integral<long> : public true_type{};
	
	template<> struct is_integral<char> : public true_type{};
	template<> struct is_integral<bool> : public true_type{};
	template<> struct is_integral<char16_t> : public true_type{};
	template<> struct is_integral<char32_t> : public true_type{};
	template<> struct is_integral<wchar_t> : public true_type{};

	template< class T2 > struct remove_const{typedef T2 type; };	
	template< class T2 > struct remove_const<const T2>{ typedef T2 type; };
}

#endif