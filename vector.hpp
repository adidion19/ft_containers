/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:07:31 by adidion           #+#    #+#             */
/*   Updated: 2022/03/14 14:38:08 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

#include <iostream>
#include <memory>
#include <iterator>
#include <exception>
#include "iterator.hpp"
#include "utils.hpp"
#include "reverse_iterator.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class	vector
	{
		public:
			typedef std::size_t size_type;
			typedef ft::random_access_iterator<T> iterator;
			typedef const ft::random_access_iterator<const T> const_iterator;
			typedef ft::reverse_random_access_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_random_access_iterator<const_iterator>			const_reverse_iterator;
			typedef Alloc allocator_type;
			typedef T			value_type;
			typedef const	value_type& reference;
			typedef const	value_type& const_reference;
			typedef std::ptrdiff_t difference_type;
			typedef T* pointer;
		private:
			allocator_type  _alloc;
			std::size_t _size;
			std::size_t _capacity;
			value_type *_v;
		protected:
			/* data */
		public:
		// CONSTRUCTEURS:
			explicit vector (const allocator_type& alloc = allocator_type()): _alloc(alloc), _size(0), _capacity(0)
			{
				this->_v = this->_alloc.allocate(0);
				return ;
			}
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): _alloc(alloc), _size(n), _capacity(n)
			{
				if (n < 0)
					throw (std::out_of_range("vector"));
				this->_v = this->_alloc.allocate(n);
				for(unsigned int i = 0; i < n; i++)
				{
					this->_alloc.construct(&_v[i], val);
				}
				return ;
			}
			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL) : _alloc(alloc)
			{
				InputIterator tmp = first;
				for (; tmp != last; tmp++)
					_size++;
				_capacity = _size;
				_v = _alloc.allocate(_size);
				for (unsigned int i = 0; i < _size; i++)
				{
					_alloc.construct(_v + i, *first);
					first++;
				}
				return ;
			}
			vector (const vector& x) :  _alloc(x._alloc), _size(x._size), _capacity(x._capacity)
			{
				_v = _alloc.allocate(_capacity);
				for (std::size_t i = 0; i < _size; i++)
					_alloc.construct(_v + i, x._v[i]);
			}
		// DESTRUCTEUR:
			~vector()
			{
				for (unsigned int i = 0; i != this->_size; i++)
				{
					this->_alloc.destroy(&_v[i]);
				}
				this->_alloc.deallocate(_v, this->_capacity);
				return ;
			}
		// OPERATEURS:
			vector& operator= (const vector& obj)
			{
				for (unsigned int i = 0; i < _size; i++)
					_alloc.destroy(_v + i);
				_alloc.deallocate(_v, _capacity);
				_alloc = obj._alloc;
				_capacity = obj._capacity;
				_size = obj._size;
				_v = _alloc.allocate(_capacity);
				for (unsigned int i = 0;i < _size; i++)
				{
					_alloc.construct(_v + i, obj._v[i]);
				}
				return (*this);
			}
		// ITERATEURS:
			iterator begin()
			{
				return (iterator(_v));
			}
			const_iterator begin() const
			{
				return (const_iterator(_v));
			}
			iterator end()
			{
				if (_size == 0)
					return (this->begin());
				return (iterator(_v + _size));
			}
			const_iterator end() const
			{
				if (_size == 0)
					return (this->begin());
				return (const_iterator(_v + _size));
			}
			reverse_iterator rbegin()
			{
				return (reverse_iterator(_v + _size));
			}
			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(_v + _size));
			}
			reverse_iterator rend()
			{
				return (reverse_iterator(_v));
			}
			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(_v));
			}
		// CAPACITY:
			size_type size() const
			{
				return (_size);
			}
			size_type max_size() const
			{
				return (_alloc.max_size());
			}
			void resize (size_type n, value_type val = value_type())
			{
				if (n == _size)
					return ;
				if (n < _size)
				{
					for (unsigned int i = n; i < _size; i++)
					{
						_alloc.destroy(_v + i);
					}
					_size = n;
					return ;
				}
				if (n > _capacity)
					reserve(n);
				for (unsigned int i = _size ; i < n ; i++)
					_alloc.construct(_v + i, val);
				_size = n;
				return ;
			}
			size_type capacity() const
			{
				return (_capacity);
			}
			bool empty() const
			{
				if (_size == 0)
					return (1);
				return (0);
			}
			void reserve (size_type n)
			{
				if (n >= this->max_size())
					throw std::out_of_range("vector");
				if (n <= this->capacity())
					return ;

				pointer old_v = this->_v;
				this->_v = this->_alloc.allocate(n);

				for (unsigned int i = 0; i != this->_size; i++)
				{
					this->_alloc.construct(&this->_v[i], old_v[i]);
				}
				for (unsigned int i = 0; i != this->_size; i++)
				{
					this->_alloc.destroy(&old_v[i]);
				}
				this->_alloc.deallocate(old_v, this->_capacity);
				this->_capacity = n;
			}
		// ELEMENT ACCESS:
			// selon cplusplus.com :
			//Portable programs should never call this function with an argument n that is out of range, since this causes undefined behavior.
			// -> use at instead !
			reference operator[] (size_type n)
			{
				return (_v[n]);
			}
			const_reference operator[] (size_type n) const
			{
				return (_v[n]);
			}
			//
			reference at (size_type n)
			{
				if (n >= _size)
					throw (std::out_of_range("vector"));
				return (_v[n]);
			}
			const_reference at (size_type n) const
			{
				if (n >= _size)
					throw (std::out_of_range("vector"));
				return (_v[n]);
			}
			// selon cplusplus.com : 
			// Calling this function on an empty container causes undefined behavior.
			reference front()
			{
				return (_v[0]);
			}
			const_reference front() const
			{
				return (_v[0]);
			}
			reference back()
			{
				return (_v[_size - 1]);
			}
			const_reference back() const
			{
				return (_v[_size - 1]);
			}
			//
		// MODIFIERS:
			template <class InputIterator>
			void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = nullptr)
			{
				int i = 0;
				InputIterator tmp = last;
				while (tmp-- != first)
					i++;
				resize(0);
				reserve(i);
				_size = i;
				while (first != last)
				{
					_alloc.construct(_v + (_size - i), *first);
					i--;
					first++;
				}
				return ;
			}
			void assign (size_type n, const value_type& val)
			{
				resize(0);
				reserve(n);
				_size = n;
				for (unsigned int i = 0; i < n; i++)
					_alloc.construct(_v + i, val);
				return ;
			}
			void push_back (const value_type& val)
			{
				if (this->_size >= this->_capacity)
				{
					size_type n = this->_capacity == 0 ? 2 : this->_capacity * 2;
					this->reserve(n);
				}
				this->_alloc.construct(&_v[_size], val);
				this->_size += 1;
			}
			void pop_back()
			{
				if (_size == 0)
					return ;
				resize(_size - 1);
			}
			iterator insert (iterator position, const value_type& val)
			{
				unsigned int i = 0, j = _size;

				for (iterator it = begin(); it < position; it++, i++);
				reserve(_size + 1);
				_size++;
				while (j > i)
				{
					_v[j] = _v[j - 1];
					j--;
				}
				_alloc.construct(_v + i, val);
				return (iterator(_v + i));
			}
			void insert (iterator position, size_type n, const value_type& val)
			{
				unsigned int i = 0, j = _size + n - 1;
				int boo = 0;
				for (iterator it = begin(); it < position; it++, i++);
				reserve(n + _size);
				_size += n;
				while (j >= n + i)
				{
					_v[j] = _v[j - n];
					j--;
				}
				while (j > i && j != 0)
				{
					_alloc.construct(_v + j, val);
					j--;
					boo = 1;
				}
				if (j >= i && boo == 1)
				{
					_alloc.construct(_v + j, val);
					j--;
				}
				return ;
			}
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = nullptr)
			{
				unsigned int	i = 0, pos = 0, j = 0;

				for(InputIterator tmp = first; tmp != last; tmp++)
						j++;
				for(iterator tmp = begin(); tmp != position; tmp++)
						pos++;
				reserve(_size + j);
				position = begin() + pos;
				for(iterator tmp = end() + j - 1; tmp >= position + j; tmp--)
					*tmp = *(tmp - j);
				for (InputIterator tmp = first; tmp != last; tmp++)
				{
					_alloc.construct(&position[i], *(tmp));
					i++;
				}
				_size += j;
			}
			iterator erase (iterator position)
			{
				unsigned int i = 0;
				for (iterator it = begin(); it < position; it++, i++);
				_alloc.destroy(_v + i);
				while (position + 1 < end())
				{
					*position = *position + 1;
					position++;
				}
				_size--;
				return (position);
			}
			iterator erase (iterator first, iterator last)
			{
				unsigned int i = 0;
				unsigned int diff = last - first;
				for (iterator it = begin() ; it < last; it++, i++);
				while (first < last)
				{
					last--;
					i--;
					_alloc.destroy(_v + i);
				}
				i = 0;
				while (end() > first + diff + i)
				{
					*(first + i) = *(first + diff + i);
					i++;
				}
				resize(_size - diff);
				return (first);
			}
			void swap (vector& x)
			{
				Alloc alloc;
				unsigned int size;
				unsigned int capacity;
				value_type *tmp;
				
				alloc = x._alloc;
				capacity = x._capacity;
				size = x._size;
				tmp = x._v;

				x._alloc = _alloc;
				x._capacity = _capacity;
				x._size = _size;
				x._v = _v;

				_alloc = alloc;
				_capacity = capacity;
				_size = size;
				_v = tmp;
			}
			void clear()
			{
				for (unsigned int i = 0; i != this->_size; i++)
				{
					_alloc.destroy(&_v[i]);
				}
				_size = 0;
			}
		// ALLOCATOR:
			allocator_type get_allocator() const
			{
				return (_alloc);
			}
	};

	// FONCTIONS NON_MEMBRE:
	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		vector<T,Alloc> tmp;
		tmp = x;
		x = y;
		y = tmp;
	}
	
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() == rhs.size())
		{
			for (unsigned int i = 0; i < rhs.size(); i++)
			{
				if (rhs[i] != lhs[i])
					return (0);
			}
			return (1);
		}
		return (1);
	}
	
	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() == rhs.size())
		{
			for (unsigned int i = 0; i < rhs.size(); i++)
			{
				if (rhs[i] != lhs[i])
					return (1);
			}
			return (0);
		}
		return (0);
	}
	
	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		unsigned int i = 0;

		while(i < lhs.size() && i < rhs.size())
		{
			if (rhs[i] < lhs[i])
				return (0);
			if (lhs[i] < rhs[i])
				return (1);
			i++;
		}
		if (lhs.size() < rhs.size())
			return (1);
		else
			return (0);
	}
	
	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (rhs == lhs || lhs < rhs)
			return (1);
		return (0);
	}
	
	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		unsigned int i = 0;

		while(i < lhs.size() && i < rhs.size())
		{
			if (rhs[i] > lhs[i])
				return (0);
			if (lhs[i] > rhs[i])
				return (1);
			i++;
		}
		if (lhs.size() > rhs.size())
			return (1);
		else
			return (0);
	}
	
	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (rhs == lhs || lhs > rhs)
			return (1);
		return (0);
	}	
}

#endif
