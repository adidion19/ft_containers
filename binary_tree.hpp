/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:49:06 by adidion           #+#    #+#             */
/*   Updated: 2022/03/28 16:54:17 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_TREE_HPP
# define BINARY_TREE_HPP

# include "pair.hpp"
# include "map_iterator.hpp"

namespace ft
{
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
			Node &operator=( const Node &obj )
			{
				content = obj.content;
				isBlack = obj.isBlack;
				left = obj.left;
				right = obj.right;
				root = obj.root;
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
				if (root)
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

	template < class Key, class T, class Alloc = std::allocator<Node<Key, T > > >
	class	Binary_tree
	{
		private:
			Node< Key, T> *root;
			Alloc _alloc;
			unsigned int ft_count(Node<Key, T> *root, unsigned int *i) const
			{
				if (root->left)
					ft_count(root->left, i);
				if (root->right)
					ft_count(root->right, i);
				if (root)
					(*i)++;
				return (*i);
			}
			Node<Key, T> *ft_realloc(Node<Key, T> *tmp, Node<Key, T> *newroot)
			{
				if (tmp->left)
					newroot->left = ft_realloc(tmp->left, newroot->left);
				if (tmp->right)
					newroot->right = ft_realloc(tmp->right, tmp->right);
				_alloc.construct(*newroot, *tmp);
			}
			void ft_free(Node< Key, T> *node)
			{
				if (node)
				{
					ft_free(node->left);
					ft_free(node->right);
					_alloc.destroy(node);
					_alloc.deallocate(node, 1);
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

			void	swap_isBlack(Node<Key, T> *x1, Node<Key, T> *x2)
			{
				bool tmp;
				tmp = x1->isBlack;
				x1->isBlack = x2->isBlack;
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
					return ;
				}
				Node<Key, T> *parent = x->root, *grandparent = parent->root, *uncle = x->uncle();
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
								swap_isBlack(parent, grandparent);
							else
							{
								left_rotate(parent);
								swap_isBlack(x, grandparent);
							}
							right_rotate(grandparent);
						}
						else
						{
							if (x->is_on_left())
							{
								right_rotate(parent);
								swap_isBlack(x, grandparent);
							}
							else
								swap_isBlack(parent, grandparent);
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
						else
						{
							if (x->sibling())
								x->sibling()->isBlack = 0;
						}
						if (x->is_on_left())
						{
							parent->left = NULL;
						}
						else
						{
							parent->right = NULL;
						}
					}
					_alloc.destroy(x);
					_alloc.deallocate(x, 1);
					return ;
				}
				if (!x->left || !x->right)
				{
					if (x == root)
					{
						x->content = tmp->content;
						x->left = NULL;
						x->right = NULL;
						_alloc.destroy(tmp);
						_alloc.deallocate(tmp, 1);
					}
					else
					{
						if (x->is_on_left())
							parent->left = tmp;
						else
							parent->right = tmp;
						_alloc.destroy(x);
						_alloc.deallocate(x, 1);
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

			Node<Key, T> *ft_copy(Node<Key, T> *a, Node<Key, T> *r)
			{
				if (!a)
					return (NULL);
				Node<Key, T> *newone = _alloc.allocate(1);
				_alloc.construct(newone, a->content);
				r = newone;
				r->left = ft_copy(a->left, r->left);
				r->right = ft_copy(a->right, r->right);
				return (newone);
			}

		public:
			Node<Key, T> *getRoot() const
			{
				return (root);
			}
			Alloc	getAllocator() const
			{
				return (_alloc);
			}
			Binary_tree()
			{
				root = NULL;
			}
			Binary_tree( const Binary_tree &obj)
			{
				_alloc = obj.getAllocator();
				root = ft_copy(obj.getRoot(), root);
			}
			Binary_tree<Key, T> operator=(const Binary_tree &obj)
			{
				ft_free(root);
				_alloc = obj.getAllocator();
				root = ft_copy(obj.getRoot(), root);
				return (*this);
			}
			~Binary_tree()
			{
				ft_free(root);
			}
			void	insert(ft::pair<Key,T> data)
			{
				if (!search(data.first))
				{
					Node<Key, T> *newone= _alloc.allocate(1);
					_alloc.construct(newone, data);
					if (!root)
					{
						newone->isBlack = 1;
						root = newone;
					}
					else
					{
						Node<Key, T> *tmp = search_utils(data);
						if (tmp->content == data)
							return ;
						newone->root = tmp;
						if (data < tmp->content)
							tmp->left = newone;
						else
							tmp->right = newone;
						fix_double_red(newone);
					}
				}
			}
			Node<Key, T> *search_utils(ft::pair<Key, T> n)
			{
				Node<Key, T> *tmp = root;
				while (tmp)
				{
					if (n.first < tmp->content.first)
					{
						if (!tmp->left)
							return (tmp);
						tmp = tmp->left;
					}
					else if (n.first == tmp->content.first)
						return (tmp);
					else
					{
						if (!tmp->right)
							return (tmp);
						else
							tmp = tmp->right;
					}
				}
				return tmp;
			}
			T search(const Key &n)
			{
				Node<Key, T> *tmp = root;
				while (tmp)
				{
					if (n < tmp->content.first)
					{
						if (!tmp->left)
							return (0);
						tmp = tmp->left;
					}
					else if (n == tmp->content.first)
						return (tmp->content.second);
					else
					{
						if (!tmp->right)
							return (0);
						else
							tmp = tmp->right;
					}
				}
				return (0);
			}
			void delete_one(const Key& n)
			{
				if (T x = search(n))
				{
					Node <Key, T> *y = search_utils(ft::make_pair(n, x));
					delete_node(y);
				}
			}
			void ft_print(Node< Key, T> *node)
			{
				if (node)
				{
					ft_print(node->left);
					ft_print(node->right);
					std::cout << node->content.second << std::endl;
				}
			}
			void ft_print()
			{
				if (root)
				{
					ft_print(root->left);
					ft_print(root->right);
					std::cout << root->content.second << std::endl;
				}
			}
			unsigned int size() const
			{
				unsigned int i = 0;
				ft_count(root, &i);
				return (i);
			}
			typedef map_iterator<ft::pair<Key, T> >	iterator;
	};
};

#endif
