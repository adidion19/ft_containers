/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:49:06 by adidion           #+#    #+#             */
/*   Updated: 2022/04/11 16:15:09 by adidion          ###   ########.fr       */
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
			ft::pair<const Key,T> content;
			bool isBlack;
			Node *left;
			Node *right;
			Node *root;
			//Node <Key, T> ptr;
			Node(ft::pair< const Key,T> data): content(data)
			{
				isBlack = 0;
				left = right = root = NULL;
				return ;
			}
			Node(const Node &obj): content(obj.content), isBlack(obj.isBlack), left(obj.left), right(obj.right), root(obj.root)
			{
				return;
			}
			Node(const Node &obj, bool a): content(obj.content), isBlack(obj.isBlack), left(NULL), right(NULL), root(NULL)
			{
				(void)a;
				return ;
			}
			Node &operator=( const Node &obj )
			{
				std::allocator<Node<const Key, T> >	alloc;
				*this = alloc.allocate(1);
				if (obj)
					alloc.construct(*this, *(obj));
				else
					*this = NULL;
				return (*this);
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

	template < class Key, class T, class Alloc = std::allocator<Node<const Key, T > > >
	class	Binary_tree
	{
		private:
			Node< const Key, T> *root;
			Alloc _alloc;
			Node< const Key, T> *					_null;
			unsigned int ft_count(Node<const Key, T> *root, unsigned int *i) const
			{
				//std::cout<<"A"<<std::endl;
				if (root != _null && root->left != _null)
					ft_count(root->left, i);
				if (root != _null && root->right != _null)
					ft_count(root->right, i);
				if (root != _null)
					(*i)++;
				return (*i);
			}
			Node<const Key, T> *ft_realloc(Node<const Key, T> *tmp, Node<const Key, T> *newroot)
			{
				if (tmp->left != _null)
					newroot->left = ft_realloc(tmp->left, newroot->left);
				if (tmp->right != _null)
					newroot->right = ft_realloc(tmp->right, tmp->right);
				_alloc.construct(*newroot, *tmp);
			}
			void	left_rotate(Node<const Key, T> *x)
			{
				Node<const Key, T> *tmp = x->right;
				if (x == root)
					root = tmp;
				x->move_down(tmp);
				x->right = tmp->left;
				if (tmp->left != _null)
					tmp->left->root = x;
				tmp->left = x;
			}
			void	right_rotate(Node<const Key, T> *x)
			{
				Node<const Key, T> *tmp = x->left;
				if (x == root)
					root = tmp;
				x->move_down(tmp);
				x->left = tmp->right;
				if (tmp->right != _null)
					tmp->right->root = x;
				tmp->right = x;
			}

			void	swap_isBlack(Node<const Key, T> *x1, Node<const Key, T> *x2)
			{
				bool tmp;
				tmp = x1->isBlack;
				x1->isBlack = x2->isBlack;
				x2->isBlack = tmp;
			}
			void swap_values(Node<const Key, T> *x1, Node<const Key, T> *x2)
			{
				ft::pair<const Key, T> a;
				a = x1->content;
				x1->content = x2->content;
				x2->content = a;
			}
			void fix_double_red(Node<const Key, T> *x)
			{
				if (x == root)
				{
					x->isBlack = 1;
					return ;
				}
				Node<const Key, T> *parent = x->root, *grandparent = parent->root, *uncle = x->uncle();
				if (parent->isBlack == 0)
				{
					if (uncle != _null && uncle->isBlack == 0)
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
			void	fix_double_black(Node<const Key, T> *x)
			{
				if (x == root)
					return ;
				Node<const Key, T> *sibling = x->sibling(), *parent = x->root;
				if (!sibling || sibling == _null)
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
			Node<const Key, T> *successor(Node<const Key, T> *x)
			{
				Node<const Key, T> *tmp = x;
				while (tmp->left != _null)
					tmp = tmp->left;
				return (tmp);
			}
			Node<const Key, T> *replace(Node <const Key, T> *x)
			{
				if (x->left  != _null && x->right != _null )
					return (successor(x->right));
				if (_null == x->left && _null == x->right)
					return (_null);
				if (x->left != _null )
					return (x->left);
				return (x->right);
			}
			void	delete_node(Node <const Key, T> *x)
			{
				Node<Key, T> *tmp = replace(x);
				bool boo = ((_null == tmp || tmp->isBlack == 1) && (x->isBlack == 1));
				Node<const Key, T> *parent = x->root;
				if (_null != tmp)
				{
					if (x == root)
					{
						root = _null;
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
							parent->left = _null;
						}
						else
						{
							parent->right = _null;
						}
					}
					_alloc.destroy(x);
					_alloc.deallocate(x, 1);
					return ;
				}
				if (_null == x->left || _null == x->right)
				{
					if (x == root)
					{
						x->content = tmp->content;
						x->left = _null;
						x->right = _null;
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

			Node<const Key, T> *ft_copy(Node<const Key, T> *a, Node<const Key, T> *r)
			{
				if (!a || a == _null)
					return (_null);
				Node<const Key, T> *newone = _alloc.allocate(1);
				_alloc.construct(newone, *a);
				if (a->left != _null)
					newone->left = ft_copy(a->left, newone);
				if (a->right != _null)
					newone->right = ft_copy(a->right, newone);
				newone->root = r;
				return (newone);
			}

		public:
			void ft_free(Node< const Key, T> *node)
			{
				if (node != _null)
				{
					ft_free(node->left);
					ft_free(node->right);
					_alloc.destroy(node);
					_alloc.deallocate(node, 1);
				}
			}
			void ft_free(Node< const Key, T> node)
			{
				_alloc.destroy(node);
				_alloc.deallocate(node, 1);
			}
			Node<const Key, T> *getRoot() const
			{
				return (root);
			}
			Node<Key, T> *getRoot_2() const
			{
				return (reinterpret_cast<Node<Key, T> *>(root));
			}
			Alloc	getAllocator() const
			{
				return (_alloc);
			}
			Node<const Key, T> * new_node(ft::pair<const Key,T> i)
			{
				Node<const Key, T> *node = _alloc.allocate(1);
				_alloc.construct(node, i);
				node->left = _null;
				node->right = _null;
				node->root = NULL;
				node->isBlack = 1;
				return (node);
			}
			Binary_tree()
			{
				_null = new_node(ft::pair<const Key, T>());
				_null->left = NULL;
				_null->right = NULL;
				_null->isBlack = 1;
				_null->root = NULL;
				root = _null;
			}
			Binary_tree( const Binary_tree &obj)
			{
				_alloc = obj.getAllocator();
				root = ft_copy(obj.getRoot(), NULL);
			}
			Binary_tree<Key, T> operator=(const Binary_tree &obj)
			{
				ft_free(root);
				_alloc = obj.getAllocator();
				this->root = ft_copy(obj.getRoot(), NULL);
				return (*this);
			}
			~Binary_tree()
			{
				ft_free(root);
			}
			void	insert(ft::pair<const Key,T> data)
			{
				if (!search(data.first))
				{
					Node<const Key, T> *newone= new_node(data);
					if (!root || root == _null)
					{
						newone->isBlack = 1;
						root = newone;
					}
					else
					{
						Node<const Key, T> *tmp = search_utils(data);
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
			Node<const Key, T> *search_utils(ft::pair<const Key, T> n)
			{
				Node<const Key, T> *tmp = root;
				while (tmp != _null)
				{
					if (n.first < tmp->content.first)
					{
						if (tmp->left == _null)
							return (tmp);
						tmp = tmp->left;
					}
					else if (n.first == tmp->content.first)
						return (tmp);
					else
					{
						if (tmp->right == _null)
							return (tmp);
						else
							tmp = tmp->right;
					}
				}
				return tmp;
			}
			T search(const Key &n)
			{
				Node<const Key, T> *tmp = root;
				while (tmp != _null)
				{
					if (n < tmp->content.first)
					{
						if (tmp->left == _null)
							return (0);
						tmp = tmp->left;
					}
					else if (n == tmp->content.first)
						return (tmp->content.second);
					else
					{
						if (tmp->right == _null)
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
					Node <const Key, T> *y = search_utils(ft::make_pair(n, x));
					delete_node(y);
				}
			}
			void ft_print(Node< const Key, T> *node)
			{
				if (node != _null)
				{
					ft_print(node->left);
					ft_print(node->right);
					std::cout << node->content.second << std::endl;
				}
			}
			void ft_print()
			{
				if (root != _null)
				{
					ft_print(root->left);
					ft_print(root->right);
					std::cout << "root : " << root->content.second << std::endl;
				}
			}
			unsigned int size() const
			{
				unsigned int i = 0;
				ft_count(root, &i);
				return (i);
			}
			typedef map_iterator<pair<Key, T> >	iterator;
			typedef map_iterator< const pair<const Key, T> >	const_iterator;
			Node<Key, T> *begin()
			{
				Node<Key, T>* tmp = getRoot_2();
				while (tmp->left)
					tmp = tmp->left;
				return (tmp);
			}
			Node<Key, T> *begin() const
			{
				Node<Key, T>* tmp = getRoot_2();
				while (tmp->left)
					tmp = tmp->left;
				return (tmp);
			}
			Node<Key, T> *end()
			{
				Node<Key, T>* tmp = getRoot_2();
				while (tmp->right)
					tmp = tmp->right;
				return (tmp->right);
			}
			Node<Key, T> *end_but_less()
			{
				Node<Key, T>* tmp = getRoot_2();
				while (tmp->right)
					tmp = tmp->right;
				return (tmp);
			}
			Node<Key, T> *end() const
			{
				Node<Key, T>* tmp = getRoot_2();
				while (tmp->right)
					tmp = tmp->right;
				return (tmp->right);
			}
	};
};

#endif
