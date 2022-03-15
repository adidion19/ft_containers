/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 13:14:46 by adidion           #+#    #+#             */
/*   Updated: 2022/03/15 11:02:37 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_H
#define ITERATOR_H

#include <cstddef>
#include <iostream>
#include <memory>
#include <type_traits>
#include "vector.hpp"

namespace ft
{
	template< class T > struct remove_const	{ typedef T type; };
	template< class T > struct remove_const<const T>	{ typedef T type; };

	template<class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	template <class U>
	class reverse_random_iterator;

	template < class T >
	class random_access_iterator
	{
		private:
			T*	_ptr;
		public:
			typedef T* iterator_type;
			typedef typename ft::iterator<random_access_iterator, T>::value_type			value_type;
			typedef typename ft::iterator<random_access_iterator, T>::pointer				pointer;
			typedef typename ft::iterator<random_access_iterator, T>::reference			reference;
			typedef typename ft::iterator<random_access_iterator, T>::iterator_category	iterator_category;
			typedef typename ft::iterator<random_access_iterator, T>::difference_type		difference_type;

			random_access_iterator( void ) : _ptr(NULL)
			{
				return ;
			}
			random_access_iterator( const random_access_iterator<typename remove_const<T>::type > & obj ) : _ptr(obj.base())
			{
				return ;
			}
			random_access_iterator( const reverse_random_iterator<typename remove_const<T>::type > & obj ) : _ptr(obj.base())
			{
				return ;
			}
			random_access_iterator( pointer pointer ) : _ptr(pointer)
			{
				return ;
			}

			~random_access_iterator()
			{
				return ;
			}

			random_access_iterator<T> & operator=(const random_access_iterator<typename ft::remove_const<T>::type > &obj)
			{
				_ptr = obj.base();
				return (*this);
			}

			iterator_type base() const
			{
				return (_ptr);
			}

			reference operator*() const
			{
				return (*_ptr);
			}

			pointer operator->() const
			{
				return (_ptr);
			}

			reference operator[](size_t n)
			{
				return (base()[n]);
			}

			random_access_iterator& operator++()
			{
				_ptr++;
				return (*this);
			}

			random_access_iterator& operator--()
			{
				_ptr--;
				return (*this);
			}

			random_access_iterator operator++( int )
			{
				random_access_iterator it = *this;
				_ptr++;
				return (it);
			}
			random_access_iterator operator--( int )
			{
				random_access_iterator it = *this;
				_ptr--;
				return (it);
			}
			random_access_iterator operator+( difference_type n ) const
			{
				return (random_access_iterator((base() + n)));
			}

			random_access_iterator operator-( difference_type n ) const
			{
				return (random_access_iterator(base() - n));
			}

			difference_type		operator- (random_access_iterator const & b)
			{
				return (base() - b.base());
			}

			random_access_iterator& operator+=( difference_type n )
			{
				_ptr += n;
				return (*this);
			}

			random_access_iterator& operator-=( difference_type n )
			{
				_ptr -= n;
				return (*this);
			}

	};

	template< class Iterator1, class Iterator2 >
	bool operator==( const ft::random_access_iterator<Iterator1>& lhs, const ft::random_access_iterator<Iterator2>& rhs )
	{
		return (lhs.base() == rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator!=( const ft::random_access_iterator<Iterator1>& lhs, const ft::random_access_iterator<Iterator2>& rhs )
	{
		return (lhs.base() != rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator<( const ft::random_access_iterator<Iterator1>& lhs, const ft::random_access_iterator<Iterator2>& rhs )
	{
		return (lhs.base() < rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator<=( const ft::random_access_iterator<Iterator1>& lhs, const ft::random_access_iterator<Iterator2>& rhs )
	{
		return (lhs.base() <= rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator>( const ft::random_access_iterator<Iterator1>& lhs, const ft::random_access_iterator<Iterator2>& rhs )
	{
		return (lhs.base() > rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator>=( const ft::random_access_iterator<Iterator1>& lhs, const ft::random_access_iterator<Iterator2>& rhs )
	{
		return (lhs.base() >= rhs.base());
	}

	template< class Iter >
	random_access_iterator<Iter> operator+( typename random_access_iterator<Iter>::difference_type n, const random_access_iterator<Iter>& it )
	{
		return (random_access_iterator<Iter>(it.base() + n));
	}

	template < class T >
	size_t		operator-(random_access_iterator<T> const & a, random_access_iterator<T> const & b)
	{
		return (a.base() - b.base());
	}

	template< class Iter >
	random_access_iterator<Iter> operator-( typename random_access_iterator<Iter>::difference_type n, const random_access_iterator<Iter>& it )
	{
		return (random_access_iterator<Iter>(it.base() - n));
	}
};

#endif