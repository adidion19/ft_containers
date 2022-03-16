/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:49:06 by adidion           #+#    #+#             */
/*   Updated: 2022/03/16 16:50:51 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_TREE_H
# define BINARY_TREE_H

#include "map.hpp"
# include "pair.hpp"

template < class Key, class T>
class	Node
{
	public:
		ft::pair<const Key,T> content;
		bool isBlack;
		Node *left;
		Node *right;
		Node *root;
		Node(ft::pair<const Key,T> data)
		{
			content = data;
			isBlack = 0;
			left = right = root = NULL;
			return ;
		}
		Node( const Node &obj )
		{
			content = obj.content;
			isBlack = obj.isBlack;
			left = obj.left;
			right = obj.right;
			root = obj.root;
			return ;
		}
		Node &operator=( const Node &obj )
		{
			content = x.content;
			isBlack = obj.isBlack;
			left = obj.left;
			right = obj.right;
			root = obj.root
		}
		~Node()
		{
			return ;
		}
};

template < class Key, class T>
class	Binary_tree
{
	private:
		Node<Key, T> *root;
	public:
		Binary_tree()
		{
			root = NULL;
		}
		Binary_tree( const Binary_tree &obj )
		{
			return ;
		}
		Binary_tree &operator=( const Binary_tree &obj )
		{
			return ;
		}
		~Binary_tree()
		{
			return ;
		}
		bool getColor(Node *&node)
		{
			if (node == NULL)
				return (1);
			return (node->color);
		}
		void setColor(Node *&node, int color)
		{
			if (node == NULL)
				return;
			node->color = color;
		}
		Node *insertNode(Node *&root, Node *&ptr)
		{
			if (!root)
				return (ptr);
			if (ptr->content < root->content)
			{
				root->left = insertBST()
			}
		}
};

#endif
