/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 17:04:12 by adidion           #+#    #+#             */
/*   Updated: 2022/04/11 13:46:39 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "iterator.hpp"
#include "binary_tree.hpp"
# include "utils.hpp"
#include "pair.hpp"

namespace ft
{
	template <class Key, class T>
	class Node;
	template < class Key, class T, class Alloc>
	class Binary_tree;

	template <class T>
	class map_iterator
	{
		private:
			typedef Node<typename remove_const<typename T::first_type>::type, typename T::second_type> nodes;
			nodes	*_node;
		public:
			typedef	typename T::first_type	key;
			typedef	typename T::second_type	value;
			map_iterator(): _node(NULL)
			{
				return ;
			}
			map_iterator(const map_iterator<typename remove_const<T>::type> &obj)
			{
				*this = obj;
			}
			map_iterator(nodes *n): _node(n)
			{
				return ;
			}
			//map_iterator (Node<typename remove_const<typename T::first_type>::type, typename T::second_type>): _node(a)
			//{
			//	;
			//}
			map_iterator (Node<typename T::first_type, typename T::second_type> *a): _node(a)
			{
				;
			}
			~map_iterator()
			{
				return ;
			}
			map_iterator &operator=(const map_iterator<typename remove_const<T>::type> &obj)
			{
				_node = obj.getNode();
				return (*this);
			}
			T& operator*() const
			{
				return (_node->content);
			}
			nodes *base() const
			{
				return (_node);
			}
			T* operator->() const
			{
				return (&(_node)->content);
			}
			map_iterator &	operator++()
			{
				if (_node->right)
				{
					_node = _node->right;
					while (_node->left != 0)
						_node = _node->left;
				}
				else
				{
					nodes* y = _node->root;
					while (_node && y && y->right && _node == y->right)
					{
						_node = y;
						y = y->root;
					}
					if (_node->right != y)
						_node = y;
				}
				return (*this);
			}
			map_iterator& operator++(int)
			{
				nodes *tmp = _node;
				++_node;
				return (tmp);
			}
			map_iterator& operator--()
			{
				if (!_node)
				{
				;//return (map_iterator)
				}
				if (!_node->isBlack && _node->root->root == _node)
					_node = _node->right;
				//std::cout << "AAAA" << std::endl;
				else if (_node->left != 0)
				{
					nodes* y = _node->left;
					while (y->right != 0)
						y = y->right;
					_node = y;
				}
				else
				{
					nodes* y = _node->root;
					while (_node == y->left)
					{
						_node = y;
						y = y->root;
					}
					_node = y;
				}
				return (*this);
			}
			map_iterator& operator--(int)
			{
				nodes *tmp = _node;
				_node--;
				return (tmp);
			}
			bool	operator==(const map_iterator &obj) const
			{
				return (_node == obj._node);
			}
			bool	operator!=(const map_iterator &obj) const
			{
				return (!(*this == obj));
			}
			nodes* getNode() const
			{
				return (_node);
			}
	};
};

#endif