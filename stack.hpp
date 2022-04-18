/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 15:55:09 by adidion           #+#    #+#             */
/*   Updated: 2022/04/18 16:06:47 by adidion          ###   ########.fr       */
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
		private:
			container_type		c;
		public:
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
			container_type getC() const
			{
				return (c);
			}
	};
	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.getC() == rhs.getC());
	}

	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.getC() != rhs.getC());
	}

	template <class T, class Container>
	bool operator<	(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.getC() < rhs.getC());
	}

	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.getC() <= rhs.getC());
	}

	template <class T, class Container>
	bool operator>	(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.getC() > rhs.getC());
	}

	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.getC() >= rhs.getC());
	}
}

#endif