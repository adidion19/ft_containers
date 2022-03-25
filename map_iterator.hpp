/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 17:04:12 by adidion           #+#    #+#             */
/*   Updated: 2022/03/25 14:43:24 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "map.hpp"
//#include "iterator.hpp"
#include "binary_tree.hpp"
# include "utils.hpp"

namespace ft
{
	template <class Key, class T>
	class Node;
	
	template <class T>
	class map_iterator
	{
		private:
			typedef Node<typename remove_const<typename T::first>::type, typename T::second> nodes;
			nodes	*_node;
		public:
			typedef	typename T::first	key;
			typedef	typename T::second	value;
			map_iterator(): _node(NULL)
			{
				return ;
			}
			map_iterator(const map_iterator&obj): _node(obj._node)
			{
				*this = obj;
			}
			map_iterator(nodes *n): _node(n)
			{
				return ;
			}
			~map_iterator()
			{
				return ;
			}
			map_iterator &operator=(const map_iterator &obj)
			{
				_node = obj.getNode();
			}
			T& operator*() const
			{
				return (*(_node->content));
			}
			T* operator->() const
			{
				return (_node->content);
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
					nodes* y = _node->parent;
					while (_node == y->right)
					{
						_node = y;
						y = y->parent;
					}
					if (_node->right != y)
						_node = y;
				}
				return (*this);
			}
			map_iterator& operator++(int)
			{
				nodes *tmp = _node;
				_node++;
				return (tmp);
			}
			map_iterator& operator--()
			{
				if (!_node->is_black && _node->parent->parent == _node)
					_node = _node->right;
				else if (_node->left != 0)
				{
					nodes* y = _node->left;
					while (y->right != 0)
						y = y->right;
					_node = y;
				}
				else
				{
					nodes* y = _node->parent;
					while (_node == y->left)
					{
						_node = y;
						y = y->parent;
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
			nodes* getNode() const
			{
				return (_node);
			}
	};
};

#endif