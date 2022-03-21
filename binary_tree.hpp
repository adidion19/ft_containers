/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree->hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student->s19->be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:49:06 by adidion           #+#    #+#             */
/*   Updated: 2022/03/18 18:17:08 by adidion          ###   ########->fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_TREE_H
# define BINARY_TREE_H

//#include "map->hpp"
# include "pair.hpp"

template < class Key, class T>
class	Node
{
	public:
		ft::pair<Key,T> content;
		bool isBlack;
		Node *left;
		Node *right;
		Node *root;
		Node(ft::pair<Key,T> data)
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
		Node *uncle()
		{
			if (!root || !root->root)
			{
				return (NULL);
			}
			if (root->is_on_left())
				return (root->root->right);
			return (root->root->left);
		}
		bool is_on_left()
		{
			return (this == root->left);
		}
		Node *sibling()
		{
			if (!root)
				return (NULL);
			if (is_on_left())
				return (root->right);
			return (root->left);
		}
		void	move_down(Node *n)
		{
			if (!root)
			{
				if (is_on_left())
					root->left = n;
				else
					root->right = n;
			}
			n->root = root;
			root = n;
		}
		bool has_red_child()
		{
			return ((left && left->isBlack == 0) || (right && right->isBlack == 0));
		}
};

template < class Key, class T>
class	Binary_tree
{
	private:
		Node< Key, T> *root;
		bool ll;
		bool rr;
		bool lr;
		bool rl;
		void ft_free(Node< Key, T> *node)
		{
			if (node)
			{
				ft_free(node->left);
				ft_free(node->right);
				delete node;
			}
		}
		void	left_rotate(Node<Key, T> *x)
		{
			Node<Key, T> *tmp = x->right;
			if (x == root)
				root = tmp;
			x->move_down(tmp);
			x->right = tmp->left;
			if (tmp->left)
				tmp->left->root = x;
			tmp->left = x;
		}
		Node< Key, T>	*rotate_left(Node< Key, T> *node)
		{
			Node< Key, T> *x = node->right;
			Node< Key, T> *y = x->left;
			x->left = node;
			node->right = y;
			node->root = x;
			if (y)
				y->root = node;
			return (x);
		}
		void	right_rotate(Node<Key, T> *x)
		{
			Node<Key, T> *tmp = x->left;
			if (x == root)
				root = tmp;
			x->move_down(tmp);
			x->left = tmp->right;
			if (tmp->right)
				tmp->right->root = x;
			tmp->right = x;
		}
		
		Node< Key, T>	*rotate_right(Node< Key, T> *node)
		{
			Node< Key, T> *x = node->left;
			Node< Key, T> *y = x->right;
			x->right = node;
			node->left = y;
			node->root = x;
			if (y)
				y->root = node;
			return (x);
		}

		void	swap_isBlacks(Node<Key, T> *x1, Node<Key, T> *x2)
		{
			bool tmp;
			tmp = x1->isBlack;
			x1->isBlack - x2->isBlack;
			x2->isBlack = tmp;
		}
		void swap_values(Node<Key, T> *x1, Node<Key, T> *x2)
		{
			ft::pair<Key, T> a;
			a = x1->content;
			x1->content = x2->content;
			x2->content = a;
		}
		void fix_double_red(Node<Key, T> *x)
		{
			if (x == root)
			{
				x->isBlack = 1;
			}
			Node<Key, int> *parent = x->root, *grandparent = parent->root, *uncle = x->uncle();
			if (parent->isBlack == 0)
			{
				if (uncle && uncle->isBlack == 0)
				{
					parent->isBlack = 1;
					uncle->isBlack = 1;
					grandparent->isBlack = 0;
					fix_double_red(grandparent);
				}
				else
				{
					if (parent->is_on_left())
					{
						if (x->is_on_left())
							swap_isBlacks(parent, grandparent);
						else
						{
							left_rotate(parent);
							swap_isBlacks(x, grandparent);
						}
						right_rotate(grandparent);
					}
					else
					{
						if (x->is_on_left())
						{
							right_rotate(parent);
							swap_isBlacks(x, grandparent);
						}
						else
							swap_isBlacks(parent, grandparent);
						left_rotate(grandparent);
					}
				}
			}
		}
		void	fix_double_black(Node<Key, T> *x)
		{
			if (x == root)
				return ;
			Node<Key, T> *sibling = x->sibling(), *parent = x->root;
			if (!sibling)
				fix_double_black(parent);
			else
			{
				if (sibling->isBlack == 0)
				{
					parent->isBlack = 0;
					sibling->isBlack = 1;
					if (sibling->is_on_left())
						right_rotate(parent);
					else
						left_rotate(parent);
					fix_double_black(x);
				}
				else
				{
					if (sibling->has_red_child())
					{
						if (sibling->left && sibling->left->isBlack == 0)
						{
							if (sibling->is_on_left())
							{
								sibling->left->isBlack = sibling->isBlack;
								sibling->isBlack = parent->isBlack;
								right_rotate(parent);
							}
							else
							{
								sibling->left->isBlack = parent->isBlack;
								right_rotate(sibling);
								left_rotate(parent);
							}
						}
						else
						{
							if (sibling->is_on_left())
							{
								sibling->right->isBlack = parent->isBlack;
								left_rotate(sibling);
								right_rotate(parent);
							}
							else
							{
								sibling->right->isBlack = sibling->isBlack;
								sibling->isBlack = parent->isBlack;
								left_rotate(parent);
							}
						}
						parent->isBlack = 1;
					}
					else
					{
						sibling->isBlack = 0;
						if (parent->isBlack == 1)
							fix_double_black(parent);
						else
							parent->isBlack = 1;
					}
				}
			}
		}
		Node<Key, T> *successor(Node<Key, T> *x)
		{
			Node<Key, T> *tmp = x;
			while (tmp->left)
				tmp = tmp->left;
			return (tmp);
		}
		Node<Key, T> *replace(Node <Key, T> *x)
		{
			if (x->left && x->right)
				return (successor(x->right));
			if (!x->left && !x->right)
				return (NULL);
			if (x->left)
				return (x->left);
			return (x->right);
		}
		void	delete_node(Node <Key, T> *x)
		{
			Node<Key, T> *tmp = replace(x);
			bool boo = ((!tmp || tmp->isBlack == 1) && (x->isBlack == 1));
			Node<Key, T> *parent = x->root;
			if (!tmp)
			{
				if (x == root)
				{
					root = NULL;
				}
				else
				{
					if (boo)
						fix_double_black(x);
					else if (x->sibling())
						x->sibling()->isBlack = 0;
					if (x->is_on_left())
					{
						parent->left = NULL;
					}
					else
					{
						parent->right = NULL;
					}
				}
				delete x;
				return ;
			}
			if (!x->left || !x->right)
			{
				if (x == root)
				{
					x->content = tmp->content;
					x->left = NULL;
					x->right = NULL;
					delete tmp;
				}
				else
				{
					if (x->is_on_left())
						parent->left = tmp;
					else
						parent->right = tmp;
					delete x;
					tmp->root = parent;
					if (boo)
						fix_double_black(tmp);
					else
						tmp->isBlack = 1;
				}
				return ;
			}
			swap_values(tmp, x);
			delete_node(tmp);
		}
		Node< Key, T> *insert_conditions(Node< Key, T> *newone, ft::pair<Key,T> data)
		{
			bool f = 0;
			if (!newone)
				return (new Node< Key, T> (data));
			if (data < newone->content)
			{
				newone->left = insert_conditions(newone->left, data);
				newone->left->root = newone;
				if (newone != root)
				{
					if (newone->isBlack == 0 && newone->right->isBlack == 0)
						f = 1;
				}
			}
			else
			{
				newone->right = insert_conditions(newone->right, data);
				newone->right->root = newone;
				if (newone != root)
				{
					if (newone->isBlack == 0 && newone->right->isBlack == 0)
						f = 1;
				}
			}
			// when it's okay, lets insert
			if (ll)
			{
				newone = rotate_left(newone);
				newone->isBlack = 1;
				newone->left->isBlack = 0;
				ll = 0;
			}
			else if (rr)
			{
				newone = rotate_right(newone);
				newone->isBlack = 1;
				newone->right->isBlack = 0;
				rr = 0;
			}
			else if (rl)
			{
				newone->right = rotate_right(newone->right);
				newone->right->root = newone;
				newone = rotate_left(newone);
				newone->isBlack = 1;
				newone->left->isBlack = 0;
				rl = 0;
			}
			else if (lr)
			{
				newone->left = rotate_left(newone->left);
				newone->left->root = newone;
				newone = rotate_right(newone);
				newone->isBlack = 1;
				newone->right->isBlack = 0;
				lr = 0;
			}
			if (f)
			{
				if (newone->root->right == newone)
				{
					if (!newone->root->left || newone->root->left->isBlack == 1)
					{
						if (newone->left && newone->left->isBlack == 0)
							rl = 1;
						else if (newone->right && newone->right->isBlack == 0)
							ll = 1;
					}
					else
					{
						newone->root->left->isBlack = 1;
						root->isBlack = 1;
						if (newone->root != root)
							newone->root->isBlack = 0;
					}
				}
				else
				{
					if (!newone->root->right || newone->root->right->isBlack == 1)
					{
						if (newone->left && newone->left->isBlack == 0)
							rr = 1;
						else if (newone->right && newone->right->isBlack == 0)
							lr = 1;
					}
					else
					{
						newone->root->right->isBlack = 1;
						newone->isBlack = 1;
						if (newone->root != root)
							newone->root->isBlack = 0;
					}
				}
				f = 0;
			}
			return (newone);
		}

	public:
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
		void	insert(ft::pair<Key,T> data)
		{
			if (!search(data))
			{
				if (!root)
				{
					root = new Node<Key,T>(data);
					root->isBlack = 1;
				}
				else
					root = insert_conditions(root, data);
			}
		}
		Node<Key, T> *search(ft::pair<Key, T> n)
		{
			Node<Key, T> *tmp = root;
			while (tmp)
			{
				if (n < tmp->content)
				{
					if (!tmp->left)
						return (NULL);
					tmp = tmp->left;
				}
				else if (n == tmp->content)
					return (tmp);
				else
				{
					if (!tmp->right)
						return (NULL);
					else
						tmp = tmp->right;
				}
			}
			return (NULL);
		}
		void delete_one(ft::pair<Key, T> n)
		{
			if (Node<Key, T> *x = search(n))
			{
				delete_node(x);
			}
		}
};

#endif
