/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 15:55:09 by adidion           #+#    #+#             */
/*   Updated: 2022/04/20 14:31:01 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"
#include "utils.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef size_t			size_type;
			typedef T				value_type;
			typedef Container		container_type;
			container_type		c;
			explicit stack (const container_type& ctnr = container_type())
			{
				c = ctnr;
				return ;
			}
			bool empty() const
			{
				return (c.empty());
			}
			size_type size() const
			{
				return (c.size());
			}
			value_type& top()
			{
				return (c.back());
			}
			const value_type& top() const
			{
				return (c.back());
			}
			void push (const value_type& val)
			{
				c.push_back(val);
			}
			void pop()
			{
				c.pop_back();
			}
			template <class T1, class Container1>
			friend bool operator==(const stack<T1, Container1>& lhs, const stack<T1, Container1>& rhs)
			{
				return (lhs.c == rhs.c);
			}
			template <class T1, class Container1>
			friend bool operator<(const stack<T1, Container1>& lhs, const stack<T1, Container1>& rhs)
			{
				return (lhs.c < rhs.c);
			}
	};
	template <class T, class Container>
	bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (!(lhs == rhs));
	}
	template <class T, class Container>
	bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (rhs < lhs);
	}
	template <class T, class Container>
	bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (!(rhs < lhs));
	}
	template <class T, class Container>
	bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (!(lhs < rhs));
	}
}

#endif