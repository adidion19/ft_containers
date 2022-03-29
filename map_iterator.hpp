/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 17:04:12 by adidion           #+#    #+#             */
/*   Updated: 2022/03/29 13:51:57 by adidion          ###   ########.fr       */
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
	
	template <class T>
	class map_iterator
	{
		private:
			typedef Node<typename remove_const<typename T::first_type>::type, typename T::second_type> nodes;
			Node<typename T::first_type, typename T::second_type> *a;
			nodes	*_node;
		public:
			typedef	typename T::first_type	key;
			typedef	typename T::second_type	value;
			map_iterator(): a(NULL), _node(NULL)
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
				nodes tmp = _node;
				return (tmp->content);
			}
			T operator->()
			{
				a = _node;
				return (a->content);
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
					while (_node == y->right)
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
			bool	operator==(const map_iterator &obj) const;
			bool	operator!=(const map_iterator &obj) const;
			nodes* getNode() const
			{
				return (_node);
			}
	};
};

#endif