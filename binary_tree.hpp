/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:49:06 by adidion           #+#    #+#             */
/*   Updated: 2022/03/18 16:53:04 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_TREE_H
# define BINARY_TREE_H

//#include "map.hpp"
# include "pair.hpp"

template < class Key, class T>
class	Node
{
	public:
		ft::pair<const Key,T> content;
		bool isBlack;
		Node left;
		Node right;
		Node root;
		Node(ft::pair<const Key,T> data)
		{
			content = data;
			isBlack = 0;
			left = right = root = NULL;
			return ;
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
		Node<Key, T> root;
		bool ll;
		bool rr;
		bool lr;
		bool rl;
	public:
		void ft_free(Node<Key, T> node)
		{
			if (node)
			{
				ft_free(node.left);
				ft_free(node.right);
				delete root;
			}
		}
		Binary_tree()
		{
			root = NULL;
			ll = 0;
			rr = 0;
			lr = 0;
			rl = 0;
		}
		~Binary_tree()
		{
			ft_free(root);
		}
		Node<Key, T>	rotate_left(Node<Key, T> node)
		{
			Node<Key, T> x = node.right;
			Node<Key, T> y = x.left;
			x.left = node;
			node.right = y;
			node.root = x;
			if (!y)
				y.root = node;
			return (x);
		}
		Node<Key, T>	rotate_right(Node<Key, T> node)
		{
			Node<Key, T> x = node.left;
			Node<Key, T> y = x.right;
			x.right = node;
			node.left = y;
			node.root = x;
			if (!y)
				y.root = node;
			return (x);
		}

		Node<Key, T> insert_conditions(Node<Key, T> newone, ft::pair<const Key,T> data)
		{
			bool f = 0;
			if (!newone)
				return (new Node<Key, T>(data));
			if (data < newone.data)
			{
				newone.left = insert_conditions(newone.left, data);
				newone.left.root = newone;
				if (newone != root)
				{
					if (newone.isBlack == 0 && newone.right.isBlack == 0)
						f = 1;
				}
			}
			else
			{
				newone.right = insert_conditions(newone.right, data);
				newone.right.parent = newone;
				if (newone != root)
				{
					if (newone.isBlack == 0 && newone.right.isBlack == 0)
						f = 1;
				}
			}
			// when it's okay, lets insert
			if (ll)
			{
				newone = rotate_left(newone);
				newone.isBlack = 1;
				newone.left.isBlack = 0;
				ll = 0;
			}
			else if (rr)
			{
				newone = rotate_right(newone);
				newone.isBlack = 1;
				newone.right.isBlack = 0;
				rr = 0;
			}
			else if (rl)
			{
				newone.right = rotate_right(newone.right);
				newone.right.root = newone;
				newone = rotate_left(newone);
				newone.isBlack = 1;
				newone.left.isBlack = 0;
				rl = 0;
			}
			else if (lr)
			{
				newone.left = rotate_left(newone.left);
				newone.left.root = newone;
				newone = rotate_right(newone);
				newone.isBlack = 1;
				newone.right.isBlack = 0;
				lr = 0;
			}
			if (f)
			{
				if (newone.root.right == newone)
				{
					if (!newone.root.left || newone.root.left.isBlack == 1)
					{
						if (newone.left && newone.left.isBlack == 0)
							rl = 1;
						else if (newone.right && newone.right.isBlack == 0)
							ll = 1;
					}
					else
					{
						newone.root.left.isBlack == 1;
						root.isBlack = 1;
						if (newone.root != root)
							newone.parent.isBlack = 0;
					}
				}
				else
				{
					if (!newone.root.right || newone.root.right.isBlack == 1)
					{
						if (newone.left && newone.left.isBlack == 0)
							rr = 1;
						else if (newone.right && newone.right.isBlack == 0)
							lr = 1;
					}
					else
					{
						newone.root.right.isBlack = 1;
						newone.isBlack = 1;
						if (newone.parent != root)
							newone.root.isBlack = 0;
					}
				}
				f = 0;
			}
			return (newone);
		}

		void	insert(ft::pair<const Key,T> data)
		{
			if (!root)
			{
				root = new Node<Key,T>(data);
				root.isBlack = 1;
			}
			else
				root = insert_conditions(root, data);
		}

};

#endif
