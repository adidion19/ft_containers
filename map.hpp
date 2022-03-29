/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:01:20 by adidion           #+#    #+#             */
/*   Updated: 2022/03/29 13:49:40 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include <iostream>
#include <memory>
#include <iterator>
#include <exception>
#include "iterator.hpp"
# include "pair.hpp"
# include "binary_tree.hpp"
#include "reverse_iterator.hpp"

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map
	{
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef ft::pair<const key_type, mapped_type> value_type;
			typedef Compare key_compare;
			//typedef 
			typedef Alloc allocator_type;
			typedef typename allocator_type::reference		reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename ft::map_iterator<pair<const Key, T> >	iterator;
			typedef	ft::map_iterator<const pair<const Key, T> >	const_iterator;
			typedef	ft::reverse_random_access_iterator<iterator> 				reverse_iterator;
			typedef	ft::reverse_random_access_iterator<const_iterator>		const_reverse_iterator;
			typedef typename Alloc::pointer	pointer;
			typedef typename Alloc::const_pointer	const_pointer;
			typedef std::ptrdiff_t	difference_type;
			typedef std::size_t size_type;
		private:
			Binary_tree<Key, T> _rb;
			const key_compare &_cmp;
			const allocator_type& _alloc;
		public:
		// CONSTRUCTEURS
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _cmp(comp), _alloc(alloc)
			{
				return ;
			}
			//template <class InputIterator>
			//map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
			map (const map& x): _cmp(x._cmp), _alloc(x._alloc)
			{
				_rb = x._rb;
			}
		// DESTRUCTEUR
			~map()
			{
				return ;
			}
		// OPERATEUR =
			map& operator= (const map& x)
			{
				_rb = x.rb;
				_cmp = x.cmp;
				_alloc = x._alloc;
				return (*this);
			}
		// ITERATEURS
			//iterator begin();
			//const_iterator begin() const;
			//iterator end();
			//const_iterator end() const;
			//reverse_iterator rbegin();
			//const_reverse_iterator rbegin() const;
			//reverse_iterator rend();
			//const_reverse_iterator rend() const;
		//CAPACITY
			bool empty() const
			{
				if (!_rb.size())
					return (1);
				return (0);
			}
			size_type size() const
			{
				return (_rb.size());
			}
			size_type max_size() const
			{
				return (_alloc.max_size());
			}
		//ELEMENT ACCESS
			mapped_type& operator[] (const key_type& k)
			{
				T s = _rb.search(k);
				if (!s)
					return (_rb.insert(ft::make_pair(k, T())).first->second);
				return (s);
			}
			T& at( const Key& key )
			{
				T s = _rb.search(key);
				if (!s)
					throw(std::out_of_range("map"));
				return (s);
			}
			const T& at( const Key& key ) const
			{
				T s = _rb.search(key);
				if (!s)
					throw(std::out_of_range("map"));
				return (s);
			}
		// MODIFIERS
			//pair<iterator,bool> insert (const value_type& val);
			//iterator insert (iterator position, const value_type& val);
			//template <class InputIterator>
			//void insert (InputIterator first, InputIterator last);
			//void erase (iterator position);
			size_type erase (const key_type& k)
			{
				_rb.delete_one(k);
			}
			//void erase (iterator first, iterator last);
			void swap (map& x)
			{
				map a = x;
				x = *this;
				*this = a;
			}
			void clear()
			{
				_rb.ft_free(_rb.root);
			}
		// OBSERVERS
			key_compare key_comp() const
			{
				return (_cmp);
			}
			//value_compare value_comp() const;
		// OPERATIONS
			//iterator find (const key_type& k);
			//const_iterator find (const key_type& k) const;
			//size_type count (const key_type& k) const;
			//iterator lower_bound (const key_type& k);
			//const_iterator lower_bound (const key_type& k) const;
			//iterator upper_bound (const key_type& k);
			//const_iterator upper_bound (const key_type& k) const;
			//pair<const iterator, const iterator> equal_range (const key_type& k) const;
			//pair<iterator,iterator> equal_range (const key_type& k);
		// ALLOCATOR
			allocator_type get_allocator() const
			{
				return (_alloc);
			}
	};
	//template< class Key, class T, class Compare, class Alloc >
	//bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs );
	//template< class Key, class T, class Compare, class Alloc > 
	//bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs );
	//template< class Key, class T, class Compare, class Alloc >
	//bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs );
	//template< class Key, class T, class Compare, class Alloc >
	//bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs );
	//template< class Key, class T, class Compare, class Alloc >
	//bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs );
	//template< class Key, class T, class Compare, class Alloc >
	//bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs );
	//template< class Key, class T, class Compare, class Alloc >
	//void swap( ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs );
}

#endif
