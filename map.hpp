/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:01:20 by adidion           #+#    #+#             */
/*   Updated: 2022/03/22 12:15:43 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

#include <iostream>
#include <memory>
#include <iterator>
#include <exception>
# include "pair.hpp"

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
			typedef typename Alloc::pointer					pointer;
			typedef typename Alloc::const_pointer			const_pointer;
			typedef std::ptrdiff_t	difference_type;
			typedef std::size_t size_type;
		// CONSTRUCTEURS
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
			//template <class InputIterator>
			//map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
			map (const map& x);
		// DESTRUCTEUR
			~map();
		// OPERATEUR =
			map& operator= (const map& x);
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
			bool empty() const;
			size_type size() const;
			size_type max_size() const;
		//ELEMENT ACCESS
			mapped_type& operator[] (const key_type& k);
		// MODIFIERS
			//pair<iterator,bool> insert (const value_type& val);
			//iterator insert (iterator position, const value_type& val);
			//template <class InputIterator>
			//void insert (InputIterator first, InputIterator last);
			//void erase (iterator position);
			size_type erase (const key_type& k);
			//void erase (iterator first, iterator last);
			void swap (map& x);
			void clear();
		// OBSERVERS
			key_compare key_comp() const;
			//value_compare value_comp() const;
		// OPERATIONS
			//iterator find (const key_type& k);
			//const_iterator find (const key_type& k) const;
			//size_type count (const key_type& k) const;
			//iterator lower_bound (const key_type& k);
			//const_iterator lower_bound (const key_type& k) const;
			//iterator upper_bound (const key_type& k);
			//const_iterator upper_bound (const key_type& k) const;
			//pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
			//pair<iterator,iterator> equal_range (const key_type& k);
		// ALLOCATOR
			allocator_type get_allocator() const;
	};
	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs );
	template< class Key, class T, class Compare, class Alloc > 
	bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs );
	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs );
	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs );
	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs );
	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs );
	template< class Key, class T, class Compare, class Alloc >
	void swap( ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs );
}

#endif
