/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:20:48 by adidion           #+#    #+#             */
/*   Updated: 2022/03/29 15:54:54 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

#include <iostream>
#include <memory>
#include <iterator>
#include <exception>

namespace ft
{
	template < class T1, class T2 >
	struct pair
	{
		public:
			typedef T1 first_type;
			typedef T2 second_type;
			first_type	first;
			second_type	second;
			pair(): first(first_type()), second(second_type())
			{
				return ;
			}
			pair( const T1& x, const T2& y ): first(x), second(y)
			{
				return ;
			}
			template< class U1, class U2 >
			pair( const pair<U1, U2>& p )
			{
				first = p.first;
				second = p.second;
				return ;
			}
			pair& operator=( const pair& ref )
			{
				first = ref.first;
				second = ref.second;
				return (*this);
			}
	};

	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
	}

	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (!(lhs<rhs));
	}

	template <class T1, class T2>
	pair<T1,T2> make_pair (T1 x, T2 y)
	{
		return (pair<T1, T2>(x, y));
	}
}

#endif