/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:01:20 by adidion           #+#    #+#             */
/*   Updated: 2022/04/18 17:44:02 by adidion          ###   ########.fr       */
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
#include "map_iterator.hpp"
# include "utils.hpp"

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,T> > >
	class map
	{
		public:
			typedef Key																key_type;
			typedef T																mapped_type;
			typedef ft::pair<const key_type,mapped_type>							value_type;
			typedef Compare															key_compare;
			typedef std::allocator<ft::pair<const Key,T> >							allocator_type;
			typedef value_type&														reference;
			typedef const value_type&												const_reference;
			typedef value_type*														pointer;
			typedef const value_type*												const_pointer;
			typedef int																difference_type;
			typedef size_t															size_type;
			typedef ft::Node<const Key, T>											node;
			typedef ft::Binary_tree<key_type, mapped_type, key_compare, allocator_type>	Binary_tree;
			typedef typename ft::map_iterator<value_type, node>						iterator;
			typedef	ft::map_iterator<const value_type, node>						const_iterator;
			typedef ft::reverse_map_iterator<value_type, node>						reverse_iterator;
			typedef ft::reverse_map_iterator<const value_type, node>				const_reverse_iterator;
		private:
			class value_compare
			{
				protected:
					Compare comp;
				public:
					value_compare (Compare c) : comp(c)
					{
						return ;
					}
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};
			Binary_tree _rb;
			key_compare _cmp;
			allocator_type _alloc;
		public:
		// CONSTRUCTEURS
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _rb(Binary_tree()), _cmp(comp), _alloc(alloc)
			{
				return ;
			}
			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: _rb(Binary_tree()), _cmp(comp), _alloc(alloc)
			{
				while (first != last)
				{
					_rb.insert(ft::make_pair(first->first, first->second));
					++first;
				}
			}
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
				clear();
				_rb = x._rb;//insert(x.begin(), x.end());
				_alloc = x._alloc;
				_cmp = x._cmp;
				return (*this);
			}
		// ITERATEURS
			iterator begin()
			{
				return (iterator(_rb.begin()));
			}
			const_iterator begin() const
			{
				return (const_iterator(_rb.begin()));
			}
			iterator end()
			{
				return (iterator(_rb.end()));
			}
			const_iterator end() const
			{
				return (const_iterator(_rb.end()));
			}
			reverse_iterator rbegin()
			{
				return (reverse_iterator(_rb.rbegin()));
			}
			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(_rb.rbegin()));
			}
			reverse_iterator rend()
			{
				return (reverse_iterator(_rb.rend()));
			}
			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(_rb.rend()));
			}
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
				return (*((insert(ft::make_pair(k,mapped_type()))).first)).second;
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
			pair<iterator,bool> insert (const value_type& val)
			{
				return (_rb.insert(val));
			}
			iterator insert (iterator position, const value_type& val)
			{
				ft::pair<iterator,bool> tmp = _rb.insert(val);
				(void)position;
				return (tmp.first);
			}
			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				while (first != last)
				{
					_rb.insert(ft::make_pair(first->first, first->second));
					++first;
				}
			}
			void erase (iterator position)
			{
				key_type tmp = position->first;
				_rb.delete_one(tmp);
			}
			size_type erase (const key_type& k)
			{
				return (_rb.delete_one(k));
			}
			void erase (iterator first, iterator last)
			{
				_rb.ft_free(first, last);
			}
			void swap (map& x)
			{
				key_compare tmp = x._cmp;
				x._cmp = _cmp;
				_cmp = tmp;
				allocator_type tmp2 = x._alloc;
				x._alloc = _alloc;
				_alloc = tmp2;
				_rb.ft_swap(x._rb);
			}
			void clear()
			{
				_rb.ft_free(begin(), end());
			}
		// OBSERVERS
			key_compare key_comp() const
			{
				return (_cmp);
			}
			value_compare value_comp() const
			{
				return (value_compare(_cmp));
			}
		// OPERATIONS
			iterator find (const key_type& k)
			{
				return (_rb.find(k));
			}
			const_iterator find (const key_type& k) const
			{
				return (_rb.find(k));
			}
			size_type count (const key_type& k) const
			{
				return (_rb.count(k));
			}
			iterator lower_bound (const key_type& k)
			{
				return (_rb.lower_bound(k));
			}
			const_iterator lower_bound (const key_type& k) const
			{
				return (_rb.lower_bound(k));
			}
			iterator upper_bound (const key_type& k)
			{
				return (_rb.upper_bound(k));
			}
			const_iterator upper_bound (const key_type& k) const
			{
				return (_rb.upper_bound(k));
			}
			pair<const_iterator, const_iterator> equal_range (const key_type& k) const
			{
				return (_rb.equal_range(k));
			}
			pair<iterator,iterator> equal_range (const key_type& k)
			{
				return (_rb.equal_range(k));
			}
		// ALLOCATOR
			allocator_type get_allocator() const
			{
				return (_alloc);
			}
	};
	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		typename ft::map<Key, T>::const_iterator	it = lhs.begin(), rit = rhs.begin(), end = lhs.end(), rend = rhs.end();

		while (it != end && rit != rend)
		{
			if (*it != *rit)
				return (0);
			it++;
			rit++;
		}
		if (rhs.size() == lhs.size())
			return (1);
		return (0);
	}
	template< class Key, class T, class Compare, class Alloc > 
	bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs == rhs));
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(rhs < lhs));
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (rhs < lhs);
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs < rhs));
	}
	template< class Key, class T, class Compare, class Alloc >
	void swap( ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs)
	{
		lhs.swap(rhs);
	}
}

#endif
