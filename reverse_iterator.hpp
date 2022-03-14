/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:32:30 by adidion           #+#    #+#             */
/*   Updated: 2022/03/14 12:49:37 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_H
#define REVERSE_ITERATOR_H

#include "iterator.hpp"
#include "vector.hpp"

namespace ft
{
	template < class Iter >
	class reverse_random_access_iterator
	{
		private:
			Iter	_ptr;
		public:
			typedef Iter iterator_type;
			typedef typename Iter::value_type			value_type;
			typedef typename Iter::pointer				pointer;
			typedef typename Iter::reference			reference;
			typedef typename Iter::iterator_category	iterator_category;
			typedef typename Iter::difference_type		difference_type;

			reverse_random_access_iterator() : _ptr()
			{
				return ;
			}
			explicit reverse_random_access_iterator(iterator_type it) : _ptr(it)
			{
				return ;
			}
			explicit reverse_random_access_iterator(pointer p) : _ptr(iterator_type(p))
			{
				return ;
			}
			template <class Iterator>
			reverse_random_access_iterator(const reverse_random_access_iterator<Iterator> & ref) : _ptr(ref.base())
			{
				return ;
			}

			~reverse_random_access_iterator()
			{
				return ;
			}

			reverse_random_access_iterator<Iter> & operator=(const reverse_random_access_iterator<typename ft::remove_const<Iter>::type > &obj)
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
				iterator_type	tmp = this->_ptr;
				tmp--;
				return (*tmp);
			}

			pointer operator->() const
			{
				return (*_ptr);
			}

			reference operator[](size_t n)
			{
				return (*(_ptr - n - 1));
			}

			reverse_random_access_iterator& operator++()
			{
				_ptr--;
				return (*this);
			}

			reverse_random_access_iterator& operator--()
			{
				_ptr++;
				return (*this);
			}

			reverse_random_access_iterator operator++( int )
			{
				reverse_random_access_iterator it = *this;
				_ptr--;
				return (*this);
			}
			reverse_random_access_iterator operator--( int )
			{
				reverse_random_access_iterator it = *this;
				_ptr++;
				return (*this);
			}
			reverse_random_access_iterator operator+( difference_type n ) const
			{
				return (reverse_random_access_iterator((base() - n)));
			}

			reverse_random_access_iterator operator-( difference_type n ) const
			{
				return (reverse_random_access_iterator((base() + n)));
			}

			reverse_random_access_iterator& operator+=( difference_type n )
			{
				_ptr -= n;
				return (*this);
			}

			reverse_random_access_iterator& operator-=( difference_type n )
			{
				_ptr += n;
				return (*this);
			}

	};

	template< class Iterator1, class Iterator2 >
	bool operator==( const ft::reverse_random_access_iterator<Iterator1>& lhs, const ft::reverse_random_access_iterator<Iterator2>& rhs )
	{
		return (lhs.base() == rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator!=( const ft::reverse_random_access_iterator<Iterator1>& lhs, const ft::reverse_random_access_iterator<Iterator2>& rhs )
	{
		return (lhs.base() != rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator<( const ft::reverse_random_access_iterator<Iterator1>& lhs, const ft::reverse_random_access_iterator<Iterator2>& rhs )
	{
		return (lhs.base() > rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator<=( const ft::reverse_random_access_iterator<Iterator1>& lhs, const ft::reverse_random_access_iterator<Iterator2>& rhs )
	{
		return (lhs.base() >= rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator>( const ft::reverse_random_access_iterator<Iterator1>& lhs, const ft::reverse_random_access_iterator<Iterator2>& rhs )
	{
		return (lhs.base() < rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator>=( const ft::reverse_random_access_iterator<Iterator1>& lhs, const ft::reverse_random_access_iterator<Iterator2>& rhs )
	{
		return (lhs.base() <= rhs.base());
	}

	template< class Iter >
	reverse_random_access_iterator<Iter> operator+( typename reverse_random_access_iterator<Iter>::difference_type n, const reverse_random_access_iterator<Iter>& it )
	{
		return (reverse_random_access_iterator<Iter>(it.base() - n));
	}

	template< class Iter >
	reverse_random_access_iterator<Iter> operator-( typename reverse_random_access_iterator<Iter>::difference_type n, const reverse_random_access_iterator<Iter>& it )
	{
		return (reverse_random_access_iterator<Iter>(it.base() + n));
	}
};

#endif